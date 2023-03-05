/**
 * For now this file is distant for quick testing.
 */

#include <iostream>
#include "ConverterJSON.hpp"
#include "InvertedIndex.hpp"
#include "SearchServer.hpp"

int main()
{
	InvertedIndex idx;
	idx.UpdateDocumentBase(ConverterJSON::GetTextDocuments());

	SearchServer server(idx);
	auto answers = server.search(ConverterJSON::GetRequests());

	ConverterJSON::PutAnswers(answers);
	return 0;
}
