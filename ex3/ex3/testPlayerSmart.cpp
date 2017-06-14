#include "testPlayerSmart.h"
#include "iostream"


void testPlayerSmart::printCoordinate(const Coordinate& coord)
{
	//std::cout << "coordinate: " << "row: " << coord.row << "col: " << coord.col << "depth: " << coord.depth << std::endl;
}

void testPlayerSmart::testpourImbalancedToAttackOptions()
{
	PlayerSmart tempPlayer;
	std::set<Coordinate> coordinates;
	for (int i = 1; i < 6; i++) {
		for (int j = 1; j < 6; j++) {
			for (int k = 1; k < 6; k++) {
				tempPlayer.imbalancedAttackOptions.insert(Coordinate(i, j, k));
			}
		}
	}

	tempPlayer.pourImbalancedToAttackOptions();

	for (int i = 1; i < 6; i++) {
		for (int j = 1; j < 6; j++) {
			for (int k = 1; k < 6; k++) {
				if (tempPlayer.attackOptions.find(Coordinate(i, j, k)) == tempPlayer.attackOptions.end()) {
					std::cout << "bad bad bad bad bad bad news didnt pour ";
					printCoordinate(Coordinate(i, j, k));
					std::cout << "to attack options from Imbalanced" << std::endl;
				}
			}
		}
	}

	std::cout << "only good things can be said about pourImbalancedToAttackOptions !!!!!! " << std::endl;
}

void testPlayerSmart::testupdateShipsCount()
{
	PlayerSmart tmpPlayer;
	std::vector<std::pair<int, int>> count; // vector of enemie's ship's: pair of <shipSize,count>

	count.push_back(std::make_pair(1, 2));
	count.push_back(std::make_pair(2, 3));
	count.push_back(std::make_pair(3, 0));
	count.push_back(std::make_pair(4, 1));

	tmpPlayer.shipsCount = count;
	tmpPlayer.updateShipsCount(1);
	tmpPlayer.updateShipsCount(4);
	if (tmpPlayer.shipsCount.at(0).second != 1) {
		std::cout << "ho no didnt update the ships count properly index0 :(" << std::endl;
	}
	if (tmpPlayer.shipsCount.at(3).second != 0) {
		std::cout << "ho no didnt update the ships count properly index3 :(" << std::endl;
	}

	for (int i = 1; i < 6; i++) {
		for (int j = 1; j < 6; j++) {
			for (int k = 1; k < 6; k++) {
				tmpPlayer.imbalancedAttackOptions.insert(Coordinate(i, j, k));
			}
		}
	}
	tmpPlayer.updateShipsCount(2);
	if (tmpPlayer.isBoardBalanced == true) {
		std::cout << "omg didnt set imbalnced properly!!!!!1" << std::endl;
	}

	for (int i = 1; i < 6; i++) {
		for (int j = 1; j < 6; j++) {
			for (int k = 1; k < 6; k++) {
				if (tmpPlayer.attackOptions.find(Coordinate(i, j, k)) == tmpPlayer.attackOptions.end()) {
					std::cout << "bad bad bad bad bad bad news didnt pour ";
					printCoordinate(Coordinate(i, j, k));
					std::cout << "to attack options from Imbalanced" << std::endl;
				}
			}
		}
	}

	std::cout << "updateShipsCount is very very Good :)" << std::endl;
}

void testPlayerSmart::testgetMinShipSize()
{
	PlayerSmart tmpPlayer;
	std::vector<std::pair<int, int>> count; // vector of enemie's ship's: pair of <shipSize,count>

	count.push_back(std::make_pair(1, 2));
	count.push_back(std::make_pair(2, 3));
	count.push_back(std::make_pair(3, 0));
	count.push_back(std::make_pair(4, 1));

	tmpPlayer.shipsCount = count;
	int res = tmpPlayer.getMinShipSize();
	if (res != 1) {
		std::cout << "ho no min ship size should be 1 but we got " << res << " :(" << std::endl;
	}

	tmpPlayer.shipsCount.at(0).second = 0;
	tmpPlayer.shipsCount.at(1).second = 0;

	res = tmpPlayer.getMinShipSize();
	if (res != 4) {
		std::cout << "ho no min ship size should be 4 but we got " << res << " :(" << std::endl;
	}

	std::cout << "Good boy! " << std::endl;
}

void testPlayerSmart::testCheck6Util1()
{

	PlayerSmart tempPlayer;
	// create 10*10*10 board
	for (int i = 1; i < 10; i++) {
		for (int j = 1; j < 10; j++) {
			for (int k = 1; k < 10; k++) {
				tempPlayer.attackOptions.insert(Coordinate(i, j, k));
			}
		}
	}


	std::vector<std::pair<int, int>> count;
	count.push_back(std::make_pair(10, 5));


	// target coor will be 2, 5, 4
	tempPlayer.attackOptions.erase(tempPlayer.attackOptions.find(Coordinate(2, 5, 4)));

	// create 'walls' around it
	//horizontal
	tempPlayer.attackOptions.erase(tempPlayer.attackOptions.find(Coordinate(2, 1, 4)));
	tempPlayer.attackOptions.erase(tempPlayer.attackOptions.find(Coordinate(2, 8, 4)));

	//vertical
	tempPlayer.attackOptions.erase(tempPlayer.attackOptions.find(Coordinate(6, 5, 4)));
	//coordinates.erase(coordinates.find(Coordinate(0, 5, 4))); already a wall

	//deptical
	//coordinates.erase(coordinates.find(Coordinate(2, 5, 0))); alreay a wall
	tempPlayer.attackOptions.erase(tempPlayer.attackOptions.find(Coordinate(2, 5, 8)));

	std::set<Coordinate> imbalancedTest;
	// horizontal
	imbalancedTest.insert(Coordinate(2, 2, 4));
	imbalancedTest.insert(Coordinate(2, 3, 4));
	imbalancedTest.insert(Coordinate(2, 4, 4));
	imbalancedTest.insert(Coordinate(2, 6, 4));
	imbalancedTest.insert(Coordinate(2, 7, 4));

	//vertical
	imbalancedTest.insert(Coordinate(3, 5, 4));
	imbalancedTest.insert(Coordinate(4, 5, 4));
	imbalancedTest.insert(Coordinate(5, 5, 4));
	imbalancedTest.insert(Coordinate(1, 5, 4));

	// deptical 
	imbalancedTest.insert(Coordinate(2, 5, 1));
	imbalancedTest.insert(Coordinate(2, 5, 2));
	imbalancedTest.insert(Coordinate(2, 5, 3));
	imbalancedTest.insert(Coordinate(2, 5, 4));
	imbalancedTest.insert(Coordinate(2, 5, 6));
	imbalancedTest.insert(Coordinate(2, 5, 7));

	// set attack options 
	tempPlayer.shipsCount = count;

	// test function
	tempPlayer.checkSixDirections(Coordinate(2, 5, 4));

	for (auto coor : imbalancedTest) {
		if (!tempPlayer.isInImbalancedOptions(coor)) {
			std::cout << "missing coordinate in imbalanced horizontal";
			printCoordinate(coor);
			std::cout << " fix this now!!!!!" << std::endl;
		}

		if (tempPlayer.isInAttackOptions(coor)) {
			std::cout << "coordinate shoukdnt be in attack options";
			printCoordinate(coor);
			std::cout << " fix this now!!!!!" << std::endl;
		}
	}
}

void testPlayerSmart::testcheck6Util2()
{

	PlayerSmart tempPlayer;
	// create 10*10*10 board
	for (int i = 1; i < 10; i++) {
		for (int j = 1; j < 10; j++) {
			for (int k = 1; k < 10; k++) {
				tempPlayer.attackOptions.insert(Coordinate(i, j, k));
			}
		}
	}


	std::vector<std::pair<int, int>> count;
	count.push_back(std::make_pair(1, 5));

	// target coor will be 2, 5, 4
	tempPlayer.attackOptions.erase(tempPlayer.attackOptions.find(Coordinate(2, 5, 4)));

	// create 'walls' around it
	//horizontal
	tempPlayer.attackOptions.erase(tempPlayer.attackOptions.find(Coordinate(2, 1, 4)));
	tempPlayer.attackOptions.erase(tempPlayer.attackOptions.find(Coordinate(2, 8, 4)));

	//vertical
	tempPlayer.attackOptions.erase(tempPlayer.attackOptions.find(Coordinate(6, 5, 4)));
	//coordinates.erase(coordinates.find(Coordinate(0, 5, 4))); already a wall

	//deptical
	//coordinates.erase(coordinates.find(Coordinate(2, 5, 0))); alreay a wall
	tempPlayer.attackOptions.erase(tempPlayer.attackOptions.find(Coordinate(2, 5, 8)));

	// set attack options 
	tempPlayer.shipsCount = count;

	// test function
	tempPlayer.checkSixDirections(Coordinate(2, 5, 4));

	if (tempPlayer.imbalancedAttackOptions.size() != 0) {
		std::cout << "imbalanced should be of size 0";
	}

	std::set<Coordinate> coordinates;
	for (int i = 1; i < 10; i++) {
		for (int j = 1; j < 10; j++) {
			for (int k = 1; k < 10; k++) {
				coordinates.insert(Coordinate(i, j, k));
			}
		}
	}

	for (auto coor : coordinates) {
		if (tempPlayer.attackOptions.find(coor) == tempPlayer.attackOptions.end()) {
			std::cout << "coordinate should be in attack options";
			printCoordinate(coor);
			std::cout << " fix this now!!!!!" << std::endl;
		}
	}

}

