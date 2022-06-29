#include <iostream>
#include <vector>
#include <map>
#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "SearchServer.h"

int main() {
    ConverterJSON converterJson;

    std::vector<std::string> textDocs;
    textDocs = converterJson.GetTextDocuments();
    for (const auto& textDoc : textDocs) {
        std::cout << textDoc << std::endl;
    }

    InvertedIndex invertedIndex;
    invertedIndex.UpdateDocumentBase(textDocs);

    SearchServer searchServer(invertedIndex);

    std::vector<std::vector<RelativeIndex>> relativeIndex;
    relativeIndex = searchServer.Search(converterJson.GetRequests());

    std::vector<std::vector<std::pair<int, float>>> answers;

    size_t answersCount = 0;
    for (const auto& answer : relativeIndex) {
        std::vector<std::pair<int, float>> docs;
        std::cout << "Request: " << answersCount << std::endl;
        for (const auto& [docId, rank]: answer) {
            docs.emplace_back(std::make_pair(docId, rank));
            std::cout << "(" << docId << ", " << rank << ")" << std::endl;
        }
        ++answersCount;
        answers.emplace_back(docs);
    }

    converterJson.PutAnswers(answers);

    return 0;
}
