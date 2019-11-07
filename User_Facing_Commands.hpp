#ifndef USER_FACING_COMMANDS_HPP
#define USER_FACING_COMMANDS_HPP
#include "HashMap.hpp"
#include <iostream>

void create(const std::string& username, const std::string& password, HashMap& map);

void login(const std::string& username, const std::string& password, HashMap& map);

void removeCommand(const std::string& username, HashMap& map);

void quit();

#endif
