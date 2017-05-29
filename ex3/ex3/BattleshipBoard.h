#pragma once
#include <set>
#include "IBattleshipGameAlgo.h"

class BattleshipBoard 
{
public:
	BattleshipBoard() : matrix(nullptr), rows(-1), cols(-1), depth(-1), isSuccCreated(false) {}								/* empty constructor */
	explicit BattleshipBoard(const char *** inputMatix, int inputRows, int inputCols, int inputDepth);
	explicit BattleshipBoard(const std::string& boardPath);
	
	~BattleshipBoard() { deleteMatrix(const_cast<const char***>(matrix), rows, cols, depth); }

	BattleshipBoard& operator=(const BattleshipBoard& otherBoard);															/* copy assignment */

																															//todo: add move ctor, and other from rule of 5


	char*** GetCopyOfBoardMatrix()const { return copyMatrix(const_cast<const char***>(matrix), rows, cols, depth); };		/* returns a new copy of the main matrix */

	const char*** createPlayerBoard(int playerID)const;																		/* returns a new copy of a player matrix board  */

	int getRows() const { return rows; }
	int getCols() const { return cols; }
	int getDepth() const { return depth; }
	
	bool isSuccessfullyCreated() const { return (rows > 0 && cols > 0 && depth > 0 && matrix && isSuccCreated); }

	bool CheckIfHasAdjacentShips() const;																					/* checks if the matrix conatins adjacent ships, if so - prints relevant message */

	static bool IsShipCharInBoard(char ch);


																															/* given a player's matrix board,
																															returns set of pairs, which contains for each ship it's coordinates:
																															for example: {<'m', {<1,2,1>,<1,3,1>}> , <'P', {<8,5,4> , <8,6,4> , <8,7,4>}> } */
	std::set<std::pair<char, std::set<Coordinate>>> ExtractShipsDetails()const;

	/* given matrix board and specific coordintets and ship char, inserts to the set coordOfCurrentShip all coordinates of this current ship (recursive function) */
	static void getAllCurrShipCoords(char*** matrix, int x, int y, int z, char currShipChar, std::set<Coordinate>& coordOfCurrentShip, int matRows, int matCols, int matDepth);

	/* checks if given coordinate is a valid location in board*/
	bool isCoordianteInBoard(int x, int y, int z)const { return isCoordianteInBoard(x, y, z, rows, cols, depth); };
	static bool isCoordianteInBoard(int x, int y, int z, int rowsNum, int colsNum, int depthNum) { return (x >= 0 && x < rowsNum && y >= 0 && y < colsNum && z >= 0 && z < depthNum); }

	
	static char*** copyMatrix(const char*** matrix, int rows, int cols, int depths);										/* returns a new copy of given matrix */

	
	static void deleteMatrix(const char*** matrix, int rows, int cols, int depths);											/* deletes char*** matrix */

	std::set<Coordinate> getNearbyCoordinates(int x, int y, int z)const;												    /* given a coordinate location in board, returns a set of surrondings coordinates of this point */

	static bool isPlayerShip(const int playerId, const char shipChar);														//todo: document

	char getCoordValue(const int x, const int y, const int z)const { if (isCoordianteInBoard(x, y, z)) return matrix[x][y][z]; else return ' '; }  //todo: document


private:

	static const int PLAYERID_A = 0;
	static const int PLAYERID_B = 1;
	static const char RUBBER_BOAT = 'B';
	static const char ROCKET_SHIP = 'P';
	static const char SUBMARINE = 'M';
	static const char DESTROYER = 'D';


	char*** matrix;
	int rows;
	int cols;
	int depth;
	bool isSuccCreated;


	static char*** AllocateNewMatrix(int rows, int cols, int depths);												 /* allocates new matrix in given size  */
	static void InitEmptyMatrix(char*** matrix, int rows, int cols, int depths);									 /* init already allocated matrix with ' ' */

	static bool IsShip(char ch);																					 /* given a char, checks if it a valid ship char*/
	static void CopyInputLineToBoard(char*** matrix, const std::string& line, int currRow, int cols, int depths);	 /* given a input line string, copies this line to the matrix board */



	/* function from the game manager of ex2 - I think that in this ex it should be here. TODO: still I need to think if it is true */



};