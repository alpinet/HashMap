#include <iostream>
#include <sstream>
#include "HashMap.hpp"
#include "User_Facing_Commands.hpp"

int main()
{
	HashMap hash;
	std::string total_input;
	std::string input1;
	std::string input2;
	std::string input3;
	bool run = true;
	bool debug = false;
	while(run)
	{
		input2 = "";
		input3 = "";
		getline(std::cin, total_input);
		std::istringstream in(total_input);
		in >> input1;
		in >> input2;
		in >> input3;
		//CREATE Command
		if (input1 == "CREATE" && input2 != "" && input3 != "")
		{
			create(input2,input3,hash);
		}
		//LOGIN Command
		else if (input1 == "LOGIN" && input2 != "" && input3 != "")
		{
			login(input2,input3,hash);
		}
		//REMOVE Command
		else if (input1 == "REMOVE" && input2 != "" && input3 == "")
		{
			removeCommand(input2,hash);
		}
		//CLEAR Command
		else if (input1 == "CLEAR" && input2 == "" && input3 == "")
		{
			hash.clear();
		}
		//QUIT Command
		else if (input1 == "QUIT" && input2 == "" && input3 == "")
		{
			quit();
			run = false;
		}
		//DEBUG ON Command
		else if (input1 == "DEBUG" && input2 == "ON" && input3 == "")
		{
			if (debug == false)
			{
				debug = true;
				std::cout << "ON NOW" << std::endl;
			}
			else if (debug == true)
			{
				std::cout << "ON ALREADY" << std::endl;
			}
		}
		//DEBUG OFF
		else if (input1 == "DEBUG" && input2 == "OFF" && input3 == "")
		{
			if (debug == true)
			{
				debug = false;
				std::cout<<"OFF NOW" << std::endl;
			}
			else if (debug == false)
			{
				std::cout << "OFF ALREADY" << std::endl;
			}
		}
		//LOGIN COUNT
		else if (input1 == "LOGIN" && input2 == "COUNT" && input3 == "")
		{
			if (debug == true)
			{
				std::cout << hash.size() << std::endl;
			}
			else if (debug == false)
			{
				std::cout << "INVALID" << std::endl;
			}
		}
		//BUCKET COUNT
		else if (input1 == "BUCKET" && input2 == "COUNT" && input3 == "")
		{
			if (debug == true)
			{
				std::cout << hash.bucketCount() << std::endl;
			}
			else if (debug == false)
			{
				std::cout << "INVALID" << std::endl;
			}
		}
		//LOAD FACTOR
		else if (input1 == "LOAD" && input2 == "FACTOR" && input3 == "")
		{
			if (debug == true)
			{
				std::cout << hash.loadFactor() << std::endl;
			}
			else if (debug == false)
			{
				std::cout << "INVALID" << std::endl;
			}
		}
		//MAX BUCKET SIZE
		else if (input1 == "MAX" && input2 == "BUCKET" && input3 == "SIZE")
		{
			if (debug == true)
			{
				std::cout << hash.maxBucketSize() << std::endl;
			}
			else if (debug == false)
			{
				std::cout << "INVALID" << std::endl;
			}
		}
		else
		{
			std::cout << "INVALID" << std::endl;
		}
	}
    return 0;
}

