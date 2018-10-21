#include "IniParser.h"

#include <fstream>
#include <iostream>
#include <regex>
#include "logmanager.h"


IniParser::IniParser()
{
}


IniParser::~IniParser()
{
}

bool IniParser::LoadIniFile(std::string filename)
{
	std::ifstream infile;
	infile.open(filename);

	std::regex bracketRegex("(\\[|\\])");
	std::regex bracketOrSpace("(\\[|\\]|\\n|\\r)");
	std::regex nonBrackets("([^\\[^\\]]+)");
	std::regex equals("(=)");
	std::string nextLine;
	std::smatch match;

	int sectionCount = 0;

	if (!infile.eof())
	{
		std::getline(infile, nextLine);
	}

	while (!infile.eof())
	{
		if (std::regex_search(nextLine, match, bracketRegex))
		{
			// Section Titles

			std::smatch match2;
			std::string sectionKey;

			std::regex_search(nextLine, match2, nonBrackets); // Get the stuff not in the brackets
			int split_index = match2.position(); // Index of string where match occurs
			sectionKey = nextLine.substr(split_index, match2.length()); // Substract the index and end index of search
			
			LogManager::GetInstance().Log(sectionKey.c_str());
	
			std::map<std::string, std::string> sectionMap;
			std::smatch match3;

			bool foundBrackets = false;
			bool foundKeyValuePair = false;
			while (!infile.eof() && !foundBrackets)
			{
				std::string key;
				std::string value;

				std::getline(infile, nextLine);
				foundBrackets = std::regex_search(nextLine, match, bracketRegex);
				bool foundSpace = (nextLine.length() == 0);
				if (!foundBrackets && !foundSpace)
				{
					// Get position of the =
					std::regex_search(nextLine, match3, equals);
					int equalIndex = match3.position();

					// Right now, key value pairs in the file needs to have ONE space beside the = on both sides like this: x = 255.
					// Will make it more robust if there is time.
					key = nextLine.substr(0, equalIndex - 1);
					value = nextLine.substr(equalIndex + 2, (nextLine.length() - equalIndex));
					LogManager::GetInstance().Log(("Key: " + key + "|" + "Value: " + value + "|").c_str());

					sectionMap[key] = value;
					foundKeyValuePair = true;
				}
				//LogManager::GetInstance().Log("");
			}
			if (foundKeyValuePair)
			{
				fileMap[sectionKey] = sectionMap;
			}
		}
	}
	
	infile.close();

	//LogManager::GetInstance().Log(GetValueAsString("3", "x").c_str());
	return false;
}

std::string IniParser::GetValueAsString(std::string iniSection, std::string key)
{
	std::map<std::string, std::string> sectionMap = fileMap.at(iniSection);
	return sectionMap.at(key);
}

int IniParser::GetValueAsInt(std::string iniSection, std::string key)
{
	std::map<std::string, std::string> sectionMap = fileMap.at(iniSection);
	return std::stoi(sectionMap.at(key));
}

float IniParser::GetValueAsFloat(std::string iniSection, std::string key)
{
	std::map<std::string, std::string> sectionMap = fileMap.at(iniSection);
	return std::stof(sectionMap.at(key));
}

bool IniParser::GetValueAsBoolean(std::string iniSection, std::string key)
{
	std::map<std::string, std::string> sectionMap = fileMap.at(iniSection);
	std::string val = sectionMap.at(key);
	bool returnValue = false;
	if (val == "true") 
	{
		returnValue = true;
	}

	return returnValue;
}

int IniParser::GetMapLength() const
{
	return fileMap.size();
}
