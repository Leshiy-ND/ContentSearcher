//
// Created by user-leshiy on 18.02.23.
//

#include "InvertedIndex.hpp"

//#include <iostream>
#include <thread> // CMakeLists.txt + set(CMAKE_CXX_FLAGS -pthread)

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs)
{
	docs = std::move(input_docs);
	freq_dictionary.clear();
	std::vector<std::thread> vec_of_threads;

	for (auto doc_it = docs.begin(); doc_it != docs.end(); ++doc_it) // Перевести в многопоточость!!!
	{
		if (doc_it->empty()) continue;
		std::size_t doc_id = doc_it - docs.begin();
		std::string& doc_link = *doc_it;
//		std::cout << "- THREAD OF FILE #" << doc_id << std::endl;
		std::thread th([this, &doc_link, doc_id]
		{
//			std::cout << "  Reading file #" << doc_id << std::endl;
			std::string word;
			std::map<std::string, std::size_t> doc_dictionary; // Individual Document Word Count
			for (auto& symbol : doc_link)
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

//			std::cout << "  Waiting to add file #" << doc_id << std::endl;
			m_dictionary_is_being_edited.lock();
//			std::cout << "  Adding file #" << doc_id << std::endl;
			for (auto & record : doc_dictionary)
			{
				if (freq_dictionary.find(record.first) == freq_dictionary.end())
					freq_dictionary[record.first] = { {doc_id, record.second} };
				else
					freq_dictionary[record.first].push_back({doc_id, record.second});
			}
//			std::cout << "  File #" << doc_id << " is added" << std::endl;
			m_dictionary_is_being_edited.unlock();
		});
		vec_of_threads.push_back(std::move(th));
	}
	for (auto& th : vec_of_threads)
	{
		if (th.joinable())
			th.join();
//		std::cout << "- ENDING A THREAD" << std::endl;
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
