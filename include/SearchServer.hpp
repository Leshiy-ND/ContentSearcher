#ifndef CONTENTSEARCHER_SEARCHSERVER_HPP
#define CONTENTSEARCHER_SEARCHSERVER_HPP

#include <vector>
#include <string>
#include "InvertedIndex.hpp"


struct RelativeIndex
{
	std::size_t doc_id;
	float       rank;

	bool operator == (const RelativeIndex& other) const; // Необходимо для проведения тестов
	bool operator  < (const RelativeIndex& other) const; // Необходимо для сортировки по возростанию
};


class SearchServer
{
private:
	InvertedIndex& index;

public:
	/**
	 * @param idx - в конструктор класса передаётся ссылка
	 * на класс InvertedIndex, чтобы SearchServer мог узнать
	 * частоту слов встречаемых в запросе
	 */
	explicit SearchServer(InvertedIndex& idx) : index(idx) {};

	/**
	 * Метод обработки поисковых запросов
	 * @param queries_input - поисковые запросы взятые из файла requests.json
	 * @return Возвращает отсортированный список релевантных ответов
	 * для заданных запросов
	 */
	std::vector<std::vector<RelativeIndex>> search(
			const std::vector<std::string>& queries_input);
};


#endif //CONTENTSEARCHER_SEARCHSERVER_HPP
