/**
 * For now this file is distant for quick testing.
 */

#include <iostream>
#include "ConverterJSON.hpp"
#include "InvertedIndex.hpp"

int main()
{
	std::cout << "Hello, World!" << std::endl;
	auto texts    = ConverterJSON::GetTextDocuments();
	auto limit    = ConverterJSON::GetResponsesLimit();
	auto requests = ConverterJSON::GetRequests();
	ConverterJSON::PutAnswers({{{0, 0.989}, {1, 0.897}, {2, 0.750}, {3, 0.670}, {4, 0.561}},
	                           {{0, 0.769}},
	                           {}});
	InvertedIndex idx;
	idx.UpdateDocumentBase({
		"london is the capital of great britain",
		"big ben is the nickname for the Great bell of the striking clock"
	});
	std::cout << "Goodbye, World!" << std::endl;
	return 0;
}
