#ifndef CONTENTSEARCHER_INVERTEDINDEX_HPP
#define CONTENTSEARCHER_INVERTEDINDEX_HPP

#include <vector>
#include <string>
#include <map>

struct Entry
{
	std::size_t doc_id, count;

	bool operator == (const Entry& _other) const
	{
		return (doc_id == _other.doc_id && count == _other.count);
	}
};

class InvertedIndex
{
private:
	std::vector<std::string> docs; // список содержимого документов
	std::map<std::string, std::vector<Entry>> freq_dictionary; // частотный словарь
	bool dictionary_is_being_edited = false;

public:
	InvertedIndex() = default;

	/**
	 * Обновить или заполнить базу документов, по которой будем совершать поиск
	 * @param texts_input - содержимое документов
	 * */
	void UpdateDocumentBase(std::vector<std::string> input_docs);

	/**
	 * Метод определяет количество вхождений слова word в загруженной базе документов
	 * @param word - слово, частоту вхождений которого необходимо определить
	 * @return Возвращает подготовленный список с частотой слов
	 */
	std::vector<Entry> GetWordCount(const std::string& word);
};


#endif //CONTENTSEARCHER_INVERTEDINDEX_HPP
