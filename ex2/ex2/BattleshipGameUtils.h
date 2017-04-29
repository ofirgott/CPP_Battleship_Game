#pragma once
#include <string>
#include <vector>


class BattleshipGameUtils
{
public:

	static bool isValidDir(const std::string& path);
	static bool isStringEndsWith(const std::string& str, const std::string& suffix);

	static std::vector<std::string> BattleshipGameUtils::SortedDirlistSpecificExtension(std::string const& dirPath, std::string const& ext);




};
