#include "ConverterJSON.h"
#include <nlohmann/json.hpp>
#include <fstream>

#include <iostream>
#include "VersionConfig.h"
#include <exception>

using Json = nlohmann::json;

std::vector<std::string> ConverterJSON::GetTextDocuments()
{
	std::ifstream configFile("config.json");
	if (!configFile.is_open())
		throw std::logic_error("config file is missing");
	Json configJson = Json::parse(configFile);
	configFile.close();
	if (!configJson.contains("config"))
		throw std::logic_error("config file is empty");

	if (!configJson["config"].contains("version"))
		throw std::logic_error("config.configJson has no file version");
	if (APPLICATION_VERSION != configJson["config"]["version"])
		throw std::logic_error("config.configJson has incorrect file version");

	if (configJson["config"].contains("name"))
		std::cout << "[MESSAGE]: Starting " << std::string(configJson["config"]["name"]) << "..." << std::endl;
	else
		std::cout << "[WARNING]: No \"name\" specified at config.configJson." << std::endl;

	if (!configJson.contains("files"))
	{
		std::cout << "[WARNING]: No \"files\" specified at config.configJson." << std::endl;
		return {};
	}
	std::vector<std::string> texts;
	std::stringstream buffer;
	for (const auto& it : configJson["files"])
	{
		std::ifstream document(it);
		if (document.is_open())
		{
			buffer.clear();
			buffer << document.rdbuf();
			texts.push_back(buffer.str());
			document.close();
		}
		else
		{
			std::cout << "[WARNING]: No such file as \"" << std::string(it) << "\" or no access to it." << std::endl;
		}
	}
	return texts;
}

int ConverterJSON::GetResponsesLimit()
{
	std::ifstream configFile("config.json");
	if (!configFile.is_open())
		throw std::logic_error("config file is missing");
	Json configJson = Json::parse(configFile);
	configFile.close();
	if (!configJson.contains("config"))
		throw std::logic_error("config file is empty");

	if (configJson["config"].contains("max_responses"))
		return configJson["config"]["max_responses"];
	else
		return 5;
}

std::vector<std::string> ConverterJSON::GetRequests()
{
	std::ifstream requestsFile("requests.json");
	if (!requestsFile.is_open())
		throw std::logic_error("requests file is missing");
	Json requestsJson = Json::parse(requestsFile);
	requestsFile.close();

	if (!requestsJson.contains("requests"))
		throw std::logic_error("requests file is empty");

	return requestsJson["requests"].get<std::vector<std::string>>();
}

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>> answers)
{
	///
}