void testPlayerSmart::testCheck6Util3()
{

	PlayerSmart tempPlayer;
	// create 10*10*10 board
	for (int i = 1; i < 10; i++) {
		for (int j = 1; j < 10; j++) {
			for (int k = 1; k < 10; k++) {
				tempPlayer.attackOptions.insert(Coordinate(i, j, k));
			}
		}
	}


	std::vector<std::pair<int, int>> count;
	count.push_back(std::make_pair(2, 2));

	// target coor will be 2, 5, 4
	tempPlayer.attackOptions.erase(tempPlayer.attackOptions.find(Coordinate(2, 5, 4)));

	// create 'walls' around it
	//horizontal
	tempPlayer.attackOptions.erase(tempPlayer.attackOptions.find(Coordinate(2, 3, 4)));
	tempPlayer.attackOptions.erase(tempPlayer.attackOptions.find(Coordinate(2, 8, 4)));

	//vertical
	tempPlayer.attackOptions.erase(tempPlayer.attackOptions.find(Coordinate(6, 5, 4)));
	//coordinates.erase(coordinates.find(Coordinate(0, 5, 4))); already a wall

	//deptical
	//coordinates.erase(coordinates.find(Coordinate(2, 5, 0))); alreay a wall
	tempPlayer.attackOptions.erase(tempPlayer.attackOptions.find(Coordinate(2, 5, 8)));

	std::set<Coordinate> imbalancedTest;
	// horizontal
	imbalancedTest.insert(Coordinate(2, 4, 4));

	//vertical
	imbalancedTest.insert(Coordinate(1, 5, 4));


	// set attack options 
	tempPlayer.shipsCount = count;

	// test function
	tempPlayer.checkSixDirections(Coordinate(2, 5, 4));

	for (auto coor : imbalancedTest) {
		if (!tempPlayer.isInImbalancedOptions(coor)) {
			std::cout << "missing coordinate in imbalanced horizontal";
			printCoordinate(coor);
			std::cout << " fix this now!!!!!" << std::endl;
		}

		if (tempPlayer.isInAttackOptions(coor)) {
			std::cout << "coordinate shoukdnt be in attack options";
			printCoordinate(coor);
			std::cout << " fix this now!!!!!" << std::endl;
		}
	}
}

void testPlayerSmart::testcheckSixDirections()
{

	std::cout << "should remove from all directions of 2,5,4 " << std::endl;
	testCheck6Util1();

	std::cout << "shouldnt remove anything from attack options " << std::endl;
	testcheck6Util2();

	std::cout << "remove only from some directions " << std::endl;
	testCheck6Util3();

	std::cout << "check 6 directions is fine" << std::endl;
}

void testPlayerSmart::testtransferCoordinatesToSecondPoll()
{

	{
		PlayerSmart tempPlayer;
		for (int i = 1; i < 6; i++) {
			for (int j = 1; j < 6; j++) {
				for (int k = 1; k < 6; k++) {
					tempPlayer.attackOptions.insert(Coordinate(i, j, k));
				}
			}
		}


		//// Horizontal !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!	
		tempPlayer.attackOptions.erase(tempPlayer.attackOptions.find(Coordinate(2, 5, 4)));
		tempPlayer.attackOptions.erase(tempPlayer.attackOptions.find(Coordinate(2, 1, 4)));

		tempPlayer.transferCoordinatesToSecondPoll(Coordinate(2, 5, 4), 3, false, true, -1);

		std::set<Coordinate> imbalancedTest;
		imbalancedTest.insert(Coordinate(2, 2, 4));
		imbalancedTest.insert(Coordinate(2, 3, 4));
		imbalancedTest.insert(Coordinate(2, 4, 4));

		for (auto coor : imbalancedTest) {
			if (!tempPlayer.isInImbalancedOptions(coor)) {
				std::cout << "missing coordinate in imbalanced horizontal";
				printCoordinate(coor);
				std::cout << " fix this now!!!!!" << std::endl;
			}
		}
	}


	{
		PlayerSmart tempPlayer;
		for (int i = 1; i < 6; i++) {
			for (int j = 1; j < 6; j++) {
				for (int k = 1; k < 6; k++) {
					tempPlayer.attackOptions.insert(Coordinate(i, j, k));
				}
			}
		}

		//// Vertical !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		tempPlayer.attackOptions.erase(tempPlayer.attackOptions.find(Coordinate(5, 3, 4)));
		tempPlayer.attackOptions.erase(tempPlayer.attackOptions.find(Coordinate(1, 3, 4)));

		tempPlayer.transferCoordinatesToSecondPoll(Coordinate(1, 3, 4), 3, true, false, +1);

		std::set<Coordinate> imbalancedTest;
		imbalancedTest.insert(Coordinate(2, 3, 4));
		imbalancedTest.insert(Coordinate(3, 3, 4));
		imbalancedTest.insert(Coordinate(4, 2, 4));

		for (auto coor : imbalancedTest) {
			if (!tempPlayer.isInImbalancedOptions(coor)) {
				std::cout << "missing coordinate in imbalanced vertical ";
				printCoordinate(coor);
				std::cout << " fix this now!!!!!" << std::endl;
			}
		}

	}

	{
		PlayerSmart tempPlayer;
		std::set<Coordinate> coordinates;
		for (int i = 1; i < 10; i++) {
			for (int j = 1; j < 10; j++) {
				for (int k = 1; k < 10; k++) {
					coordinates.insert(Coordinate(i, j, k));
				}
			}
		}


		//// deptical !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		tempPlayer.attackOptions.erase(tempPlayer.attackOptions.find(Coordinate(7, 3, 1)));
		tempPlayer.attackOptions.erase(tempPlayer.attackOptions.find(Coordinate(7, 3, 8)));

		tempPlayer.transferCoordinatesToSecondPoll(Coordinate(7, 3, 8), 6, false, false, -1);


		std::set<Coordinate> imbalancedTest;
		imbalancedTest.insert(Coordinate(7, 3, 2));
		imbalancedTest.insert(Coordinate(7, 3, 3));
		imbalancedTest.insert(Coordinate(7, 3, 4));
		imbalancedTest.insert(Coordinate(7, 3, 5));
		imbalancedTest.insert(Coordinate(7, 3, 6));
		imbalancedTest.insert(Coordinate(7, 3, 7));

		for (auto coor : imbalancedTest) {
			if (!tempPlayer.isInImbalancedOptions(coor)) {
				std::cout << "missing coordinate in imbalanced vertical ";
				printCoordinate(coor);
				std::cout << " fix this now!!!!! deptical" << std::endl;
			}
		}
	}

	std::cout << "Hopefully we got here and the transfer function works fine !!! praise the lord!!!!!" << std::endl;
}

void testPlayerSmart::testcountDistance()
{

	{
		PlayerSmart tempPlayer;
		for (int i = 1; i < 6; i++) {
			for (int j = 1; j < 6; j++) {
				for (int k = 1; k < 6; k++) {
					tempPlayer.attackOptions.insert(Coordinate(i, j, k));
				}
			}
		}
		int res;

		//// Horizontal !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!	
		tempPlayer.attackOptions.erase(tempPlayer.attackOptions.find(Coordinate(2, 5, 4)));
		tempPlayer.attackOptions.erase(tempPlayer.attackOptions.find(Coordinate(2, 1, 4)));

		res = tempPlayer.countDistance(Coordinate(2, 5, 4), 0, false, true, -1);
		if (res != -1) {
			std::cout << "the distance was supposed to be -1 !!!!  got " << res << " :(" << std::endl;
		}

		res = tempPlayer.countDistance(Coordinate(2, 5, 4), 4, false, true, -1);
		if (res != 3) {
			std::cout << "the distance was supposed to be 3 (2,5,4) !!!!  got " << res << " :(" << std::endl;
		}

		res = tempPlayer.countDistance(Coordinate(2, 1, 4), 4, false, true, +1);
		if (res != 3) {
			std::cout << "the distance was supposed to be 3 (2,1,4)!!!!  got " << res << " :(" << std::endl;
		}

		// wall at 2,6,4
		res = tempPlayer.countDistance(Coordinate(2, 5, 4), 5, false, true, -1);
		if (res != 4) {
			std::cout << "the distance was supposed to be 4 (2,6,4) !!!!  got " << res << " :(" << std::endl;
		}
	}

	{
		PlayerSmart tempPlayer;
		for (int i = 1; i < 6; i++) {
			for (int j = 1; j < 6; j++) {
				for (int k = 1; k < 6; k++) {
					tempPlayer.attackOptions.insert(Coordinate(i, j, k));
				}
			}
		}
		int res;
		//// Vertical !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		tempPlayer.attackOptions.erase(tempPlayer.attackOptions.find(Coordinate(5, 3, 4)));
		tempPlayer.attackOptions.erase(tempPlayer.attackOptions.find(Coordinate(1, 3, 4)));

		res = tempPlayer.countDistance(Coordinate(5, 3, 4), 0, true, false, -1);
		if (res != -1) {
			std::cout << "the distance was supposed to be -1 !!!!(vertical)  got " << res << " :(" << std::endl;
		}

		res = tempPlayer.countDistance(Coordinate(5, 3, 4), 5, true, false, -1);
		if (res != 4) {
			std::cout << "the distance was supposed to be 4 (5,3,4) !!!!  got " << res << " :(" << std::endl;
		}

		res = tempPlayer.countDistance(Coordinate(1, 3, 4), 5, true, false, +1);
		if (res != 4) {
			std::cout << "the distance was supposed to be 4 (1,3,4)!!!!  got " << res << " :(" << std::endl;
		}

		// wall at 6,3,4
		res = tempPlayer.countDistance(Coordinate(5, 3, 4), 5, true, false, +1);
		if (res != 0) {
			std::cout << "the distance was supposed to be 0 (6,3,4) !!!!  got " << res << " :(" << std::endl;
		}
	}
	{
		PlayerSmart tempPlayer;
		for (int i = 1; i < 10; i++) {
			for (int j = 1; j < 10; j++) {
				for (int k = 1; k < 10; k++) {
					tempPlayer.attackOptions.insert(Coordinate(i, j, k));
				}
			}
		}
		int res;

		//// deptical !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		tempPlayer.attackOptions.erase(tempPlayer.attackOptions.find(Coordinate(7, 3, 1)));
		tempPlayer.attackOptions.erase(tempPlayer.attackOptions.find(Coordinate(7, 3, 8)));

		res = tempPlayer.countDistance(Coordinate(7, 3, 8), 0, false, false, -1);
		if (res != -1) {
			std::cout << "the distance was supposed to be -1 !!!!(horizontal)  got " << res << " :(" << std::endl;
		}

		res = tempPlayer.countDistance(Coordinate(7, 3, 8), 7, false, false, -1);
		if (res != 6) {
			std::cout << "the distance was supposed to be 6 (7,3,8) !!!!  got " << res << " :(" << std::endl;
		}

		res = tempPlayer.countDistance(Coordinate(7, 3, 1), 7, false, false, +1);
		if (res != 6) {
			std::cout << "the distance was supposed to be 6 (7,3,1)!!!!  got " << res << " :(" << std::endl;
		}

		// wall at 7,3,10
		res = tempPlayer.countDistance(Coordinate(7, 3, 1), 10, false, false, +1);
		if (res != 8) {
			std::cout << "the distance was supposed to be 8 (7, 3, 1) wall !!!!  got " << res << " :(" << std::endl;
		}
	}
	std::cout << "Hopefully we got here and the count function works fine !!! praise the lord!!!!!" << std::endl;

}

