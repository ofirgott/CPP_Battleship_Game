
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
	if (isDone) {
		return std::make_pair(std::numeric_limits<int>::max(), std::numeric_limits<int>::max());
	}
	std::pair<int, int> nextAttack = pMoves[cAttack];
	cAttack++;
	if (cAttack == pMoves.size()) {
		isDone = true;
	}

	return nextAttack;
}

void Player::notifyOnAttackResult(int player, int row, int col, AttackResult result)
{
	//todo
}



Player::Player(int user_id, const std::string attackFilePath)
{
	id = user_id;
	tScore = 0;
	pBoard = nullptr;
	cShips = 5;
	cAttack = 0;

	//std::string str = attackFilePath;
	//pMoves = parseAttackFile(str);
	pMoves = parseAttackFile(attackFilePath.c_str());
	// check the case that the parsing failed 
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
	printf("players distructor\n");
	pMoves.clear();
	if (pBoard == NULL) {
		return;
	}

	// release the ship's matrix
	for (int i = 0; i < NROWS; i++) {
		/*	for (int j = 0; j < NCOLS; j++)
		{
		if (pBoard[i][j] != nullptr) {
		delete pBoard[i][j]; // free Battleship*
		}
		}*/
		delete[] pBoard[i]; // Battleship**
	}
	delete[] pBoard; //  (Battleship***)
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

// issue with the pointers to battleship!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
std::pair<AttackResult, int> Player::realAttack(std::pair<int, int> coor)
{
	if (coor.first > 10 || coor.first < 1 || coor.second < 1 || coor.second > 10) {
		// shouldent get here !!!!!!!!!!! 
		return std::pair<AttackResult, int>(AttackResult::Miss, 0);
	}

	int attackRes;
	// check field defenition in class def ???????????????????????
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
				retPair = std::pair<AttackResult, int>(AttackResult::Hit, 0);
			}
			else
			{ // attackRes == -1 
			  // shouldnt get here , already checked if ship is mine !!!!!!!!!!! 
				retPair = std::pair<AttackResult, int>(AttackResult::Miss, 0);
			}
		}
		else { // this ship is mine but already sank
			retPair = std::pair<AttackResult, int>(AttackResult::Miss, 0);
		}
	}

	if (retPair.first == AttackResult::Sink) { // should update number ships left for player
		cShips = cShips - 1;
	}

	return retPair;
}



std::vector<std::pair<int, int>>  Player::parseAttackFile(const char* attackFilePath)
{
	//char* path = attackFilePath.c_str();
	std::ifstream fd(attackFilePath); //creating an ifstream & open attackPath 
	std::string line;
	std::vector<std::string> tokens;
	std::vector<std::pair<int, int>> result;

	if (!fd) {// if open failed 
		std::cout << "ERROR: couldn't open attack file " << attackFilePath << std::endl;
		// in case of failure insert <inf,inf>
		result.push_back(std::make_pair(std::numeric_limits<int>::max(), std::numeric_limits<int>::max()));
		return result;
	}

	while (std::getline(fd, line)) //getline returns null if reached eof. /todo: do i have to check if getline failed?? 
	{
		tokens = split(line, ',');
		if (tokens.size() != 2) // if more then 2 tokens go to next line
		{
			continue;
		}

		std::pair<int, int> tmpPair(stoi(tokens[0]), stoi(tokens[1])); ////////// check if stoi failed??????????????? 
		if (tmpPair.first > NROWS || tmpPair.first < 1 || tmpPair.second > NCOLS || tmpPair.second < 1) {
			continue;
		}
		result.push_back(tmpPair);
	}

	fd.close();

	return result;
}

std::vector<std::string> Player::split(const std::string & s, char delim)
{
	std::vector<std::string> elems;
	std::stringstream strSt(s);
	std::string item;

	while (std::getline(strSt, item, delim))
	{
		elems.push_back(item);
	}

	return elems;
}
