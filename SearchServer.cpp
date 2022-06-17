#include <iostream>
#include <vector>
#include <map>
#include <set>
#include "InvertedIndex.h"
//#include "ConverterJSON.h"
#include "SearchServer.h"

std::vector<std::vector<RelativeIndex>> SearchServer::Search(const std::vector<std::string> &queriesInput) {
//    ConverterJSON converterJson;
//    InvertedIndex invertedIndex;
    std::vector<std::string> inputDocs;
    _index.UpdateDocumentBase(inputDocs);
//    std::vector<std::string> requests = converterJson.GetRequests();

    for (const auto& request : queriesInput) {
        std::string currentWord;
        std::set<std::string> wordSet;
        for (const auto& symbol : request) {
            if (std::isalnum(symbol)) {
                currentWord += symbol;
            }
            else if (currentWord.length() != 0) {
                wordSet.insert(currentWord);
                currentWord = "";
            }
        }
        std::vector<std::pair<std::string, size_t>> wordsCount;
        for (auto& word : wordSet) {
            wordsCount.emplace_back(std::make_pair(word, _index.GetWordCount(word)[0].count));
        }
    }


    return std::vector<std::vector<RelativeIndex>>();
}
