#include "ShipsBoard.h"

ShipsBoard::ShipsBoard(std::set<Ship*> ShipsSet, int Rows, int Cols, int Depth) : rows(Rows), cols(Cols), depth(Depth), shipsSet(ShipsSet), shipsBoardVec(Rows*Cols*Depth)
{
	/*shipsBoardVec entries already set to nullptr */
	
	// for each ship in the set. go overall its coordinates and put a pointer in the ships Board
	for (auto shipPtr : ShipsSet) {
		for (auto& part : shipPtr->body) {
			setShipPtrCoord(part.first.row, part.first.col, part.first.depth, shipPtr);
		}
	}
}

ShipsBoard::~ShipsBoard()
{
	for (auto ship : shipsSet)
	{
		delete ship;		/* TODO: Ofir:  "we want to convert pointer to be smart pointer" - we should not use new & delete */
	}
}

void ShipsBoard::setShipPtrCoord(int r, int c, int d, Ship* newShipPtr)
{
	if (!isCoordianteInShipBoard(r, c, d)) return;
	shipsBoardVec[BattleshipGameUtils::calcCoordIndex(r, c, d, rows, cols, depth)] = newShipPtr;
}

Ship* ShipsBoard::operator()(int r, int c, int d) const
{
	if(isCoordianteInShipBoard(r, c, d))
		return shipsBoardVec[BattleshipGameUtils::calcCoordIndex(r, c, d, rows, cols, depth)];
	else return nullptr;
}


//
//Ship * &ShipsBoard::operator()(int r, int c, int d)
//{
//	if (isCoordianteInShipBoard(r, c, d))
//		return shipsBoardVec[BattleshipGameUtils::calcCoordIndex(r, c, d, rows, cols, depth)];
//	else return nullptr;
//}
//
//
