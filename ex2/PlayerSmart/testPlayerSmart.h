#pragma once
#include"PlayerSmart.h"
#include  <iostream>;

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
			for (int j = 0; j < tmpPlayer.attackedShips.size; j++) {
				std::cout << incrementalCoorsTemp.at(j);
			}
			std::cout << std::endl;
		}

		std::cout << "this is after marged 3,4,5 with 1, 2 ,shuold have marged  3,4,5 with 1, 2 and erace not needed vector" << std::endl;
		std::pair<int, int> nextPairTosearch = std::make_pair(4, 2);
		tmpPlayer.mergeShipDetails(&nextPairTosearch, 0);// does one is the first index or second(i need second)

		for (auto& details : tmpPlayer.attackedShips) {
			std::vector<int> incrementalCoorsTemp = details.incrementalCoors;
			for (int j = 0; j < tmpPlayer.attackedShips.size; j++) {
				std::cout << incrementalCoorsTemp.at(j);
			}
			std::cout << std::endl;
		}


		std::cout << "before another try for marge " << std::endl;

		nextPairTosearch = std::make_pair(4, 3);
		tmpPlayer.mergeShipDetails(&nextPairTosearch, 2);// does one is the first index or second(i need second)

		for (auto& details : tmpPlayer.attackedShips) {
			std::vector<int> incrementalCoorsTemp = details.incrementalCoors;
			for (int j = 0; j < tmpPlayer.attackedShips.size; j++) {
				std::cout << incrementalCoorsTemp.at(j);
			}
			std::cout << std::endl;
		}

		std::cout << "shuold not have marged/chenged " << std::endl;
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
		auto find = tmpPlayer.attackOptions.find(std::make_pair(4, 6));
		if (find != tmpPlayer.attackOptions.end())
		{
			std::cout << "not good!didnt delete 4,6! " << std::endl;
		}
		else {//didnt find it was deleted before
			std::cout << " good! 4,6 deleted:)! " << std::endl;
		}



		tmpPlayer.removeSankFromReleventCoors(2);
		std::cout << "checking for vector 7,8-8 - vertical" << std::endl;
		auto find = tmpPlayer.attackOptions.find(std::make_pair(6, 8));
		if (find != tmpPlayer.attackOptions.end())
		{
			std::cout << "not good!didnt delete 6,8! " << std::endl;
		}
		else {//didnt find it was deleted before
			std::cout << " good!6,8 deleted:)! " << std::endl;
		}
		auto find = tmpPlayer.attackOptions.find(std::make_pair(10, 8));
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
			for (int j = 0; j < tmpPlayer.attackedShips.size; j++) {
				std::cout << incrementalCoorsTemp.at(j);
			}
			std::cout << std::endl;
		}




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
		std::pair<int, int> output;
		res = tmpPlayer.addCoorToShipsInProcess(1, 1, &output, AttackResult::Hit);
		if (res != 3)
		{
			std::cout << "error in addCoorToShipsInProcess <1,1> ";
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
		std::cout << "next Pair <0,1> got:" << output.first << ',' << output.second << std::endl;

		std::cout << " print vectors: (onlythe first should be different) " << std::endl;
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
		res = tmpPlayer.addCoorToShipsInProcess(3, 8, &output, AttackResult::Miss);
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


		std::pair<int, int> nextCoor;
		nextCoor = tmpPlayer.nextAttackFromCoors(sizeThree_1, 3);

		if ((nextCoor.first != 4) || (nextCoor.second != 2))
		{
			std::cout << "error <4,2>" << std::endl;
			return -1;
		}

		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(nextCoor));

		nextCoor = tmpPlayer.nextAttackFromCoors(sizeThree_1, 3);

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

		res = tmpPlayer.findPairInAttackedShips(target);
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
		res = tmpPlayer.findPairInAttackedShips(target);
		if (res != -1)
		{
			std::cout << "error <10,10>  0" << std::endl;
			return -1;
		}

		target = std::make_pair(4, 6);
		res = tmpPlayer.findPairInAttackedShips(target);
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

		//should return <1,3> up
		res = tmpPlayer.sizeOneAttack(target);
		if ((res.first != 1) || (res.second != 3))
		{
			std::cout << "error 1,3" << std::endl;
			return -1;
		}
		allCoors.erase(allCoors.find(res));

		//should return <3,3> down
		res = tmpPlayer.sizeOneAttack(target);
		if ((res.first != 3) || (res.second != 3))
		{
			std::cout << "error 3,3" << std::endl;
			return -1;
		}
		allCoors.erase(allCoors.find(res));

		//should return <2,2>  left
		res = tmpPlayer.sizeOneAttack(target);
		if ((res.first != 2) || (res.second != 2))
		{
			std::cout << "error 2,2" << std::endl;
			return -1;
		}
		allCoors.erase(allCoors.find(res));

		//should return <3,3> right
		res = tmpPlayer.sizeOneAttack(target);
		if ((res.first != 2) || (res.second != 4))
		{
			std::cout << "error 2,4" << std::endl;
			return -1;
		}
		allCoors.erase(allCoors.find(res));


		//should return <-1, -1> none
		res = tmpPlayer.sizeOneAttack(target);
		if ((res.first != -1) || (res.second != -1))
		{
			std::cout << "error -1,-1" << std::endl;
			return -1;
		}
		allCoors.erase(allCoors.find(res));

		//check rightest edge 
		target = std::make_pair(4, 5);
		allCoors.erase(allCoors.find(target));
		target = std::make_pair(5, 5);
		// should return left (5,4)
		res = tmpPlayer.sizeOneAttack(target);
		if ((res.first != 5) || (res.second != 4))
		{
			std::cout << "error 5,4" << std::endl;
			return -1;
		}
		allCoors.erase(allCoors.find(res));

		// check the leftest 
		target = std::make_pair(1, 1);
		res = tmpPlayer.sizeOneAttack(target);
		if ((res.first != 2) || (res.second != 1))
		{
			std::cout << "error 2,1" << std::endl;
			return -1;
		}
		allCoors.erase(allCoors.find(res));


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
	static int testnotifyOnAttackResult() {
	}
	static int testsetBoard() {
	}

};