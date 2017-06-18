#include "GamePlayerData.h"
#include "BattleshipBoard.h"
#include "BattleshipGameManager.h"


GamePlayerData & GamePlayerData::operator=(GamePlayerData && other) noexcept
{

	id = other.id;
	playerAlgo = other.playerAlgo;
	hasMoreMoves = other.hasMoreMoves;
	score = other.score;
	std::swap(shipsBoard, other.shipsBoard);
	currShipsCount = other.currShipsCount;
	
	return *this;
}


Coordinate GamePlayerData::getAlgoNextAttack() const
{

	Coordinate tmpAttack = playerAlgo->attack();

	if (tmpAttack.row == -1 && tmpAttack.col == -1 && tmpAttack.depth == -1) { // player doesnt have anymore moves 
		return tmpAttack;
	}

	// while the given coordinates are not in the board && the player has more moves
	while (!shipsBoard.isCoordianteInShipBoard(tmpAttack.row - 1, tmpAttack.col - 1,tmpAttack.depth-1 ))
	{
		tmpAttack = playerAlgo->attack();
		if (tmpAttack.row == -1 && tmpAttack.col == -1 && tmpAttack.depth == -1) { // player doesnt have anymore moves
			return tmpAttack;
		}

	}
	return tmpAttack;
}


std::pair<AttackResult, int> GamePlayerData::realAttack(Coordinate coor)
{
	if (!shipsBoard.isCoordianteInShipBoard(coor.row - 1, coor.col - 1, coor.depth - 1)){
		return std::pair<AttackResult, int>(AttackResult::Miss, 0);
	}

	int attackRes;
	std::pair<AttackResult, int> retPair;
	Ship* shipPtr = shipsBoard(coor.row - 1,coor.col - 1,coor.depth - 1);

	if (shipPtr == nullptr) {// doesnt have a ship in this coordinates
		retPair = std::pair<AttackResult, int>(AttackResult::Miss, 0);
	}
	else { // have a ship in this coordinates 
		if (shipPtr->isAlive()) {// not sank yet
			attackRes = shipPtr->updateAttack(coor.row - 1, coor.col - 1,coor.depth -1);
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
				retPair = std::make_pair(AttackResult::Hit, -1);
			}
			else
			{ // attackRes == -1  
				retPair = std::make_pair(AttackResult::Miss, 0);
			}
		}
		else { // this ship is mine but already sank
			retPair = std::make_pair(AttackResult::Miss, 0);
		}
	}

	if (retPair.first == AttackResult::Sink) { //  update number ships left for player
		currShipsCount = currShipsCount - 1;
	}

	return retPair;
}