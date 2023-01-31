#ifndef CONTENTSEARCHER_CONVERTERJSON_H
#define CONTENTSEARCHER_CONVERTERJSON_H

#include <vector>
#include <string>
#include <exception>

/**
* Класс для работы с JSON-файлами
*/
class ConverterJSON {
private:
	class ConfigFileIsEmpty : public std::exception
	{
	public: const char* what() const noexcept override;
	};

public:
	ConverterJSON() = default;
	/**
	* Метод получения содержимого файлов
	* @return Возвращает список с содержимым файлов перечисленных
	*
	 в config.json
	*/
	static std::vector<std::string> GetTextDocuments();
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
	void putAnswers(std::vector<std::vector<std::pair<int, float>>>
	answers);
};

#endif //CONTENTSEARCHER_CONVERTERJSON_H
