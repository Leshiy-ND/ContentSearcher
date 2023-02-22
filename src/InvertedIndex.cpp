//
// Created by user-leshiy on 18.02.23.
//

#include "InvertedIndex.hpp"

#include <iostream>
#include <utility>

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs)
{
	docs = std::move(input_docs);
	freq_dictionary.clear();

	for (auto doc_it = docs.begin(); doc_it != docs.end(); ++doc_it) // Перевести в многопоточость!!!
	{
		if (doc_it->empty()) continue;
		/// НАЧАЛО НОВОГО ПОТОКА
		std::size_t doc_id = doc_it - docs.begin();
		std::cout << "Reading file #" << doc_id << std::endl;
		std::string word;
		std::map<std::string, std::size_t> doc_dictionary; // Individual Document Word Count
		for (auto& symbol : *doc_it)
		{
			if      ('a' <= symbol && symbol <= 'z') word += symbol;
			else if ('A' <= symbol && symbol <= 'Z') word += char(_tolower(symbol));
			else
			{
				if (word.empty()) continue;
				if (doc_dictionary.find(word) == doc_dictionary.end())
					 doc_dictionary[word]  = 1;
				else doc_dictionary[word] += 1;
				word.clear();
			}
		}
		// while (!freq_dictionary.isAvailable());
		// freq_dictionary.setAvailable(false);
		// freq_dictionary += doc_dictionary;
		// freq_dictionary.setAvailable(true);

		std::cout << "Waiting to add file #" << doc_id << std::endl;
		while(dictionary_is_being_edited);
		dictionary_is_being_edited = true;
		std::cout << "Adding file #" << doc_id << std::endl;
		for (auto & record : doc_dictionary)
		{
			if (freq_dictionary.find(record.first) == freq_dictionary.end())
				freq_dictionary[record.first] = { {doc_id, record.second} };
			else
				freq_dictionary[record.first].push_back({doc_id, record.second});
		}
		std::cout << "File #" << doc_id << " is added" << std::endl;
		dictionary_is_being_edited = false;
		/// КОНЕЦ ПОТОКА
	}
	for (auto & record : freq_dictionary)
		record.second.resize(record.second.size());
//	freq_dictionary[word] = { {docID_0, times_3}, {docID_2, times_1} };
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word)
{
	///
	return {};
}
