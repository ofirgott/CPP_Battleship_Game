//#pragma once
//#include "testShipInProcess.h"
//
//int testShipInProcess::testShipInProcessConstructor()
//{
//	//test constructor;
//	ShipInProcess sizeOneShip(2, 2, 2);
//	if (!sizeOneShip.compareShipsFields(true, true, true, Coordinate(-1, -1, -1), Coordinate(2, 2, 2), createVector(), 1)) {
//		std::cout << "error in size 1 ship constructor " << std::endl;
//	}
//
//	std::cout << "constructor is Good!! " << std::endl;
//
//	return 0;
//
//}
//
//int testShipInProcess::testaddToSizeOneShip()
//{
//	int tmp = 0;
//	//ship 0
//	ShipInProcess shipTest(2, 2, 2);
//	tmp = shipTest.addToSizeOneShip(2, 2, 3);//depth
//	if (tmp != 1) {
//		std::cout << "error in addToSizeOneShip depth ret value" << std::endl;
//	}
//
//	if (!shipTest.compareShipsFields(false, false, true, Coordinate(2, 2, -1), Coordinate(2, 2, 2), createVector(2, 3), 2)) {
//		std::cout << "error in addToSizeOneShip depth comparing fields" << std::endl;
//	}
//
//	if (!ShipInProcess::testMinMaxCoors(shipTest, 3, 2)) {
//		std::cout << "error in addToSizeOneShip depth min max " << std::endl;
//	}
//
//	// ship 1 
//	ShipInProcess shipTest1(2, 2, 2);
//	tmp = shipTest1.addToSizeOneShip(2, 3, 2);//col
//	if (tmp != 1) {
//		std::cout << "error in addToSizeOneShip col ret value " << std::endl;
//	}
//	if (!shipTest1.compareShipsFields(false, true, false, Coordinate(2, -1, 2), Coordinate(2, 2, 2), createVector(2, 3), 2)) {
//		std::cout << "error in addToSizeOneShip col compare fields" << std::endl;
//	}
//
//	if (!ShipInProcess::testMinMaxCoors(shipTest1, 3, 2)) {
//		std::cout << "error in addToSizeOneShip col min max " << std::endl;
//	}
//
//	// ship 2 
//	ShipInProcess shipTest2(2, 2, 2);
//	tmp = shipTest2.addToSizeOneShip(1, 2, 2);//row
//	if (tmp != 1) {
//		std::cout << "error in addToSizeOneShip row ret val" << std::endl;
//	}
//	if (!shipTest2.compareShipsFields(true, false, false, Coordinate(-1, 2, 2), Coordinate(2, 2, 2), createVector(1, 2), 2)) {
//		std::cout << "error in addToSizeOneShip row compare fields" << std::endl;
//	}
//
//	if (!ShipInProcess::testMinMaxCoors(shipTest2, 2, 1)) {
//		std::cout << "error in addToSizeOneShip row min max " << std::endl;
//	}
//
//	//ship3
//	ShipInProcess shipTest3(2, 2, 2);
//	tmp = shipTest3.addToSizeOneShip(0, 2, 2);
//	if (tmp != -1) {
//		std::cout << "error in addToSizeOneShip ship3 " << std::endl;
//	}
//	if (!shipTest3.compareShipsFields(true, true, true, Coordinate(-1, -1, -1), Coordinate(2, 2, 2), createVector(), 1)) {
//		std::cout << "error in addToSizeOneShip shouldnt add ship3 " << std::endl;
//	}
//
//	//ship 4
//	ShipInProcess shipTest4(3, 3, 3);
//	tmp = shipTest4.addToSizeOneShip(3, 1, 3);//should not add
//	if (tmp != -1) {
//		std::cout << "error in addToSizeOneShip ship4 " << std::endl;
//	}
//
//	if (!shipTest4.compareShipsFields(true, true, true, Coordinate(-1, -1, -1), Coordinate(3, 3, 3), createVector(), 1)) {
//		std::cout << "error in addToSizeOneShip shouldnt add ship4 " << std::endl;
//	}
//
//	ShipInProcess shipTest5(3, 3, 3);
//	tmp = shipTest5.addToSizeOneShip(3, 3, 1);//should not add
//	if (tmp != -1) {
//		std::cout << "error in addToSizeOneShip ship5 " << std::endl;
//	}
//	if (!shipTest5.compareShipsFields(true, true, true, Coordinate(-1, -1, -1), Coordinate(3, 3, 3), createVector(), 1)) {
//		std::cout << "error in addToSizeOneShip shouldnt add ship5 " << std::endl;
//	}
//
//
//	ShipInProcess shipTest6(3, 3, 2);
//	tmp = shipTest6.addToSizeOneShip(3, 3, 5);//should not add
//	if (tmp != -1) {
//		std::cout << "error in addToSizeOneShip ship6 " << std::endl;
//	}
//	if (!shipTest6.compareShipsFields(true, true, true, Coordinate(-1, -1, -1), Coordinate(3, 3, 2), createVector(), 1)) {
//		std::cout << "error in addToSizeOneShip shouldnt add ship6 " << std::endl;
//	}
//
//	ShipInProcess shipTest7(3, 3, 2);
//	tmp = shipTest7.addToSizeOneShip(4, 0, 5);//should not add
//	if (tmp != -1) {
//		std::cout << "error in addToSizeOneShip ship7 " << std::endl;
//	}
//	if (!shipTest7.compareShipsFields(true, true, true, Coordinate(-1, -1, -1), Coordinate(3, 3, 2), createVector(), 1)) {
//		std::cout << "error in addToSizeOneShip shouldnt add ship7 " << std::endl;
//	}
//
//	std::cout << "addToSizeOneShip done!" << std::endl;
//	return 0;
//}
//
//std::vector<int> testShipInProcess::createVector(int a0, int a1, int a2, int a3, int a4, int a5, int a6)
//{
//	std::vector<int> vic;
//
//	if (a0 != -1) {
//		vic.push_back(a0);
//	}
//	if (a1 != -1) {
//		vic.push_back(a1);
//	}
//	if (a2 != -1) {
//		vic.push_back(a2);
//	}
//	if (a3 != -1) {
//		vic.push_back(a3);
//	}
//	if (a4 != -1) {
//		vic.push_back(a4);
//	}
//	if (a5 != -1) {
//		vic.push_back(a5);
//	}
//	if (a6 != -1) {
//		vic.push_back(a6);
//	}
//	return vic;
//}
//
//int testShipInProcess::testisPartOfShip()
//{
//	ShipInProcess shipTest(-1, -1, -1);
//
//	shipTest.setShipsFields(true, false, false, Coordinate(2, 1, 4), Coordinate(-1, 1, 4), createVector(2, 3, 4, 5), 4);
//	if (!shipTest.isPartOfShip(2, 1, 4)) {
//		std::cout << "error in is part of ship " << "2,1,4" << std::endl;
//	}
//	if (!shipTest.isPartOfShip(3, 1, 4)) {
//		std::cout << "error in is part of ship " << "3,1,4" << std::endl;
//	}
//	if (!shipTest.isPartOfShip(4, 1, 4)) {
//		std::cout << "error in is part of ship " << "4,1,4" << std::endl;
//	}
//	if (!shipTest.isPartOfShip(5, 1, 4)) {
//		std::cout << "error in is part of ship " << "5,1,4" << std::endl;
//	}
//	// shouldnt be part of ship 
//	if (shipTest.isPartOfShip(6, 1, 4)) {
//		std::cout << "error in is part of ship " << "6,1,4" << std::endl;
//	}
//	if (shipTest.isPartOfShip(1, 1, 4)) {
//		std::cout << "error in is part of ship " << "1,1,4" << std::endl;
//	}
//	if (shipTest.isPartOfShip(5, 10, 4)) {
//		std::cout << "error in is part of ship " << "5,10,4" << std::endl;
//	}
//
//	if (shipTest.isPartOfShip(0, 0, 0)) {
//		std::cout << "error in is part of ship " << "0,0,0" << std::endl;
//	}
//	if (shipTest.isPartOfShip(5, 2, 4)) {
//		std::cout << "error in is part of ship " << "5,2,4" << std::endl;
//	}
//	if (shipTest.isPartOfShip(5, 1, 5)) {
//		std::cout << "error in is part of ship " << "5,1,5" << std::endl;
//	}
//	std::cout << "ispartOfship isDone !!!" << std::endl;
//	return 0;
//}
//
//int testShipInProcess::testaddCoordinate()
//{
//
//
//	//static bool compareShipsFields(ShipInProcess& shipToTest, bool Vertical, bool Horizontal, bool Dimentional,
//	//	Coordinate consCoors, Coordinate firstCoor, std::vector<int> incremtCoors, int Size)
//
//	//good entery
//	{
//		ShipInProcess shipTest4(-1, -1, -1);
//		shipTest4.setShipsFields(true, false, false, Coordinate(2, 1, 2), Coordinate(-1, 1, 2), createVector(2, 3, 4, 5), 4);
//
//		int res = shipTest4.addCoordinate(6, 1, 2);
//		if (res != 1) {
//			std::cout << "error in testaddCoordinate 6,1,2 retval" << std::endl;
//		}
//		if (!shipTest4.compareShipsFields(true, false, false, Coordinate(-1, 1, 2), Coordinate(2, 1, 2), createVector(2, 3, 4, 5, 6), 5)) {
//			std::cout << "error in testaddCoordinate 6,1,2 compare" << std::endl;
//		}
//
//	}
//	//not good
//	{
//		ShipInProcess shipTest1(-1, -1, -1);
//		shipTest1.setShipsFields(true, false, false, Coordinate(2, 1, 2), Coordinate(-1, 1, 2), createVector(2, 3, 4, 5), 4);
//
//		int res = shipTest1.addCoordinate(7, 1, 2);
//		if (res != -1) {
//			std::cout << "error in testaddCoordinate 7,1,2 retval" << std::endl;
//		}
//
//		if (!shipTest1.compareShipsFields(true, false, false, Coordinate(-1, 1, 2), Coordinate(2, 1, 2), createVector(2, 3, 4, 5), 4)) {
//			std::cout << "error in testaddCoordinate 7,1,2 compare" << std::endl;
//		}
//	}
//	//was alredy in
//	{
//		ShipInProcess shipTest2(-1, -1, -1);
//		shipTest2.setShipsFields(true, false, false, Coordinate(2, 1, 2), Coordinate(-1, 1, 2), createVector(2, 3, 4, 5), 4);
//
//		int res = shipTest2.addCoordinate(2, 1, 2);
//		if (res != 0) {
//			std::cout << "error in testaddCoordinate 2,1,2 retval" << std::endl;
//		}
//		if (!shipTest2.compareShipsFields(true, false, false, Coordinate(-1, 1, 2), Coordinate(2, 1, 2), createVector(2, 3, 4, 5), 4)) {
//			std::cout << "error in testaddCoordinate 2,1,2 compare" << std::endl;
//		}
//	}
//	//was alredy in
//	{
//		ShipInProcess shipTest3(-1, -1, -1);
//		shipTest3.setShipsFields(true, false, false, Coordinate(2, 1, 2), Coordinate(-1, 1, 2), createVector(2, 3, 4, 5), 4);
//
//		int res = shipTest3.addCoordinate(3, 1, 2);
//		if (res != 0) {
//			std::cout << "error in testaddCoordinate 3,1,2 retval" << std::endl;
//		}
//		if (!shipTest3.compareShipsFields(true, false, false, Coordinate(-1, 1, 2), Coordinate(2, 1, 2), createVector(2, 3, 4, 5), 4)) {
//			std::cout << "error in testaddCoordinate 3,1,2 compare" << std::endl;
//		}
//	}
//
//	std::cout << "testaddCoordinate is Done!!!! " << std::endl;
//	return 0;
//}
//
//int testShipInProcess::testMegreShipsVectors()
//{
//	/* check horizontal !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
//	{ // add from above
//	  //Coordinate consCoor(5, -1, 1);
//		std::vector<int> originalVec = createVector(1, 2);
//		Coordinate coorToadd(5, 3, 1);
//		std::vector<int> expectedRes = createVector(1, 2, 3);
//
//		std::vector<int> actualRes = ShipInProcess::mergeShipsVectors(originalVec, coorToadd, true, false);
//		if (!ShipInProcess::compareVector(actualRes, expectedRes)) {
//			std::cout << "error in MegreShipsVectors ships coors should have been: <5,1,1>  <5,2,1>  <5,3,1>" << std::endl;
//			ShipInProcess::printVector(actualRes);
//		}
//	}
//
//	{ // add from buttom
//	  //Coordinate consCoor(5, -1, 1);
//		std::vector<int> originalVec = createVector(4, 5);
//		Coordinate coorToadd(5, 3, 1);
//		std::vector<int> expectedRes = createVector(3, 4, 5);
//
//		std::vector<int> actualRes = ShipInProcess::mergeShipsVectors(originalVec, coorToadd, true, false);
//		if (!ShipInProcess::compareVector(actualRes, expectedRes)) {
//			std::cout << " error in MegreShipsVectors ships coors should have been: <5,3,1>  <5,4,1>  <5,5,1>" << std::endl;
//			ShipInProcess::printVector(actualRes);
//		}
//	}
//
//	{ // souldnt add from above
//	  //Coordinate consCoor(5, -1, 1);
//		std::vector<int> originalVec = createVector(1, 2);
//		Coordinate coorToadd(5, 5, 1);
//		std::vector<int> expectedRes = createVector(1, 2);
//
//		std::vector<int> actualRes = ShipInProcess::mergeShipsVectors(originalVec, coorToadd, true, false);
//		if (!ShipInProcess::compareVector(actualRes, expectedRes)) {
//			std::cout << " error in MegreShipsVectors ships coors should have been: <5,1,1>  <5,2,1>" << std::endl;
//			ShipInProcess::printVector(actualRes);
//		}
//	}
//
//	{ //shoudnt add from buttom
//	  //Coordinate consCoor(5, -1, 1);
//		std::vector<int> originalVec = createVector(1, 2);
//		Coordinate coorToadd(5, -1, 1);
//		std::vector<int> expectedRes = createVector(1, 2);
//
//		std::vector<int> actualRes = ShipInProcess::mergeShipsVectors(originalVec, coorToadd, true, false);
//		if (!ShipInProcess::compareVector(actualRes, expectedRes)) {
//			std::cout << " error in MegreShipsVectors ships coors should have been: <5,1,1>  <5,2,1>" << std::endl;
//			ShipInProcess::printVector(actualRes);
//		}
//	}
//
//
//	/* check vertical !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
//	{ //add from above
//	  //Coordinate consCoor(-1, 5, 1);
//		std::vector<int> originalVec = createVector(1, 2);
//		Coordinate coorToadd(3, 5, 1);
//		std::vector<int> expectedRes = createVector(1, 2, 3);
//
//		std::vector<int> actualRes = ShipInProcess::mergeShipsVectors(originalVec, coorToadd, false, true);
//		if (!ShipInProcess::compareVector(actualRes, expectedRes)) {
//			std::cout << " error in MegreShipsVectors ships coors should have been: <1,5,1>  <2,5,1> <3,5,1>" << std::endl;
//			ShipInProcess::printVector(actualRes);
//		}
//	}
//
//	{ //add from buttom
//	  //Coordinate consCoor(-1, 5, 1);
//		std::vector<int> originalVec = createVector(4, 5);
//		Coordinate coorToadd(3, 5, 1);
//		std::vector<int> expectedRes = createVector(3, 4, 5);
//
//		std::vector<int> actualRes = ShipInProcess::mergeShipsVectors(originalVec, coorToadd, false, true);
//		if (!ShipInProcess::compareVector(actualRes, expectedRes)) {
//			std::cout << " error in MegreShipsVectors ships coors should have been: <3,5,1>  <4,5,1> <5,5,1>" << std::endl;
//			ShipInProcess::printVector(actualRes);
//		}
//	}
//
//	{ //shouldnt add from buttom
//	  //Coordinate consCoor(-1, 5, 1);
//		std::vector<int> originalVec = createVector(1, 2);
//		Coordinate coorToadd(5, 5, 1);
//		std::vector<int> expectedRes = createVector(1, 2);
//
//		std::vector<int> actualRes = ShipInProcess::mergeShipsVectors(originalVec, coorToadd, false, true);
//		if (!ShipInProcess::compareVector(actualRes, expectedRes)) {
//			std::cout << " error in MegreShipsVectors ships coors should have been: <1,5,1>  <2,5,1> " << std::endl;
//			ShipInProcess::printVector(actualRes);
//		}
//	}
//
//	{ //shouldnt add from buttom
//	  //Coordinate consCoor(-1, 5, 1);
//		std::vector<int> originalVec = createVector(1, 2);
//		Coordinate coorToadd(-1, 5, 1);
//		std::vector<int> expectedRes = createVector(1, 2);
//
//		std::vector<int> actualRes = ShipInProcess::mergeShipsVectors(originalVec, coorToadd, false, true);
//		if (!ShipInProcess::compareVector(actualRes, expectedRes)) {
//			std::cout << " error in MegreShipsVectors ships coors should have been: <1,5,1>  <2,5,1> " << std::endl;
//			ShipInProcess::printVector(actualRes);
//		}
//	}
//
//	/* check dimentional !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
//	{ //add from above
//	  //Coordinate consCoor(5, 1 , -1);
//		std::vector<int> originalVec = createVector(1, 2);
//		Coordinate coorToadd(5, 1, 3);
//		std::vector<int> expectedRes = createVector(1, 2, 3);
//
//		std::vector<int> actualRes = ShipInProcess::mergeShipsVectors(originalVec, coorToadd, false, false);
//		if (!ShipInProcess::compareVector(actualRes, expectedRes)) {
//			std::cout << " error in MegreShipsVectors ships coors should have been: <5,1,1>  <5,1,2> <5,1,3>" << std::endl;
//			ShipInProcess::printVector(actualRes);
//		}
//	}
//
//	{ //add from buttom
//	  //Coordinate consCoor(5,1,-1);
//		std::vector<int> originalVec = createVector(4, 5);
//		Coordinate coorToadd(5, 1, 3);
//		std::vector<int> expectedRes = createVector(3, 4, 5);
//
//		std::vector<int> actualRes = ShipInProcess::mergeShipsVectors(originalVec, coorToadd, false, false);
//		if (!ShipInProcess::compareVector(actualRes, expectedRes)) {
//			std::cout << " error in MegreShipsVectors ships coors should have been: <5,1,3>  <5,1,4> <5,1,4>" << std::endl;
//			ShipInProcess::printVector(actualRes);
//		}
//	}
//
//	{ //shouldnt add from buttom
//	  //Coordinate consCoor(5,1,-1);
//		std::vector<int> originalVec = createVector(1, 2);
//		Coordinate coorToadd(5, 1, 4);
//		std::vector<int> expectedRes = createVector(1, 2);
//
//		std::vector<int> actualRes = ShipInProcess::mergeShipsVectors(originalVec, coorToadd, false, false);
//		if (!ShipInProcess::compareVector(actualRes, expectedRes)) {
//			std::cout << " error in MegreShipsVectors ships coors should have been: <5,1,1>  <5,1,2> " << std::endl;
//			ShipInProcess::printVector(actualRes);
//		}
//	}
//
//	{ //shouldnt add from buttom
//	  //Coordinate consCoor(5,1,-1);
//		std::vector<int> originalVec = createVector(1, 2);
//		Coordinate coorToadd(5, 1, -1);
//		std::vector<int> expectedRes = createVector(1, 2);
//
//		std::vector<int> actualRes = ShipInProcess::mergeShipsVectors(originalVec, coorToadd, false, false);
//		if (!ShipInProcess::compareVector(actualRes, expectedRes)) {
//			std::cout << " error in MegreShipsVectors ships coors should have been: <5,1,1>  <5,1,2> " << std::endl;
//			ShipInProcess::printVector(actualRes);
//		}
//	}
//
//	std::cout << "testMegreShipsVectors is Done !!!!!!!!!!!!!!" << std::endl;
//	return 1;
//}
//
//int testShipInProcess::testmegreShipsInProcess()
//{
//
//	{// many coors to one coor 
//		ShipInProcess originShip(2, 2, 2);
//		originShip.addCoordinate(2, 2, 3);
//		originShip.addCoordinate(2, 2, 4);
//		ShipInProcess secondShip(2, 2, 5);
//
//		originShip.megreShipsInProcess(secondShip);
//		if (!originShip.compareShipsFields(false, false, true, Coordinate(2, 2, -1), Coordinate(2, 2, 2), createVector(2, 3, 4, 5), 4)) {
//			std::cout << "ships coors should have been : <2,2,2> <2,2,3> <2,2,4> <2,2,5> 1" << std::endl;
//		}
//	}
//
//	{ //one to many
//		ShipInProcess originShip(2, 2, 5);
//		ShipInProcess secondShip(2, 2, 2);
//		secondShip.addCoordinate(2, 2, 3);
//		secondShip.addCoordinate(2, 2, 4);
//
//		originShip.megreShipsInProcess(secondShip);
//		if (!originShip.compareShipsFields(false, false, true, Coordinate(2, 2, -1), Coordinate(2, 2, 5), createVector(2, 3, 4, 5), 4)) {
//			std::cout << "ships coors should have been : <2,2,2> <2,2,3> <2,2,4> <2,2,5> 2" << std::endl;
//		}
//	}
//
//	{ //many to many
//		ShipInProcess originShip(2, 2, 2);
//		originShip.addCoordinate(2, 2, 3);
//		originShip.addCoordinate(2, 2, 4);
//
//		ShipInProcess secondShip(2, 2, 5);
//		secondShip.addCoordinate(2, 2, 6);
//		secondShip.addCoordinate(2, 2, 7);
//
//		originShip.megreShipsInProcess(secondShip);
//		if (!originShip.compareShipsFields(false, false, true, Coordinate(2, 2, -1), Coordinate(2, 2, 2), createVector(2, 3, 4, 5, 6, 7), 6)) {
//			std::cout << "ships coors should have been : <2,2,2> <2,2,3> <2,2,4> <2,2,5> <2,2,5> <2,2,6> <2,2,7> 3" << std::endl;
//		}
//	}
//
//	{ //one to one
//		ShipInProcess originShip(2, 2, 6);
//		ShipInProcess secondShip(2, 2, 7);
//
//		originShip.megreShipsInProcess(secondShip);
//		if (!originShip.compareShipsFields(false, false, true, Coordinate(2, 2, -1), Coordinate(2, 2, 6), createVector(6, 7), 2)) {
//			std::cout << "ships coors should have been : <2,2,6> <2,2,7> 4" << std::endl;
//		}
//	}
//
//	std::cout << "testmegreShipsInProcess is Done!!!!!" << std::endl;
//	return 0;
//}
//
//int testShipInProcess::testupdateInnerFields()
//{
//	//	updateInnerFields(bool vertical, bool horizontal, bool dimensional, int firstCoor, int secondCoor);
//
//	ShipInProcess shipTest(1, 5, 9);
//	shipTest.updateInnerFields(false, true, false, 5, 6);
//
//	if (!shipTest.compareShipsFields(false, true, false, Coordinate(1, -1, 9), Coordinate(1, 5, 9), createVector(5, 6), 2)) {
//		std::cout << "error in updateInnerFields" << std::endl;
//	}
//	std::cout << "testupdateInnerFields is Done!!!!!" << std::endl;
//	return 0;
//}
