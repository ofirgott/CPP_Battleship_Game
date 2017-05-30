#pragma once
#include <set>
#include "IBattleshipGameAlgo.h"
#include <vector>

class BattleshipBoard 
{
public:
	BattleshipBoard() : rows(-1), cols(-1), depth(-1), isSuccCreated(false) {}								/* empty constructor */
	explicit BattleshipBoard(std::vector<char> board, int inputRows, int inputCols, int inputDepth);
	explicit BattleshipBoard(const std::string& boardPath);
	
	~BattleshipBoard();

	BattleshipBoard& operator=(const BattleshipBoard& otherBoard);															/* copy assignment */

																															//todo: add move ctor, and other from rule of 5


	char*** GetCopyOfBoardMatrix()const { return copyMatrix(const_cast<const char***>(matrix), rows, cols, depth); };		/* returns a new copy of the main matrix  TODO: maybe we dont need it */

	const std::vector<char> createPlayerBoard(int playerID)const;																		/* returns a new copy of a player matrix board  */

	int getRows() const { return rows; }
	int getCols() const { return cols; }
	int getDepth() const { return depth; }
	
	bool isSuccessfullyCreated() const { return (rows > 0 && cols > 0 && depth > 0 && !boardVec.empty() && isSuccCreated); }

	bool CheckIfHasAdjacentShips() const;																					/* checks if the matrix conatins adjacent ships, if so - prints relevant message */

	static bool IsShipCharInBoard(char ch);


																															/* given a player's matrix board,
																															returns set of pairs, which contains for each ship it's coordinates:
																															for example: {<'m', {<1,2,1>,<1,3,1>}> , <'P', {<8,5,4> , <8,6,4> , <8,7,4>}> } */
	std::set<std::pair<char, std::set<Coordinate>>> ExtractShipsDetails()const;

	/* given matrix board and specific coordintets and ship char, inserts to the set coordOfCurrentShip all coordinates of this current ship (recursive function) */
	static void getAllCurrShipCoords(std::vector<char> board, int x, int y, int z, char currShipChar, std::set<Coordinate>& coordOfCurrentShip, int boardRows, int boardCols, int boardDepth);

	/* checks if given coordinate is a valid location in board*/
	bool isCoordianteInBoard(int x, int y, int z)const { return isCoordianteInBoard(x, y, z, rows, cols, depth); };
	static bool isCoordianteInBoard(int x, int y, int z, int rowsNum, int colsNum, int depthNum) { return (x >= 0 && x < rowsNum && y >= 0 && y < colsNum && z >= 0 && z < depthNum); }

	
	static std::vector<char> copyMatrix(const std::vector<char> board, int rows, int cols, int depths);										/* returns a new copy of given matrix */

	
	static void deleteMatrix(const char*** matrix, int rows, int cols, int depths);											/* deletes char*** matrix TODO: maybe we dont need it */

	std::set<Coordinate> getNearbyCoordinates(int x, int y, int z)const;												    /* given a coordinate location in board, returns a set of surrondings coordinates of this point */

	static bool isPlayerShip(const int playerId, const char shipChar);														//todo: document

	char getCoordValue(const int x, const int y, const int z)const { if (isCoordianteInBoard(x, y, z)) return (*this)(x, y, z); else return ' '; }  //todo: document and adjust to the board interface

	char operator()(int x, int y, int z)const {	return boardVec.at(calcCoordIndex(x, y, z, rows, cols, depth)); }

	static char getBoardCoord(std::vector<char> boardVector, int x, int y, int z, int rowsNum, int colsNum, int depthNum);
	
	
	/* TODO: need to check this calculation if it is true: http://www.cplusplus.com/forum/general/137677/, https://stackoverflow.com/questions/10238699/dynamically-allocating-3d-array, https://stackoverflow.com/questions/2178909/how-to-initialize-3d-array-in-c */
	static int calcCoordIndex(int x, int y, int z, int boardRows, int boardCols, int boardDepth) { return x + y * boardCols + z * boardCols * boardRows;  }

private:

	static const int PLAYERID_A = 0;
	static const int PLAYERID_B = 1;
	static const char RUBBER_BOAT = 'B';
	static const char ROCKET_SHIP = 'P';
	static const char SUBMARINE = 'M';
	static const char DESTROYER = 'D';
	static const char BLANK_CHAR = ' ';


	std::vector<char> boardVec;
	int rows;
	int cols;
	int depth;
	bool isSuccCreated;


	static char*** AllocateNewMatrix(int rows, int cols, int depths);												 /* allocates new matrix in given size   TODO: maybe we dont need it */

	static std::vector<char> InitNewEmptyBoardVector(int rows, int cols, int depths);									 /* init already allocated matrix with ' ' */

	static void CopyInputLineToBoard(std::vector<char>& boardVec, const std::string& line, int currRow, int cols, int depths);	 /* given a input line string, copies this line to the matrix board */



	



};
