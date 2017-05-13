#pragma once
#include"PlayerSmart.h"
#include  <iostream>;

class testPlayerSmart {
public:
	testPlayerSmart() {};
	~testPlayerSmart() {};
	
	//done
	static int testisInAttackOptions() {
		PlayerSmart tempPlayer;

		std::set<std::pair<int, int>> coordinates;
		for (int i = 1; i < 6; i++) {
			for (int j = 1; j < 6; j++) {
				coordinates.insert(std::make_pair(i, j));
			}
		}
		tempPlayer.attackOptions = coordinates;
		bool res = tempPlayer.isInAttackOptions(std::make_pair(1, 1));
		std::cout << "should be true " << res << std::endl;
		res = tempPlayer.isInAttackOptions(std::make_pair(6, 6));
		std::cout << "should be true " << res << std::endl;
		res = tempPlayer.isInAttackOptions(std::make_pair(3, 2));
		std::cout << "should be true " << res << std::endl;
		res = tempPlayer.isInAttackOptions(std::make_pair(0, 0));
		std::cout << "should be fales " << res << std::endl;
		res = tempPlayer.isInAttackOptions(std::make_pair(7, 7));
		std::cout << "should be false " << res << std::endl;
	}
	//done
	static int testremoveOneCoordinate() {
		PlayerSmart tempPlayer;

		std::set<std::pair<int, int>> coordinates;
		for (int i = 1; i < 6; i++) {
			for (int j = 1; j < 6; j++) {
				coordinates.insert(std::make_pair(i, j));
			}
		}
		tempPlayer.attackOptions = coordinates;

		tempPlayer.removeOneCoordinate(std::make_pair(1, 1));
		auto find = tempPlayer.attackOptions.find(std::make_pair(1, 1));
		if (find != tempPlayer.attackOptions.end())
		{
			std::cout << "not good!didnt delete! " << std::endl;
		}
		else {//didnt find it was deleted before
			std::cout << " good! deleted:)! " << std::endl;
		}




	}//done
	//done
	static int testremoveAllIrreleventCoordinates() {
		PlayerSmart tempPlayer;

		std::set<std::pair<int, int>> coordinates;
		for (int i = 1; i < 8; i++) {
			for (int j = 1; j < 8; j++) {
				coordinates.insert(std::make_pair(i, j));
			}
		}
		tempPlayer.attackOptions = coordinates;
		//case of in edge(shuold remove only one side) vertical
		tempPlayer.removeAllIrreleventCoordinates(std::make_pair(1, 1), true, false);
		auto find = tempPlayer.attackOptions.find(std::make_pair(1, 2));
		if (find != tempPlayer.attackOptions.end())
		{
			std::cout << "not good!didnt delete 1,2 wich is erelevent for vertical! " << std::endl;
		}
		else {
			std::cout << "good boy! " << std::endl;
		}
		//case of in edge(shuold remove only one side) horizontal
		tempPlayer.removeAllIrreleventCoordinates(std::make_pair(8, 8), false, true);
		find = tempPlayer.attackOptions.find(std::make_pair(7, 8));
		if (find != tempPlayer.attackOptions.end())
		{
			std::cout << "not good!didnt delete 7,8! wich is erelevent for horizontal! " << std::endl;
		}
		else {
			std::cout << "good boy! " << std::endl;
		}
		//case of in middle(shuold remove two side) vertical
		tempPlayer.removeAllIrreleventCoordinates(std::make_pair(3, 3), true, false);
		auto find = tempPlayer.attackOptions.find(std::make_pair(3, 2));
		if (find != tempPlayer.attackOptions.end())
		{
			std::cout << "not good!didnt delete 3,2 wich is erelevent for vertical! " << std::endl;
		}
		else {
			std::cout << "good boy! " << std::endl;
		}
		auto find = tempPlayer.attackOptions.find(std::make_pair(3, 4));
		if (find != tempPlayer.attackOptions.end())
		{
			std::cout << "not good!didnt delete 3,4 wich is erelevent for vertical! " << std::endl;
		}
		else {
			std::cout << "good boy! " << std::endl;
		}


		//case of in middle(shuold remove two side) horizontal
		tempPlayer.removeAllIrreleventCoordinates(std::make_pair(6, 6), false, true);
		find = tempPlayer.attackOptions.find(std::make_pair(5, 6));
		if (find != tempPlayer.attackOptions.end())
		{
			std::cout << "not good!didnt delete 5,6! wich is erelevent for horizontal! " << std::endl;
		}
		else {
			std::cout << "good boy! " << std::endl;
		}
		find = tempPlayer.attackOptions.find(std::make_pair(7, 6));
		if (find != tempPlayer.attackOptions.end())
		{
			std::cout << "not good!didnt delete 7,6! wich is erelevent for horizontal! " << std::endl;
		}
		else {
			std::cout << "good boy! " << std::endl;
		}





	}
	
//diana done

