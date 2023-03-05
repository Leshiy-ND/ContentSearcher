#include "SearchServer.hpp"
#include <gtest/gtest.h>



void TestSearchServerFunctionality(
		const std::vector<std::string>&                docs,
		const std::vector<std::string>&                requests,
		const std::vector<std::vector<RelativeIndex>>& expected)
{
	InvertedIndex idx;
	idx.UpdateDocumentBase(docs);
	SearchServer srv(idx);

	std::vector<std::vector<RelativeIndex>> result = srv.search(requests);
	ASSERT_EQ(result, expected);
}

TEST(TestCaseSearchServer, TestSimple)
{
	const std::vector<std::string> docs = {
			"milk milk milk milk water water water",
			"milk water water",
			"milk milk milk milk milk water water water water water",
			"americano cappuccino"
	};
	const std::vector<std::string> requests = {
			"milk water",
			"sugar"
	};
	const std::vector<std::vector<RelativeIndex>> expected = {
			{ {2, 1.00}, {0, 0.70}, {1, 0.30},           },
			{                                            }
	};
	TestSearchServerFunctionality(docs, requests, expected);
}

TEST(TestCaseSearchServer, TestTop5)
{
	const std::vector<std::string> docs = {
			"london is the capital of great britain",
			"paris is the capital of france",
			"berlin is the capital of germany",
			"rome is the capital of italy",
			"madrid is the capital of spain",
			"lisbon is the capital of portugal",
			"bern is the capital of switzerland",
			"moscow is the capital of russia",
			"kiev is the capital of ukraine",
			"minsk is the capital of belarus",
			"astana is the capital of kazakhstan",
			"beijing is the capital of china",
			"tokyo is the capital of japan",
			"bangkok is the capital of thailand",
			"welcome to moscow the capital of russia the third rome",
			"amsterdam is the capital of netherlands",
			"helsinki is the capital of finland",
			"oslo is the capital of norway",
			"stockholm is the capital of sweden",
			"riga is the capital of latvia",
			"tallinn is the capital of estonia",
			"warsaw is the capital of poland"
	};
	const std::vector<std::string> requests = {
			"moscow is the capital of russia"
	};
	const std::vector<std::vector<RelativeIndex>> expected = {
			{
				{7,  1.0        },
				{14, 1.0        },
				{0,  0.666666687},
				{1,  0.666666687},
				{2,  0.666666687}
			}
	};
	TestSearchServerFunctionality(docs, requests, expected);
}