int testPlayerSmart::testisInAttackOptions()
{
	PlayerSmart tempPlayer;
	Coordinate coorToInsert(0, 0, 0);

	for (int i = 1; i < 6; i++) {
		for (int j = 1; j < 6; j++) {
			for (int k = 1; k < 6; k++) {
				tempPlayer.attackOptions.insert(Coordinate(i, j, k));
			}
		}
	}

	bool res = tempPlayer.isInAttackOptions(Coordinate(1, 1, 1));
	std::cout << "should be true " << res << std::endl;
	res = tempPlayer.isInAttackOptions(Coordinate(6, 6, 6));
	std::cout << "should be false " << res << std::endl;
	res = tempPlayer.isInAttackOptions(Coordinate(3, 2, 2));
	std::cout << "should be true " << res << std::endl;
	res = tempPlayer.isInAttackOptions(Coordinate(0, 0, 0));
	std::cout << "should be fales " << res << std::endl;
	res = tempPlayer.isInAttackOptions(Coordinate(7, 7, 7));
	std::cout << "should be false " << res << std::endl;
	return 0;
}

int testPlayerSmart::testremoveOneCoordinate()
{
	PlayerSmart tempPlayer;

	for (int i = 1; i < 6; i++) {
		for (int j = 1; j < 6; j++) {
			for (int k = 1; k < 6; k++) {
				tempPlayer.attackOptions.insert(Coordinate(i, j, k));
			}
		}
	}
	Coordinate tmpPair = Coordinate(1, 1, 1);

	tempPlayer.removeOneCoordinate(tmpPair);
	auto find = tempPlayer.attackOptions.find(Coordinate(1, 1, 1));
	if (find != tempPlayer.attackOptions.end())
	{
		std::cout << "not good!didnt delete! " << std::endl;
	}
	else {//didnt find it was deleted before
		std::cout << " good! deleted:)! " << std::endl;
	}


	return 0;
}
int testPlayerSmart::testremoveAllIrreleventCoordinates()
{
	PlayerSmart tempPlayer;

	for (int i = 1; i < 8; i++) {
		for (int j = 1; j < 8; j++) {
			for (int k = 1; k < 8; k++) {
				tempPlayer.attackOptions.insert(Coordinate(i, j, k));
			}
		}
	}
	//case of in edge(shuold remove only one side) vertical
	tempPlayer.removeAllIrreleventCoordinates(Coordinate(1, 1, 1), true, false, false);
	auto find = tempPlayer.attackOptions.find(Coordinate(1, 2, 1));
	auto find2 = tempPlayer.attackOptions.find(Coordinate(1, 1, 2));

	if (find != tempPlayer.attackOptions.end())
	{
		std::cout << "not good!didnt delete 1,2,1 wich is erelevent for vertical! " << std::endl;
	}
	else {
		std::cout << "good boy! " << std::endl;
	}
	if (find2 != tempPlayer.attackOptions.end())
	{
		std::cout << "not good!didnt delete 1,1,2 wich is erelevent for vertical! " << std::endl;
	}
	else {
		std::cout << "good boy! " << std::endl;
	}
	//case of in edge(shuold remove only one side) horizontal
	tempPlayer.removeAllIrreleventCoordinates(Coordinate(8, 8, 8), false, true, false);
	find = tempPlayer.attackOptions.find(Coordinate(7, 8, 8));
	find2 = tempPlayer.attackOptions.find(Coordinate(8, 8, 7));

	if (find != tempPlayer.attackOptions.end())
	{
		std::cout << "not good!didnt delete 7,8,8! wich is erelevent for horizontal! " << std::endl;
	}
	else {
		std::cout << "good boy! " << std::endl;
	}

	if (find2 != tempPlayer.attackOptions.end())
	{
		std::cout << "not good!didnt delete 8,8,7! wich is erelevent for horizontal! " << std::endl;
	}
	else {
		std::cout << "good boy! " << std::endl;
	}
	//case of in edge(shuold remove only one side) dimentional
	tempPlayer.removeAllIrreleventCoordinates(Coordinate(8, 8, 8), false, true, false);
	find = tempPlayer.attackOptions.find(Coordinate(7, 8, 8));
	find2 = tempPlayer.attackOptions.find(Coordinate(8, 7, 8));

	if (find != tempPlayer.attackOptions.end())
	{
		std::cout << "not good!didnt delete 7,8,8! wich is erelevent for horizontal! " << std::endl;
	}
	else {
		std::cout << "good boy! " << std::endl;
	}

	if (find2 != tempPlayer.attackOptions.end())
	{
		std::cout << "not good!didnt delete 8,7,8! wich is erelevent for horizontal! " << std::endl;
	}
	else {
		std::cout << "good boy! " << std::endl;
	}
	//case of in middle(shuold remove two side) vertical
	tempPlayer.removeAllIrreleventCoordinates(Coordinate(3, 3, 3), true, false, false);
	find = tempPlayer.attackOptions.find(Coordinate(3, 2, 3));
	if (find != tempPlayer.attackOptions.end())
	{
		std::cout << "not good!didnt delete 3,2,3 wich is erelevent for vertical! " << std::endl;
	}
	else {
		std::cout << "good boy! " << std::endl;
	}
	find = tempPlayer.attackOptions.find(Coordinate(3, 4, 3));
	if (find != tempPlayer.attackOptions.end())
	{
		std::cout << "not good!didnt delete 3,4,3 wich is erelevent for vertical! " << std::endl;
	}
	else {
		std::cout << "good boy! " << std::endl;
	}
	find = tempPlayer.attackOptions.find(Coordinate(3, 3, 2));
	if (find != tempPlayer.attackOptions.end())
	{
		std::cout << "not good!didnt delete 3,3,2 wich is erelevent for dimentional! " << std::endl;
	}
	else {
		std::cout << "good boy! " << std::endl;
	}
	find = tempPlayer.attackOptions.find(Coordinate(3, 3, 4));
	if (find != tempPlayer.attackOptions.end())
	{
		std::cout << "not good!didnt delete 3,3,4 wich is erelevent for dimentional! " << std::endl;
	}
	else {
		std::cout << "good boy! " << std::endl;
	}

	//case of in middle(shuold remove two side) horizontal
	tempPlayer.removeAllIrreleventCoordinates(Coordinate(6, 6, 6), false, true, false);
	find = tempPlayer.attackOptions.find(Coordinate(5, 6, 6));
	if (find != tempPlayer.attackOptions.end())
	{
		std::cout << "not good!didnt delete 5,6,6! wich is erelevent for horizontal! " << std::endl;
	}
	else {
		std::cout << "good boy! " << std::endl;
	}
	find = tempPlayer.attackOptions.find(Coordinate(7, 6, 6));
	if (find != tempPlayer.attackOptions.end())
	{
		std::cout << "not good!didnt delete 7,6,6! wich is erelevent for horizontal! " << std::endl;
	}
	else {
		std::cout << "good boy! " << std::endl;
	}
	find = tempPlayer.attackOptions.find(Coordinate(6, 6, 5));
	if (find != tempPlayer.attackOptions.end())
	{
		std::cout << "not good!didnt delete 6,6,5! wich is erelevent for horizontal! " << std::endl;
	}
	else {
		std::cout << "good boy! " << std::endl;
	}
	find = tempPlayer.attackOptions.find(Coordinate(6, 6, 7));
	if (find != tempPlayer.attackOptions.end())
	{
		std::cout << "not good!didnt delete 6,6,7! wich is erelevent for horizontal! " << std::endl;
	}
	else {
		std::cout << "good boy! " << std::endl;
	}
	//case of in middle(shuold remove two side) dimentional
	tempPlayer.removeAllIrreleventCoordinates(Coordinate(6, 6, 6), false, false, true);
	find = tempPlayer.attackOptions.find(Coordinate(5, 6, 6));
	if (find != tempPlayer.attackOptions.end())
	{
		std::cout << "not good!didnt delete 5,6,6! wich is erelevent for horizontal! " << std::endl;
	}
	else {
		std::cout << "good boy! " << std::endl;
	}
	find = tempPlayer.attackOptions.find(Coordinate(7, 6, 6));
	if (find != tempPlayer.attackOptions.end())
	{
		std::cout << "not good!didnt delete 7,6,6! wich is erelevent for horizontal! " << std::endl;
	}
	else {
		std::cout << "good boy! " << std::endl;
	}
	find = tempPlayer.attackOptions.find(Coordinate(6, 5, 6));
	if (find != tempPlayer.attackOptions.end())
	{
		std::cout << "not good!didnt delete 6,5,6! wich is erelevent for horizontal! " << std::endl;
	}
	else {
		std::cout << "good boy! " << std::endl;
	}
	find = tempPlayer.attackOptions.find(Coordinate(6, 7, 6));
	if (find != tempPlayer.attackOptions.end())
	{
		std::cout << "not good!didnt delete 6,7,6! wich is erelevent for horizontal! " << std::endl;
	}
	else {
		std::cout << "good boy! " << std::endl;
	}

	return 0;
}
int testPlayerSmart::testmergeShipDetails()
{
	PlayerSmart tmpPlayer;
	std::vector<ShipInProcess> allShips;

	//create Set of options
	for (int i = 1; i<10; i++)
	{
		for (int j = 1; j<10; j++)
		{
			for (int k = 1; k < 10; k++) {
				tmpPlayer.attackOptions.insert(Coordinate(i, j, k));
			}

		}
	}

	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(1, 1, 1)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 1, 1)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(3, 8, 8)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(7, 8, 8)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(8, 8, 8)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 3, 2)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 5, 2)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 4, 2)));


	// create ships
	ShipInProcess sizeOne_1(1, 1, 1);
	ShipInProcess sizeOne_2(3, 8, 8);
	ShipInProcess sizeOne_3(7, 9, 8);

	ShipInProcess sizeTwo_1(7, 8, 8);
	sizeTwo_1.addCoordinate(8, 8, 8);

	ShipInProcess sizeThree_1(4, 3, 2);
	sizeThree_1.addCoordinate(4, 4, 2);
	sizeThree_1.addCoordinate(4, 5, 2);

	ShipInProcess sizeTwo_2(4, 1, 2);
	sizeTwo_2.addCoordinate(4, 2, 2);

	ShipInProcess sizeThree_2(2, 4, 7);
	sizeThree_2.addCoordinate(2, 4, 8);
	sizeThree_2.addCoordinate(2, 4, 9);

	ShipInProcess sizeTwo_3(2, 4, 5);
	sizeTwo_3.addCoordinate(2, 4, 6);

	allShips.push_back(sizeThree_2);
	allShips.push_back(sizeThree_1);
	allShips.push_back(sizeTwo_3);
	allShips.push_back(sizeTwo_2);
	allShips.push_back(sizeTwo_1);
	allShips.push_back(sizeOne_1);
	allShips.push_back(sizeOne_2);
	allShips.push_back(sizeOne_3);


	tmpPlayer.attackedShips = allShips;


	std::cout << "this is before marged 3,4,5 with 1, 2 " << std::endl;

	int i = 0;
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

	std::cout << "this is after marged 3,4,5 with 1, 2 ,shuold have marged  3,4,5 with 1, 2 and erace not needed vector" << std::endl;
	Coordinate nextPairTosearch = Coordinate(4, 2, 2);
	tmpPlayer.mergeShipDetails(&nextPairTosearch, 0);// does one is the first index or second(i need second)

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


	std::cout << "before another try for marge " << std::endl;

	nextPairTosearch = Coordinate(4, 3, 2);
	tmpPlayer.mergeShipDetails(&nextPairTosearch, 2);// does one is the first index or second(i need second)

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

	std::cout << "shuold not have marged/chenged " << std::endl;

	std::cout << "now for dimentional merge...this is before marged 3,4,5 with 1, 2 " << std::endl;
	std::cout << "this is before marged 3,4,5 with 1, 2 " << std::endl;

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

	std::cout << "this is after marged 7,8,9 with 5, 6,shuold have marged   7,8,9 with 5,6 and erace not needed vector" << std::endl;
	Coordinate nextPairTosearch4 (2, 4, 7);
	tmpPlayer.mergeShipDetails(&nextPairTosearch4, 0);// does one is the first index or second(i need second)

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


	std::cout << "before another try for marge " << std::endl;

	Coordinate nextPairTosearch2 (2, 4, 8);
	tmpPlayer.mergeShipDetails(&nextPairTosearch2, 2);// does one is the first index or second(i need second)

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

	std::cout << "shuold not have marged/chenged " << std::endl;



	std::cout << "this is after marged 7,8-8 with 7,9,shuold not marged !!!" << std::endl;
	Coordinate nextPairTosearch3(7, 9, 8);
	tmpPlayer.mergeShipDetails(&nextPairTosearch3, 1);// does one is the first index or second(i need second)

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

	return 0;
}

