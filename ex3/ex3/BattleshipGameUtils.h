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

/* todo: add duco and understand we do we need this excactly..*/
bool inline operator <(const Coordinate& c1, const Coordinate& c2) {
	if (c1.col == c2.col) {
		if (c1.row == c2.row) {
			return c1.depth < c2.depth;
		}
		return c1.row < c2.row;
	}
	return c1.col < c2.col;
}
