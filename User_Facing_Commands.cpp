#include "User_Facing_Commands.hpp"
#include "HashMap.hpp"
#include <iostream>

void create(const std::string& username, const std::string& password, HashMap& map)
{
	if (map.contains(username))
	{
		std::cout << "EXISTS" << std::endl;
	}
	else
	{
		std::cout << "CREATED" << std::endl;
		map.add(username,password);
	}
}

void login(const std::string& username, const std::string& password, HashMap& map)
{
	if (map.contains(username) && password == map.value(username))
	{
		std::cout << "SUCCEEDED" << std::endl;
	}
	else
	{
		std::cout<< "FAILED" << std::endl;
	}
}

void removeCommand(const std::string& username, HashMap& map)
{
	if (map.contains(username)!= true)
	{
		std::cout << "NONEXISTENT" << std::endl;
	}
	else
	{
		map.remove(username);
		std::cout << "REMOVED" << std::endl;
	}
}

void quit()
{
	std::cout << "GOODBYE" << std::endl;
}
