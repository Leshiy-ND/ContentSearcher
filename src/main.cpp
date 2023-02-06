#include <iostream>
#include "ConverterJSON.h"

int main()
{
	std::cout << "Hello, World!" << std::endl;
	auto texts    = ConverterJSON::GetTextDocuments();
	auto limit    = ConverterJSON::GetResponsesLimit();
	auto requests = ConverterJSON::GetRequests();
	std::cout << "Goodbye, World!" << std::endl;
	return 0;
}
