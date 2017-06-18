#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include "IBattleshipGameAlgo.h"
#include <set>


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
	static int calcCoordIndex(int r, int c, int d, int boardRows, int boardCols) { return r + c * boardCols + d * boardCols * boardRows; }
	static bool isCoordianteInBoard(int r, int c, int d, int rowsNum, int colsNum, int depthNum) { return (r >= 0 && r < rowsNum && c >= 0 && c < colsNum && d >= 0 && d < depthNum); }
	template <typename I>
	static I randomElement(I begin, I end);


	/*utility functions****************************************************************************************/
	/*returns (1,0,0), (0,1,0) (0,0,1) ,(1,0,0), (0,1,0) (0,0,1)*/
	static std::vector<Coordinate> setSixOptionsVector();
	/*(0, 1, 0)(0, -1, 0)*/
	static std::vector<Coordinate> setHorizontalOptionsVector();
	/*(1, 0, 0)(-1, 0, 0)*/
	static std::vector<Coordinate> setVerticalOptionsVector();
	/*(0, 0, 1)(0, 0, -1)*/
	static std::vector<Coordinate> setDimentionalOptionsVector();
	/* move all coors in tempOptions to allOptions*/
	static void mergeVector(std::vector<Coordinate>& allOptions, const std::vector<Coordinate>& tempOptions);;
	/*(1, 0, 1)(1, 0, -1)(0, 1, 1) (0, 1, -1) (0, 0, 1) (0, 0, -1)*/
	static std::vector<Coordinate> setVectorForCheckSixDirections();

	/*utility functions ****************************************************************************************/

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

/* taken from http://stackoverflow.com/a/6943003  */
template<typename I>
inline I BattleshipGameUtils::randomElement(I begin, I end)
{
	auto n = std::distance(begin, end);
	auto divisor = (RAND_MAX + 1) / n;

	auto k = n;

	do { k = std::rand() / divisor; } while (k >= n);

	std::advance(begin, k);
	return begin;
}

/* Coordinate Utils */
bool operator <(const Coordinate& c1, const Coordinate& c2);
std::string to_string(Coordinate c);
std::ostream& operator<<(std::ostream& out, const Coordinate& c);

