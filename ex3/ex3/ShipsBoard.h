#pragma once
#include <vector>
#include "Ship.h"
#include "BattleshipGameUtils.h"


class ShipsBoard
{
public:
	ShipsBoard() : rows(0), cols(0), depth(0) {}
	ShipsBoard(std::list<Ship>& ShipsSet, int Rows, int Cols, int Depth);

	~ShipsBoard() = default;
	
	ShipsBoard(const ShipsBoard& otherBoard) = delete;														/* deletes copy constructor */
	ShipsBoard& operator=(const ShipsBoard& otherBoard) = delete;

	ShipsBoard(ShipsBoard&& otherBoard) noexcept;													/* move constructor */
	ShipsBoard& operator=(ShipsBoard&& otherBoard) noexcept;										/* move assignment */

	int Rows() const { return rows; }
	int Cols() const { return cols; }
	int Depth() const { return depth; }
	
	//bool isSet()const { return rows > 0 && cols > 0 && depth > 0 && !shipsBoardVec.empty(); }
	
	Ship* operator() (int r, int c, int d)const;
	/* checks if given coordinate is a valid location in board*/
	bool isCoordianteInShipBoard(int r, int c, int d)const { return BattleshipGameUtils::isCoordianteInBoard(r, c, d, rows, cols, depth); };

private:

	int rows;
	int cols;
	int depth;
	std::list<Ship> shipsList;
	std::vector<Ship*> shipsBoardVec;

	void setShipPtrCoord(int r, int c, int d, Ship* newShip);

};
