//
// Created by user-leshiy on 25.02.23.
//

#include <map>
#include <numeric>
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
		const std::vector<std::string> &queries_input)
{
	for (auto&& query : queries_input)
	{
		std::string word;
		std::map<std::string, std::size_t> tmp_dict; // After being filled, gets translated to vec<str> unique_words
		for (auto& symbol : query)
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
				word.clear(); // ^  ^  ^  ^  ^  ^  ^  ^  ^  ^  ^  ^  ^  ^  copy_end  ^
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
		word.clear(); // ^  ^  ^  ^  ^  ^  ^  ^  ^  ^  ^  ^  ^  ^  copy_end  ^

		std::vector<std::string> unique_words;
		unique_words.reserve(tmp_dict.size());
		for (auto&& word_n_count : tmp_dict)
			unique_words.emplace_back(word_n_count.first);
		for (std::size_t i = 0; i < unique_words.size() - 1; ++i)
		{
			for (std::size_t j = i+1; j < unique_words.size(); ++j)
			{
				if (tmp_dict[unique_words[i]] < tmp_dict[unique_words[j]])
					std::swap(unique_words[i], unique_words[j]);
			}
		}
		tmp_dict.clear();

		///...
	}
	return {};
}
