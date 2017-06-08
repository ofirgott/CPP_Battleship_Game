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
	explicit BattleshipBoard(const BoardData & boardData);													/* constructor for player BoardData type */
	
	~BattleshipBoard() = default;																			

	//todo: check if we can delete the copy ctor
	
	
	BattleshipBoard(const BattleshipBoard& otherBoard);														/* copy constructor */
	BattleshipBoard& operator=(const BattleshipBoard& otherBoard) = delete;									/* delete copy assignment */

	BattleshipBoard(BattleshipBoard&& otherBoard) noexcept;													/* move constructor */
	BattleshipBoard& operator=(BattleshipBoard&& otherBoard) noexcept;										/* move assignment */
	

	

	int getRows() const { return rows; }
	int getCols() const { return cols; }
	int getDepth() const { return depth; }


	std::vector<char> createPlayerBoard(int playerID)const;															// todo: maybe we can delete this function
	bool isSuccessfullyCreated() const { return (rows > 0 && cols > 0 && depth > 0 && !boardVec.empty() && isSuccCreated); }

	bool CheckIfHasAdjacentShips() const;																			/* checks if the matrix conatins adjacent ships, if so - prints relevant message */

	static bool IsShipCharInBoard(char ch);


	/* given a player's matrix board,
	returns set of pairs, which contains for each ship it's coordinates:
	for example: {<'m', {<1,2,1>,<1,3,1>}> , <'P', {<8,5,4> , <8,6,4> , <8,7,4>}> } */
	std::set<std::pair<char, std::set<Coordinate>>> ExtractShipsDetails()const;

	/* given matrix board and specific coordintets and ship char, inserts to the set coordOfCurrentShip all coordinates of this current ship (recursive function) */
	static void getAllCurrShipCoords(std::vector<char> board, int r, int c, int d, char currShipChar, std::set<Coordinate>& coordOfCurrentShip, int boardRows, int boardCols, int boardDepth);

	/* checks if given coordinate is a valid location in board*/
	bool isCoordianteInBoard(int r, int c, int d)const { return isCoordianteInBoard(r, c, d, rows, cols, depth); };
	static bool isCoordianteInBoard(int r, int c, int d, int rowsNum, int colsNum, int depthNum) { return (r >= 0 && r < rowsNum && c >= 0 && c < colsNum && d >= 0 && d < depthNum); }


	std::set<Coordinate> getNearbyCoordinates(Coordinate coord)const;												    /* given a coordinate location in board, returns a set of surrondings coordinates of this point */

	static bool isPlayerShip(const int playerId, const char shipChar);														//todo: document



	char operator()(int r, int c, int d)const;		/* getter */

	void setCoord(int r, int c, int d, char ch);		/* setter */

														//char getCoordValue(const int r, const int c, const int d)const { if (isCoordianteInBoard(r, c, d)) return (*this)(r, c, d); else return ' '; }  //todo: document and adjust to the board interface
														//static char getBoardCoord(std::vector<char> boardVector, int r, int c, int d, int rowsNum, int colsNum, int depthNum);


														/* TODO: need to check this calculation if it is true: http://www.cplusplus.com/forum/general/137677/, https://stackoverflow.com/questions/10238699/dynamically-allocating-3d-array, https://stackoverflow.com/questions/2178909/how-to-initialize-3d-array-in-c */
	static int calcCoordIndex(int r, int c, int d, int boardRows, int boardCols, int boardDepth) { return r + c * boardCols + d * boardCols * boardRows; }

	static void countShipsTypes(const std::set<std::pair<char, std::set<Coordinate>>>& allShipsDetails, std::vector<std::pair<int, int>>& shipsCountVec);

	static const char BLANK_CHAR = ' ';

private:

	static const int PLAYERID_A = 0;
	static const int PLAYERID_B = 1;
	static const char RUBBER_BOAT = 'B';
	static const char ROCKET_SHIP = 'P';
	static const char SUBMARINE = 'M';
	static const char DESTROYER = 'D';
	static const char BOARD_DIM_DELIMITER = 'x';


	std::vector<char> boardVec;
	int rows;
	int cols;
	int depth;
	bool isSuccCreated;


	static std::vector<char> InitNewEmptyBoardVector(int rows, int cols, int depths);					/* init already allocated matrix with ' ' */

	void CopyInputLineToBoard(const std::string& line, int currDepth, int currRow);	 /* given a input line string, copies this line to the board */

	/**
	 * \brief 
	 * \param line 
	 * \return 
	 */
	bool parseBoardDimensions(const std::string& line);					

};
