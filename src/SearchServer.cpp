//
// Created by user-leshiy on 25.02.23.
//

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
		///
	}
	return {};
}
