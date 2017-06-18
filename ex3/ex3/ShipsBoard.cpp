#include "ShipsBoard.h"


ShipsBoard::ShipsBoard( std::list<Ship>& inputShipsList, int Rows, int Cols, int Depth) : rows(Rows), cols(Cols), depth(Depth), shipsList(std::move(inputShipsList)), shipsBoardVec(Rows*Cols*Depth)
{
	/*shipsBoardVec entries already set to nullptr */
	
	/* for each ship in the list, go over all its coordinates and put a pointer in the ships Board */
	for (auto &ship : shipsList) {
		for (auto& part : ship.body) {
			setShipPtrCoord(part.first.row, part.first.col, part.first.depth, &ship);
		}
	}
}


ShipsBoard::ShipsBoard(ShipsBoard && otherBoard) noexcept : rows(otherBoard.rows), cols(otherBoard.cols), depth(otherBoard.depth) 
{
	/* steal the ships objects and the pointers to us */
	std::swap(shipsBoardVec, otherBoard.shipsBoardVec);
	std::swap(shipsList, otherBoard.shipsList);
}

ShipsBoard & ShipsBoard::operator=(ShipsBoard && otherBoard) noexcept
{
	rows = otherBoard.rows;
	cols = otherBoard.cols;
	depth = otherBoard.depth;
	
	/* steal the ships objects and the pointers to us */
	std::swap(shipsBoardVec, otherBoard.shipsBoardVec);
	std::swap(shipsList, otherBoard.shipsList);

	return *this;
}


void ShipsBoard::setShipPtrCoord(int r, int c, int d, Ship* newShipPtr)
{

	if (!isCoordianteInShipBoard(r, c, d)) return;
	shipsBoardVec[BattleshipGameUtils::calcCoordIndex(r, c, d, rows, cols)] = newShipPtr;					/* assign ship pointer to the relevant coordinate in shipsBoardVec*/
}

/* for easy access */
Ship* ShipsBoard::operator()(int r, int c, int d) const
{
	if(isCoordianteInShipBoard(r, c, d))
		return shipsBoardVec[BattleshipGameUtils::calcCoordIndex(r, c, d, rows, cols)];
	else return nullptr;
}