int testPlayerSmart::testremoveSankFromReleventCoors()
{
	PlayerSmart tmpPlayer;
	std::vector<ShipInProcess> allShips;

	//create Set of options
	for (int i = 1; i<10; i++)
	{
		for (int j = 1; j<10; j++)
		{
			for (int k = 1; k < 10; k++) {
				tmpPlayer.attackOptions.insert(Coordinate(i, j, k));
			}
		}
	}

	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(1, 1, 1)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 1, 1)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(3, 8, 1)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(7, 8, 1)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(8, 8, 1)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 3, 1)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 5, 1)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 4, 1)));


	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(3, 3, 1)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(3, 4, 1)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(3, 5, 1)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(5, 3, 1)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(5, 4, 1)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(5, 5, 1)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(7, 7, 1)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(8, 7, 1)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(7, 9, 1)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(8, 9, 1)));


	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(7, 3, 1)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(7, 3, 2)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(7, 3, 3)));

	// create ships
	ShipInProcess sizeOne_1(1, 1, 1);
	ShipInProcess sizeOne_2(3, 8, 1);

	ShipInProcess sizeTwo_1(7, 8, 1);
	sizeTwo_1.addCoordinate(8, 8, 1);

	ShipInProcess sizeThree_1(4, 3, 1);
	sizeThree_1.addCoordinate(4, 4, 1);
	sizeThree_1.addCoordinate(4, 5, 1);

	ShipInProcess sizeThree_2(7, 3, 1);
	sizeThree_2.addCoordinate(7, 3, 2);
	sizeThree_2.addCoordinate(7, 3, 3);


	allShips.push_back(sizeThree_1);
	allShips.push_back(sizeThree_2);
	allShips.push_back(sizeTwo_1);
	allShips.push_back(sizeOne_1);
	allShips.push_back(sizeOne_2);

	tmpPlayer.attackedShips = allShips;

	tmpPlayer.removeSankFromReleventCoors(0);
	std::cout << "checking for vector 4-3,4,5 - horizontal " << std::endl;
	auto find = tmpPlayer.attackOptions.find(Coordinate(4, 2, 1));
	if (find != tmpPlayer.attackOptions.end())
	{
		std::cout << "not good!didnt delete 4,2,1! " << std::endl;
	}
	else {//didnt find it was deleted before
		std::cout << " good!4,2,1 deleted:)! " << std::endl;
	}
	find = tmpPlayer.attackOptions.find(Coordinate(4, 6, 1));
	if (find != tmpPlayer.attackOptions.end())
	{
		std::cout << "not good!didnt delete 4,6,1! " << std::endl;
	}
	else {//didnt find it was deleted before
		std::cout << " good! 4,6,1 deleted:)! " << std::endl;
	}

	//check for dimentuonal
	tmpPlayer.removeSankFromReleventCoors(0);
	std::cout << "checking for vector 7,3-1,2,3 - horizontal " << std::endl;

	Coordinate coor(4, 2, 1);
	if (tmpPlayer.isInAttackOptions(coor))
	{
		std::cout << "not good!didnt delete 7,3,4! " << std::endl;
	}
	else {//didnt find it was deleted before
		std::cout << " good!7,3,4 deleted:)! " << std::endl;
	}


	tmpPlayer.removeSankFromReleventCoors(0);
	std::cout << "checking for vector 7,8-8 - vertical" << std::endl;
	find = tmpPlayer.attackOptions.find(Coordinate(6, 8, 1));
	if (find != tmpPlayer.attackOptions.end())
	{
		std::cout << "not good!didnt delete 6,8,1! " << std::endl;
	}
	else {//didnt find it was deleted before
		std::cout << " good!6,8 deleted:)! " << std::endl;
	}
	find = tmpPlayer.attackOptions.find(Coordinate(9, 8, 1));
	if (find != tmpPlayer.attackOptions.end())
	{
		std::cout << "not good!didnt delete 9,8,1! " << std::endl;
	}
	else {//didnt find it was deleted before
		std::cout << " good! 9,8,1 deleted:)! " << std::endl;
	}

	std::cout << " check that the vector 7,8-8 and 4-3,4,5 are gone!-->" << std::endl;
	int i = 0;
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

	return 0;
}

