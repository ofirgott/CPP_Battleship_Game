#include "ShipsBoard.h"


ShipsBoard::ShipsBoard( std::list<Ship>& inputShipsList, int Rows, int Cols, int Depth) : rows(Rows), cols(Cols), depth(Depth), shipsList(std::move(inputShipsList)), shipsBoardVec(Rows*Cols*Depth)
{
	/*shipsBoardVec entries already set to nullptr */
	
	// for each ship in the set. go overall its coordinates and put a pointer in the ships Board
	for (auto &ship : shipsList) {
		for (auto& part : ship.body) {
			setShipPtrCoord(part.first.row, part.first.col, part.first.depth, &ship);
		}
	}
}

//ShipsBoard::~ShipsBoard()
//{
//	for (auto ship : shipsSet)
//	{
//		delete ship;		/* TODO: Ofir:  "we want to convert pointer to be smart pointer" - we should not use new & delete */
//	}
//}


ShipsBoard::ShipsBoard(ShipsBoard && otherBoard) noexcept : rows(otherBoard.rows), cols(otherBoard.cols), depth(otherBoard.depth) //shipsList(std::move(otherBoard.shipsList))
{
	std::swap(shipsBoardVec, otherBoard.shipsBoardVec);
	std::swap(shipsList, otherBoard.shipsList);
}

ShipsBoard & ShipsBoard::operator=(ShipsBoard && otherBoard) noexcept
{
	rows = otherBoard.rows;
	cols = otherBoard.cols;
	depth = otherBoard.depth;
	std::swap(shipsBoardVec, otherBoard.shipsBoardVec);
	std::swap(shipsList, otherBoard.shipsList);
	//foreach
	//std::swap(shipsBoardVec, otherBoard.shipsBoardVec);
	//for (auto &ship : shipsList) {
	////for (auto it = shipsList.begin(); it != shipsList.end(); ++it){
	//	for (auto &part : ship.body) {
	//		setShipPtrCoord(part.first.row, part.first.col, part.first.depth, ship);
	//	}
	//}
	return *this;
}


void ShipsBoard::setShipPtrCoord(int r, int c, int d, Ship* newShipPtr)
{
	if (!isCoordianteInShipBoard(r, c, d)) return;
	shipsBoardVec[BattleshipGameUtils::calcCoordIndex(r, c, d, rows, cols)] = newShipPtr;
}

Ship* ShipsBoard::operator()(int r, int c, int d) const
{
	if(isCoordianteInShipBoard(r, c, d))
		return shipsBoardVec[BattleshipGameUtils::calcCoordIndex(r, c, d, rows, cols)];
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
