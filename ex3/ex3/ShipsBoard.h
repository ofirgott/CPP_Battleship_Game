#pragma once
#include <vector>
#include "Ship.h"
#include "BattleshipGameUtils.h"

/* Created for the (single) game manager */

class ShipsBoard
{
public:
	ShipsBoard() : rows(0), cols(0), depth(0) {}
	ShipsBoard(std::list<Ship>& ShipsSet, int Rows, int Cols, int Depth);

	~ShipsBoard() = default;																		/* shipsBoardVec pointers will be deleted automatically when shipList will destruct	*/
	
	ShipsBoard(const ShipsBoard& otherBoard) = delete;												/* deletes copy constructor */
	ShipsBoard& operator=(const ShipsBoard& otherBoard) = delete;									/* deletes copy assignment */

	ShipsBoard(ShipsBoard&& otherBoard) noexcept;													/* move constructor */
	ShipsBoard& operator=(ShipsBoard&& otherBoard) noexcept;										/* move assignment */

	int Rows() const { return rows; }
	int Cols() const { return cols; }
	int Depth() const { return depth; }
	
	
	Ship* operator() (int r, int c, int d)const;
	/* checks if given coordinate is a valid location in board*/
	bool isCoordianteInShipBoard(int r, int c, int d)const { return BattleshipGameUtils::isCoordianteInBoard(r, c, d, rows, cols, depth); };

private:

	int rows;
	int cols;
	int depth;
	std::list<Ship> shipsList;																		/* to maintain the ships objects*/
	std::vector<Ship*> shipsBoardVec;																/* 1D vector that represents 3D board of pointers to ships objects*/

	void setShipPtrCoord(int r, int c, int d, Ship* newShip);

};
