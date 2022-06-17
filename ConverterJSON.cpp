//#include <string>
//#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>
#include "nlohmann/json.hpp"
#include "ConverterJSON.h"

std::string ConverterJSON::FileNameNormalize(std::string_view fileName) {
    std::string normalFileName;
    size_t startIndex = 0;
    if (fileName[0] == '/') startIndex = 1;
    for (size_t i = startIndex; i < fileName.length(); ++i) {
        if (fileName[i] == '/') {
            normalFileName += "\\";
        }
        else {
            normalFileName += fileName[i];
        }
    }
    return normalFileName;
}

void ConverterJSON::LoadConfig() {
    std::ifstream configFile("config.json");
    if (configFile.is_open()) {
        nlohmann::json configJson;
        configFile >> configJson;
        _fileNames = configJson["files"];
        _responsesLimit = configJson["config"]["max_responses"];
        _configIsLoaded = true;
        configFile.close();
    }
    else {
        throw "Config file not found!";
    }
}

void ConverterJSON::LoadTextDocs() {
    for (const auto& fileName : _fileNames) {
        std::ifstream textFile(FileNameNormalize(fileName));
        if (textFile.is_open()) {
            std::string text;
            textFile >> text;
            while (!textFile.eof()) {
                std::string word;
                textFile >> word;
                text += " " + word;
            }
            _textDocs.push_back(text);
            textFile.close();
        }
        else {
            std::cerr << "File \"" << fileName << "\" is not exist!" << std::endl;
        }
    }
    _textIsLoaded = true;
}

std::string ConverterJSON::IndexToString3(size_t index) {
    std::ostringstream sStream;
    if (index < 1000) {
        sStream << std::setw(3) << std::setfill('0') << std::to_string(index);
        return sStream.str();
    }
    else
        return "000";
}

std::vector<std::string> ConverterJSON::GetTextDocuments() {
    if (!_configIsLoaded) LoadConfig();
    if (!_textIsLoaded) LoadTextDocs();

    return _textDocs;
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
                }
                else {
                    size_t docNumber = 0;
                    for (const auto& [docId, rank]: answer) {
                        answersJson["answers"][requestString]["relevance"][docNumber]["docid"] = docId;
                        answersJson["answers"][requestString]["relevance"][docNumber]["rank"] = rank;
                        ++docNumber;
                    }
                }
            }
            else {
                answersJson["answers"][requestString]["result"] = "false";
            }
            ++requestNumber;
        }
        answersFile << answersJson;
        answersFile.close();
    }
    else {
        std::cerr << "File \"answers.json\" is occupied by another process!" << std::endl;
    }
}



