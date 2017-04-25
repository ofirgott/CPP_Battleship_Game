
#include "Player.h"
#include "BattleshipBoard.h"


Player::~Player()
{
	for (auto it = _instancesVec.begin(); it != _instancesVec.end(); ++it)
	{
		delete(*it);
	}
}

void Player::setBoard(int player, const char** board, int numRows, int numCols)
{
	// copy board
	auto copyBoard = BattleshipBoard::copyMatrix(const_cast<char**>(board), numRows, numCols);		//copyBoard is char**

	// create a set containing all ships details i.e letter and coordinated for each ship (extract from board)
	auto allShipsDetails = BattleshipBoard::ExtractShipsDetails(copyBoard, numRows, numCols);		// allShipsDetails is std::set<std::pair<char, std::set<std::pair<int, int>>>>

	// free memory allocated for copyBoard
	BattleshipBoard::deleteMatrix(copyBoard, numRows, numCols);

	// for each ship detail in allShipsDetails allocate a new ship ith this details
	auto shipsSet = Ship::createShipSet(allShipsDetails);		//shipsSet is std::set<Ship*>

	// create matrix of pointers to the ships allocated for this player
	pBoard = Ship::createShipMatrix(shipsSet);
	
}