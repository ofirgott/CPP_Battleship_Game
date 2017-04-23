#include "Player.h"


void Player::setBoard(int player, const char** board, int numRows, int numCols)
{
	// copy board
	char** copyBoard = BattleshipBoard::copyMatrix(const_cast<char**>(board), numRows, numCols);

	// create a set containing all ships details i.e letter and coordinated for each ship (extract from board)
	std::set<std::pair<char, std::set<std::pair<int, int>>>> allShipsDetails = BattleshipBoard::ExtractShipsDetails(copyBoard, numRows, numCols);

	// free memory allocated for copyBoard
	BattleshipBoard::deleteMatrix(copyBoard, numRows, numCols);

	// for each ship detail in allShipsDetails allocate a new ship ith this details
	std::set<Ship*> shipsSet = Ship::createShipSet(allShipsDetails);

	// create matrix of pointers to the ships allocated for this player
	pBoard = Ship::createShipMatrix(shipsSet);

	//todo : maybe we want also here to do id =-1 beacuse of allocation failure
}