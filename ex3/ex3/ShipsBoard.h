#pragma once
#include <vector>
#include "Ship.h"
#include "BattleshipGameUtils.h"


class ShipsBoard
{
	ShipsBoard() = delete;
	ShipsBoard(std::set<Ship*> ShipsSet, int Rows, int Cols, int Depth);

	~ShipsBoard();
	
	ShipsBoard(const ShipsBoard& otherBoard) = delete;														/* deletes copy constructor */
	ShipsBoard& operator=(const ShipsBoard& otherBoard) = delete;

	int Rows() const { return rows; }
	int Cols() const { return cols; }
	int Depth() const { return depth; }
	
	
	
	Ship* operator() (int r, int c, int d)const;
	

	

private:

	int rows;
	int cols;
	int depth;
	std::set<Ship*> shipsSet;
	std::vector<Ship*> shipsBoardVec;

	void setShipPtrCoord(int r, int c, int d, Ship* newShipPtr);

	/* checks if given coordinate is a valid location in board*/
	bool isCoordianteInShipBoard(int r, int c, int d)const { return BattleshipGameUtils::isCoordianteInBoard(r, c, d, rows, cols, depth); };
};
