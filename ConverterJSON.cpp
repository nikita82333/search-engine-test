//#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>
#include <exception>
#include "nlohmann/json.hpp"
#include "ConverterJSON.h"

void ConverterJSON::NormalizeFileNames(std::vector<std::string>& fileNames) {
    for (auto& fileName : fileNames) {
        if (fileName[0] == '/') fileName.erase(0, 1);
#ifdef _WIN32
        std::string win32FileName;
        for (char symbol : fileName) {
            if (symbol == '/') {
                win32FileName += "\\";
            } else {
                win32FileName += symbol;
            }
        }
        fileName = win32FileName;
#endif
    }
}

void ConverterJSON::LoadConfig() {
    std::ifstream configFile("config.json");
    if (configFile.is_open()) {
        nlohmann::json configJson;
        configFile >> configJson;
        configFile.close();
        if (configJson.contains("config")) {
            try {
                _fileNames = configJson["files"];
                _responsesLimit = configJson["config"]["max_responses"];
                _programName = configJson["config"]["name"];
                _configFileVersion = configJson["config"]["version"];
                _configIsLoaded = true;
            } catch (...) {
                std::cerr <<"Error: Config file has incorrect format!" << std::endl;
                throw std::runtime_error("Config file has incorrect format!");
            }
            NormalizeFileNames(_fileNames);
        } else {
            std::cerr <<"Error: Config file is empty!" << std::endl;
            throw std::runtime_error("Config file is empty!");
        }
    } else {
        std::cerr <<"Error: Config file is missing!" << std::endl;
        throw std::runtime_error("Config file is missing!");
    }
}

std::string ConverterJSON::IndexToString3(size_t index) {
    std::ostringstream sStream;
    if (index < 1000) {
        sStream << std::setw(3) << std::setfill('0') << std::to_string(index);
        return sStream.str();
    } else
        return "000";
}

std::vector<std::string> ConverterJSON::GetTextDocuments() {
    if (!_configIsLoaded) LoadConfig();
    std::vector<std::string> textDocs;
    for (const auto& fileName : _fileNames) {
        std::ifstream textFile(fileName);
        if (textFile.is_open()) {
            std::string text;
            textFile >> text;
            while (!textFile.eof()) {
                std::string word;
                textFile >> word;
                text += " " + word;
            }
            textDocs.emplace_back(text);
            textFile.close();
        } else {
            std::cerr << "Warning: File \"" << fileName << "\" is not exist!" << std::endl;
        }
    }

    return textDocs;
}

int ConverterJSON::GetResponsesLimit() {
    if (!_configIsLoaded) LoadConfig();
    return _responsesLimit;
}

std::vector<std::string> ConverterJSON::GetRequests() {
    std::ifstream requestsFile("requests.json");
    std::vector<std::string> requests;
    if (requestsFile.is_open()) {
        nlohmann::json requestsJson;
        requestsFile >> requestsJson;
        requests = requestsJson["requests"];
    }
    requestsFile.close();
    return requests;
}

void ConverterJSON::PutAnswers(const std::vector<std::vector<std::pair<int, float>>>& answers) {
    std::ofstream answersFile("answers.json");
    if (answersFile.is_open()) {
        nlohmann::json answersJson;
        size_t requestNumber = 1;
        for (const auto& answer : answers) {
            std::string requestString = "request" + IndexToString3(requestNumber);
            answersJson["answers"][requestString];
            if (!answer.empty()) {
                answersJson["answers"][requestString]["result"] = "true";
                if (answer.size() == 1) {
                    answersJson["answers"][requestString]["docid"] = answer[0].first;
                    answersJson["answers"][requestString]["rank"] = answer[0].second;
                } else {
                    size_t docNumber = 0;
                    for (const auto& [docId, rank]: answer) {
                        answersJson["answers"][requestString]["relevance"][docNumber]["docid"] = docId;
                        answersJson["answers"][requestString]["relevance"][docNumber]["rank"] = rank;
                        ++docNumber;
                    }
                }
            } else {
                answersJson["answers"][requestString]["result"] = "false";
            }
            ++requestNumber;
        }
        answersFile << std::setw(2) << answersJson;
        answersFile.close();
    } else {
        std::cerr << "Warning: File \"answers.json\" is occupied by another process!" << std::endl;
    }
}

std::string ConverterJSON::GetProgramName() {
    if (!_configIsLoaded) LoadConfig();
    return _programName;
}

std::string ConverterJSON::GetConfigFileVersion() {
    if (!_configIsLoaded) LoadConfig();
    return _configFileVersion;
}