int testPlayerSmart::testnotifyOnAttackResult()
{
	{
		PlayerSmart tmpPlayer;
		std::vector<ShipInProcess> allShips;

		//create Set of options
		for (int i = 1; i < 10; i++)
		{
			for (int j = 1; j < 10; j++)
			{
				for (int k = 1; k < 10; k++) {
					tmpPlayer.attackOptions.insert(Coordinate(i, j, k));

				}
			}
		}

		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(1, 1, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 1, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(3, 8, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(7, 8, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(8, 8, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 3, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 5, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 4, 1)));


		// clear envirnment
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(7, 6, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(8, 6, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(7, 9, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(8, 9, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(3, 3, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(3, 5, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(3, 4, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(5, 3, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(5, 5, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(5, 4, 1)));


		// create ships
		ShipInProcess sizeOne_1(1, 1, 1);
		ShipInProcess sizeOne_2(3, 8, 1);
		ShipInProcess sizeOne_3(9, 2, 1);


		ShipInProcess sizeTwo_1(7, 8, 1);
		sizeTwo_1.addCoordinate(8, 8, 1);

		ShipInProcess sizeThree_1(4, 3, 1);
		sizeThree_1.addCoordinate(4, 4, 1);
		sizeThree_1.addCoordinate(4, 5, 1);

		ShipInProcess sizeTwo_2(5, 8, 1);

		allShips.push_back(sizeThree_1);
		allShips.push_back(sizeTwo_1);
		allShips.push_back(sizeTwo_2);
		allShips.push_back(sizeOne_3);
		allShips.push_back(sizeOne_1);
		allShips.push_back(sizeOne_2);

		tmpPlayer.attackedShips = allShips;
		//miss
		auto find = tmpPlayer.attackOptions.find(Coordinate(8, 2, 1));
		tmpPlayer.notifyOnAttackResult(0, Coordinate(8, 2, 1), AttackResult::Miss);//miss 8,2,1
		find = tmpPlayer.attackOptions.find(Coordinate(8, 2, 1));
		if (find != tmpPlayer.attackOptions.end())
		{
			std::cout << "not good!didnt delete 8,2,1 to options ! " << std::endl;
		}
		else {
			std::cout << " good!8,2,1 deleted from options:)! " << std::endl;
		}


		//hit (merge one coor with one ship)
		find = tmpPlayer.attackOptions.find(Coordinate(4, 2, 1));
		tmpPlayer.notifyOnAttackResult(0, Coordinate(4, 2, 1), AttackResult::Hit);//Hit 4,2
		find = tmpPlayer.attackOptions.find(Coordinate(4, 2, 1));
		if (find != tmpPlayer.attackOptions.end())
		{
			std::cout << "not good!didnt deleted 4,2,1 to options ! " << std::endl;
		}
		else {
			std::cout << " good !4,2,1 deleted from options:)! " << std::endl;
		}

		std::cout << " should be here vector horizontal 4-2,3,4,5 " << std::endl;
		int i = 0;
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



		//hit (merge one coor with one ship)
		find = tmpPlayer.attackOptions.find(Coordinate(2, 1, 1));
		tmpPlayer.notifyOnAttackResult(0, Coordinate(2, 1, 1), AttackResult::Hit);//Hit 2,1
		find = tmpPlayer.attackOptions.find(Coordinate(2, 1, 1));
		if (find != tmpPlayer.attackOptions.end())
		{
			std::cout << "not good!didnt deleted 2,1,1 to options ! " << std::endl;
		}
		else {
			std::cout << " good !2,1,1 deleted from options:)! " << std::endl;
		}

		std::cout << " should be here vector horizontal 1,2-1 " << std::endl;
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

		//hit merge two vectors 
		find = tmpPlayer.attackOptions.find(Coordinate(6, 8, 1));
		tmpPlayer.notifyOnAttackResult(0, Coordinate(6, 8, 1), AttackResult::Hit);//Hit 6,8
		find = tmpPlayer.attackOptions.find(Coordinate(6, 8, 1));
		if (find != tmpPlayer.attackOptions.end())
		{
			std::cout << "not good!didnt deleted 6,8,1 to options ! " << std::endl;
		}
		else {
			std::cout << " good !6,8,1 deleted from options:)! " << std::endl;
		}

		std::cout << " should be here vector vertical 5,6,7,8-8 and delete vector single 5,8 " << std::endl;
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

		//sink
		find = tmpPlayer.attackOptions.find(Coordinate(2, 8, 1));
		tmpPlayer.notifyOnAttackResult(0, Coordinate(2, 8, 1), AttackResult::Sink);//Hit 6,8
		find = tmpPlayer.attackOptions.find(Coordinate(2, 8, 1));
		if (find != tmpPlayer.attackOptions.end())
		{
			std::cout << "not good!didnt deleted 2,8,1 to options ! " << std::endl;
		}
		else {
			std::cout << " good !2,8,1 deleted from options:)! " << std::endl;
		}

		std::cout << " should  delete vector 2,3-8 " << std::endl;
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

	}


	//for dimentuonal //////////////////////////////////////////////////////////////////////////////////////////
	{
		PlayerSmart tmpPlayer2;
		std::vector<ShipInProcess> allShips2;

		//create Set of options
		for (int i = 1; i < 10; i++)
		{
			for (int j = 1; j < 10; j++)
			{
				for (int k = 1; k < 10; k++) {
					tmpPlayer2.attackOptions.insert(Coordinate(i, j, k));

				}
			}
		}

		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 1, 1)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 4, 1)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 3, 8)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 7, 8)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 8, 8)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 4, 3)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 4, 5)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 4, 4)));


		// clear envirnment
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 7, 6)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 8, 6)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 7, 9)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 8, 9)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 3, 3)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 3, 5)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 3, 4)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 5, 3)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 5, 5)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 5, 4)));


		// create ships
		ShipInProcess sizeOne_1(2, 1, 1);
		ShipInProcess sizeOne_2(2, 3, 8);
		ShipInProcess sizeOne_3(2, 9, 2);


		ShipInProcess sizeTwo_1(2, 7, 8);
		sizeTwo_1.addCoordinate(2, 8, 8);

		ShipInProcess sizeThree_1(2, 4, 3);
		sizeThree_1.addCoordinate(2, 4, 4);
		sizeThree_1.addCoordinate(2, 4, 5);

		ShipInProcess sizeTwo_2(2, 5, 8);

		allShips2.push_back(sizeThree_1);
		allShips2.push_back(sizeTwo_1);
		allShips2.push_back(sizeTwo_2);
		allShips2.push_back(sizeOne_3);
		allShips2.push_back(sizeOne_1);
		allShips2.push_back(sizeOne_2);

		tmpPlayer2.attackedShips = allShips2;
		//miss
		auto find = tmpPlayer2.attackOptions.find(Coordinate(2, 8, 2));
		tmpPlayer2.notifyOnAttackResult(0, Coordinate(2, 8, 2), AttackResult::Miss);//miss 8,2,1
		find = tmpPlayer2.attackOptions.find(Coordinate(2, 8, 2));
		if (find != tmpPlayer2.attackOptions.end())
		{
			std::cout << "not good!didnt delete 2,8,2 to options ! " << std::endl;
		}
		else {
			std::cout << " good!2,8,2 deleted from options:)! " << std::endl;
		}


		//hit (merge one coor with one ship)
		find = tmpPlayer2.attackOptions.find(Coordinate(2, 4, 2));
		tmpPlayer2.notifyOnAttackResult(0, Coordinate(2, 4, 2), AttackResult::Hit);//Hit 4,2
		find = tmpPlayer2.attackOptions.find(Coordinate(2, 4, 2));
		if (find != tmpPlayer2.attackOptions.end())
		{
			std::cout << "not good!didnt deleted 2,4,2, to options ! " << std::endl;
		}
		else {
			std::cout << " good !2,4,2 deleted from options:)! " << std::endl;
		}

		std::cout << " should be here vector dimentional 2,4-2,3,4,5 " << std::endl;
		int i = 0;
		for (auto& shipDetail : tmpPlayer2.attackedShips)
		{
			std::cout << i;
			for (auto coor : shipDetail.incrementalCoors)
			{
				std::cout << coor << ',';
			}
			std::cout << std::endl;
			i++;
		}



		//hit (merge one coor with one ship)
		find = tmpPlayer2.attackOptions.find(Coordinate(2, 2, 1));
		tmpPlayer2.notifyOnAttackResult(0, Coordinate(2, 2, 1), AttackResult::Hit);//Hit 2,1
		find = tmpPlayer2.attackOptions.find(Coordinate(2, 2, 1));
		if (find != tmpPlayer2.attackOptions.end())
		{
			std::cout << "not good!didnt deleted 2,2,1 to options ! " << std::endl;
		}
		else {
			std::cout << " good !2,2,1 deleted from options:)! " << std::endl;
		}

		std::cout << " should be here vector dimentional 1,2-1 " << std::endl;
		i = 0;
		for (auto& shipDetail : tmpPlayer2.attackedShips)
		{
			std::cout << i;
			for (auto coor : shipDetail.incrementalCoors)
			{
				std::cout << coor << ',';
			}
			std::cout << std::endl;
			i++;
		}

		//hit merge two vectors 
		find = tmpPlayer2.attackOptions.find(Coordinate(2, 6, 8));
		tmpPlayer2.notifyOnAttackResult(0, Coordinate(2, 6, 8), AttackResult::Hit);//Hit 6,8
		find = tmpPlayer2.attackOptions.find(Coordinate(2, 6, 8));
		if (find != tmpPlayer2.attackOptions.end())
		{
			std::cout << "not good!didnt deleted 2,6,8 to options ! " << std::endl;
		}
		else {
			std::cout << " good !2,6,8 deleted from options:)! " << std::endl;
		}

		std::cout << " should be here vector horizontal 5,6,7,8-8 and delete vector single 5,8 " << std::endl;
		i = 0;
		for (auto& shipDetail : tmpPlayer2.attackedShips)
		{
			std::cout << i;
			for (auto coor : shipDetail.incrementalCoors)
			{
				std::cout << coor << ',';
			}
			std::cout << std::endl;
			i++;
		}

		//sink
		find = tmpPlayer2.attackOptions.find(Coordinate(2, 2, 8));
		tmpPlayer2.notifyOnAttackResult(0, Coordinate(2, 2, 8), AttackResult::Sink);//Hit 6,8
		find = tmpPlayer2.attackOptions.find(Coordinate(2, 2, 8));
		if (find != tmpPlayer2.attackOptions.end())
		{
			std::cout << "not good!didnt deleted 2,2,8 to options ! " << std::endl;
		}
		else {
			std::cout << " good !2,2,8 deleted from options:)! " << std::endl;
		}

		std::cout << " should  delete vector 2,3-8 " << std::endl;
		i = 0;
		for (auto& shipDetail : tmpPlayer2.attackedShips)
		{
			std::cout << i;
			for (auto coor : shipDetail.incrementalCoors)
			{
				std::cout << coor << ',';
			}
			std::cout << std::endl;
			i++;
		}
	}

	return 0;
}

