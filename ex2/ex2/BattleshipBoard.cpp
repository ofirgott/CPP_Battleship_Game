#include "BattleshipBoard.h"
#include <iostream>
#include <set>
#include <fstream>
#include <string>
#include <locale>


/* called only once in a specific game */
BattleshipBoard::BattleshipBoard(const std::string& boardPath, int boardRows, int boardCols) : rows(boardRows), cols(boardCols), isSuccCreated(false)
{

	if (boardPath.empty() || rows <= 0 || cols <= 0)				/* invalid input for a new board */
		return;

	std::string line;

	matrix = AllocateNewMatrix(rows, cols);
	InitEmptyMatrix(matrix, rows, cols);

	std::ifstream boardFile(boardPath.c_str());
	if (boardFile.is_open())
	{
		int rowCnt = 0;											/* we need to read only ROWS (10) rows from the board input file */

		while (rowCnt < rows && std::getline(boardFile, line))  /* while we read < 10 lines or we don't reach to eof in board file */
		{
			CopyInputLineToBoard(matrix, line, rowCnt, cols);
			rowCnt++;
		}
		boardFile.close();
	}
	else {														/* we can't open the board file */
		std::cout << "Error opening board file in " << boardPath << std::endl;
		return;
	}

	isSuccCreated = true;

}


BattleshipBoard & BattleshipBoard::operator=(const BattleshipBoard & otherBoard)
{
	if (this != &otherBoard)
	{
		rows = otherBoard.rows;
		cols = otherBoard.cols;
		matrix = copyMatrix(const_cast<const char**>(otherBoard.matrix), otherBoard.rows, otherBoard.cols);
		isSuccCreated = true;
	}

	return *this;
}
bool BattleshipBoard::isPlayerShip(const int playerId, const char shipChar)
{
	return ((isupper(shipChar) && playerId == PLAYERID_A) || (islower(shipChar) && playerId == PLAYERID_B));
}
const char ** BattleshipBoard::createPlayerBoard(int playerID)const
{
	char** playerBoard = AllocateNewMatrix(rows, cols);
	InitEmptyMatrix(playerBoard, rows, cols);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (IsShipCharInBoard(matrix[i][j]) && playerID == PLAYERID_A && isPlayerShip(playerID, matrix[i][j]))		/* returns clean matrix of player A*/
				playerBoard[i][j] = matrix[i][j];
			else if (IsShipCharInBoard(matrix[i][j]) && playerID == PLAYERID_B && isPlayerShip(playerID, matrix[i][j]))	/* returns clean matrix of player B */
				playerBoard[i][j] = matrix[i][j];
		}
	}

	return const_cast<const char **>(playerBoard);
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
			currPos = matrix[i][j];
			if (currPos == ' ') continue;			/* if current position is not a ship - it is a ' ', because we clean the board at the begining */

			auto nearbyCoordSet = getNearbyCoordinates(i, j);

			for (auto adjacentCoor : nearbyCoordSet)		/* for each nearby coordinate we check if we have adjacent ship (surronding other char) */
			{
				char adjacentVal = matrix[adjacentCoor.first][adjacentCoor.second];

				if (IsShipCharInBoard(adjacentVal) && adjacentVal != currPos)
				{
					std::cout << "Adjacent Ships on Board" << std::endl;
					return true;
				}
			}
		}
	}
	return false;
}


char** BattleshipBoard::AllocateNewMatrix(int rows, int cols)
{
	char** matrix = new char*[rows];
	for (int i = 0; i < rows; i++)
	{
		matrix[i] = new char[cols];
	}
	return matrix;
}

void BattleshipBoard::InitEmptyMatrix(char ** matrix, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			matrix[i][j] = ' ';
		}
	}
}


std::set<std::pair<int, int>> BattleshipBoard::getNearbyCoordinates(int x, int y)const
/* we check in this function every coordinate seperatly */
{
	std::set<std::pair<int, int>> adjCoordSet;
	if (isCoordianteInBoard(x - 1, y)) adjCoordSet.insert(std::make_pair(x - 1, y)); //todo: ofir needs to remove the constants!
	if (isCoordianteInBoard(x + 1, y)) adjCoordSet.insert(std::make_pair(x + 1, y));
	if (isCoordianteInBoard(x, y - 1)) adjCoordSet.insert(std::make_pair(x, y - 1));
	if (isCoordianteInBoard(x, y + 1)) adjCoordSet.insert(std::make_pair(x, y + 1));

	return std::set<std::pair<int, int>>(adjCoordSet);
}


