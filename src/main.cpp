#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

using Json = nlohmann::json;

int main() {
	std::cout << "Hello, World!" << std::endl;
	std::cout << "General Newbie!" << std::endl;
	Json json;
	json["testing, huh"] = "yes, testing";
	std::cout << json;
	std::ifstream ifs("answers.json");
	Json jf = Json::parse(ifs);
	std::cout << jf;
	return 0;
}
