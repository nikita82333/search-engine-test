#include <iostream>
#include <vector>
#include "ConverterJSON.h"

int main() {
    ConverterJSON converterJson;

    std::vector<std::string> fileNames;
    fileNames = converterJson.GetTextDocuments();
    for (const auto& fileName : fileNames) {
        std::cout << fileName << std::endl;
    }

    std::cout << converterJson.GetResponsesLimit() << std::endl;

    std::vector<std::string> requests;
    requests = converterJson.GetRequests();
    for (const auto& request : requests) {
        std::cout << request << std::endl;
    }

    return 0;
}