int testPlayerSmart::testaddCoorToShipsInProcess()
{
		{
		PlayerSmart tmpPlayer;
		std::vector<ShipInProcess> allShips;

		//create Set of options
		for (int i = 1; i < 10; i++)
		{
			for (int j = 1; j < 10; j++)
			{
				for (int k = 1; k < 10; k++) {
					tmpPlayer.attackOptions.insert(Coordinate(i, j, k));

				}
			}
		}

		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(1, 1, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 1, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(3, 8, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(7, 8, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(8, 8, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 3, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 5, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 4, 1)));


		// clear envirnment
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(7, 6, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(8, 6, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(7, 9, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(8, 9, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(3, 3, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(3, 5, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(3, 4, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(5, 3, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(5, 5, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(5, 4, 1)));

		// create ships
		ShipInProcess sizeOne_1(1, 1, 1);
		ShipInProcess sizeOne_2(3, 8, 1);
		ShipInProcess sizeOne_3(9, 2, 1);


		ShipInProcess sizeTwo_1(7, 8, 1);
		sizeTwo_1.addCoordinate(8, 8, 1);

		ShipInProcess sizeThree_1(4, 3, 1);
		sizeThree_1.addCoordinate(4, 4, 1);
		sizeThree_1.addCoordinate(4, 5, 1);

		ShipInProcess sizeTwo_2(5, 8, 1);

		allShips.push_back(sizeThree_1);
		allShips.push_back(sizeTwo_1);
		allShips.push_back(sizeTwo_2);
		allShips.push_back(sizeOne_3);
		allShips.push_back(sizeOne_1);
		allShips.push_back(sizeOne_2);

		tmpPlayer.attackedShips = allShips;

		int res;
		Coordinate output(-1, -1, -1);
		res = tmpPlayer.addCoorToShipsInProcess(2, 1, 1, &output, AttackResult::Hit);
		if (res != 2)
		{
			std::cout << "error in addCoorToShipsInProcess <2,1,1> ";
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
		std::cout << "next Pair <3,1,1> got:" << output.row << ',' << output.col << ',' << output.depth << std::endl;

		res = tmpPlayer.addCoorToShipsInProcess(4, 6, 1, &output, AttackResult::Sink);
		if (res != 0)
		{
			std::cout << "error in addCoorToShipsInProcess (4,6,1) ";
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
		std::cout << "next Pair <4,7,1> got:" << output.row << ',' << output.col << ',' << output.depth << std::endl;

		/////////////////////////
		res = tmpPlayer.addCoorToShipsInProcess(3, 8, 1, &output, AttackResult::Hit);
		if (res != -1)
		{
			std::cout << "error in addCoorToShipsInProcess  <3,8,1>";
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
		std::cout << "next Pair <4,7,1> got:" << output.row << ',' << output.col << ',' << output.depth << std::endl;

		/////////////////////////
		std::cout << "new ship shoud be added" << std::endl;
		res = tmpPlayer.addCoorToShipsInProcess(7, 2, 1, &output, AttackResult::Hit);
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
		std::cout << "next Pair <4,7,1> got:" << output.row << ',' << output.col << ',' << output.depth << std::endl;
	}	
	//dimentional///////////////////////////////////////////////////////////////////////////////////

	{
		PlayerSmart tmpPlayer2;
		std::vector<ShipInProcess> allShips2;

		//create Set of options
		for (int i = 1; i < 10; i++)
		{
			for (int j = 1; j < 10; j++)
			{
				for (int k = 1; k < 10; k++) {
					tmpPlayer2.attackOptions.insert(Coordinate(i, j, k));

				}
			}
		}

		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 1, 1)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 4, 1)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 3, 8)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 7, 8)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 8, 8)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 4, 3)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 4, 5)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 4, 4)));


		// clear envirnment
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 7, 6)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 8, 6)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 7, 9)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 8, 9)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 3, 3)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 3, 5)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 3, 4)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 5, 3)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 5, 5)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 5, 4)));


		// create ships
		ShipInProcess sizeOne_1(2, 1, 1);
		ShipInProcess sizeOne_2(2, 3, 8);
		ShipInProcess sizeOne_3(2, 9, 2);


		ShipInProcess sizeTwo_1(2, 7, 8);
		sizeTwo_1.addCoordinate(2, 8, 8);

		ShipInProcess sizeThree_1(2, 4, 3);
		sizeThree_1.addCoordinate(2, 4, 4);
		sizeThree_1.addCoordinate(2, 4, 5);

		ShipInProcess sizeTwo_2(2, 5, 8);

		allShips2.push_back(sizeThree_1);
		allShips2.push_back(sizeTwo_1);
		allShips2.push_back(sizeTwo_2);
		allShips2.push_back(sizeOne_3);
		allShips2.push_back(sizeOne_1);
		allShips2.push_back(sizeOne_2);

		tmpPlayer2.attackedShips = allShips2;

		int res;
		Coordinate output(-1, -1, -1);
		res = tmpPlayer2.addCoorToShipsInProcess(2, 2, 1, &output, AttackResult::Hit);
		if (res != 2)
		{
			std::cout << "error in addCoorToShipsInProcess <2,2,1> ";
			return -1;
		}

		// print vector
		int i = 0;
		std::cout << " print vectors: (only one should be different) " << std::endl;
		for (auto& shipDetail : tmpPlayer2.attackedShips)
		{
			std::cout << i;
			for (auto coor : shipDetail.incrementalCoors)
			{
				std::cout << coor << ',';
			}
			std::cout << std::endl;
			i++;
		}
		std::cout << "next Pair <2,3,1> got:" << output.row << ',' << output.col << ',' << output.depth << std::endl;

		res = tmpPlayer2.addCoorToShipsInProcess(2, 4, 6, &output, AttackResult::Sink);
		if (res != 0)
		{
			std::cout << "error in addCoorToShipsInProcess (2,4,6) ";
			return -1;
		}

		// print vector
		std::cout << " print vectors: (3 coors to 4) " << std::endl;
		i = 0;
		for (auto& shipDetail : tmpPlayer2.attackedShips)
		{
			std::cout << i;
			for (auto coor : shipDetail.incrementalCoors)
			{
				std::cout << coor << ',';
			}

			std::cout << std::endl;
			i++;
		}
		std::cout << "next Pair <2,4,7> got:" << output.row << ',' << output.col << ',' << output.depth << std::endl;

		/////////////////////////
		res = tmpPlayer2.addCoorToShipsInProcess(2, 3, 8, &output, AttackResult::Hit);
		if (res != -1)
		{
			std::cout << "error in addCoorToShipsInProcess  <2,3,8>";
			return -1;
		}

		// print vector
		i = 0;
		std::cout << "should be the same as before" << std::endl;
		for (auto& shipDetail : tmpPlayer2.attackedShips)
		{
			std::cout << i;
			for (auto coor : shipDetail.incrementalCoors)
			{
				std::cout << coor << ',';
			}

			std::cout << std::endl;
			i++;
		}
		std::cout << "next Pair <2,4,7> got:" << output.row << ',' << output.col << ',' << output.depth << std::endl;

		/////////////////////////
		std::cout << "new ship shoud be added" << std::endl;
		res = tmpPlayer2.addCoorToShipsInProcess(2, 7, 2, &output, AttackResult::Hit);
		if (res != -1)
		{
			std::cout << "error in addCoorToShipsInProcess ";
			return -1;
		}

		// print vector
		i = 0;
		for (auto& shipDetail : tmpPlayer2.attackedShips)
		{
			std::cout << i;
			for (auto coor : shipDetail.incrementalCoors)
			{
				std::cout << coor << ',';
			}

			std::cout << std::endl;
			i++;
		}
		std::cout << "next Pair <2,4,7> got:" << output.row << ',' << output.col << ',' << output.depth << std::endl;
	}
	return 0;
}

