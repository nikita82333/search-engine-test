#include <iostream>
#include <vector>
#include <map>
#include <thread>
#include <mutex>
#include "InvertedIndex.h"
//#include "ConverterJSON.h"

void InvertedIndex::UpdateDocumentBase(std::vector<std::string>& inputDocs) {
//    ConverterJSON converterJson;
//    _docs = converterJson.GetTextDocuments();
    _docs = inputDocs;
    std::mutex freqDictAccess;
    std::vector<std::thread> threads;
    size_t docId = 0;
    for (const auto& doc : _docs) {
        threads.emplace_back(std::thread([this, &doc, &freqDictAccess, docId]() {
            std::map<std::string, size_t> wordMap;
            std::string currentWord;
            for (const auto& symbol : doc) {
                if (std::isalnum(symbol)) {
                    currentWord += symbol;
                }
                else if (currentWord.length() != 0) {
                    if (wordMap.count(currentWord) == 0) { wordMap[currentWord] = 1; }
                    else { wordMap[currentWord] += 1; }
                    currentWord = "";
                }
            }

            freqDictAccess.lock();
            for (const auto& [word, count] : wordMap) {
                if (_freqDictionary.count(word) == 0) {
                    _freqDictionary.emplace(word, std::vector<Entry>{{docId, count}});
                }
                else {
                    _freqDictionary[word].push_back(Entry{docId, count});
                }
            }
            freqDictAccess.unlock();
        }));
        ++docId;
    }

    for (auto& thread : threads) {
        thread.join();
    }
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string &word) {
    auto it = _freqDictionary.find(word);
    return it->second;
}

