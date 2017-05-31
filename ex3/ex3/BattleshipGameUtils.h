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
