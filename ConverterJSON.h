#ifndef SEARCH_ENGINE_CONVERTERJSON_H
#define SEARCH_ENGINE_CONVERTERJSON_H

/**
* Класс для работы с JSON-файлами
*/
class ConverterJSON {
private:
    std::vector<std::string> _fileNames;
    int _responsesLimit = 0;
    std::string _programName;
    std::string _configFileVersion;
    bool _configIsLoaded = false;

    void LoadConfig();
    static void NormalizeFileNames(std::vector<std::string>& fileNames);
    static std::string IndexToString3(size_t index);

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
    void PutAnswers(const std::vector<std::vector<std::pair<int, float>>>& answers);

    std::string GetProgramName();
    std::string GetConfigFileVersion();
};


#endif //SEARCH_ENGINE_CONVERTERJSON_H
