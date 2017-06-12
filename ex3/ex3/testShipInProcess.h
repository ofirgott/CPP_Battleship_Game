#pragma once
#include "ShipInProcess.h"
#include  <iostream>;
#include <vector>

class testShipInProcess {
public:
	testShipInProcess() {};
	~testShipInProcess() {};

	// : isVertical(true), isHorizontal(true), isDimentional(true), constantCoors(-1, -1, -1), firstCoordinate(row, col, depth), shipSize(1) {}
	static int testShipInProcessConstructor();


	/* assumes the ship is of size 1, if belongs to the ship add and return 1, else return -1*/
	static int testaddToSizeOneShip();

	// create the vector a0,a1,a2,a3,a4
	static std::vector<int> createVector(int a0, int a1, int a2, int a3, int a4, int a5, int a6);

	/* return true if coordinate(row,col,depth) belongs to ship, elsereturn false*/
	static int testisPartOfShip();

    /* given Coordinate add it to the ship's internal representation if the coordinates
    belongs to this ship. return 1 if added Coordinate to the Ship, else return -1 */
	static int testaddCoordinate();

	// /* merge Ships Vectors, assumse mainVector size>1 */
	static int testMegreShipsVectors();
	
	//	/* given other ship that it's coordinates belong to this ship, add its details to this ship*/
	static int testmegreShipsInProcess();

	static int testupdateInnerFields();

};


//
//
//int main() {
//	testShipInProcess::testShipInProcessConstructor();
//	testShipInProcess::testaddToSizeOneShip();
//	testShipInProcess::testisPartOfShip();
//	testShipInProcess::testaddCoordinate();
//	testShipInProcess::testMegreShipsVectors();
//	testShipInProcess::testmegreShipsInProcess();
//	testShipInProcess::testupdateInnerFields();
//}