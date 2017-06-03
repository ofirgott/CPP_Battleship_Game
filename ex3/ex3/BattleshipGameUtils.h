#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iterator>


class BattleshipGameUtils
{
public:
	template<typename Out>
	static void splitStringByToken(const std::string &str, char delim, Out result);
	static bool getFullPath(std::string& path);
	static bool isValidDir(const std::string& path);
	static bool isStringEndsWith(const std::string& str, const std::string& suffix);
	static std::vector<std::string> SortedDirlistSpecificExtension(std::string const& dirPath, std::string const& ext);


};


template<typename Out>
inline void BattleshipGameUtils::splitStringByToken(const std::string & str, char delim, Out result)
{
	std::stringstream ss;
	ss.str(str);
	std::string item;
	while (std::getline(ss, item, delim)) {
		*(result++) = item;
	}
}