int testPlayerSmart::testnextAttackFromCoors()
{
	{
		PlayerSmart tmpPlayer;
		std::vector<ShipInProcess> allShips;

		//create Set of options
		for (int i = 1; i < 10; i++)
		{
			for (int j = 1; j < 10; j++)
			{
				for (int k = 1; k < 10; k++) {
					tmpPlayer.attackOptions.insert(Coordinate(i, j, k));

				}
			}
		}

		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(1, 1, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 1, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(3, 8, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(7, 8, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(8, 8, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 3, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 5, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 4, 1)));


		// clear envirnment
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(7, 6, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(8, 6, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(7, 9, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(8, 9, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(3, 3, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(3, 5, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(3, 4, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(5, 3, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(5, 5, 1)));
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(5, 4, 1)));

		// create ships
		ShipInProcess sizeOne_1(1, 1, 1);
		ShipInProcess sizeOne_2(3, 8, 1);
		ShipInProcess sizeOne_3(9, 2, 1);


		ShipInProcess sizeTwo_1(7, 8, 1);
		sizeTwo_1.addCoordinate(8, 8, 1);

		ShipInProcess sizeThree_1(4, 3, 1);
		sizeThree_1.addCoordinate(4, 4, 1);
		sizeThree_1.addCoordinate(4, 5, 1);

		ShipInProcess sizeTwo_2(5, 8, 1);

		allShips.push_back(sizeThree_1);
		allShips.push_back(sizeTwo_1);
		allShips.push_back(sizeTwo_2);
		allShips.push_back(sizeOne_3);
		allShips.push_back(sizeOne_1);
		allShips.push_back(sizeOne_2);


		tmpPlayer.attackedShips = allShips;


		Coordinate nextCoor(-1, -1, -1);
		nextCoor = tmpPlayer.nextAttackFromCoors(sizeThree_1, 3);

		if ((nextCoor.row != 4) || (nextCoor.col != 2) || (nextCoor.depth != 1))
		{
			std::cout << "error <4,2,1>" << std::endl;
			return -1;
		}

		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(nextCoor));
		nextCoor = Coordinate(4, 1, 1);
		tmpPlayer.removeOneCoordinate(nextCoor);
		nextCoor = Coordinate(3, 2, 1);
		tmpPlayer.removeOneCoordinate(nextCoor);
		nextCoor = Coordinate(5, 2, 1);
		tmpPlayer.removeOneCoordinate(nextCoor);

		nextCoor = tmpPlayer.nextAttackFromCoors(sizeThree_1, 4);
		if ((nextCoor.row != 4) || (nextCoor.col != 6) || (nextCoor.depth != 1))
		{
			std::cout << "error <4,6,1>" << std::endl;
			return -1;
		}
		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(nextCoor));


		nextCoor = tmpPlayer.nextAttackFromCoors(sizeTwo_1, 2);
		if ((nextCoor.row != 6) || (nextCoor.col != 8) || (nextCoor.depth != 1))
		{
			std::cout << "error <6,8>" << std::endl;
			return -1;
		}
		std::cout << "done!" << std::endl;
	}
	//dimentional///////////////////////////////////////////////////////////////////////////////////////////////////

	{
		PlayerSmart tmpPlayer2;
		std::vector<ShipInProcess> allShips2;

		//create Set of options
		for (int i = 1; i < 10; i++)
		{
			for (int j = 1; j < 10; j++)
			{
				for (int k = 1; k < 10; k++) {
					tmpPlayer2.attackOptions.insert(Coordinate(i, j, k));

				}
			}
		}

		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 1, 1)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 4, 1)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 3, 8)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 7, 8)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 8, 8)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 4, 3)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 4, 5)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 4, 4)));


		// clear envirnment
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 7, 6)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 8, 6)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 7, 9)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 8, 9)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 3, 3)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 3, 5)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 3, 4)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 5, 3)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 5, 5)));
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 5, 4)));


		// create ships
		ShipInProcess sizeOne_1(2, 1, 1);
		ShipInProcess sizeOne_2(2, 3, 8);
		ShipInProcess sizeOne_3(2, 9, 2);


		ShipInProcess sizeTwo_1(2, 7, 8);
		sizeTwo_1.addCoordinate(2, 8, 8);

		ShipInProcess sizeThree_1(2, 4, 3);
		sizeThree_1.addCoordinate(2, 4, 4);
		sizeThree_1.addCoordinate(2, 4, 5);

		ShipInProcess sizeTwo_2(2, 5, 8);

		allShips2.push_back(sizeThree_1);
		allShips2.push_back(sizeTwo_1);
		allShips2.push_back(sizeTwo_2);
		allShips2.push_back(sizeOne_3);
		allShips2.push_back(sizeOne_1);
		allShips2.push_back(sizeOne_2);

		tmpPlayer2.attackedShips = allShips2;



		Coordinate nextCoor(-1, -1, -1);
		nextCoor = tmpPlayer2.nextAttackFromCoors(sizeThree_1, 3);

		if ((nextCoor.row != 2) || (nextCoor.col != 4) || (nextCoor.depth != 2))
		{
			std::cout << "error <2,4,2>" << std::endl;
			return -1;
		}

		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(nextCoor));
		nextCoor = Coordinate(2, 4, 1);
		tmpPlayer2.removeOneCoordinate(nextCoor);
		nextCoor = Coordinate(2, 3, 2);
		tmpPlayer2.removeOneCoordinate(nextCoor);
		nextCoor = Coordinate(2, 5, 2);
		tmpPlayer2.removeOneCoordinate(nextCoor);

		nextCoor = tmpPlayer2.nextAttackFromCoors(sizeThree_1, 4);
		if ((nextCoor.row != 2) || (nextCoor.col != 4) || (nextCoor.depth != 6))
		{
			std::cout << "error <2,4,6>" << std::endl;
			return -1;
		}
		tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(nextCoor));


		nextCoor = tmpPlayer2.nextAttackFromCoors(sizeTwo_1, 2);
		if ((nextCoor.row != 2) || (nextCoor.col != 6) || (nextCoor.depth != 8))
		{
			std::cout << "error <2,6,8>" << std::endl;
			return -1;
		}
		std::cout << "done!" << std::endl;

	}
	return 0;

}

int testPlayerSmart::testfindPairInAttackedShips()
{
	{
		{
			PlayerSmart tmpPlayer;
			std::vector<ShipInProcess> allShips;

			//create Set of options
			for (int i = 1; i < 10; i++)
			{
				for (int j = 1; j < 10; j++)
				{
					for (int k = 1; k < 10; k++) {
						tmpPlayer.attackOptions.insert(Coordinate(i, j, k));

					}
				}
			}

			tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(1, 1, 1)));
			tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 1, 1)));
			tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(3, 8, 1)));
			tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(7, 8, 1)));
			tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(8, 8, 1)));
			tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 3, 1)));
			tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 5, 1)));
			tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 4, 1)));


			// clear envirnment
			tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(7, 6, 1)));
			tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(8, 6, 1)));
			tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(7, 9, 1)));
			tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(8, 9, 1)));
			tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(3, 3, 1)));
			tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(3, 5, 1)));
			tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(3, 4, 1)));
			tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(5, 3, 1)));
			tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(5, 5, 1)));
			tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(5, 4, 1)));

			// create ships
			ShipInProcess sizeOne_1(1, 1, 1);
			ShipInProcess sizeOne_2(3, 8, 1);
			ShipInProcess sizeOne_3(9, 2, 1);


			ShipInProcess sizeTwo_1(7, 8, 1);
			sizeTwo_1.addCoordinate(8, 8, 1);

			ShipInProcess sizeThree_1(4, 3, 1);
			sizeThree_1.addCoordinate(4, 4, 1);
			sizeThree_1.addCoordinate(4, 5, 1);

			ShipInProcess sizeTwo_2(5, 8, 1);

			allShips.push_back(sizeThree_1);
			allShips.push_back(sizeTwo_1);
			allShips.push_back(sizeTwo_2);
			allShips.push_back(sizeOne_3);
			allShips.push_back(sizeOne_1);
			allShips.push_back(sizeOne_2);

			tmpPlayer.attackedShips = allShips;
			int res;
			res = tmpPlayer.findCoorInAttackedShips(Coordinate(4, 3, 1), 0);
			if (res != 0)
			{
				std::cout << "error <4,3,1> 0" << std::endl;
				return -1;
			}

			res = tmpPlayer.findCoorInAttackedShips(Coordinate(4, 3, 1), 2);
			if (res != -1)
			{
				std::cout << "error <4,3,1> 2" << std::endl;
				return -1;
			}

			res = tmpPlayer.findCoorInAttackedShips(Coordinate(4, 3, 1), 4);
			if (res != -1)
			{
				std::cout << "error <4,3,1>  4" << std::endl;
				return -1;
			}


			res = tmpPlayer.findCoorInAttackedShips(Coordinate(10, 10, 1), 0);
			if (res != -1)
			{
				std::cout << "error <10,10,1>  0" << std::endl;
				return -1;
			}


			res = tmpPlayer.findCoorInAttackedShips(Coordinate(4, 6, 1), 0);
			if (res != -1)
			{
				std::cout << "error <4,6,1>  0" << std::endl;
				return -1;
			}


			res = tmpPlayer.findCoorInAttackedShips(Coordinate(3, 8, 1), 0);
			if (res != 3)
			{
				std::cout << "error <3,8,1> 0" << std::endl;
				return -1;
			}

		}

	}
	////////////////////////////////////dimentional

	{

		{
			PlayerSmart tmpPlayer2;
			std::vector<ShipInProcess> allShips2;

			//create Set of options
			for (int i = 1; i < 10; i++)
			{
				for (int j = 1; j < 10; j++)
				{
					for (int k = 1; k < 10; k++) {
						tmpPlayer2.attackOptions.insert(Coordinate(i, j, k));

					}
				}
			}

			tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 1, 1)));
			tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 4, 1)));
			tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 3, 8)));
			tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 7, 8)));
			tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 8, 8)));
			tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 4, 3)));
			tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 4, 5)));
			tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 4, 4)));


			// clear envirnment
			tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 7, 6)));
			tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 8, 6)));
			tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 7, 9)));
			tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 8, 9)));
			tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 3, 3)));
			tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 3, 5)));
			tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 3, 4)));
			tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 5, 3)));
			tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 5, 5)));
			tmpPlayer2.attackOptions.erase(tmpPlayer2.attackOptions.find(Coordinate(2, 5, 4)));


			// create ships
			ShipInProcess sizeOne_1(2, 1, 1);
			ShipInProcess sizeOne_2(2, 3, 8);
			ShipInProcess sizeOne_3(2, 9, 2);


			ShipInProcess sizeTwo_1(2, 7, 8);
			sizeTwo_1.addCoordinate(2, 8, 8);

			ShipInProcess sizeThree_1(2, 4, 3);
			sizeThree_1.addCoordinate(2, 4, 4);
			sizeThree_1.addCoordinate(2, 4, 5);

			ShipInProcess sizeTwo_2(2, 5, 8);

			allShips2.push_back(sizeThree_1);
			allShips2.push_back(sizeTwo_1);
			allShips2.push_back(sizeTwo_2);
			allShips2.push_back(sizeOne_3);
			allShips2.push_back(sizeOne_1);
			allShips2.push_back(sizeOne_2);

			tmpPlayer2.attackedShips = allShips2;

			int res;


			res = tmpPlayer2.findCoorInAttackedShips(Coordinate(2, 4, 3), 0);
			if (res != 0)
			{
				std::cout << "error <2,4,3> 0" << std::endl;
				return -1;
			}

			res = tmpPlayer2.findCoorInAttackedShips(Coordinate(2, 4, 3), 2);
			if (res != -1)
			{
				std::cout << "error <2,4,3> 2" << std::endl;
				return -1;
			}

			res = tmpPlayer2.findCoorInAttackedShips(Coordinate(2, 4, 3), 4);
			if (res != -1)
			{
				std::cout << "error <2,4,3>  4" << std::endl;
				return -1;
			}


			res = tmpPlayer2.findCoorInAttackedShips(Coordinate(2, 10, 10), 0);
			if (res != -1)
			{
				std::cout << "error <2,10,10>  0" << std::endl;
				return -1;
			}

			res = tmpPlayer2.findCoorInAttackedShips(Coordinate(2, 4, 6), 0);
			if (res != -1)
			{
				std::cout << "error <2,4,6>  0" << std::endl;
				return -1;
			}

			res = tmpPlayer2.findCoorInAttackedShips(Coordinate(2, 3, 8), 0);
			if (res != 3)
			{
				std::cout << "error <2,3,8> 0" << std::endl;
				return -1;
			}
		}
	}
	return 0;
}

