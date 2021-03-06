#pragma once
#include <set>
#include <iostream>
#include "Constants.h"

class BattleshipBoard
{
public:
	BattleshipBoard() : matrix(nullptr), rows(-1), cols(-1) {}						/* empty constructor */
	BattleshipBoard(const std::string& boardPath, int rows, int cols);
	~BattleshipBoard() { deleteMatrix(matrix, rows, cols); }
	
	BattleshipBoard(const BattleshipBoard& otherBoard) : matrix(otherBoard.matrix), rows(otherBoard.rows), cols(otherBoard.cols) {}			/*  copy constructor */
	BattleshipBoard& operator=(const BattleshipBoard& otheBoard) = delete;			/* deletes the assignment operator - we want game to be a Non Copyable object */
	
	
	char** GetCopyOfBoard()const { return copyMatrix(matrix, rows, cols); };		/* returns a new copy of the main matrix */
	const char** createPlayerBoard(int playerID)const;								/* returns a new copy of a player matrix board */
	int getRows() const { return rows; }
	int getCols() const { return cols; }
	bool CheckIfHasAdjacentShips() const;											/* checks if the matrix conatins adjacent ships, if so - prints relevant message */			
	static bool IsShipCharInBoard(char ch);											/* checks if given char is a ship char */
	
	/* given a player's matrix board, 
	   returns set of pairs, which contains for each ship it's coordinates: 
	   for example: {<'m', {<1,2>,<1,3>}> , <'P', {<8,5> , <8,6> , <8,7>}> } */
	static std::set<std::pair<char, std::set<std::pair<int, int>>>> ExtractShipsDetails(char** matrix, int rows, int cols);
	
	/* given matrix board and specific coordintets and ship char, inserts to the set coordOfCurrentShip all coordinates of this current ship (recursive function) */
	static void getAllCurrShipCoords(char** matrix, int x, int y, char currShipChar, std::set<std::pair<int,int>>& coordOfCurrentShip);
	
	/* checks if given coordinate is a valid location in board*/
	static bool isCoordianteInBoard(int x, int y, int rowsNum, int colsNum);
	
	/* returns a new copy of given matrix */
	static char** copyMatrix(char** matrix, int rows, int cols);
	
	/* deletes char** matrix */
	static void deleteMatrix(char** matrix, int rows, int cols);


	private:
	
	char** matrix;
	int rows;
	int cols;
	
	static char** AllocateNewMatrix(int rows, int cols);						 /* allocates new matrix in given size */
	static void InitEmptyMatrix(char** matrix, int rows, int cols);				 /* init already allocated matrix with ' ' */
	static std::set<std::pair<int,int>> getNearbyCoordinates(int x, int y);      /* given a coordinate location in board, returns a set of surrondings coordinates of this point */
	static bool BattleshipBoard::IsShip(char ch);								 /* given a char, checks if it a valid ship char*/
	static void CopyInputLineToBoard(char** matrix, const std::string& line, int currRow, int cols); /* given a input line string, copies this line to the matrix board */
	
	
};

