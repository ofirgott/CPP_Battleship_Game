#include "BattleshipBoard.h"
#include <iostream>
#include <set>
#include <fstream>
#include <string>
#include <locale>



/* called only once in a specific game */
BattleshipBoard::BattleshipBoard(const std::string& boardPath, int board_rows, int board_cols)
{

	if (boardPath.empty() || board_rows <= 0 || board_cols <= 0)				/* invalid input for a new board */
	{
		rows = -1;
		return;
	}

	std::string line;
	rows = board_rows;
	cols = board_cols;
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
		rows = -1;
	}

}


const char ** BattleshipBoard::createPlayerBoard(int playerID)const
{
	char** playerBoard = AllocateNewMatrix(rows, cols);
	InitEmptyMatrix(playerBoard, rows, cols);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (IsShipCharInBoard(matrix[i][j]) && isupper(matrix[i][j]) && playerID == PLAYERID_A)		/* returns clean matrix of player A*/
				playerBoard[i][j] = matrix[i][j];
			else if (IsShipCharInBoard(matrix[i][j]) && islower(matrix[i][j]) && playerID == PLAYERID_B)	/* returns clean matrix of player B */
				playerBoard[i][j] = matrix[i][j];
		}
	}

	return const_cast <const char**>(playerBoard);
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


std::set<std::pair<int, int>> BattleshipBoard::getNearbyCoordinates(int x, int y)
/* we check in this function every coordinate seperatly */
{
	std::set<std::pair<int, int>> adjCoordSet;
	if (isCoordianteInBoard(x - 1, y, ROWS, COLS)) adjCoordSet.insert(std::make_pair(x - 1, y));
	if (isCoordianteInBoard(x + 1, y, ROWS, COLS)) adjCoordSet.insert(std::make_pair(x + 1, y));
	if (isCoordianteInBoard(x, y - 1, ROWS, COLS)) adjCoordSet.insert(std::make_pair(x, y - 1));
	if (isCoordianteInBoard(x, y + 1, ROWS, COLS)) adjCoordSet.insert(std::make_pair(x, y + 1));

	return std::set<std::pair<int, int>>(adjCoordSet);
}

bool BattleshipBoard::isCoordianteInBoard(int x, int y, int rowsNum, int colsNum)
{
	if (x >= 0 && x < rowsNum && y >= 0 && y <= colsNum) return true;
	else return false;
}

char ** BattleshipBoard::copyMatrix(char ** matrix, int rows, int cols)
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

void BattleshipBoard::deleteMatrix(char ** matrix, int rows, int cols)
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
std::set<std::pair<char, std::set<std::pair<int, int>>>> BattleshipBoard::ExtractShipsDetails(char** matrix, int rows, int cols)	/* get a valid matrix (only ships of one player) */
{
	std::set<std::pair<char, std::set<std::pair<int, int>>>> setOfShipsDetails;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (matrix[i][j] == ' ') continue;

			std::set<std::pair<int, int>> coordOfCurrentShip;

			char currShipChar = matrix[i][j];

			getAllCurrShipCoords(matrix, i, j, currShipChar, coordOfCurrentShip);

			setOfShipsDetails.insert(std::make_pair(currShipChar, coordOfCurrentShip));		/* insert to the big set current ship details - <'m', {<1,2>,<1,3>}>*/

			for (auto coord : coordOfCurrentShip)
			{
				matrix[coord.first][coord.second] = ' ';	/* clear the board from this ship (we should have a copy of the board) */
			}
			coordOfCurrentShip.clear();
		}
	}

	return std::set<std::pair<char, std::set<std::pair<int, int>>>>(setOfShipsDetails);
}



void BattleshipBoard::getAllCurrShipCoords(char** matrix, int x, int y, char currShipChar, std::set<std::pair<int, int>> &coordOfCurrentShip)
{
	/*  note that in this function we can coordinate with line 0! if we want to use this function outside, we need to pay attention for this. */

	if (currShipChar == matrix[x][y])
	{
		matrix[x][y] = ' ';												/* clear the current position and add it to the coordinates set*/
		coordOfCurrentShip.insert(std::make_pair(x, y));

		if (isCoordianteInBoard(x, y + 1, ROWS, COLS))
			getAllCurrShipCoords(matrix, x, y + 1, currShipChar, coordOfCurrentShip);
		if (isCoordianteInBoard(x, y - 1, ROWS, COLS))
			getAllCurrShipCoords(matrix, x, y - 1, currShipChar, coordOfCurrentShip);
		if (isCoordianteInBoard(x + 1, y, ROWS, COLS))
			getAllCurrShipCoords(matrix, x + 1, y, currShipChar, coordOfCurrentShip);
		if (isCoordianteInBoard(x - 1, y, ROWS, COLS))
			getAllCurrShipCoords(matrix, x - 1, y, currShipChar, coordOfCurrentShip);
	}
}
