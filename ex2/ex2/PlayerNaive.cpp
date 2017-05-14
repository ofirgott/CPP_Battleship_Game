
#include "../ex2/PlayerNaive.h"
#include "../ex2/BattleshipBoard.h"
#include <fstream>


void PlayerNaive::setBoard(int player, const char ** board, int numRows, int numCols)
{
std::set<std::pair<int, int>> result;
std::set<std::pair<char, std::set<std::pair<int, int>>>> setOfShipsDetails;
std::pair<int, int> pairToInsert(0, 0);

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
	// foreach shipDetail add all its surroundings to the not allowed coors to attack 
	while (it != setOfShipsDetails.end())
	{
		for (auto coord : it->second) {//for every ship we add each of her coord and around it
			result.insert(coord);
			if (coord.first + 1 <= numRows) {//down
				updateCoordinatesNaive(pairToInsert, coord.first + 1, coord.second);
				result.insert(pairToInsert);
			}
			if (coord.first - 1 > 0) {//up
				updateCoordinatesNaive(pairToInsert, coord.first - 1, coord.second);
				result.insert(pairToInsert);
			}
			if (coord.second + 1 <= numCols) {//right
				updateCoordinatesNaive(pairToInsert, coord.first, coord.second + 1);
				result.insert(pairToInsert);
			}
			if (coord.second - 1 > 0) {//left
				updateCoordinatesNaive(pairToInsert, coord.first, coord.second - 1);
				result.insert(pairToInsert);
			}
		}
		++it;
	}

	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			updateCoordinatesNaive(pairToInsert, i, j);
			if (result.find(pairToInsert) == result.end()) {//checking it's not my ship/around it - it's not in result
				updateCoordinatesNaive(pairToInsert, i + 1, j + 1);//+1 to fit the board indentation
				movesVector.push_back(pairToInsert);//adding to the vector of moves by order 
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
	++movesVectorItr;	
						/* move forward in the attacks vector for the next attack() call */
	return nextValidAttack;

}


bool PlayerNaive::init(const std::string & path)
{
	return (id != -1);// if false - set board failed
}

IBattleshipGameAlgo* GetAlgorithm()
{
	_instancesVec.push_back(new PlayerNaive());		// Create new instance and keep it in vector
	return _instancesVec[_instancesVec.size() - 1];		// Return last instance
}
