#include"ShipInProcess.h"
#include  <iostream>;
class testShipInProcess {
public:
	testShipInProcess(){};
	~testShipInProcess(){};
	int testaddToSizeOneShip() {
		ShipInProcess shipTest(2, 2);
		shipTest.addToSizeOneShip(2, 3);//right
		std::cout << "right add " << shipTest.getMaxCoor;
		ShipInProcess shipTest1(2, 2);
		shipTest1.addToSizeOneShip(2, 1);//left
		std::cout << "left add " << shipTest.getMinCoor;
		ShipInProcess shipTest2(2, 2);
		shipTest2.addToSizeOneShip(1, 2);//up
		std::cout << "up add " << shipTest.getMinCoor;
		ShipInProcess shipTest2(2, 2);
		shipTest2.addToSizeOneShip(3, 2);//down
		std::cout << "down add " << shipTest.getMaxCoor;
		ShipInProcess shipTest3(3, 3);
		shipTest3.addToSizeOneShip(1, 3);//should not add
		std::cout << "should be (3,3) and not (1,3) " << shipTest.getMinCoor;
		ShipInProcess shipTest3(3, 3);
		shipTest3.addToSizeOneShip(3, 1);//should not add
		std::cout << "should be (3,3) and not (3,1) " << shipTest.getMinCoor;
		ShipInProcess shipTest4(3, 3);
		shipTest4.addToSizeOneShip(3, 5);//should not add
		std::cout << "should be (3,3) and not (3,5) " << shipTest.getMaxCoor;
		ShipInProcess shipTest5(3, 3);
		shipTest5.addToSizeOneShip(5,3);//should not add
		std::cout << "should be (3,3) and not (5,3) " << shipTest.getMaxCoor;
		
	}
	int testisPartOfShip() {
		ShipInProcess shipTest(2, 2);
		shipTest.incrementalCoors.insert(shipTest.incrementalCoors.end(), 3);
		shipTest.incrementalCoors.insert(shipTest.incrementalCoors.end(), 4);
		shipTest.incrementalCoors.insert(shipTest.incrementalCoors.end(), 5);		


		std::cout << "should be true " << shipTest.isPartOfShip(2, 4);
		std::cout << "should be true " << shipTest.isPartOfShip(2, 5);
		std::cout << "should be true " << shipTest.isPartOfShip(2, 2);

		std::cout << "should be false " << shipTest.isPartOfShip(2, 6);
		std::cout << "should be false " << shipTest.isPartOfShip(1, 2);
	}

	int testaddCoordinate() {
		ShipInProcess shipTest(2, 2);
		shipTest.incrementalCoors.insert(shipTest.incrementalCoors.end(), 3);
		shipTest.incrementalCoors.insert(shipTest.incrementalCoors.end(), 4);
		shipTest.incrementalCoors.insert(shipTest.incrementalCoors.end(), 5);

		//good entery
		int res=shipTest.addCoordinate(2, 6);
		std::cout << "should be true for (2,6)" << shipTest.isPartOfShip(2, 6) << "res should be 1 got in" << res;
		//not good
		shipTest.addCoordinate(2, 8);
		std::cout << "should be falue for(2,8)" << shipTest.isPartOfShip(2,8) << "res should be -1 didnt get in" << res;
		//was alredy in
		shipTest.addCoordinate(2,2);
		std::cout << "should be true for (2,2)" << shipTest.isPartOfShip(2,2) << "res should be 0 alredy in" << res;	
	}


