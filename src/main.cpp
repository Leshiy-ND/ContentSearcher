#include <iostream>
#include "ConverterJSON.hpp"

int main()
{
	std::cout << "Hello, World!" << std::endl;
	auto texts    = ConverterJSON::GetTextDocuments();
	auto limit    = ConverterJSON::GetResponsesLimit();
	auto requests = ConverterJSON::GetRequests();
	ConverterJSON::PutAnswers({{{0, 0.989}, {1, 0.897}, {2, 0.750}, {3, 0.670}, {4, 0.561}},
	                           {{0, 0.769}},
	                           {}});
	std::cout << "Goodbye, World!" << std::endl;
	return 0;
}
