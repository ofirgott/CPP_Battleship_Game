
#pragma once
//#include <fstream>
//#include <vector>
#include <set>
#include <iostream>

class BattleshipBoard
{
public:
	BattleshipBoard() : matrix(nullptr), rows(0), cols(0) , isBoardSet(false) {}	//todo: check if needed - empty c'tor
	BattleshipBoard(const std::string& boardPath, int rows, int cols);
	//BattleshipBoard(char** matrix, int rows, int cols);
	//BattleshipBoard(const BattleshipBoard& copy) : BattleshipBoard(copy.matrix, copy.rows, copy.cols){}
	char** GetCopyOfBoard()const { return copyMatrix(matrix, rows, cols); };


	~BattleshipBoard() { deleteMatrix(matrix, rows, cols); }
	int getRows() const { return rows; }
	int getCols() const { return cols; }
	//char** getBoard() const; 
	const char** createPlayerBoard(int playerID);	
	bool CheckIfHasAdjacentShips() const;
	//char GetCoordinate(int x, int y) const { return matrix[x - 1][y - 1]; };

	 void CopyInputLineToBoard(char** matrix, const std::string& line, int currRow, int cols);
	 static bool IsShipCharInBoard(char ch);
	 static std::set<std::pair<char, std::set<std::pair<int, int>>>> ExtractShipsDetails(char** matrix, int rows, int cols);
	//return set of pairs, which contains for each ship it's coordinates:
	// for example: {<'m', {<1NE,2>,<1,3>}> , <'P', {<8,5> , <8,6> , <8,7>}> }
	 static void getAllCurrShipCoords(char** matrix, int x, int y, char currShipChar, std::set<std::pair<int,int>>& coordOfCurrentShip);	//it is a fucking recursive function!
	static bool isCoordianteInBoard(int x, int y, int rowsNum, int colsNum);
	static char** copyMatrix(char** matrix, int rows, int cols);
	void printBoard(char** matrix, int rows, int cols) { for (int i = 0; i < rows; i++)for (int j = 0; j < cols ; j++)std::cout << matrix[i][j]<<", "; }
	static void deleteMatrix(char** matrix, int rows, int cols);
private:
	char** matrix;
	int rows;
	int cols;
	bool isBoardSet;
	void LoadBattleshipBoardFromFile(const std::string& board_path, char** board, int rows, int cols);
	char** AllocateNewMatrix(int rows, int cols);
	void InitEmptyMatrix(char** matrix, int rows, int cols);
	 std::set<std::pair<int,int>> getNearbyCoordinates(int x, int y)const;
	 static bool BattleshipBoard::IsBoard(char ch);
	
	
};

