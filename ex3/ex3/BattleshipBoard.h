#pragma once
#include <set>
#include "IBattleshipGameAlgo.h"
#include <vector>
#include "BattleshipGameUtils.h"

class BattleshipBoard
{
public:
	BattleshipBoard() : rows(-1), cols(-1), depth(-1), isSuccCreated(false) {}								/* empty constructor */
	explicit BattleshipBoard(std::vector<char> board, int inputRows, int inputCols, int inputDepth);
	explicit BattleshipBoard(const std::string& boardPath);				
	explicit BattleshipBoard(const BoardData & boardData);													/* constructor for player BoardData type */
	
	~BattleshipBoard() = default;																			

	BattleshipBoard(const BattleshipBoard& otherBoard) = delete;											/* deletes copy constructor */
	BattleshipBoard& operator=(const BattleshipBoard& otherBoard) = delete;									/* deletes copy assignment */

	BattleshipBoard(BattleshipBoard&& otherBoard) noexcept;													/* move constructor */
	BattleshipBoard& operator=(BattleshipBoard&& otherBoard) noexcept;										/* move assignment */
	
	int getRows() const { return rows; }
	int getCols() const { return cols; }
	int getDepth() const { return depth; }

	bool isSuccessfullyCreated() const { return (rows > 0 && cols > 0 && depth > 0 && !boardVec.empty() && isSuccCreated); }

	/* given a player's board,
	returns set of pairs, which contains for each ship it's coordinates:
	for example: {<'m', {<1,2,1>,<1,3,1>}> , <'P', {<8,5,4> , <8,6,4> , <8,7,4>}> } */
	std::set<std::pair<char, std::set<Coordinate>>> ExtractShipsDetails()const;

	/* given a boardVec and specific coordintets and ship char, inserts to the set coordOfCurrentShip all coordinates of this current ship (recursive function) */
	static void getAllCurrShipCoords(std::vector<char> board, int r, int c, int d, char currShipChar, std::set<Coordinate>& coordOfCurrentShip, int boardRows, int boardCols, int boardDepth);

	/* checks if given coordinate is a valid location in board*/
	bool isCoordianteInBoard(int r, int c, int d)const { return BattleshipGameUtils::isCoordianteInBoard(r, c, d, rows, cols, depth); };
	
	/* given a coordinate location in board, returns a set of surrondings coordinates of this point */
	std::set<Coordinate> getNearbyCoordinates(Coordinate coord)const;		   

	/* given shipChar and playerId, check if the shipChar belongs to this player*/
	static bool isPlayerShip(const int playerId, const char shipChar);							

	/* getter for specific coord in board */
	char operator()(int r, int c, int d)const;		
	
	/* setter for specific coord in board */
	void setCoord(int r, int c, int d, char ch);	

	/* given set of shipsDetails, counts each ship type and update shipsCountsVec respectively */
	static void countShipsTypes(const std::set<std::pair<char, std::set<Coordinate>>>& allShipsDetails, std::vector<std::pair<int, int>>& shipsCountVec);
	
	/* checks if the matrix conatins adjacent ships, if so - prints relevant message to the log */
	bool CheckIfHasAdjacentShips() const;	
	

	/* given game mainBoard, update the two input sets with the ships details belongs to each player */
	void ExtractShipsDetailsOfGamePlayers(std::set<std::pair<char, std::set<Coordinate>>>& detailsPlayerA, std::set<std::pair<char, std::set<Coordinate>>>& detailsPlayerB)const;

	static const char BLANK_CHAR = ' ';

private:

	static const int PLAYERID_A = 0;
	static const int PLAYERID_B = 1;
	static const char RUBBER_BOAT = 'B';
	static const char ROCKET_SHIP = 'P';
	static const char SUBMARINE = 'M';
	static const char DESTROYER = 'D';
	static const char BOARD_DIM_DELIMITER = 'x';

	std::vector<char> boardVec;							/* we will represent this 3D board with 1D char vector */
	int rows;
	int cols;
	int depth;
	bool isSuccCreated;

	/* init Board vector with ' ' */
	static std::vector<char> InitNewEmptyBoardVector(int rows, int cols, int depths);					

	/* given a input line string, copies this line to the board */
	void CopyInputLineToBoard(const std::string& line, int currDepth, int currRow);	

	/* parse first row of board file - the dimensions row */
	bool parseBoardDimensions(std::string& line);		
	
	/* given a ship char, checks if it represents valid ship char in board */
	static bool IsShipCharInBoard(char ch);

};
