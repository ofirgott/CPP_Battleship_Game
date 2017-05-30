#include "BattleshipBoard.h"
#include <iostream>

BattleshipBoard::BattleshipBoard(const char *** inputMatix, int inputRows, int inputCols, int inputDepth) : matrix(copyMatrix(inputMatix, inputRows, inputCols, inputDepth)), rows(inputRows), cols(inputCols), depth(inputDepth), isSuccCreated(true) {}

BattleshipBoard::BattleshipBoard(const std::string & boardPath)
{
}

BattleshipBoard & BattleshipBoard::operator=(const BattleshipBoard & otherBoard)
{
	// TODO: insert return statement here
}

const char *** BattleshipBoard::createPlayerBoard(int playerID) const
{
	return nullptr;
}

/* for battleship pixel in the board, we will check if the adjacent pixels of this pixel (up, down, left and right)
is a different ship - if so, we have an adjacent error in board.
*/
bool BattleshipBoard::CheckIfHasAdjacentShips() const
{
	char currPos;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			for (int k = 0; k < depth; k++)
			{
				currPos = (*this)(i, j, k);

				if (currPos == ' ') continue;			/* if current position is not a ship - it is a ' ', because we clean the board at the begining */

				auto nearbyCoordSet = getNearbyCoordinates(i, j, k);

				for (auto adjacentCoor : nearbyCoordSet)		/* for each nearby coordinate we check if we have adjacent ship (surronding other char)  */
				{
					char adjacentVal = (*this)(adjacentCoor.row, adjacentCoor.col, adjacentCoor.depth);

					if (IsShipCharInBoard(adjacentVal) && adjacentVal != currPos)
					{
						// TODO: print to the logger std::cout << "Adjacent Ships on Board" << std::endl;
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool BattleshipBoard::IsShipCharInBoard(char ch)
{
	ch = toupper(ch);
	return (ch == RUBBER_BOAT || ch == ROCKET_SHIP || ch == SUBMARINE || ch == DESTROYER);
}

std::set<std::pair<char, std::set<Coordinate>>> BattleshipBoard::ExtractShipsDetails() const
{
	auto boardVecCopy = boardVec;
	std::set<std::pair<char, std::set<Coordinate>>> setOfShipsDetails;
	char currShipChar;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			for (int k = 0; k < depth; k++)
			{
				int currIndex = calcCoordIndex(i, j, k, rows, cols, depth);
				
				if((currShipChar = boardVecCopy.at(currIndex)) == ' ') continue;

				std::set<Coordinate> coordOfCurrentShip;

				getAllCurrShipCoords(boardVecCopy, i, j, k, currShipChar, coordOfCurrentShip, rows, cols, depth);

				setOfShipsDetails.insert(std::make_pair(currShipChar, coordOfCurrentShip));				/* insert to the big set current ship details - <'m', {<1,2>,<1,3>}>*/

				for (auto coord : coordOfCurrentShip)
				{
					currIndex = calcCoordIndex(coord.row, coord.col, coord.depth, rows, cols, depth);
					boardVecCopy.at(currIndex) = ' ';													/* clear the board from this ship (we should have a copy of the board) */
				}
				coordOfCurrentShip.clear();
			}
		}
	}

	return std::set<std::pair<char, std::set<Coordinate>>>(setOfShipsDetails);
}

void BattleshipBoard::getAllCurrShipCoords(std::vector<char> board, int x, int y, int z, char currShipChar, std::set<Coordinate>& coordOfCurrentShip, int boardRows, int boardCols, int boardDepth)
{
	/*  note that in this function we can coordinate with line 0! if we want to use this function outside, we need to pay attention for this. */

	int CoordIndex = calcCoordIndex(x, y, z, boardRows, boardCols, boardDepth);
	if (currShipChar == board.at(CoordIndex))
	{
		board.at(CoordIndex) = ' ';												/* clear the current position and add it to the coordinates set*/
		coordOfCurrentShip.insert({x, y, z});

		if(isCoordianteInBoard(x, y + 1, z, boardRows, boardCols, boardDepth))
			getAllCurrShipCoords(board, x, y + 1, z, currShipChar, coordOfCurrentShip, boardCols, boardRows, boardDepth);
		if (isCoordianteInBoard(x, y - 1, z, boardCols, boardRows, boardDepth))
			getAllCurrShipCoords(board, x, y - 1, z, currShipChar, coordOfCurrentShip, boardCols, boardRows, boardDepth);
		if (isCoordianteInBoard(x + 1, y, z, boardCols, boardRows, boardDepth))
			getAllCurrShipCoords(board, x + 1, y, z, currShipChar, coordOfCurrentShip, boardCols, boardRows, boardDepth);
		if (isCoordianteInBoard(x - 1, y, z, boardCols, boardRows, boardDepth))
			getAllCurrShipCoords(board, x - 1, y, z, currShipChar, coordOfCurrentShip, boardCols, boardRows, boardDepth);
		if (isCoordianteInBoard(x, y, z + 1, boardCols, boardRows, boardDepth))
			getAllCurrShipCoords(board, x, y, z + 1, currShipChar, coordOfCurrentShip, boardCols, boardRows, boardDepth);
		if (isCoordianteInBoard(x, y, z - 1, boardCols, boardRows, boardDepth))
			getAllCurrShipCoords(board, x, y, z - 1, currShipChar, coordOfCurrentShip, boardCols, boardRows, boardDepth);
	}
}

char *** BattleshipBoard::copyMatrix(const char *** matrix, int rows, int cols, int depths)
{
	return nullptr;
}

void BattleshipBoard::deleteMatrix(const char *** matrix, int rows, int cols, int depths)
{
}

std::set<Coordinate> BattleshipBoard::getNearbyCoordinates(int x, int y, int z) const
/* we check in this function every coordinate seperatly */
{
	std::set<Coordinate> adjCoordSet;
	
	if (isCoordianteInBoard(x - 1, y, z)) adjCoordSet.insert({x - 1, y, z});    //adjCoordSet.insert(std::make_pair(x - 1, y)
	if (isCoordianteInBoard(x + 1, y, z)) adjCoordSet.insert({x + 1, y, z});
	if (isCoordianteInBoard(x, y - 1, z)) adjCoordSet.insert({x, y - 1, z});
	if (isCoordianteInBoard(x, y + 1, z)) adjCoordSet.insert({x, y + 1, z});

	return std::set<Coordinate>(adjCoordSet);
}

bool BattleshipBoard::isPlayerShip(const int playerId, const char shipChar)
{
	return false;
}

char BattleshipBoard::getBoardCoord(std::vector<char> boardVector, int x, int y, int z, int rowsNum, int colsNum, int depthNum)
{
	return boardVector.at(calcCoordIndex(x, y, z, rowsNum, colsNum, depthNum));
}




/* this is strange to return reference to a vector, so we will return by value, and then we will make move to prevent new allocation */
std::vector<char> BattleshipBoard::InitNewEmptyBoardVector(int rows, int cols, int depths)
{
	std::vector<char> vec(rows * cols * depths, BLANK_CHAR);
	return vec;
}
 

void BattleshipBoard::CopyInputLineToBoard(char *** matrix, const std::string & line, int currRow, int cols, int depths)
{
}
