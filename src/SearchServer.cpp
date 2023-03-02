//
// Created by user-leshiy on 25.02.23.
//

#include <map>
#include <numeric>
#include <set>
#include <iostream>
#include "SearchServer.hpp"


bool RelativeIndex::operator==(const RelativeIndex& other) const
{
	return (this->doc_id == other.doc_id && this->rank == other.rank);
}

bool RelativeIndex::operator<(const RelativeIndex &other) const
{
	if (this->doc_id  < other.doc_id) return true;
	if (this->doc_id != other.doc_id) return false;
	return (this->rank < other.rank);
}


std::vector<std::vector<RelativeIndex>> SearchServer::search(
		const std::vector<std::string>& queries_input)
{
	for (auto&& query : queries_input)
	{
		std::string word;
		std::map<std::string, std::size_t> tmp_dict; // After being filled, gets translated to vec<str> unique_words
		for (auto&& symbol : query)
		{
			if      ('a' <= symbol && symbol <= 'z') word += symbol;
			else if ('A' <= symbol && symbol <= 'Z') word += char(_tolower(symbol));
			else
			{
				if (word.empty()) continue;
				if (tmp_dict.find(word) == tmp_dict.end()) // v copy_start v
				{
					std::size_t tmp_int = 0;
					auto entries = index.GetWordCount(word);
					for (auto&& entry : entries)
						tmp_int += entry.count;
					tmp_dict[word] = tmp_int;
				}
				word.clear();  //  ^  ^  ^  ^  ^  ^  ^  ^  ^  ^  copy_end  ^
			}
		}
		if (tmp_dict.find(word) == tmp_dict.end()) // v copy_start v
		{
			std::size_t tmp_int = 0;
			auto entries = index.GetWordCount(word);
			for (auto&& entry : entries)
				tmp_int += entry.count;
			tmp_dict[word] = tmp_int;
		}
		word.clear();  //  ^  ^  ^  ^  ^  ^  ^  ^  ^  ^  copy_end  ^

		std::vector<std::string> unique_words;
		unique_words.reserve(tmp_dict.size());
		for (auto&& word_n_count : tmp_dict)
			unique_words.emplace_back(word_n_count.first);
		for (std::size_t i = 0; i < unique_words.size() - 1; ++i)
		{
			for (std::size_t j = i+1; j < unique_words.size(); ++j)
			{
				if (tmp_dict[unique_words[i]] > tmp_dict[unique_words[j]])
					std::swap(unique_words[i], unique_words[j]);
			}
		}
		tmp_dict.clear();
		// Words of the query are sorted into vec<str> unique_words by rarity (steps 1-3)

		std::set<std::size_t> doc_ids;
		if (!unique_words.empty())
			for (auto&& entry : index.GetWordCount(unique_words[0]))
				doc_ids.insert(entry.doc_id);
		if (unique_words.size() > 1)
			for (auto it = unique_words.begin() + 1; it != unique_words.end(); ++it)
			{
				std::set<std::size_t> matching_docs;
				for (auto &&entry: index.GetWordCount(*it))
					if (doc_ids.find(entry.doc_id) != doc_ids.end())
						matching_docs.insert(entry.doc_id);
				doc_ids = matching_docs;
			}
		// List of docs containing all words of the query (steps 4-5)

		///...
	}
	///...
	return {};
}
