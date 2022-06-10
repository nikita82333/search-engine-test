//#include <string>
#include <vector>
#include <fstream>
#include "nlohmann/json.hpp"
#include "ConverterJSON.h"


void ConverterJSON::LoadConfig() {
    std::ifstream configFile("config.json");
    if (configFile.is_open()) {
        configFile >> configJson;
        fileNames = configJson["files"];
        responsesLimit = configJson["config"]["max_responses"];
        configIsLoaded = true;
    }
    else {
        throw "Config file not found!";
    }
}

std::vector<std::string> ConverterJSON::GetTextDocuments() {
    if (!configIsLoaded) LoadConfig();
    return fileNames;
}

int ConverterJSON::GetResponsesLimit() {
    if (!configIsLoaded) LoadConfig();
    return responsesLimit;
}

std::vector<std::string> ConverterJSON::GetRequests() {
    std::ifstream requestsFile("requests.json");
    std::vector<std::string> requests;
    if (requestsFile.is_open()) {
        nlohmann::json requestsJson;
        requestsFile >> requestsJson;
        requests = requestsJson["requests"];
    }
    return requests;
}

void ConverterJSON::PutAnswers(std::vector<std::vector<std::pair<int, float>>> answers) {

}
