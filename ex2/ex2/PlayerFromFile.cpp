#include "PlayerFromFile.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


//todo: need to add implementaion of searching the attack file + adding prints

std::pair<int, int> PlayerFromFile::attack()
{

	if (isDone) { // if no more moves return out of bound coordinates
		return std::make_pair(std::numeric_limits<int>::max(), std::numeric_limits<int>::max());
	}
	//get next attack from player's moves vector
	std::pair<int, int> nextAttack = pMoves[cAttack];
	cAttack++;
	// check if player finished all his moves
	if (cAttack == pMoves.size()) {
		isDone = true;
	}

	return nextAttack;
}

std::vector<std::pair<int, int>> PlayerFromFile::parseAttackFile(const char * attackFilePath)
{
	std::ifstream fd(attackFilePath); //creating an ifstream & open attackPath 
	std::string line;
	std::vector<std::string> tokens;
	std::vector<std::pair<int, int>> result;
	int token1 = 0;
	int token2 = 0;
	bool isVAlidSplit;

	if (!fd) {// if open failed 
		std::cout << "ERROR: couldn't open attack file " << attackFilePath << std::endl;
		// in case of failure insert <inf,inf>
		result.push_back(std::make_pair(std::numeric_limits<int>::max(), std::numeric_limits<int>::max()));
		return result;
	}

	while (std::getline(fd, line)) //getline returns null if reached eof. 
	{
		tokens = split(line, ',', &isVAlidSplit);
		if (!isVAlidSplit) {
			std::cout << "ERROR: in parsing line in attack file " << attackFilePath << std::endl;
			result.clear();
			// in case of failure insert <inf,inf>
			result.push_back(std::make_pair(std::numeric_limits<int>::max(), std::numeric_limits<int>::max()));
			return result;
		}

		if (tokens.size() != 2) { // if more/less then 2 tokens ignore line
			continue;
		}

		/* check if there is a gap between the first digit to the second
		for example : "d         n" , while d &n are digits */
		if (isSeperated(tokens[0])) {
			continue;
		}

		try { //covers the cases that the string doesnt represent a number
			token1 = stoi(tokens[0]);
			token2 = stoi(tokens[1]);

		}
		catch (const std::exception&) {
			continue;
		}

		std::pair<int, int> tmpPair(token1, token2);
		// if bad coordinates skip to the next line 
		if (tmpPair.first > ROWS || tmpPair.first < 1 || tmpPair.second > COLS || tmpPair.second < 1) {
			continue;
		}
		result.push_back(tmpPair);
	}

	if (!fd) {
		if (!fd.eof()) { // error in reading from attack file - kill the game 
			std::cout << "ERROR: in reading from attack file " << attackFilePath << std::endl;
			// in case of failure return vector of size 1 and the first coor is <inf,inf>
			result.clear();
			result.push_back(std::make_pair(std::numeric_limits<int>::max(), std::numeric_limits<int>::max()));
			return result;
		}
	}
	fd.close();

	return result;
}

std::vector<std::string> PlayerFromFile::split(const std::string & s, char delim, bool * succsessfulSplit)
{
	std::vector<std::string> elems;
	std::stringstream strSt(s);
	std::string item;

	while (std::getline(strSt, item, delim))
	{
		elems.push_back(item);
	}

	if (!strSt) {
		if (!strSt.eof()) { // error in reading from string (getline)
			elems.clear();
			*succsessfulSplit = false;
			return elems;
		}
	}

	*succsessfulSplit = true;
	return elems;
}

bool PlayerFromFile::isSeperated(const std::string & token)
{

	int length = (int)size(token);
	int firstDigitIndex = length;

	// find the index of the first digit in the token
	for (int i = 0; i < length; i++) {
		if (isdigit(token[i])) {
			firstDigitIndex = i;
			break;
		}
	}

	if (firstDigitIndex == length) {
		return false;
	}

	// check if there is a digit after firstDigitIndex+1 in the string 
	for (int j = (firstDigitIndex + 2); j < length; j++) {
		if (isdigit(token[j])) {
			return true;
		}
	}

	return false;
}

IBattleshipGameAlgo* GetAlgorithm()
{
	_instancesVec.push_back(new PlayerFromFile());			// Create new instance and keep it in vector
	return _instancesVec[_instancesVec.size() - 1];			// Return last instance
}