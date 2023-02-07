#include "ConverterJSON.h"
#include <nlohmann/json.hpp>
#include <fstream>

#include <iostream>
#include "VersionConfig.h"
#include <exception>

using Json = nlohmann::json;

std::vector<std::string> ConverterJSON::GetTextDocuments()
{
	std::ifstream iFile("config.json");
	if (!iFile.is_open())
		throw std::logic_error("config file is missing");
	Json json = Json::parse(iFile);
	iFile.close();
	if (!json.contains("config"))
		throw std::logic_error("config file is empty");

	if (!json["config"].contains("version"))
		throw std::logic_error("config.json has no file version");
	if (APPLICATION_VERSION != json["config"]["version"])
		throw std::logic_error("config.json has incorrect file version");

	if (json["config"].contains("name"))
		std::cout << "[MESSAGE]: Starting " << std::string(json["config"]["name"]) << "..." << std::endl;
	else
		std::cout << "[WARNING]: No \"name\" specified at config.json." << std::endl;

	if (!json.contains("files"))
	{
		std::cout << "[WARNING]: No \"files\" specified at config.json." << std::endl;
		return {};
	}
	std::vector<std::string> texts;
	std::stringstream buffer;
	for (const auto& path : json["files"])
	{
		std::ifstream document(path);
		if (document.is_open())
		{
			buffer.clear();
			buffer << document.rdbuf();
			texts.push_back(buffer.str());
			document.close();
		}
		else
		{
			std::cout << "[WARNING]: No such file as \"" << std::string(path) << "\" or no access to path." << std::endl;
		}
	}
	return texts;
}

int ConverterJSON::GetResponsesLimit()
{
	std::ifstream iFile("config.json");
	if (!iFile.is_open())
		throw std::logic_error("config file is missing");
	Json json = Json::parse(iFile);
	iFile.close();
	if (!json.contains("config"))
		throw std::logic_error("config file is empty");

	if (json["config"].contains("max_responses"))
		return json["config"]["max_responses"];
	else
		return 5;
}

std::vector<std::string> ConverterJSON::GetRequests()
{
	std::ifstream iFile("requests.json");
	if (!iFile.is_open())
		throw std::logic_error("requests file is missing");
	Json json = Json::parse(iFile);
	iFile.close();

	if (!json.contains("requests"))
		throw std::logic_error("requests file is empty");

	return json["requests"].get<std::vector<std::string>>();
}

void ConverterJSON::PutAnswers(std::vector<std::vector<std::pair<int, float>>> answers)
{
	char zfill = answers.size() / 10 + 1;
	if (zfill < 3) zfill = 3;
	Json json;

	for (auto it = answers.begin(); it < answers.end(); ++it)
	{
		std::string reqKey = std::to_string(it - answers.begin() + 1);
		reqKey.insert(reqKey.begin(), zfill - reqKey.size(), '0');
		reqKey = "request" + reqKey;
		json["answers"][reqKey]["result"] = !it->empty();
		if (it->empty()) continue;
		if (it->size() == 1)
		{
			json["answers"][reqKey]["docid"] = it->begin()->first;
			json["answers"][reqKey]["rank"] = it->begin()->second;
			continue;
		}
		Json relevance;
		for (auto &&pair : *it)
		{
			relevance["docid"] = pair.first;
			relevance["rank"] = pair.second;
			json["answers"][reqKey]["relevance"].push_back(relevance);
		}
	}
	std::ofstream oFile("answers.json");
	oFile << json;
	oFile.close();
}
