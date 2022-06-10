#ifndef SEARCH_ENGINE_CONVERTERJSON_H
#define SEARCH_ENGINE_CONVERTERJSON_H



/**
* Класс для работы с JSON-файлами
*/
class ConverterJSON {
private:
    nlohmann::json configJson;
    std::vector<std::string> fileNames;
    int responsesLimit = 0;
    bool configIsLoaded = false;

    void LoadConfig();

public:
    ConverterJSON() = default;

/**
* Метод получения содержимого файлов
* @return Возвращает список с содержимым файлов перечисленных
* в config.json
*/
    std::vector<std::string> GetTextDocuments();

/**
* Метод считывает поле max_responses для определения предельного
* количества ответов на один запрос
* @return
*/
    int GetResponsesLimit();

/**
* Метод получения запросов из файла requests.json
* @return возвращает список запросов из файла requests.json
*/
    std::vector<std::string> GetRequests();

/**
* Положить в файл answers.json результаты поисковых запросов
*/
    void PutAnswers(std::vector<std::vector<std::pair<int, float>>> answers);
};

#endif //SEARCH_ENGINE_CONVERTERJSON_H