	static int testsizeOneAttack() {
	}

	static int testfindPairInAttackedShips() {
	}

/////////////////////////////////////////////




	static int testremoveSankFromReleventCoors() {
	}
	static int testnotifyOnAttackResult() {
	}



	static int testmergeShipDetails() {
		PlayerSmart tmpPlayer;
		std::vector<ShipInProcess> allShips;

		//create Set of options
		std::set<std::pair<int, int>> allCoors;
		for (int i = 1; i<10; i++)
		{
			for (int j = 1; j<10; j++)
			{
				allCoors.insert(std::make_pair(i, j));
			}
		}

		allCoors.erase(allCoors.find(std::make_pair(1, 1)));
		allCoors.erase(allCoors.find(std::make_pair(4, 1)));
		allCoors.erase(allCoors.find(std::make_pair(3, 8)));
		allCoors.erase(allCoors.find(std::make_pair(7, 8)));
		allCoors.erase(allCoors.find(std::make_pair(8, 8)));
		allCoors.erase(allCoors.find(std::make_pair(4, 3)));
		allCoors.erase(allCoors.find(std::make_pair(4, 5)));
		allCoors.erase(allCoors.find(std::make_pair(4, 4)));


		// create ships
		ShipInProcess sizeOne_1(1, 1);
		ShipInProcess sizeOne_2(3, 8);

		ShipInProcess sizeTwo_1(7, 8);
		sizeTwo_1.addCoordinate(8, 8);

		ShipInProcess sizeThree_1(4, 3);
		sizeThree_1.addCoordinate(4, 4);
		sizeThree_1.addCoordinate(4, 5);

		ShipInProcess sizeTwo_2(4, 1);
		sizeTwo_2.addCoordinate(4, 2);

		allShips.push_back(sizeThree_1);
		allShips.push_back(sizeTwo_2);
		allShips.push_back(sizeTwo_1);
		allShips.push_back(sizeOne_1);
		allShips.push_back(sizeOne_2);
		

		tmpPlayer.attackOptions = allCoors;
		tmpPlayer.attackedShips = allShips;

		
		for (int i = 0; i < tmpPlayer.attackedShips.size; i++)
		{
			for (int i = 0; i < tmpPlayer.attackedShips.size; i++) {
				std::cout << tmpPlayer.attackedShips.at(i).at(j);
			}
			std::cout << std::endl;
		}

		std::cout << "this is before marged 3,4,5 with 1, 2 " << std::endl;
		std::pair<int, int> nextPairTosearch = std::make_pair(4, 2);
		tmpPlayer.mergeShipDetails(&nextPairTosearch, 0);// does one is the first index or second(i need second)
		std::vector<int> incrementalCoorsTemp;
		for (int i = 0; i < tmpPlayer.attackedShips.size; i++)
		{
			incrementalCoorsTemp = tmpPlayer.attackedShips.at(i).incrementalCoors;
			for (int j = 0; j < tmpPlayer.attackedShips.size; j++) {
				std::cout << incrementalCoorsTemp.at(j);
			}
			std::cout << std::endl;
		}

			std::cout << "shuold have marged  3,4,5 with 1, 2 and erace not needed vector "<<std::endl;

	
			nextPairTosearch = std::make_pair(4, 3);
			tmpPlayer.mergeShipDetails(&nextPairTosearch, 2);// does one is the first index or second(i need second)
			
			for (int i = 0; i < tmpPlayer.attackedShips.size; i++)
			{
				incrementalCoorsTemp = tmpPlayer.attackedShips.at(i).incrementalCoors;
				for (int j = 0; j < tmpPlayer.attackedShips.size; j++) {
					std::cout << incrementalCoorsTemp.at(j);
				}
				std::cout << std::endl;
			}

			std::cout << "shuold not have marged/chenged " << std::endl;
	}
	
	static int testaddCoorToShipsInProcess() {
	}
	static int testnextAttackFromCoors() {
	}


	static int testattack() {
	}
	static int testsetBoard() {
	}

};