int testPlayerSmart::testsizeOneAttack()
{
	PlayerSmart tmpPlayer;

	for (int i = 1; i<10; i++)
	{
		for (int j = 1; j<10; j++)
		{
			for (int k = 1; k < 10; k++) {
				tmpPlayer.attackOptions.insert(Coordinate(i, j, k));
			}

		}
	}

	// check all sides
	Coordinate res(-1, -1, -1);
	Coordinate target(2, 3, 3);
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(target));

	tmpPlayer.attackOptions = tmpPlayer.attackOptions;
	//should return <1,3,3> x-1
	res = tmpPlayer.sizeOneAttack(target);
	if (!compareCoordinates(res, Coordinate(1, 3, 3)))
	{
		std::cout << "error 1,3,3" << std::endl;
		return -1;
	}

	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(res));

	//should return <3,3,3> down x+1
	res = tmpPlayer.sizeOneAttack(target);
	if (!compareCoordinates(res, Coordinate(3, 3, 3)))
	{
		std::cout << "error 3,3,3" << std::endl;
		return -1;
	}

	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(res));
	//should return <2,2,3>  left y-1
	res = tmpPlayer.sizeOneAttack(target);
	if (!compareCoordinates(Coordinate(2, 2, 2), res))
	{
		std::cout << "error 2,2,3" << std::endl;
		return -1;
	}
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(res));

	//should return <2,4,3> right y+1
	res = tmpPlayer.sizeOneAttack(target);
	if (!compareCoordinates(Coordinate(2, 4, 3), res))
	{
		std::cout << "error 2,4,3" << std::endl;
		return -1;
	}
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(res));


	//should return <2,3,2> right z-1
	res = tmpPlayer.sizeOneAttack(target);
	if (!compareCoordinates(Coordinate(2, 3, 2), res))
	{
		std::cout << "error 2,3,2" << std::endl;
		return -1;
	}
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(res));

	//should return <2,3,4> right z+1
	res = tmpPlayer.sizeOneAttack(target);
	if (!compareCoordinates(Coordinate(2, 3, 4), res))
	{
		std::cout << "error 2,3,4" << std::endl;
		return -1;
	}
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(res));

	//should return <-1, -1> none
	res = tmpPlayer.sizeOneAttack(target);
	if (!compareCoordinates(Coordinate(-1, -1, -1), res))
	{
		std::cout << "error -1,-1,-1" << std::endl;
		return -1;
	}
	tmpPlayer.removeOneCoordinate(res);
	//		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(res));

	///////////////////////////////////////////////////////////////////////////////check rightest edge 
	target = Coordinate(9, 10, 10);
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(target));
	target = Coordinate(10, 10, 10);
	// should return left (10,9,10)
	res = tmpPlayer.sizeOneAttack(target);
	if (!compareCoordinates(Coordinate(10, 9, 10), res))
	{
		std::cout << "error 10,9,10" << std::endl;
		return -1;
	}
	tmpPlayer.removeOneCoordinate(res);

	//in depth
	res = tmpPlayer.sizeOneAttack(target);
	if (!compareCoordinates(Coordinate(10, 10, 9), res))
	{
		std::cout << "error 10,10,9" << std::endl;
		return -1;
	}
	tmpPlayer.removeOneCoordinate(res);

	//none left
	res = tmpPlayer.sizeOneAttack(target);
	if (!compareCoordinates(Coordinate(-1, -1, -1), res))
	{
		std::cout << "error -1,-1,-1" << std::endl;
		return -1;
	}


	// check the leftest 
	target = Coordinate(1, 1, 1);
	res = tmpPlayer.sizeOneAttack(target);
	if (!compareCoordinates(Coordinate(2, 1, 1), res))
	{
		std::cout << "error 2,1, 1" << std::endl;
		return -1;
	}
	tmpPlayer.removeOneCoordinate(res);
	std::cout << "done!" << std::endl;
	return 0;
}

int testPlayerSmart::testattack()
{
	PlayerSmart tmpPlayer;
	//check the case that attack options is empty and imbalanced options is empty
	Coordinate nextCoordinate = tmpPlayer.attack();
	if (!compareCoordinates(nextCoordinate, Coordinate(-1, -1, -1))) {
		std::cout << "error in case that both pool's are empty" << std::endl;
	}

	// in case that imbalanced not empty should pour the new options to attack options
	tmpPlayer.imbalancedAttackOptions.insert(Coordinate(5, 5, 5));
	nextCoordinate = tmpPlayer.attack();
	if (!compareCoordinates(nextCoordinate, Coordinate(5, 5, 5))) {
		std::cout << " error in the case attackoptions is empty but imbalanced isnt empty" << std::endl;
	}
	tmpPlayer.imbalancedAttackOptions.clear();

	///////////////////////////////////////////////////
	std::vector<ShipInProcess> allShips;
	//create Set of options
	for (int i = 1; i<10; i++)
	{
		for (int j = 1; j<10; j++)
		{
			for (int k = 1; j < 10; j++) {
				tmpPlayer.attackOptions.insert(Coordinate(i, j, k));
			}

		}
	}

	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(1, 5, 1)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(3, 5, 8)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(7, 6, 8)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(8, 6, 8)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 2, 3)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 2, 5)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 2, 4)));

	// create ships
	ShipInProcess sizeOne_1(1, 5, 1);
	ShipInProcess sizeOne_2(3, 5, 8);

	ShipInProcess sizeTwo_1(7, 6, 8);
	sizeTwo_1.addCoordinate(8, 6, 8);

	ShipInProcess sizeThree_1(4, 2, 3);
	sizeThree_1.addCoordinate(4, 2, 4);
	sizeThree_1.addCoordinate(4, 2, 5);

	allShips.push_back(sizeThree_1);
	allShips.push_back(sizeTwo_1);
	allShips.push_back(sizeOne_1);
	allShips.push_back(sizeOne_2);

	// clear envirnment
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(7, 6, 8)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(8, 6, 8)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(7, 6, 9)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(8, 6, 9)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(7, 7, 8)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(8, 7, 8)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(7, 5, 8)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(8, 5, 8)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(7, 6, 7)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(8, 6, 7)));


	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 2, 3)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 2, 4)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 2, 5)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(3, 2, 3)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(5, 2, 3)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 1, 3)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 3, 3)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(3, 2, 4)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(5, 2, 4)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 1, 4)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 3, 4)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(3, 2, 5)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(5, 2, 5)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 1, 5)));
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 3, 5)));

	tmpPlayer.attackedShips = allShips;
	nextCoordinate = tmpPlayer.attack();

	if (!compareCoordinates(Coordinate(4, 2, 2), nextCoordinate))
	{
		std::cout << "error <4,2,2> " << std::endl;
		return -1;
	}

	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 2, 2)));

	nextCoordinate = tmpPlayer.attack();
	if (!compareCoordinates(Coordinate(4, 2, 6), nextCoordinate))
	{
		std::cout << "error <4,2,6> " << std::endl;
		return -1;
	}
	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 2, 6)));
	tmpPlayer.attackedShips.erase(tmpPlayer.attackedShips.begin(), tmpPlayer.attackedShips.end());

	// in case there are no ships in process return random element 
	nextCoordinate = tmpPlayer.attack();
	if (!tmpPlayer.isInAttackOptions(nextCoordinate))
	{
		std::cout << "last " << std::endl;
		return -1;
	}

	std::cout << "done!!!!!!!!!!!!! " << std::endl;
	return 0;
}

bool testPlayerSmart::compareCoordinates(Coordinate coor1, Coordinate coor2)

{
	return (coor1.col == coor2.col && coor1.row == coor2.row && coor1.depth == coor2.depth);
}