#include <iostream>
#include "ConverterJSON.hpp"
#include "InvertedIndex.hpp"
#include "SearchServer.hpp"

int main()
{
	try
	{
		InvertedIndex idx;
		idx.UpdateDocumentBase(ConverterJSON::GetTextDocuments());

		SearchServer server(idx);
		auto answers = server.search(ConverterJSON::GetRequests());

		ConverterJSON::PutAnswers(answers);
	}
	catch (const std::exception &x)
	{
		std::cerr << "[ERROR]: " << x.what() << std::endl;
		return 64;
	}
	return 0;
}
