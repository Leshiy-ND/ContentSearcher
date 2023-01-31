#include "ConverterJSON.h"
#include <nlohmann/json.hpp>
#include <fstream>

#include <iostream>

using Json = nlohmann::json;

std::vector<std::string> ConverterJSON::GetTextDocuments()
{
	std::ifstream configFile("config.json");
	if (!configFile.is_open())
		throw std::logic_error("config file is missing");
	Json json = Json::parse(configFile);
	configFile.close();
	if (!json.contains("config"))
		throw std::logic_error("config file is empty");

	std::vector<std::string> texts;
	if (!json.contains("files"))
		return texts;
	for (const auto& it : json["files"])
	{
		std::cout << std::string(it) << std::endl;
//		std::ifstream document(it);
//		if (document.is_open())
//		{
//			std::string text;
//			text << document;
//			texts.push_back(text);
//			document.close();
//		}
	}
	///
	return texts;
}

int ConverterJSON::GetResponsesLimit()
{
	///
	return 0;
}

std::vector<std::string> ConverterJSON::GetRequests()
{
	///
	return std::vector<std::string>();
}

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>> answers)
{
	///
}

const char *ConverterJSON::ConfigFileIsEmpty::what() const noexcept
{
	return "config file is empty";
}