	int testMegreShipsVectors()
	{
		std::vector<int> vec;
		std::vector<int> resVector;
		std::pair<int, int> coor;
		int consCoor = 5;

		
		/* check vorizontal !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1*/
		vec.push_back(1);
		vec.push_back(2);
		coor = std::make_pair(consCoor, 3);
		// test <1,2> +  3  - horizintal
		// ships coors shold be : <5 , 1>  <5,2> , <5, 3>

		resVector = ShipInProcess::mergeShipsVectors(vec, coor, false);
		std::cout << "ships coors shold be : <consCoor, 1>  <consCoor, 2>, <consCoor, 3>" << std::endl;
		std::cout << "ships coors are : " << std::endl;
		for (int i = 0; i < vec.size(); i++)
		{
			std::cout << "<" << consCoor << ',' << vec.at(i) << "> ";
		}
		vec.clear();


		// insert from left horizontal
		vec.push_back(4);
		vec.push_back(5);
		coor = std::make_pair(consCoor, 3);

		// ships coors shold be : <5 , 3>  <5,4> , <5, 5>
		resVector = ShipInProcess::mergeShipsVectors(vec, coor, false);
		std::cout << "ships coors shold be : <consCoor, 3>  <consCoor, 4>, <consCoor, 5>" << std::endl;
		std::cout << "ships coors are : " << std::endl;
		for (int i = 0; i < vec.size(); i++)
		{
			std::cout << "<" << consCoor << ',' << vec.at(i) << "> ";
		}
		vec.clear();



		vec.push_back(1);
		vec.push_back(2);
		coor = std::make_pair(consCoor, 5);
		// shouldnt add not not oncremental / coors
		// ships coors shold be : <5 , 1>  <5,2> 
		resVector = ShipInProcess::mergeShipsVectors(vec, coor, false);
		std::cout << "ships coors shold be : <consCoor, 1>  <consCoor, 2>" << std::endl;
		std::cout << "ships coors are : " << std::endl;
		for (int i = 0; i < vec.size(); i++)
		{
			std::cout << "<" << consCoor << ',' << vec.at(i) << "> ";
		}
		vec.clear();


		vec.push_back(1);
		vec.push_back(2);
		coor = std::make_pair(consCoor, -1);
		// shouldnt add not not oncremental / coors
		// ships coors shold be : <5 , 1>  <5,2> 
		resVector = ShipInProcess::mergeShipsVectors(vec, coor, false);
		std::cout << "ships coors shold be : <consCoor, 1>  <consCoor, 2>" << std::endl;
		std::cout << "ships coors are : " << std::endl;
		for (int i = 0; i < vec.size(); i++)
		{
			std::cout << "<" << consCoor << ',' << vec.at(i) << "> ";
		}
		vec.clear();



		/* check vertical !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1*/
		vec.push_back(1);
		vec.push_back(2);
		coor = std::make_pair(3, consCoor);

		resVector = ShipInProcess::mergeShipsVectors(vec, coor, true);
		std::cout << "ships coors shold be : <1, consCoor>  < 2, consCoor>, <3, consCoor>" << std::endl;
		std::cout << "ships coors are : " << std::endl;
		for (int i = 0; i < vec.size(); i++)
		{
			std::cout << "<" << vec.at(i) << ',' << consCoor << "> ";
		}
		vec.clear();


		// insert from left horizontal
		vec.push_back(4);
		vec.push_back(5);
		coor = std::make_pair(3, consCoor);

		resVector = ShipInProcess::mergeShipsVectors(vec, coor, true);
		std::cout << "ships coors shold be : <3, consCoor>  <4, consCoor>, <5 , consCoor>" << std::endl;
		std::cout << "ships coors are : " << std::endl;
		for (int i = 0; i < vec.size(); i++)
		{
			std::cout << "<" << vec.at(i) << ',' << consCoor << "> ";
		}
		vec.clear();



		vec.push_back(1);
		vec.push_back(2);
		coor = std::make_pair(5, consCoor);
		resVector = ShipInProcess::mergeShipsVectors(vec, coor, true);
		std::cout << "ships coors shold be : <consCoor, 1>  <consCoor, 2>" << std::endl;
		std::cout << "ships coors are : " << std::endl;
		for (int i = 0; i < vec.size(); i++)
		{
			std::cout << "<" << vec.at(i) << ',' << consCoor << "> ";
		}
		vec.clear();


		vec.push_back(1);
		vec.push_back(2);
		coor = std::make_pair(-1, consCoor);
		// shouldnt add not not oncremental / coors
		resVector = ShipInProcess::mergeShipsVectors(vec, coor, true);
		std::cout << "ships coors shold be : <consCoor, 1>  <consCoor, 2>" << std::endl;
		std::cout << "ships coors are : " << std::endl;
		for (int i = 0; i < vec.size(); i++)
		{
			std::cout << "<" << vec.at(i) << ',' << consCoor << "> ";
		}
		vec.clear();

		return 1;
	}


