#include "game.hpp"

int main(int argc, char *args[])
{
	//game instance_of_game;

	/*
	std::ifstream ifs("alice.json");
	Json::Reader reader;
	Json::Value obj;
	reader.parse(ifs, obj); // reader can also read strings
	std::cout << "Book: " << obj["book"].asString() << std::endl;
	std::cout << "Year: " << obj["year"].asUInt() << std::endl;
	const Json::Value &characters = obj["characters"]; // array of characters
	for (int i = 0; i < characters.size(); i++)
	{
		std::cout << "    name: " << characters[i]["name"].asString();
		std::cout << " chapter: " << characters[i]["chapter"].asUInt();
		std::cout << std::endl;
	}
	*/

	
	std::ofstream file_id;
	file_id.open("data/scores.json");

	Json::Value value_obj;
	std::string user_id = "1";
	/*
	value_obj[user_id]["name"] = "kilian";
	value_obj[user_id]["score"] = 12;

	user_id = "2";
	value_obj[user_id]["name"] = "didier";
	value_obj[user_id]["score"] = 3;*/

	user_id = "3";
	value_obj[user_id]["name"] = "dinde";
	value_obj[user_id]["score"] = 4;

	Json::StyledWriter styledWriter;
	file_id << styledWriter.write(value_obj);

	file_id.close();
	

	return 0;
}