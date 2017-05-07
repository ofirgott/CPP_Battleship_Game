#include "../ex2/PlayerNaive.h"
#include "../ex2/BattleshipGameUtils.h"
#include <sstream>
#include <fstream>


void PlayerNaive::setBoard(int player, const char ** board, int numRows, int numCols)
{
std::set<std::pair<int, int>> result;
std::set<std::pair<char, std::set<std::pair<int, int>>>> setOfShipsDetails;

id = player;
boardRows = numRows;
boardCols = numCols;
BattleshipBoard boardTemp(board, numRows, numCols);
if (!boardTemp.isSuccessfullyCreated()) {
	id = -1;
}
if (id != -1) {

	setOfShipsDetails = boardTemp.ExtractShipsDetails();
	std::set<std::pair<int, int>> coordOfCurrentShip;
	auto it = setOfShipsDetails.begin();
	while (it != setOfShipsDetails.end())
	{
		for (auto coord : it->second) {//for every ship we add each of her coord and around it
			result.insert(coord);
			if (coord.first + 1 <= numRows) {//down
				result.insert(std::make_pair(coord.first + 1, coord.second));
			}
			if (coord.first - 1 > 0) {//up
				result.insert(std::make_pair(coord.first - 1, coord.second));
			}
			if (coord.second + 1 <= numCols) {//right
				result.insert(std::make_pair(coord.first, coord.second + 1));
			}
			if (coord.second - 1 > 0) {//left
				result.insert(std::make_pair(coord.first, coord.second - 1));
			}
		}
		++it;
	}
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			if (result.find(std::make_pair(i, j)) == result.end()) {//checking it's not my ship/around it - it's not in result
				movesVector.push_back(std::make_pair(i+1, j+1));//adding to the vector of moves by order 
			}
		}
	}
}
	movesVectorItr = movesVector.begin();
}


std::pair<int, int> PlayerNaive::attack()
{

	if (id == UNDEFINED_PLAYERID || movesVectorItr == movesVector.end())	// the Id check is just to be sure that the plyaer already initialized
	{
		return std::make_pair(-1, -1);
	}

	// else - we have more moves - we want to output only valid moves according to the player board dimmensions
	std::pair<int, int> nextValidAttack;

	while (!BattleshipBoard::isCoordianteInBoard(movesVectorItr->first - 1, movesVectorItr->second - 1, boardRows, boardCols))
	{
		++movesVectorItr;
	}

	nextValidAttack = *movesVectorItr;			 /* the valid attack pair we will output*/
	++movesVectorItr;							/* move forward in the attacks vector for the next attack() call */

	return nextValidAttack;
}


bool PlayerNaive::init(const std::string & path)
{
	if (id == -1) {//set board failed 
		return false;
	}
	return true;
}

IBattleshipGameAlgo* GetAlgorithm()
{
	_instancesVec.push_back(new PlayerNaive());		// Create new instance and keep it in vector
	return _instancesVec[_instancesVec.size() - 1];		// Return last instance
}
