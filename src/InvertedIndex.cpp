//
// Created by user-leshiy on 18.02.23.
//

#include "InvertedIndex.hpp"

#include <algorithm>
#include <thread> // CMakeLists.txt + set(CMAKE_CXX_FLAGS -pthread)


bool Entry::operator == (const Entry &other) const
{
	return (this->doc_id == other.doc_id && this->count == other.count);
}

bool Entry::operator < (const Entry &other) const
{
	if (this->doc_id  < other.doc_id) return true;
	if (this->doc_id != other.doc_id) return false;
	return (this->count < other.count);
}


void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs)
{
	docs = std::move(input_docs);
	freq_dictionary.clear();
	std::vector<std::thread> vec_of_threads;

	for (auto doc_it = docs.begin(); doc_it != docs.end(); ++doc_it)
	{
		if (doc_it->empty()) continue;
		std::size_t doc_id = doc_it - docs.begin();
		std::string& doc_link = *doc_it;
		std::thread th([this, &doc_link, doc_id]
		{
			std::string word;
			std::map<std::string, std::size_t> doc_dictionary; // Индивидуальный для документа словарь ради минимизации конфликта записи
			for (auto& symbol : doc_link)
			{
				if      ('a' <= symbol && symbol <= 'z') word += symbol;
				else if ('A' <= symbol && symbol <= 'Z') word += char(_tolower(symbol));
				else
				{
					if (word.empty()) continue;
					if (doc_dictionary.find(word) == doc_dictionary.end()) // v copy_start v
						 doc_dictionary[word]  = 1;
					else doc_dictionary[word] += 1;
					word.clear();  //  ^  ^  ^  ^  ^  ^  ^  ^  ^  ^  ^  ^  ^  ^  copy_end  ^
				}
			}
			if (doc_dictionary.find(word) == doc_dictionary.end()) // v copy_start v
				 doc_dictionary[word]  = 1;
			else doc_dictionary[word] += 1;
			word.clear();  //  ^  ^  ^  ^  ^  ^  ^  ^  ^  ^  ^  ^  ^  ^  copy_end  ^

			m_dictionary_is_being_edited.lock();
			for (auto & record : doc_dictionary)
			{
				if (freq_dictionary.find(record.first) == freq_dictionary.end())
					freq_dictionary[record.first] = { {doc_id, record.second} };
				else
					freq_dictionary[record.first].push_back({doc_id, record.second});
			}
			m_dictionary_is_being_edited.unlock();
		});
		vec_of_threads.push_back(std::move(th));
	}
	for (auto& th : vec_of_threads)
	{
		if (th.joinable())
			th.join();
	}
	for (auto&& record : freq_dictionary)
	{
		record.second.resize(record.second.size());
		std::sort(record.second.begin(), record.second.end());
	}
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word)
{
	return freq_dictionary[word];
}