	int testmegreShipsInProcess() {
		ShipInProcess shipTest(2, 2);
		shipTest.incrementalCoors.insert(shipTest.incrementalCoors.end(), 3);
		shipTest.incrementalCoors.insert(shipTest.incrementalCoors.end(), 4);
		ShipInProcess shipTest1(2, 5);

		ShipInProcess shipTest2(2, 5);
		ShipInProcess shipTest3(2, 2);
		shipTest3.incrementalCoors.insert(shipTest3.incrementalCoors.end(), 3);
		shipTest3.incrementalCoors.insert(shipTest3.incrementalCoors.end(), 4);
		
		ShipInProcess shipTest4(2, 2);
		shipTest4.incrementalCoors.insert(shipTest4.incrementalCoors.end(), 3);
		shipTest4.incrementalCoors.insert(shipTest4.incrementalCoors.end(), 4);
		ShipInProcess shipTest5(2, 5);
		shipTest5.incrementalCoors.insert(shipTest5.incrementalCoors.end(), 6);
		shipTest5.incrementalCoors.insert(shipTest5.incrementalCoors.end(), 7);


		ShipInProcess shipTest6(2, 6);
		ShipInProcess shipTest7(2, 7);




		shipTest.megreShipsInProcess(shipTest1);// this ship-many to oter ship 1size 
		std::cout << "ships coors shold be : <consCoor, 2>  <consCoor, 3>	<consCoor, 4>	<consCoor, 5>" << std::endl;
		std::cout << "ships coors are : " << std::endl;
		for (int i = 0; i < shipTest.incrementalCoors.size(); i++)
		{
			std::cout << "<" << shipTest.constantCoor << ',' << shipTest.incrementalCoors.at(i) << "> ";
		}


		shipTest2.megreShipsInProcess(shipTest3);// this ship-1size to oter ship many
		std::cout << "ships coors shold be : <consCoor, 2>  <consCoor, 3>	<consCoor, 4>	<consCoor, 5>" << std::endl;
		std::cout << "ships coors are : " << std::endl;
		for (int i = 0; i < shipTest2.incrementalCoors.size(); i++)
		{
			std::cout << "<" << shipTest2.constantCoor << ',' << shipTest2.incrementalCoors.at(i) << "> ";
		}
				
		shipTest4.megreShipsInProcess(shipTest5);// this ship-many to oter ship many
		std::cout << "ships coors shold be : <consCoor, 2>  <consCoor, 3>	<consCoor, 4>	<consCoor, 5>	<consCoor, 6>	<consCoor, 7>" << std::endl;
		std::cout << "ships coors are : " << std::endl;
		for (int i = 0; i < shipTest4.incrementalCoors.size(); i++)
		{
			std::cout << "<" << shipTest4.constantCoor << ',' << shipTest4.incrementalCoors.at(i) << "> ";
		}

		shipTest6.megreShipsInProcess(shipTest7);// this ship-1size to oter ship 1size
		std::cout << "ships coors shold be : <consCoor, 6>  <consCoor, 7>" << std::endl;
		std::cout << "ships coors are : " << std::endl;
		for (int i = 0; i < shipTest6.incrementalCoors.size(); i++)
		{
			std::cout << "<" << shipTest6.constantCoor << ',' << shipTest6.incrementalCoors.at(i) << "> ";
		}









	
	
	}

};
