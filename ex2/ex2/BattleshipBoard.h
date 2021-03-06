#pragma once
#include <set>
#include <iostream>

class BattleshipBoard
{
public:
	BattleshipBoard() : matrix(nullptr), rows(-1), cols(-1), isSuccCreated(false) {}						/* empty constructor */
	BattleshipBoard(const char ** inputMatix, int inputRows, int inputCols) : matrix(copyMatrix(inputMatix, inputRows, inputCols)), rows(inputRows), cols(inputCols), isSuccCreated(true) {}
	BattleshipBoard(const std::string& boardPath, int rows, int cols);
	~BattleshipBoard() { deleteMatrix(const_cast<const char**>(matrix), rows, cols); }


	BattleshipBoard& operator=(const BattleshipBoard& otherBoard); // copy assignment

	char** GetCopyOfBoardMatrix()const { return copyMatrix(const_cast<const char**>(matrix), rows, cols); };		/* returns a new copy of the main matrix */
	const char** createPlayerBoard(int playerID)const;								/* returns a new copy of a player matrix board  */
	int getRows() const { return rows; }
	int getCols() const { return cols; }
	bool isSuccessfullyCreated() const { return (rows > 0 && cols > 0 && matrix && isSuccCreated); }
	bool CheckIfHasAdjacentShips() const;											/* checks if the matrix conatins adjacent ships, if so - prints relevant message */
	static bool IsShipCharInBoard(char ch);											/* checks if given char is a ship char */

																					/* given a player's matrix board,
																					returns set of pairs, which contains for each ship it's coordinates:
																					for example: {<'m', {<1,2>,<1,3>}> , <'P', {<8,5> , <8,6> , <8,7>}> } */
	std::set<std::pair<char, std::set<std::pair<int, int>>>> ExtractShipsDetails()const;

	/* given matrix board and specific coordintets and ship char, inserts to the set coordOfCurrentShip all coordinates of this current ship (recursive function) */
	static void getAllCurrShipCoords(char** matrix, int x, int y, char currShipChar, std::set<std::pair<int, int>>& coordOfCurrentShip, int matRows, int matCols);

	/* checks if given coordinate is a valid location in board*/
	bool isCoordianteInBoard(int x, int y)const { return isCoordianteInBoard(x, y, rows, cols); };
	static bool isCoordianteInBoard(int x, int y, int rowsNum, int colsNum){ return (x >= 0 && x < rowsNum && y >= 0 && y < colsNum); }

	/* returns a new copy of given matrix */
	static char** copyMatrix(const char** matrix, int rows, int cols);

	/* deletes char** matrix */
	static void deleteMatrix(const char** matrix, int rows, int cols);
	std::set<std::pair<int, int>> getNearbyCoordinates(int x, int y)const;      /* given a coordinate location in board, returns a set of surrondings coordinates of this point */
	static bool isPlayerShip(const int playerId, const char shipChar);
	char getCoordValue(const int x, const int y)const { if (isCoordianteInBoard(x, y)) return matrix[x][y]; else return ' '; }

	private:
	
	static const int PLAYERID_A = 0;
	static const int PLAYERID_B  = 1;
	static const char RUBBER_BOAT = 'B';
	static const char ROCKET_SHIP = 'P';
	static const char SUBMARINE = 'M';
	static const char DESTROYER = 'D';
	

	char** matrix;
	int rows;
	int cols;
	bool isSuccCreated;

	static char** AllocateNewMatrix(int rows, int cols);						 /* allocates new matrix in given size  */
	static void InitEmptyMatrix(char** matrix, int rows, int cols);				 /* init already allocated matrix with ' ' */
	
	static bool IsShip(char ch);								 /* given a char, checks if it a valid ship char*/
	static void CopyInputLineToBoard(char** matrix, const std::string& line, int currRow, int cols); /* given a input line string, copies this line to the matrix board */


};
