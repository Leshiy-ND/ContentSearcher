//
// Created by user-leshiy on 25.02.23.
//

#include <map>
#include <set>
#include <cmath>
#include "SearchServer.hpp"


bool RelativeIndex::operator==(const RelativeIndex& other) const
{
	return (this->doc_id == other.doc_id && fabsf(this->rank - other.rank) < .01f);
}


std::vector<std::vector<RelativeIndex>> SearchServer::search(
		const std::vector<std::string>& queries_input)
{
	std::vector<std::vector<RelativeIndex>> resultTotal;
	resultTotal.reserve(queries_input.size());

	for (auto&& query : queries_input)
	{
		if (query.empty())
		{
			resultTotal.emplace_back();
			continue;
		}
		// If there is no query, then resultTotal of the query is false (pre-step 6)

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
		// The query is separated into not unique words (steps 0.0-0.5)

		std::vector<std::string> unique_words; // It's a vector (not a set) as we care about order
		unique_words.reserve(tmp_dict.size());
		for (auto&& word_n_count : tmp_dict)
			unique_words.emplace_back(word_n_count.first);
		for (auto itI = unique_words.begin(); itI < unique_words.end() - 1; ++itI)
			for (auto itJ = itI + 1; itJ < unique_words.end(); ++itJ)
				if (tmp_dict[*itI] > tmp_dict[*itJ])
					std::iter_swap(itI, itJ);
		tmp_dict.clear();
		// Words of the query are sorted into vec<str> unique_words by rarity (steps 1-3)

		std::set<std::size_t> doc_ids; // It's a set (not a vector) as it easier for managing unique stuff
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

		if (doc_ids.empty())
		{
			resultTotal.emplace_back();
			continue;
		}
		// If there is no matching docs, then resultTotal of the query is false (step 6)

		std::map<std::size_t, std::size_t> absRelevances; // {doc_id, absRelevance}
		for (auto&& unique_word : unique_words)
		{
			auto entries = index.GetWordCount(unique_word);
			for (auto&& entry : entries)
			{
				if (doc_ids.find(entry.doc_id) == doc_ids.end()) // If it's entry of non valuable document
					continue;
				if (absRelevances.find(entry.doc_id) == absRelevances.end())
					absRelevances[entry.doc_id] = 0;
				absRelevances[entry.doc_id] += entry.count;
			}
		}
		unique_words.clear();
		doc_ids.clear(); // From now on all valuable documents are mentioned in map absRelevances

		std::size_t highestRelevance = 1;
		for (auto&& absRelevance : absRelevances)
			if (highestRelevance < absRelevance.second)
				highestRelevance = absRelevance.second;

		std::vector<RelativeIndex> resultOfQuery; // Part of resultTotal (vector (of i) for vector of vectors (of i))
		resultOfQuery.reserve(doc_ids.size());
		for (auto&& absRelevance : absRelevances)
		{
			auto& doc_id = absRelevance.first;
			float rank = (float)absRelevance.second / (float)highestRelevance;
			resultOfQuery.push_back({doc_id, rank});
		}
		absRelevances.clear();
		// Relative relevances are calculated (step 7)

		for (auto itI = resultOfQuery.begin(); itI < resultOfQuery.end() - 1; ++itI)
			for (auto itJ = itI + 1; itJ < resultOfQuery.end(); ++itJ)
				if (itI->rank < itJ->rank)
					std::iter_swap(itI, itJ);
		// Results are sorted by relative relevances (step 8)

		resultTotal.emplace_back(std::move(resultOfQuery));
	}
	return resultTotal;
}
