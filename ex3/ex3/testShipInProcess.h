//#pragma once
//#include"ShipInProcess.h"
//#include  <iostream>;
//
//class testShipInProcess {
//public:
//	testShipInProcess() {};
//	~testShipInProcess() {};
//
//	static void printVector(std::vector<int> vec, int consCoor) {
//		std::cout << "vector coors are";
//		std::cout << "const is: " << consCoor << " incremental are: ";
//		for (int i = 0; i < vec.size(); i++)
//		{
//			std::cout << vec.at(i);
//		}
//		std::cout << std::endl;
//	}
//
//	static int testaddToSizeOneShip() {
//
//		ShipInProcess shipTest(2, 2);
//		shipTest.addToSizeOneShip(2, 3);//right
//		std::cout << "ships max shold be :  3" << std::endl;
//		std::cout << "ships coors are : " << std::endl;
//		std::cout << "right add " << shipTest.getMaxCoor() << std::endl;
//
//		ShipInProcess shipTest1(2, 2);
//		shipTest1.addToSizeOneShip(2, 1);//left
//		std::cout << "ships max shold be :  1" << std::endl;
//		std::cout << "ships coors are : " << std::endl;
//		std::cout << "left add " << shipTest1.getMinCoor() << std::endl;
//
//		ShipInProcess shipTest2(2, 2);
//		shipTest2.addToSizeOneShip(1, 2);//up
//		std::cout << "ships max shold be :  1" << std::endl;
//		std::cout << "ships coors are : " << std::endl;
//		std::cout << "up add " << shipTest2.getMinCoor() << std::endl;
//
//		ShipInProcess shipTest3(2, 2);
//		shipTest3.addToSizeOneShip(3, 2);//down
//		std::cout << "ships max shold be :  3" << std::endl;
//		std::cout << "ships coors are : " << std::endl;
//		std::cout << "down add " << shipTest3.getMaxCoor() << std::endl;
//
//
//		ShipInProcess shipTest4(3, 3);
//		shipTest4.addToSizeOneShip(1, 3);//should not add
//		std::cout << "pair should be : 3,3 ";
//		std::cout << " pair is: " << shipTest4.firstPair.first << shipTest4.firstPair.second;
//		std::cout << " shipSize " << shipTest4.shipSize << std::endl;
//
//
//		ShipInProcess shipTest5(3, 3);
//		shipTest5.addToSizeOneShip(3, 1);//should not add
//		std::cout << "pair should be : 3,3 ";
//		std::cout << " pair is: " << shipTest5.firstPair.first << shipTest5.firstPair.second;
//		std::cout << " shipSize " << shipTest5.shipSize << std::endl;
//
//
//		ShipInProcess shipTest6(3, 3);
//		shipTest6.addToSizeOneShip(3, 5);//should not add
//		std::cout << "pair should be : 3,3 ";
//		std::cout << " pair is: " << shipTest6.firstPair.first << shipTest6.firstPair.second;
//		std::cout << " shipSize " << shipTest6.shipSize << std::endl;
//
//
//		ShipInProcess shipTest7(3, 3);
//		shipTest7.addToSizeOneShip(5, 3);//should not add
//		std::cout << "pair should be : 3,3 ";
//		std::cout << " pair is: " << shipTest7.firstPair.first << shipTest7.firstPair.second;
//		std::cout << " shipSize " << shipTest7.shipSize << std::endl;
//
//
//		return 0;
//	}
//
//	static int testisPartOfShip() {
//		ShipInProcess shipTest(2, 2);
//		shipTest.isHorizontal = true;
//		shipTest.isVertical = false;
//		shipTest.constantCoor = 2;
//		shipTest.shipSize = 4;
//		shipTest.incrementalCoors.insert(shipTest.incrementalCoors.end(), 2);
//		shipTest.incrementalCoors.insert(shipTest.incrementalCoors.end(), 3);
//		shipTest.incrementalCoors.insert(shipTest.incrementalCoors.end(), 4);
//		shipTest.incrementalCoors.insert(shipTest.incrementalCoors.end(), 5);
//
//
//		std::cout << "should be true " << shipTest.isPartOfShip(2, 4) << std::endl;
//		std::cout << "should be true " << shipTest.isPartOfShip(2, 5) << std::endl;
//		std::cout << "should be true " << shipTest.isPartOfShip(2, 2) << std::endl;
//
//		std::cout << "should be false " << shipTest.isPartOfShip(2, 6) << std::endl;
//		std::cout << "should be false " << shipTest.isPartOfShip(1, 2) << std::endl;
//		return 0;
//	}
//
//	static int testaddCoordinate() {
//		ShipInProcess shipTest(2, 2);
//		shipTest.isHorizontal = true;
//		shipTest.isVertical = false;
//		shipTest.constantCoor = 2;
//		shipTest.shipSize = 4;
//		shipTest.incrementalCoors.insert(shipTest.incrementalCoors.end(), 2);
//		shipTest.incrementalCoors.insert(shipTest.incrementalCoors.end(), 3);
//		shipTest.incrementalCoors.insert(shipTest.incrementalCoors.end(), 4);
//		shipTest.incrementalCoors.insert(shipTest.incrementalCoors.end(), 5);
//
//
//		//good entery
//		int res = shipTest.addCoordinate(2, 6);
//		std::cout << "should be true for (2,6) " << shipTest.isPartOfShip(2, 6) << " res should be 1 got in" << res << std::endl;
//		//not good
//		res = shipTest.addCoordinate(2, 8);
//		std::cout << "should be falue for(2,8) " << shipTest.isPartOfShip(2, 8) << " res should be -1 didnt get in" << res << std::endl;
//		//was alredy in
//		res = shipTest.addCoordinate(2, 2);
//		std::cout << "should be true for (2,2) " << shipTest.isPartOfShip(2, 2) << " res should be 0 alredy in" << res << std::endl;
//		return 0;
//	}
//
//
//	static int testMegreShipsVectors()
//	{
//		std::vector<int> vec;
//		std::pair<int, int> coor;
//		int consCoor = 5;
//
//
//		/* check vorizontal !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1*/
//		vec.push_back(1);
//		vec.push_back(2);
//		coor = std::make_pair(consCoor, 3);
//		// test <1,2> +  3  - horizintal
//		// ships coors shold be : <5 , 1>  <5,2> , <5, 3>
//
//		vec = ShipInProcess::mergeShipsVectors(vec, coor, false);
//		std::cout << "ships coors shold be : <consCoor, 1>  <consCoor, 2>, <consCoor, 3>" << std::endl;
//		std::cout << "ships coors are : ";
//		for (int i = 0; i < vec.size(); i++)
//		{
//			std::cout << "<" << consCoor << ',' << vec.at(i) << "> ";
//		}
//		vec.clear();
//		std::cout << std::endl;
//
//		// insert from left horizontal
//		vec.push_back(4);
//		vec.push_back(5);
//		coor = std::make_pair(consCoor, 3);
//
//		// ships coors shold be : <5 , 3>  <5,4> , <5, 5>
//		vec = ShipInProcess::mergeShipsVectors(vec, coor, false);
//		std::cout << "ships coors shold be : <consCoor, 3>  <consCoor, 4>, <consCoor, 5>" << std::endl;
//		std::cout << "ships coors are : ";
//		for (int i = 0; i < vec.size(); i++)
//		{
//			std::cout << "<" << consCoor << ',' << vec.at(i) << "> ";
//		}
//		vec.clear();
//		std::cout << std::endl;
//
//
//		vec.push_back(1);
//		vec.push_back(2);
//		coor = std::make_pair(consCoor, 5);
//		// shouldnt add not not oncremental / coors
//		// ships coors shold be : <5 , 1>  <5,2> 
//		vec = ShipInProcess::mergeShipsVectors(vec, coor, false);
//		std::cout << "ships coors shold be : <consCoor, 1>  <consCoor, 2>" << std::endl;
//		std::cout << "ships coors are : ";
//		for (int i = 0; i < vec.size(); i++)
//		{
//			std::cout << "<" << consCoor << ',' << vec.at(i) << "> ";
//		}
//		vec.clear();
//		std::cout << std::endl;
//
//		vec.push_back(1);
//		vec.push_back(2);
//		coor = std::make_pair(consCoor, -1);
//		// shouldnt add not not oncremental / coors
//		// ships coors shold be : <5 , 1>  <5,2> 
//		vec = ShipInProcess::mergeShipsVectors(vec, coor, false);
//		std::cout << "ships coors shold be : <consCoor, 1>  <consCoor, 2>" << std::endl;
//		std::cout << "ships coors are : ";
//		for (int i = 0; i < vec.size(); i++)
//		{
//			std::cout << "<" << consCoor << ',' << vec.at(i) << "> ";
//		}
//		vec.clear();
//		std::cout << std::endl;
//
//
//		/* check vertical !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1*/
//		vec.push_back(1);
//		vec.push_back(2);
//		coor = std::make_pair(3, consCoor);
//
//		vec = ShipInProcess::mergeShipsVectors(vec, coor, true);
//		std::cout << "ships coors shold be : <1, consCoor>  < 2, consCoor>, <3, consCoor>" << std::endl;
//		std::cout << "ships coors are : ";
//		for (int i = 0; i < vec.size(); i++)
//		{
//			std::cout << "<" << vec.at(i) << ',' << consCoor << "> ";
//		}
//		vec.clear();
//		std::cout << std::endl;
//
//		// insert from left horizontal
//		vec.push_back(4);
//		vec.push_back(5);
//		coor = std::make_pair(3, consCoor);
//
//		vec = ShipInProcess::mergeShipsVectors(vec, coor, true);
//		std::cout << "ships coors shold be : <3, consCoor>  <4, consCoor>, <5 , consCoor>";
//		std::cout << "ships coors are : ";
//		for (int i = 0; i < vec.size(); i++)
//		{
//			std::cout << "<" << vec.at(i) << ',' << consCoor << "> ";
//		}
//		vec.clear();
//		std::cout << std::endl;
//
//
//		vec.push_back(1);
//		vec.push_back(2);
//		coor = std::make_pair(5, consCoor);
//		vec = ShipInProcess::mergeShipsVectors(vec, coor, true);
//		std::cout << "ships coors shold be : <consCoor, 1>  <consCoor, 2>" << std::endl;
//		std::cout << "ships coors are : ";
//		for (int i = 0; i < vec.size(); i++)
//		{
//			std::cout << "<" << vec.at(i) << ',' << consCoor << "> ";
//		}
//		vec.clear();
//		std::cout << std::endl;
//
//		vec.push_back(1);
//		vec.push_back(2);
//		coor = std::make_pair(-1, consCoor);
//		// shouldnt add not not oncremental / coors
//		vec = ShipInProcess::mergeShipsVectors(vec, coor, true);
//		std::cout << "ships coors shold be : <consCoor, 1>  <consCoor, 2>";
//		std::cout << "ships coors are : ";
//		for (int i = 0; i < vec.size(); i++)
//		{
//			std::cout << "<" << vec.at(i) << ',' << consCoor << "> ";
//		}
//		vec.clear();
//		std::cout << std::endl;
//		return 1;
//	}
//
//
//	static int testmegreShipsInProcess() {
//		ShipInProcess shipTest(2, 2);
//		shipTest.addCoordinate(2, 3);
//		shipTest.addCoordinate(2, 4);
//		ShipInProcess shipTest1(2, 5);
//
//		ShipInProcess shipTest2(2, 5);
//		ShipInProcess shipTest3(2, 2);
//		shipTest3.addCoordinate(2, 3);
//		shipTest3.addCoordinate(2, 4);
//
//		ShipInProcess shipTest4(2, 2);
//		shipTest4.addCoordinate(2, 3);
//		shipTest4.addCoordinate(2, 4);
//		ShipInProcess shipTest5(2, 5);
//		shipTest5.addCoordinate(2, 6);
//		shipTest5.addCoordinate(2, 7);
//
//
//		ShipInProcess shipTest6(2, 6);
//		ShipInProcess shipTest7(2, 7);
//
//
//
//		shipTest.megreShipsInProcess(shipTest1);// this ship-many to oter ship 1size 
//		std::cout << "ships coors shold be : <2, 2>  <2, 3>	<2, 4>	<2, 5>" << std::endl;
//		std::cout << "ships coors are : ";
//		for (int i = 0; i < shipTest.incrementalCoors.size(); i++)
//		{
//			std::cout << "<" << shipTest.constantCoor << ',' << shipTest.incrementalCoors.at(i) << "> ";
//		}
//		std::cout << std::endl;
//
//		shipTest2.megreShipsInProcess(shipTest3);// this ship-1size to oter ship many
//		std::cout << "ships coors shold be : <2, 2>  <2, 3>	<2, 4>	<2, 5>" << std::endl;
//		std::cout << "ships coors are : ";
//		for (int i = 0; i < shipTest2.incrementalCoors.size(); i++)
//		{
//			std::cout << "<" << shipTest2.constantCoor << ',' << shipTest2.incrementalCoors.at(i) << "> ";
//		}
//		std::cout << std::endl;
//
//		shipTest4.megreShipsInProcess(shipTest5);// this ship-many to oter ship many
//		std::cout << "ships coors shold be : <2, 2>  <2, 3>	<2, 4>	<2, 5>	<2, 6>	<2, 7>" << std::endl;
//		std::cout << "ships coors are : ";
//		for (int i = 0; i < shipTest4.incrementalCoors.size(); i++)
//		{
//			std::cout << "<" << shipTest4.constantCoor << ',' << shipTest4.incrementalCoors.at(i) << "> ";
//		}
//		std::cout << std::endl;
//
//		shipTest6.megreShipsInProcess(shipTest7);// this ship-1size to oter ship 1size
//		std::cout << "ships coors shold be : <2, 6>  <2, 7>";
//		std::cout << "ships coors are : ";
//		for (int i = 0; i < shipTest6.incrementalCoors.size(); i++)
//		{
//			std::cout << "<" << shipTest6.constantCoor << ',' << shipTest6.incrementalCoors.at(i) << "> ";
//		}
//		std::cout << std::endl;
//
//		return 0;
//	}
//
//};