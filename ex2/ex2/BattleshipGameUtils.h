#pragma once
#include <string>
#include <vector>


class BattleshipGameUtils
{
public:

	static bool isValidDir(const std::string& path);
	static bool isStringEndsWith(const std::string& str, const std::string& suffix);

	static std::vector<std::string> BattleshipGameUtils::SortedDirlistSpecificExtension(std::string const& dirPath, std::string const& ext);
	
	template <typename I>
	static I randomElement(I begin, I end);

};

/* taken from http://stackoverflow.com/a/6943003 */
template<typename I>
inline I BattleshipGameUtils::randomElement(I begin, I end)
{
	const unsigned long n = std::distance(begin, end);
	const unsigned long divisor = (RAND_MAX + 1) / n;

	unsigned long k;
	do { k = std::rand() / divisor; } while (k >= n);

	std::advance(begin, k);
	return begin;
}
