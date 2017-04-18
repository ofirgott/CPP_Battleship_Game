
#pragma once
#include "Player.h"
#include <iostream>
#include <fstream>
#include <string>


void Player::setBoard(const char ** board, int numRows, int numCols)
{
	char** copyBoard = BattleshipBoard::copyMatrix(const_cast<char**>(board), numRows, numCols);
	std::set<std::pair<char, std::set<std::pair<int, int>>>> allShipsDetails = BattleshipBoard::ExtractShipsDetails(copyBoard, numRows, numCols);
	BattleshipBoard::deleteMatrix(copyBoard, numRows, numCols);
	std::set<Ship*> shipsSet = Ship::createShipSet(allShipsDetails);
	pBoard = Ship::createShipMatrix(shipsSet);
}


std::pair<int, int> Player::attack()
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

void Player::notifyOnAttackResult(int player, int row, int col, AttackResult result)
{
}


Player::Player(int user_id, const std::string attackFilePath)
{
	id = user_id;
	tScore = 0;
	pBoard = nullptr;
	cShips = 5;
	cAttack = 0;

	pMoves = parseAttackFile(attackFilePath.c_str());
	// check the case that  parsing failed 
	if ((pMoves.size() == 1) && (pMoves[0].first == std::numeric_limits<int>::max())
		&& (pMoves[0].second == std::numeric_limits<int>::max())) {
		id = -1;
		isDone = true;
	}
	else if (pMoves.size() == 0) {
		isDone = true;
	}
	else {
		isDone = false;
	}

}

Player::~Player()
{
	std::vector <std::pair<int, int>> currCoor;

	pMoves.clear();
	if (pBoard == NULL) {
		return;
	}

	// release the ship's matrix
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (pBoard[i][j] != nullptr) { // release ship exactly once 
				currCoor.clear();
				currCoor = pBoard[i][j]->getCoordinates();
				delete pBoard[i][j];
				// set all the pointers to this ship to nullptr
				for (auto& coor : currCoor) {
					pBoard[coor.first][coor.second] = nullptr;
				}
			}
		}
		delete[] pBoard[i];
	}
	delete[] pBoard;
	return;
}

int Player::getTScore()
{
	return tScore;
}

int Player::getShipsCount()
{
	return cShips;
}

bool Player::getHasMoreMoves()
{
	return !isDone;
}

int Player::getID()
{
	return id;
}

void Player::updateScore(int num)
{
	if (num < 0) {
		return;
	}
	tScore = tScore + num;
}


std::pair<AttackResult, int> Player::realAttack(std::pair<int, int> coor)
{
	if (coor.first > ROWS || coor.first < 1 || coor.second < 1 || coor.second > COLS) {
		return std::pair<AttackResult, int>(AttackResult::Miss, 0);
	}

	int attackRes;
	Ship* shipPtr = pBoard[coor.first - 1][coor.second - 1];
	std::pair<AttackResult, int> retPair;

	if (shipPtr == NULL) {// doesnt have a ship in this coordinates
		retPair = std::pair<AttackResult, int>(AttackResult::Miss, 0);
	}
	else { // have a ship in this coordinates 
		if (shipPtr->isAlive()) {// not sank yet
			attackRes = shipPtr->updateAttack(coor.first - 1, coor.second - 1);
			if (attackRes == 0) { // successful attack
				if (shipPtr->isAlive()) { // not sank yet 
					retPair = std::make_pair(AttackResult::Hit, 0);
				}
				else
				{ // the ship sank after the last attack
					retPair = std::make_pair(AttackResult::Sink, shipPtr->getPoints());
				}
			}
			else if (attackRes == 1)
			{ // already hit this part- no points given
				retPair = std::pair<AttackResult, int>(AttackResult::Hit, -1);
			}
			else
			{ // attackRes == -1  
				retPair = std::pair<AttackResult, int>(AttackResult::Miss, 0);
			}
		}
		else { // this ship is mine but already sank
			retPair = std::pair<AttackResult, int>(AttackResult::Miss, 0);
		}
	}

	if (retPair.first == AttackResult::Sink) { //  update number ships left for player
		cShips = cShips - 1;
	}

	return retPair;
}

std::vector<std::pair<int, int>>  Player::parseAttackFile(const char* attackFilePath)
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

std::vector<std::string> Player::split(const std::string & s, char delim, bool* succsessfulSplit)
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


bool Player::isSeperated(const std::string & token)
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

