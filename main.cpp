#include <iostream>
#include <vector>
#include <map>
#include "ConverterJSON.h"
#include "InvertedIndex.h"

//http://ci-plus-plus-snachala.ru/?p=11

int main() {
    ConverterJSON converterJson;

    std::vector<std::string> textDocs;
    textDocs = converterJson.GetTextDocuments();
    for (const auto& textDoc : textDocs) {
        std::cout << textDoc << std::endl;
    }
/*
    std::cout << converterJson.GetResponsesLimit() << std::endl;

    std::vector<std::string> requests;
    requests = converterJson.GetRequests();
    for (const auto& request : requests) {
        std::cout << request << std::endl;
    }


    std::vector<std::vector<std::pair<int, float>>> answers;
    std::vector<std::pair<int, float>> answer1 {{0, 0.989},{1, 0.897},{2, 0.75},{3, 0.67}};
    std::vector<std::pair<int, float>> answer2 {{0, 0.578} };
    std::vector<std::pair<int, float>> answer3 {};
    answers.push_back(answer1);
    answers.push_back(answer2);
    answers.push_back(answer3);

    converterJson.PutAnswers(answers);
*/

    InvertedIndex invertedIndex;
    //std::vector<std::string> inputDocs;

    invertedIndex.UpdateDocumentBase(textDocs);
    std::vector<Entry> entry;
    entry = invertedIndex.GetWordCount("capital");

    for (auto [docId, count] : entry) {
        std::cout << docId << ", " << count << std::endl;
    }

    return 0;
}
