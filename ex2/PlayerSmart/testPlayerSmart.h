#pragma once
#include"PlayerSmart.h"
#include  <iostream>

class testPlayerSmart {
public:
	testPlayerSmart() {};
	~testPlayerSmart() {};
	//sharon done	
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
		std::cout << "should be false " << res << std::endl;
		res = tempPlayer.isInAttackOptions(std::make_pair(3, 2));
		std::cout << "should be true " << res << std::endl;
		res = tempPlayer.isInAttackOptions(std::make_pair(0, 0));
		std::cout << "should be fales " << res << std::endl;
		res = tempPlayer.isInAttackOptions(std::make_pair(7, 7));
		std::cout << "should be false " << res << std::endl;
		return 0;
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
		std::pair<int, int> tmpPair = std::make_pair(1, 1);

		tempPlayer.removeOneCoordinate(tmpPair);
		auto find = tempPlayer.attackOptions.find(std::make_pair(1, 1));
		if (find != tempPlayer.attackOptions.end())
		{
			std::cout << "not good!didnt delete! " << std::endl;
		}
		else {//didnt find it was deleted before
			std::cout << " good! deleted:)! " << std::endl;
		}


		return 0;
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
		find = tempPlayer.attackOptions.find(std::make_pair(3, 2));
		if (find != tempPlayer.attackOptions.end())
		{
			std::cout << "not good!didnt delete 3,2 wich is erelevent for vertical! " << std::endl;
		}
		else {
			std::cout << "good boy! " << std::endl;
		}
		find = tempPlayer.attackOptions.find(std::make_pair(3, 4));
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


