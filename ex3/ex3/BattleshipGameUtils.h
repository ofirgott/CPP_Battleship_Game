#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include "IBattleshipGameAlgo.h"


class BattleshipGameUtils
{
public:
	template<typename Out>
	static void splitStringByToken(const std::string &str, char delim, Out result);
	static bool getFullPath(std::string& path);
	static bool isValidDir(const std::string& path);
	static bool isStringEndsWith(const std::string& str, const std::string& suffix);
	static std::vector<std::string> SortedDirlistSpecificExtension(std::string const& dirPath, std::string const& ext);
	static bool emptyLine(const std::string& str);
};

template<typename Out>
void BattleshipGameUtils::splitStringByToken(const std::string & str, char delim, Out result)
{
	std::stringstream ss;
	ss.str(str);
	std::string item;
	while (std::getline(ss, item, delim)) {
		*(result++) = item;
	}
}

bool operator <(const Coordinate& c1, const Coordinate& c2);
std::string to_string(Coordinate c);
std::ostream& operator<<(std::ostream& out, const Coordinate& c);
