#ifndef __INIPARSER_H__
#define __INIPARSER_H__

#include <string>

#include <map>

class IniParser
{
public:
	IniParser();
	~IniParser();

	bool LoadIniFile(std::string filename);

	std::string GetValueAsString(std::string iniSection, std::string key);
	int GetValueAsInt(std::string iniSection, std::string key);
	float GetValueAsFloat(std::string iniSection, std::string key);
	bool GetValueAsBoolean(std::string iniSection, std::string key);

	int GetMapLength() const;

protected:
	std::map<std::string, std::map<std::string, std::string>> fileMap;
};

#endif