char ** BattleshipBoard::copyMatrix(const char ** matrix, int rows, int cols)
{
	char** copy = new char*[rows];

	for (int i = 0; i < rows; i++)
	{
		copy[i] = new char[cols];
		for (int j = 0; j < cols; j++)
		{
			copy[i][j] = matrix[i][j];
		}
	}

	return copy;
}

void BattleshipBoard::deleteMatrix(const char ** matrix, int rows, int cols)
{
	if (!matrix) return;

	for (int i = 0; i < rows; i++)
		delete[] matrix[i];

	delete[] matrix;
}

void BattleshipBoard::CopyInputLineToBoard(char** matrix, const std::string& line, int currRow, int cols)
{
	size_t lineLen;
	if (line.length() < unsigned(cols))
		lineLen = line.length();
	else
		lineLen = cols;

	for (size_t j = 0; j < lineLen; j++)
	{
		if (IsShipCharInBoard(line[j])) {
			matrix[currRow][j] = line[j];  /*else it will remain ' ' */
		}
	}
}

bool BattleshipBoard::IsShip(char ch)
{
	return ch == RUBBER_BOAT || ch == ROCKET_SHIP || ch == SUBMARINE || ch == DESTROYER;
}

bool BattleshipBoard::IsShipCharInBoard(char ch)
{
	return IsShip(toupper(ch));
}

/* returns set of pairs, which contains for each ship it's coordinates:
* for example: {<'m', {<1,2>,<1,3>}> , <'P', {<8,5> , <8,6> , <8,7>}> }
* note that we don't check here the correctness of ships, only extract data
*/
std::set<std::pair<char, std::set<std::pair<int, int>>>> BattleshipBoard::ExtractShipsDetails()const	/* create new copy of the matrix and de;etes it */
{
	char** boardMatrixCopy = GetCopyOfBoardMatrix();
	std::set<std::pair<char, std::set<std::pair<int, int>>>> setOfShipsDetails;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (boardMatrixCopy[i][j] == ' ') continue;

			std::set<std::pair<int, int>> coordOfCurrentShip;

			char currShipChar = boardMatrixCopy[i][j];

			getAllCurrShipCoords(boardMatrixCopy, i, j, currShipChar, coordOfCurrentShip, rows, cols);

			setOfShipsDetails.insert(std::make_pair(currShipChar, coordOfCurrentShip));		/* insert to the big set current ship details - <'m', {<1,2>,<1,3>}>*/

			for (auto coord : coordOfCurrentShip)
			{
				boardMatrixCopy[coord.first][coord.second] = ' ';	/* clear the board from this ship (we should have a copy of the board) */
			}
			coordOfCurrentShip.clear();
		}
	}
	deleteMatrix(const_cast<const char**>(boardMatrixCopy), rows, cols);

	return std::set<std::pair<char, std::set<std::pair<int, int>>>>(setOfShipsDetails);
}



void BattleshipBoard::getAllCurrShipCoords(char** matrix, int x, int y, char currShipChar, std::set<std::pair<int, int>> &coordOfCurrentShip, int matRows, int matCols)
{
	/*  note that in this function we can coordinate with line 0! if we want to use this function outside, we need to pay attention for this. */

	if (currShipChar == matrix[x][y])
	{
		matrix[x][y] = ' ';												/* clear the current position and add it to the coordinates set*/
		coordOfCurrentShip.insert(std::make_pair(x, y));

		if (isCoordianteInBoard(x, y + 1, matCols, matRows))
			getAllCurrShipCoords(matrix, x, y + 1, currShipChar, coordOfCurrentShip, matCols, matRows);
		if (isCoordianteInBoard(x, y - 1, matCols, matRows))
			getAllCurrShipCoords(matrix, x, y - 1, currShipChar, coordOfCurrentShip, matCols, matRows);
		if (isCoordianteInBoard(x + 1, y, matCols, matRows))
			getAllCurrShipCoords(matrix, x + 1, y, currShipChar, coordOfCurrentShip, matCols, matRows);
		if (isCoordianteInBoard(x - 1, y, matCols, matRows))
			getAllCurrShipCoords(matrix, x - 1, y, currShipChar, coordOfCurrentShip, matCols, matRows);
	}
}