		return 0;
	}
	//dene
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


		std::cout << "this is before marged 3,4,5 with 1, 2 " << std::endl;
		for (auto& details : tmpPlayer.attackedShips) {
			std::vector<int> incrementalCoorsTemp = details.incrementalCoors;
			for (int j = 0; j < tmpPlayer.attackedShips.size(); j++) {
				std::cout << incrementalCoorsTemp.at(j);
			}
			std::cout << std::endl;
		}

		std::cout << "this is after marged 3,4,5 with 1, 2 ,shuold have marged  3,4,5 with 1, 2 and erace not needed vector" << std::endl;
		std::pair<int, int> nextPairTosearch = std::make_pair(4, 2);
		tmpPlayer.mergeShipDetails(&nextPairTosearch, 0);// does one is the first index or second(i need second)

		for (auto& details : tmpPlayer.attackedShips) {
			std::vector<int> incrementalCoorsTemp = details.incrementalCoors;
			for (int j = 0; j < tmpPlayer.attackedShips.size(); j++) {
				std::cout << incrementalCoorsTemp.at(j);
			}
			std::cout << std::endl;
		}


		std::cout << "before another try for marge " << std::endl;

		nextPairTosearch = std::make_pair(4, 3);
		tmpPlayer.mergeShipDetails(&nextPairTosearch, 2);// does one is the first index or second(i need second)

		for (auto& details : tmpPlayer.attackedShips) {
			std::vector<int> incrementalCoorsTemp = details.incrementalCoors;
			for (int j = 0; j < tmpPlayer.attackedShips.size(); j++) {
				std::cout << incrementalCoorsTemp.at(j);
			}
			std::cout << std::endl;
		}

		std::cout << "shuold not have marged/chenged " << std::endl;
		return 0;
	}
	//done
	static int testremoveSankFromReleventCoors() {
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



		allShips.push_back(sizeThree_1);
		allShips.push_back(sizeTwo_1);
		allShips.push_back(sizeOne_1);
		allShips.push_back(sizeOne_2);


		tmpPlayer.attackOptions = allCoors;
		tmpPlayer.attackedShips = allShips;

		tmpPlayer.removeSankFromReleventCoors(0);
		std::cout << "checking for vector 4-3,4,5 - horizontal " << std::endl;
		auto find = tmpPlayer.attackOptions.find(std::make_pair(4, 2));
		if (find != tmpPlayer.attackOptions.end())
		{
			std::cout << "not good!didnt delete 4,2! " << std::endl;
		}
		else {//didnt find it was deleted before
			std::cout << " good!4,2 deleted:)! " << std::endl;
		}
		find = tmpPlayer.attackOptions.find(std::make_pair(4, 6));
		if (find != tmpPlayer.attackOptions.end())
		{
			std::cout << "not good!didnt delete 4,6! " << std::endl;
		}
		else {//didnt find it was deleted before
			std::cout << " good! 4,6 deleted:)! " << std::endl;
		}



		tmpPlayer.removeSankFromReleventCoors(2);
		std::cout << "checking for vector 7,8-8 - vertical" << std::endl;
		find = tmpPlayer.attackOptions.find(std::make_pair(6, 8));
		if (find != tmpPlayer.attackOptions.end())
		{
			std::cout << "not good!didnt delete 6,8! " << std::endl;
		}
		else {//didnt find it was deleted before
			std::cout << " good!6,8 deleted:)! " << std::endl;
		}
		find = tmpPlayer.attackOptions.find(std::make_pair(10, 8));
		if (find != tmpPlayer.attackOptions.end())
		{
			std::cout << "not good!didnt delete 10,8! " << std::endl;
		}
		else {//didnt find it was deleted before
			std::cout << " good! 10,8 deleted:)! " << std::endl;
		}

		std::cout << " check that the vector 7,8-8 and 4-3,4,5 are gone!-->" << std::endl;
		for (auto& details : tmpPlayer.attackedShips) {
			std::vector<int> incrementalCoorsTemp = details.incrementalCoors;
			for (int j = 0; j < tmpPlayer.attackedShips.size(); j++) {
				std::cout << incrementalCoorsTemp.at(j);
			}
			std::cout << std::endl;
		}


		return 0;
	}
	//done	
	static int testnotifyOnAttackResult() {
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

		ShipInProcess sizeTwo_2(5, 8);

		allShips.push_back(sizeThree_1);
		allShips.push_back(sizeTwo_1);
		allShips.push_back(sizeTwo_2);
		allShips.push_back(sizeOne_1);
		allShips.push_back(sizeOne_2);


		tmpPlayer.attackOptions = allCoors;
		tmpPlayer.attackedShips = allShips;
		//miss
		auto find = tmpPlayer.attackOptions.find(std::make_pair(8, 2));
		if (find == tmpPlayer.attackOptions.end())
		{
			std::cout << "not good! 8,2 was sopposed to be here before notify ! " << std::endl;
		}
		tmpPlayer.notifyOnAttackResult(0, 8, 2, AttackResult::Miss);//miss 8,2
		find = tmpPlayer.attackOptions.find(std::make_pair(8, 2));
		if (find != tmpPlayer.attackOptions.end())
		{
			std::cout << "not good!didnt add 8,2 to options ! " << std::endl;
		}
		else {
			std::cout << " good!8,2 deleted from options:)! " << std::endl;
		}


		//hit (merge one coor with one ship)
		find = tmpPlayer.attackOptions.find(std::make_pair(4, 2));
		if (find == tmpPlayer.attackOptions.end())
		{
			std::cout << "not good! 4,2 was sopposed to be here before notify ! " << std::endl;
		}
		tmpPlayer.notifyOnAttackResult(0, 4, 2, AttackResult::Hit);//Hit 4,2
		find = tmpPlayer.attackOptions.find(std::make_pair(4, 2));
		if (find != tmpPlayer.attackOptions.end())
		{
			std::cout << "not good!didnt deleted 4,2 to options ! " << std::endl;
		}
		else {
			std::cout << " good !4,2 deleted from options:)! " << std::endl;
		}

		std::cout << " should be here vector horizontal 4-2,3,4,5 " << std::endl;
		for (auto& details : tmpPlayer.attackedShips) {
			std::vector<int> incrementalCoorsTemp = details.incrementalCoors;
			for (int j = 0; j < tmpPlayer.attackedShips.size(); j++) {
				std::cout << incrementalCoorsTemp.at(j);
			}
			std::cout << std::endl;
		}

		//hit merge two vectors 
		find = tmpPlayer.attackOptions.find(std::make_pair(6, 8));
		if (find == tmpPlayer.attackOptions.end())
		{
			std::cout << "not good!6,8 was sopposed to be here before notify ! " << std::endl;
		}
		tmpPlayer.notifyOnAttackResult(0, 6, 8, AttackResult::Hit);//Hit 6,8
		find = tmpPlayer.attackOptions.find(std::make_pair(6, 8));
		if (find != tmpPlayer.attackOptions.end())
		{
			std::cout << "not good!didnt deleted 6,8 to options ! " << std::endl;
		}
		else {
			std::cout << " good !6,8 deleted from options:)! " << std::endl;
		}

		std::cout << " should be here vector vertical 6,7,8-8 and delete vector single 5,8 " << std::endl;
		for (auto& details : tmpPlayer.attackedShips) {
			std::vector<int> incrementalCoorsTemp = details.incrementalCoors;
			for (int j = 0; j < tmpPlayer.attackedShips.size(); j++) {
				std::cout << incrementalCoorsTemp.at(j);
			}
			std::cout << std::endl;
		}

		//sink
		find = tmpPlayer.attackOptions.find(std::make_pair(2, 8));
		if (find == tmpPlayer.attackOptions.end())
		{
			std::cout << "not good!2,8 was sopposed to be here before notify ! " << std::endl;
		}
		tmpPlayer.notifyOnAttackResult(0, 2, 8, AttackResult::Sink);//Hit 6,8
		find = tmpPlayer.attackOptions.find(std::make_pair(2, 8));
		if (find != tmpPlayer.attackOptions.end())
		{
			std::cout << "not good!didnt deleted 2,8 to options ! " << std::endl;
		}
		else {
			std::cout << " good !2,8 deleted from options:)! " << std::endl;
		}

		std::cout << " should  delete vector 2,3-8 " << std::endl;
		for (auto& details : tmpPlayer.attackedShips) {
			std::vector<int> incrementalCoorsTemp = details.incrementalCoors;
			for (int j = 0; j < tmpPlayer.attackedShips.size(); j++) {
				std::cout << incrementalCoorsTemp.at(j);
			}
			std::cout << std::endl;
		}


		return 0;
	}
	//diana done
	static int testaddCoorToShipsInProcess() {
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

		allCoors.erase(allCoors.find(std::make_pair(2, 1)));
		allCoors.erase(allCoors.find(std::make_pair(3, 8)));
		allCoors.erase(allCoors.find(std::make_pair(7, 8)));
		allCoors.erase(allCoors.find(std::make_pair(8, 8)));
		allCoors.erase(allCoors.find(std::make_pair(4, 3)));
		allCoors.erase(allCoors.find(std::make_pair(4, 5)));
		allCoors.erase(allCoors.find(std::make_pair(4, 4)));

		// clear envirnment
		allCoors.erase(allCoors.find(std::make_pair(7, 6)));
		allCoors.erase(allCoors.find(std::make_pair(8, 6)));
		allCoors.erase(allCoors.find(std::make_pair(7, 9)));
		allCoors.erase(allCoors.find(std::make_pair(8, 9)));
		allCoors.erase(allCoors.find(std::make_pair(3, 3)));
		allCoors.erase(allCoors.find(std::make_pair(3, 5)));
		allCoors.erase(allCoors.find(std::make_pair(3, 4)));
		allCoors.erase(allCoors.find(std::make_pair(5, 3)));
		allCoors.erase(allCoors.find(std::make_pair(5, 5)));
		allCoors.erase(allCoors.find(std::make_pair(5, 4)));


		// create ships
		ShipInProcess sizeOne_1(1, 1);
		ShipInProcess sizeOne_2(3, 8);

		ShipInProcess sizeTwo_1(7, 8);
		sizeTwo_1.addCoordinate(8, 8);

		ShipInProcess sizeThree_1(4, 3);
		sizeThree_1.addCoordinate(4, 4);
		sizeThree_1.addCoordinate(4, 5);


		allShips.push_back(sizeThree_1);
		allShips.push_back(sizeTwo_1);
		allShips.push_back(sizeOne_1);
		allShips.push_back(sizeOne_2);

		tmpPlayer.attackOptions = allCoors;
		tmpPlayer.attackedShips = allShips;

		int res;
		std::pair<int, int> output;
		res = tmpPlayer.addCoorToShipsInProcess(2, 1, &output, AttackResult::Hit);
		if (res != 2)
		{
			std::cout << "error in addCoorToShipsInProcess <2,1> ";
			return -1;
		}

		// print vector
		int i = 0;
		std::cout << " print vectors: (only one should be different) " << std::endl;
		for (auto& shipDetail : tmpPlayer.attackedShips)
		{
			std::cout << i;
			for (auto coor : shipDetail.incrementalCoors)
			{
				std::cout << coor << ',';
			}
			std::cout << std::endl;
			i++;
		}
		std::cout << "next Pair <3,1> got:" << output.first << ',' << output.second << std::endl;

		res = tmpPlayer.addCoorToShipsInProcess(4, 6, &output, AttackResult::Sink);
		if (res != 0)
		{
			std::cout << "error in addCoorToShipsInProcess (4,6) ";
			return -1;
		}

		// print vector
		std::cout << " print vectors: (3 coors to 4) " << std::endl;
		i = 0;
		for (auto& shipDetail : tmpPlayer.attackedShips)
		{
			std::cout << i;
			for (auto coor : shipDetail.incrementalCoors)
			{
				std::cout << coor << ',';
			}

			std::cout << std::endl;
			i++;
		}
		std::cout << "next Pair <4,7> got:" << output.first << ',' << output.second << std::endl;

		/////////////////////////
		res = tmpPlayer.addCoorToShipsInProcess(3, 8, &output, AttackResult::Hit);
		if (res != -1)
		{
			std::cout << "error in addCoorToShipsInProcess  <3,8>";
			return -1;
		}

		// print vector
		i = 0;
		std::cout << "should be the same as before" << std::endl;
		for (auto& shipDetail : tmpPlayer.attackedShips)
		{
			std::cout << i;
			for (auto coor : shipDetail.incrementalCoors)
			{
				std::cout << coor << ',';
			}

			std::cout << std::endl;
			i++;
		}
		std::cout << "next Pair <4,7> got:" << output.first << ',' << output.second << std::endl;

		/////////////////////////
		std::cout << "new ship shoud be added" << std::endl;
		res = tmpPlayer.addCoorToShipsInProcess(7, 2, &output, AttackResult::Hit);
		if (res != -1)
		{
			std::cout << "error in addCoorToShipsInProcess ";
			return -1;
		}

		// print vector
		i = 0;
		for (auto& shipDetail : tmpPlayer.attackedShips)
		{
			std::cout << i;
			for (auto coor : shipDetail.incrementalCoors)
			{
				std::cout << coor << ',';
			}

			std::cout << std::endl;
			i++;
		}
		std::cout << "next Pair <4,7> got:" << output.first << ',' << output.second << std::endl;

		return 0;
	}
	//done
	static int testnextAttackFromCoors() {
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
		allCoors.erase(allCoors.find(std::make_pair(3, 8)));
		allCoors.erase(allCoors.find(std::make_pair(7, 8)));
		allCoors.erase(allCoors.find(std::make_pair(8, 8)));
		allCoors.erase(allCoors.find(std::make_pair(4, 3)));
		allCoors.erase(allCoors.find(std::make_pair(4, 5)));
		allCoors.erase(allCoors.find(std::make_pair(4, 4)));

		allCoors.erase(allCoors.find(std::make_pair(3, 3)));
		allCoors.erase(allCoors.find(std::make_pair(3, 4)));
		allCoors.erase(allCoors.find(std::make_pair(3, 5)));
		allCoors.erase(allCoors.find(std::make_pair(5, 3)));
		allCoors.erase(allCoors.find(std::make_pair(5, 4)));
		allCoors.erase(allCoors.find(std::make_pair(5, 5)));
		allCoors.erase(allCoors.find(std::make_pair(7, 7)));
		allCoors.erase(allCoors.find(std::make_pair(8, 7)));
		allCoors.erase(allCoors.find(std::make_pair(7, 9)));
		allCoors.erase(allCoors.find(std::make_pair(8, 9)));

		// create ships
		ShipInProcess sizeOne_1(1, 1);
		ShipInProcess sizeOne_2(3, 8);

		ShipInProcess sizeTwo_1(7, 8);
		sizeTwo_1.addCoordinate(8, 8);

		ShipInProcess sizeThree_1(4, 3);
		sizeThree_1.addCoordinate(4, 4);
		sizeThree_1.addCoordinate(4, 5);

		allShips.push_back(sizeThree_1);
		allShips.push_back(sizeTwo_1);
		allShips.push_back(sizeOne_1);
		allShips.push_back(sizeOne_2);

		tmpPlayer.attackOptions = allCoors;
		tmpPlayer.attackedShips = allShips;


		std::pair<int, int> nextCoor;
		nextCoor = tmpPlayer.nextAttackFromCoors(sizeThree_1, 3);

		if ((nextCoor.first != 4) || (nextCoor.second != 2))
		{
			std::cout << "error <4,2>" << std::endl;
			return -1;
		}

		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(nextCoor));
		nextCoor = std::make_pair(4, 1);
		tmpPlayer.removeOneCoordinate(nextCoor);
		nextCoor = std::make_pair(3, 2);
		tmpPlayer.removeOneCoordinate(nextCoor);
		nextCoor = std::make_pair(5, 2);
		tmpPlayer.removeOneCoordinate(nextCoor);

		nextCoor = tmpPlayer.nextAttackFromCoors(sizeThree_1, 4);
		if ((nextCoor.first != 4) || (nextCoor.second != 6))
		{
			std::cout << "error <4,6>" << std::endl;
			return -1;
		}
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(nextCoor));


		nextCoor = tmpPlayer.nextAttackFromCoors(sizeTwo_1, 2);
		if ((nextCoor.first != 6) || (nextCoor.second != 8))
		{
			std::cout << "error <6,8>" << std::endl;
			return -1;
		}
		std::cout << "done!" << std::endl;
		return 0;

	}
	//done
	static int testfindPairInAttackedShips() {
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
		sizeThree_1.addCoordinate(4, 5);
		sizeThree_1.addCoordinate(4, 4);

		allShips.push_back(sizeThree_1);
		allShips.push_back(sizeTwo_1);
		allShips.push_back(sizeOne_1);
		allShips.push_back(sizeOne_1);

		tmpPlayer.attackOptions = allCoors;
		tmpPlayer.attackedShips = allShips;

		int res;
		std::pair<int, int> target(4, 3);

		res = tmpPlayer.findPairInAttackedShips(target, 0);
		if (res != 1)
		{
			std::cout << "error <4,3> 0" << std::endl;
			return -1;
		}

		res = tmpPlayer.findPairInAttackedShips(target, 2);
		if (res != -1)
		{
			std::cout << "error <4,3> 2" << std::endl;
			return -1;
		}

		res = tmpPlayer.findPairInAttackedShips(target, 4);
		if (res != -1)
		{
			std::cout << "error <4,3>  4" << std::endl;
			return -1;
		}

		target = std::make_pair(10, 10);
		res = tmpPlayer.findPairInAttackedShips(target, 0);
		if (res != -1)
		{
			std::cout << "error <10,10>  0" << std::endl;
			return -1;
		}

		target = std::make_pair(4, 6);
		res = tmpPlayer.findPairInAttackedShips(target, 0);
		if (res != -1)
		{
			std::cout << "error <4,6>  0" << std::endl;
			return -1;
		}


		return 0;
	}
	//done
	static int testsizeOneAttack() {
		PlayerSmart tmpPlayer;
		std::set<std::pair<int, int>> allCoors;
		for (int i = 1; i<6; i++)
		{
			for (int j = 1; j<6; j++)
			{
				allCoors.insert(std::make_pair(i, j));
			}
		}

		// check all sides
		std::pair<int, int> res;
		std::pair<int, int> target(2, 3);
		allCoors.erase(allCoors.find(target));

		tmpPlayer.attackOptions = allCoors;
		//should return <1,3> up
		res = tmpPlayer.sizeOneAttack(target);
		if ((res.first != 1) || (res.second != 3))
		{
			std::cout << "error 1,3" << std::endl;
			return -1;
		}
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(res));

		//should return <3,3> down
		res = tmpPlayer.sizeOneAttack(target);
		if ((res.first != 3) || (res.second != 3))
		{
			std::cout << "error 3,3" << std::endl;
			return -1;
		}
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(res));

		//should return <2,2>  left
		res = tmpPlayer.sizeOneAttack(target);
		if ((res.first != 2) || (res.second != 2))
		{
			std::cout << "error 2,2" << std::endl;
			return -1;
		}
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(res));

		//should return <3,3> right
		res = tmpPlayer.sizeOneAttack(target);
		if ((res.first != 2) || (res.second != 4))
		{
			std::cout << "error 2,4" << std::endl;
			return -1;
		}
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(res));


		//should return <-1, -1> none
		res = tmpPlayer.sizeOneAttack(target);
		if ((res.first != -1) || (res.second != -1))
		{
			std::cout << "error -1,-1" << std::endl;
			return -1;
		}
		tmpPlayer.removeOneCoordinate(res);
		//		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(res));

		//check rightest edge 
		target = std::make_pair(4, 5);
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(target));
		target = std::make_pair(5, 5);
		// should return left (5,4)
		res = tmpPlayer.sizeOneAttack(target);
		if ((res.first != 5) || (res.second != 4))
		{
			std::cout << "error 5,4" << std::endl;
			return -1;
		}

		tmpPlayer.removeOneCoordinate(res);


		// check the leftest 
		target = std::make_pair(1, 1);
		res = tmpPlayer.sizeOneAttack(target);
		if ((res.first != 2) || (res.second != 1))
		{
			std::cout << "error 2,1" << std::endl;
			return -1;
		}
		tmpPlayer.removeOneCoordinate(res);
		std::cout << "done!" << std::endl;

		return 0;
	}
	//done
	static int testattack() {

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
		sizeThree_1.addCoordinate(4, 5);
		sizeThree_1.addCoordinate(4, 4);

		allShips.push_back(sizeThree_1);
		allShips.push_back(sizeTwo_1);
		allShips.push_back(sizeOne_1);
		allShips.push_back(sizeOne_1);

		tmpPlayer.attackOptions = allCoors;
		tmpPlayer.attackedShips = allShips;

		std::pair <int, int> nextPair = tmpPlayer.attack();

		if ((nextPair.first != 4) || (nextPair.second != 2))
		{
			std::cout << "error <4,2> " << std::endl;
			return -1;
		}

		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(std::make_pair(4, 2)));

		nextPair = tmpPlayer.attack();
		if ((nextPair.first != 4) || (nextPair.second != 6))
		{
			std::cout << "error <4,6> " << std::endl;
			return -1;
		}
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(std::make_pair(4, 6)));
		tmpPlayer.attackedShips.erase(tmpPlayer.attackedShips.begin(), tmpPlayer.attackedShips.end());

		nextPair = tmpPlayer.attack();
		if (!tmpPlayer.isInAttackOptions(nextPair))
		{
			std::cout << "last " << std::endl;
			return -1;
		}

		return 0;
	}
	/////////////////////////////////////////////

	//static int testsetBoard() {
	//	}

};