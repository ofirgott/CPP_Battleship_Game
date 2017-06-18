//#include "testPlayerSmart.h"
//#include "iostream"
//
//
//int testPlayerSmart::testfindPairInAttackedShips()
//{
//	// added
//	PlayerSmart tmpPlayer7;
//	for (int i = 1; i < 11; i++)
//	{
//		for (int j = 1; j < 11; j++)
//		{
//			for (int k = 1; k < 11; k++) {
//				tmpPlayer7.attackOptions.insert(Coordinate(i, j, k));
//
//			}
//		}
//	}
//
//	std::set<Coordinate> checkthis;
//
//	checkthis.insert(Coordinate(7, 9, 8));
//	checkthis.insert(Coordinate(3, 8, 8));
//	checkthis.insert(Coordinate(1, 1, 1));
//
//	checkthis.insert(Coordinate(7, 8, 8));
//	checkthis.insert(Coordinate(8, 8, 8));
//	checkthis.insert(Coordinate(7, 7, 8));
//	checkthis.insert(Coordinate(8, 7, 8));
//	checkthis.insert(Coordinate(7, 9, 8));
//	checkthis.insert(Coordinate(8, 9, 8));
//	checkthis.insert(Coordinate(7, 8, 7));
//	checkthis.insert(Coordinate(8, 8, 7));
//	checkthis.insert(Coordinate(7, 8, 9));
//	checkthis.insert(Coordinate(8, 8, 9));
//
//	checkthis.insert(Coordinate(4, 1, 2));
//	checkthis.insert(Coordinate(4, 2, 2));
//	checkthis.insert(Coordinate(3, 1, 2));
//	checkthis.insert(Coordinate(3, 2, 2));
//	checkthis.insert(Coordinate(5, 1, 2));
//	checkthis.insert(Coordinate(5, 2, 2));
//	checkthis.insert(Coordinate(4, 1, 1));
//	checkthis.insert(Coordinate(4, 2, 1));
//	checkthis.insert(Coordinate(4, 1, 3));
//	checkthis.insert(Coordinate(4, 2, 3));
//
//	checkthis.insert(Coordinate(2, 4, 5));
//	checkthis.insert(Coordinate(2, 4, 6));
//	checkthis.insert(Coordinate(1, 4, 5));
//	checkthis.insert(Coordinate(1, 4, 6));
//	checkthis.insert(Coordinate(3, 4, 5));
//	checkthis.insert(Coordinate(3, 4, 6));
//	checkthis.insert(Coordinate(2, 3, 5));
//	checkthis.insert(Coordinate(2, 3, 6));
//	checkthis.insert(Coordinate(2, 5, 5));
//	checkthis.insert(Coordinate(2, 5, 6));
//
//	checkthis.insert(Coordinate(4, 3, 2));
//	checkthis.insert(Coordinate(4, 5, 2));
//	checkthis.insert(Coordinate(4, 4, 2));
//	checkthis.insert(Coordinate(5, 3, 2));
//	checkthis.insert(Coordinate(5, 5, 2));
//	checkthis.insert(Coordinate(5, 4, 2));
//	checkthis.insert(Coordinate(3, 3, 2));
//	checkthis.insert(Coordinate(3, 5, 2));
//	checkthis.insert(Coordinate(3, 4, 2));
//	checkthis.insert(Coordinate(4, 3, 1));
//	checkthis.insert(Coordinate(4, 5, 1));
//	checkthis.insert(Coordinate(4, 4, 1));
//	checkthis.insert(Coordinate(4, 3, 3));
//	checkthis.insert(Coordinate(4, 5, 3));
//	checkthis.insert(Coordinate(4, 4, 3));
//
//	checkthis.insert(Coordinate(2, 4, 7));
//	checkthis.insert(Coordinate(2, 4, 8));
//	checkthis.insert(Coordinate(2, 4, 9));
//	checkthis.insert(Coordinate(2, 3, 7));
//	checkthis.insert(Coordinate(2, 3, 8));
//	checkthis.insert(Coordinate(2, 3, 9));
//	checkthis.insert(Coordinate(2, 5, 7));
//	checkthis.insert(Coordinate(2, 5, 8));
//	checkthis.insert(Coordinate(2, 5, 9));
//	checkthis.insert(Coordinate(1, 4, 7));
//	checkthis.insert(Coordinate(1, 4, 8));
//	checkthis.insert(Coordinate(1, 4, 9));
//	checkthis.insert(Coordinate(3, 4, 7));
//	checkthis.insert(Coordinate(3, 4, 8));
//	checkthis.insert(Coordinate(3, 4, 9));
//
//	for (auto& c : checkthis) {
//		if (!tmpPlayer7.isInAttackOptions(c)) {
//			std::cout << " error in testfindPairInAttackedShips/in creation of attackoptions " << std::endl;
//		}
//	}
//	/////// 
//	PlayerSmart tmpPlayer;
//	setTempPlayer1(tmpPlayer);
//
//	int res;
//	res = tmpPlayer.findCoorInAttackedShips(Coordinate(4, 3, 1), 0);
//	if (res != 0)
//	{
//		std::cout << "error <4,3,1> 0" << std::endl;
//		return -1;
//	}
//
//	res = tmpPlayer.findCoorInAttackedShips(Coordinate(4, 3, 1), 2);
//	if (res != -1)
//	{
//		std::cout << "error <4,3,1> 2" << std::endl;
//		return -1;
//	}
//
//	res = tmpPlayer.findCoorInAttackedShips(Coordinate(4, 3, 1), 4);
//	if (res != -1)
//	{
//		std::cout << "error <4,3,1>  4" << std::endl;
//		return -1;
//	}
//
//	res = tmpPlayer.findCoorInAttackedShips(Coordinate(10, 10, 1), 0);
//	if (res != -1)
//	{
//		std::cout << "error <10,10,1>  0" << std::endl;
//		return -1;
//	}
//
//	res = tmpPlayer.findCoorInAttackedShips(Coordinate(4, 6, 1), 0);
//	if (res != -1)
//	{
//		std::cout << "error <4,6,1>  0" << std::endl;
//		return -1;
//	}
//
//	res = tmpPlayer.findCoorInAttackedShips(Coordinate(3, 8, 1), 0);
//	if (res != 5)
//	{
//		std::cout << "error <3,8,1> 0" << std::endl;
//		return -1;
//	}
//
//	////////////////////////////////////dimentional
//
//	PlayerSmart tmpPlayer2;
//	setTempPlayer2(tmpPlayer2);
//
//
//	res = tmpPlayer2.findCoorInAttackedShips(Coordinate(2, 4, 3), 0);
//	if (res != 0)
//	{
//		std::cout << "error <2,4,3> 0" << std::endl;
//		return -1;
//	}
//
//	res = tmpPlayer2.findCoorInAttackedShips(Coordinate(2, 4, 3), 2);
//	if (res != -1)
//	{
//		std::cout << "error <2,4,3> 2" << std::endl;
//		return -1;
//	}
//
//	res = tmpPlayer2.findCoorInAttackedShips(Coordinate(2, 4, 3), 4);
//	if (res != -1)
//	{
//		std::cout << "error <2,4,3>  4" << std::endl;
//		return -1;
//	}
//
//
//	res = tmpPlayer2.findCoorInAttackedShips(Coordinate(2, 10, 10), 0);
//	if (res != -1)
//	{
//		std::cout << "error <2,10,10>  0" << std::endl;
//		return -1;
//	}
//
//	res = tmpPlayer2.findCoorInAttackedShips(Coordinate(2, 4, 6), 0);
//	if (res != -1)
//	{
//		std::cout << "error <2,4,6>  0" << std::endl;
//		return -1;
//	}
//
//	res = tmpPlayer2.findCoorInAttackedShips(Coordinate(2, 3, 8), 0);
//	if (res != 5)
//	{
//		std::cout << "error <2,3,8> 0" << std::endl;
//		return -1;
//	}
//
//	std::cout << "Done findPairInattacked" << std::endl;
//	return 0;
//}
//
//int testPlayerSmart::testremoveOneCoordinate()
//{
//	PlayerSmart tempPlayer;
//	tempPlayer.boardRows = 5;
//	tempPlayer.boardCols = 5;
//	tempPlayer.boardDepth = 5;
//	for (int i = 1; i < 6; i++) {
//		for (int j = 1; j < 6; j++) {
//			for (int k = 1; k < 6; k++) {
//				tempPlayer.attackOptions.insert(Coordinate(i, j, k));
//			}
//		}
//	}
//	Coordinate tmpPair = Coordinate(1, 1, 1);
//
//	tempPlayer.delCoorAttackOptions(tmpPair);
//	auto find = tempPlayer.attackOptions.find(Coordinate(1, 1, 1));
//	if (find != tempPlayer.attackOptions.end())
//	{
//		std::cout << "not good!didnt delete! " << std::endl;
//	}
//
//	// another check 
//
//
//	std::set<Coordinate> checkthis;
//
//	checkthis.insert(Coordinate(7, 9, 8));
//	checkthis.insert(Coordinate(3, 8, 8));
//	checkthis.insert(Coordinate(1, 1, 1));
//
//	checkthis.insert(Coordinate(7, 8, 8));
//	checkthis.insert(Coordinate(8, 8, 8));
//	checkthis.insert(Coordinate(7, 7, 8));
//	checkthis.insert(Coordinate(8, 7, 8));
//	checkthis.insert(Coordinate(7, 9, 8));
//	checkthis.insert(Coordinate(8, 9, 8));
//	checkthis.insert(Coordinate(7, 8, 7));
//	checkthis.insert(Coordinate(8, 8, 7));
//	checkthis.insert(Coordinate(7, 8, 9));
//	checkthis.insert(Coordinate(8, 8, 9));
//
//	checkthis.insert(Coordinate(4, 1, 2));
//	checkthis.insert(Coordinate(4, 2, 2));
//	checkthis.insert(Coordinate(3, 1, 2));
//	checkthis.insert(Coordinate(3, 2, 2));
//	checkthis.insert(Coordinate(5, 1, 2));
//	checkthis.insert(Coordinate(5, 2, 2));
//	checkthis.insert(Coordinate(4, 1, 1));
//	checkthis.insert(Coordinate(4, 2, 1));
//	checkthis.insert(Coordinate(4, 1, 3));
//	checkthis.insert(Coordinate(4, 2, 3));
//
//	checkthis.insert(Coordinate(2, 4, 5));
//	checkthis.insert(Coordinate(2, 4, 6));
//	checkthis.insert(Coordinate(1, 4, 5));
//	checkthis.insert(Coordinate(1, 4, 6));
//	checkthis.insert(Coordinate(3, 4, 5));
//	checkthis.insert(Coordinate(3, 4, 6));
//	checkthis.insert(Coordinate(2, 3, 5));
//	checkthis.insert(Coordinate(2, 3, 6));
//	checkthis.insert(Coordinate(2, 5, 5));
//	checkthis.insert(Coordinate(2, 5, 6));
//
//	checkthis.insert(Coordinate(4, 3, 2));
//	checkthis.insert(Coordinate(4, 5, 2));
//	checkthis.insert(Coordinate(4, 4, 2));
//	checkthis.insert(Coordinate(5, 3, 2));
//	checkthis.insert(Coordinate(5, 5, 2));
//	checkthis.insert(Coordinate(5, 4, 2));
//	checkthis.insert(Coordinate(3, 3, 2));
//	checkthis.insert(Coordinate(3, 5, 2));
//	checkthis.insert(Coordinate(3, 4, 2));
//	checkthis.insert(Coordinate(4, 3, 1));
//	checkthis.insert(Coordinate(4, 5, 1));
//	checkthis.insert(Coordinate(4, 4, 1));
//	checkthis.insert(Coordinate(4, 3, 3));
//	checkthis.insert(Coordinate(4, 5, 3));
//	checkthis.insert(Coordinate(4, 4, 3));
//
//	checkthis.insert(Coordinate(2, 4, 7));
//	checkthis.insert(Coordinate(2, 4, 8));
//	checkthis.insert(Coordinate(2, 4, 9));
//	checkthis.insert(Coordinate(2, 3, 7));
//	checkthis.insert(Coordinate(2, 3, 8));
//	checkthis.insert(Coordinate(2, 3, 9));
//	checkthis.insert(Coordinate(2, 5, 7));
//	checkthis.insert(Coordinate(2, 5, 8));
//	checkthis.insert(Coordinate(2, 5, 9));
//	checkthis.insert(Coordinate(1, 4, 7));
//	checkthis.insert(Coordinate(1, 4, 8));
//	checkthis.insert(Coordinate(1, 4, 9));
//	checkthis.insert(Coordinate(3, 4, 7));
//	checkthis.insert(Coordinate(3, 4, 8));
//	checkthis.insert(Coordinate(3, 4, 9));
//
//	PlayerSmart tmpPlayer7;
//	setTempPlayer3(tmpPlayer7);
//
//
//	for (auto& c : checkthis) {
//		if (tmpPlayer7.isInAttackOptions(c)) {
//			std::cout << " error in removeOneCoor " << std::endl;
//		}
//	}
//
//	std::cout << "Done testremoveOneCoordinate" << std::endl;
//
//	return 0;
//}
//
//
//void testPlayerSmart::setTempPlayer3(PlayerSmart& tmpPlayer) {
//
//	std::vector<ShipInProcess> allShips;
//	tmpPlayer.boardRows = 10;
//	tmpPlayer.boardCols = 10;
//	tmpPlayer.boardDepth = 10;
//	// create ships
//	ShipInProcess sizeOne_1(1, 1, 1);
//	ShipInProcess sizeOne_2(3, 8, 8);
//	ShipInProcess sizeOne_3(7, 9, 8);
//
//	ShipInProcess sizeTwo_1(7, 8, 8);
//	sizeTwo_1.addCoordinate(8, 8, 8);
//
//	ShipInProcess sizeThree_1(4, 3, 2);
//	sizeThree_1.addCoordinate(4, 4, 2);
//	sizeThree_1.addCoordinate(4, 5, 2);
//
//	ShipInProcess sizeTwo_2(4, 1, 2);
//	sizeTwo_2.addCoordinate(4, 2, 2);
//
//	ShipInProcess sizeThree_2(2, 4, 7);
//	sizeThree_2.addCoordinate(2, 4, 8);
//	sizeThree_2.addCoordinate(2, 4, 9);
//
//	ShipInProcess sizeTwo_3(2, 4, 5);
//	sizeTwo_3.addCoordinate(2, 4, 6);
//
//	allShips.push_back(sizeThree_2);
//	allShips.push_back(sizeThree_1);
//	allShips.push_back(sizeTwo_3);
//	allShips.push_back(sizeTwo_2);
//	allShips.push_back(sizeTwo_1);
//	allShips.push_back(sizeOne_1);
//	allShips.push_back(sizeOne_2);
//	allShips.push_back(sizeOne_3);
//
//	tmpPlayer.attackedShips = allShips;
//
//	//create Set of options
//	for (int i = 1; i< 11; i++)
//	{
//		for (int j = 1; j<11; j++)
//		{
//			for (int k = 1; k < 11; k++) {
//				tmpPlayer.attackOptions.insert(Coordinate(i, j, k));
//			}
//		}
//	}
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 9, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 8, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(1, 1, 1));
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 8, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 8, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 7, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 7, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 9, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 9, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 8, 7));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 8, 7));
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 8, 9));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 8, 9));
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 1, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 2, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 1, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 2, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 1, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 2, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 1, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 2, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 1, 3));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 2, 3));
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 4, 5));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 4, 6));
//	tmpPlayer.delCoorAttackOptions(Coordinate(1, 4, 5));
//	tmpPlayer.delCoorAttackOptions(Coordinate(1, 4, 6));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 4, 5));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 4, 6));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 3, 5));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 3, 6));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 5, 5));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 5, 6));
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 3, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 5, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 4, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 3, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 5, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 4, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 3, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 5, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 4, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 3, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 5, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 4, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 3, 3));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 5, 3));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 4, 3));
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 4, 7));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 4, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 4, 9));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 3, 7));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 3, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 3, 9));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 5, 7));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 5, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 5, 9));
//	tmpPlayer.delCoorAttackOptions(Coordinate(1, 4, 7));
//	tmpPlayer.delCoorAttackOptions(Coordinate(1, 4, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(1, 4, 9));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 4, 7));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 4, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 4, 9));
//
//}
//
//void testPlayerSmart::player3testMerge1(PlayerSmart& tmpPlayer) {
//	std::vector<ShipInProcess> allShips;
//
//	tmpPlayer.boardRows = 10;
//	tmpPlayer.boardCols = 10;
//	tmpPlayer.boardDepth = 10;
//
//	// create ships
//	ShipInProcess sizeOne_1(1, 1, 1);
//	ShipInProcess sizeOne_2(3, 8, 8);
//	ShipInProcess sizeOne_3(7, 9, 8);
//
//	ShipInProcess sizeTwo_1(7, 8, 8);
//	sizeTwo_1.addCoordinate(8, 8, 8);
//
//	ShipInProcess sizeThree_5(4, 3, 2);
//	sizeThree_5.addCoordinate(4, 4, 2);
//	sizeThree_5.addCoordinate(4, 5, 2);
//	sizeThree_5.addCoordinate(4, 2, 2);
//	sizeThree_5.addCoordinate(4, 1, 2);
//
//	ShipInProcess sizeThree_2(2, 4, 7);
//	sizeThree_2.addCoordinate(2, 4, 8);
//	sizeThree_2.addCoordinate(2, 4, 9);
//
//	ShipInProcess sizeTwo_3(2, 4, 5);
//	sizeTwo_3.addCoordinate(2, 4, 6);
//
//	allShips.push_back(sizeThree_2);
//	allShips.push_back(sizeThree_5);
//
//	allShips.push_back(sizeTwo_3);
//	allShips.push_back(sizeTwo_1);
//	allShips.push_back(sizeOne_1);
//	allShips.push_back(sizeOne_2);
//	allShips.push_back(sizeOne_3);
//
//	tmpPlayer.attackedShips = allShips;
//
//	//create Set of options
//	for (int i = 1; i<10; i++)
//	{
//		for (int j = 1; j<10; j++)
//		{
//			for (int k = 1; k < 10; k++) {
//				tmpPlayer.attackOptions.insert(Coordinate(i, j, k));
//			}
//		}
//	}
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 9, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 8, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(1, 1, 1));
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 8, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 8, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 7, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 7, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 9, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 9, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 8, 7));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 8, 7));
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 8, 9));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 8, 9));
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 1, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 2, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 1, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 2, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 1, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 2, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 1, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 2, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 1, 3));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 2, 3));
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 4, 5));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 4, 6));
//	tmpPlayer.delCoorAttackOptions(Coordinate(1, 4, 5));
//	tmpPlayer.delCoorAttackOptions(Coordinate(1, 4, 6));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 4, 5));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 4, 6));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 3, 5));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 3, 6));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 5, 5));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 5, 6));
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 3, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 5, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 4, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 3, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 5, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 4, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 3, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 5, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 4, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 3, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 5, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 4, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 3, 3));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 5, 3));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 4, 3));
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 4, 7));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 4, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 4, 9));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 3, 7));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 3, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 3, 9));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 5, 7));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 5, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 5, 9));
//	tmpPlayer.delCoorAttackOptions(Coordinate(1, 4, 7));
//	tmpPlayer.delCoorAttackOptions(Coordinate(1, 4, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(1, 4, 9));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 4, 7));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 4, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 4, 9));
//
//}
//
//void testPlayerSmart::player3testMerge2(PlayerSmart& tmpPlayer) {
//	std::vector<ShipInProcess> allShips;
//	tmpPlayer.boardRows = 10;
//	tmpPlayer.boardCols = 10;
//	tmpPlayer.boardDepth = 10;
//	// create ships
//	ShipInProcess sizeOne_1(1, 1, 1);
//	ShipInProcess sizeOne_2(3, 8, 8);
//	ShipInProcess sizeOne_3(7, 9, 8);
//
//	ShipInProcess sizeTwo_1(7, 8, 8);
//	sizeTwo_1.addCoordinate(8, 8, 8);
//
//	ShipInProcess sizeThree_5(4, 3, 2);
//	sizeThree_5.addCoordinate(4, 4, 2);
//	sizeThree_5.addCoordinate(4, 5, 2);
//	sizeThree_5.addCoordinate(4, 2, 2);
//	sizeThree_5.addCoordinate(4, 1, 2);
//
//	ShipInProcess sizeThree_2(2, 4, 7);
//	sizeThree_2.addCoordinate(2, 4, 8);
//	sizeThree_2.addCoordinate(2, 4, 9);
//	sizeThree_2.addCoordinate(2, 4, 6);
//	sizeThree_2.addCoordinate(2, 4, 5);
//
//	allShips.push_back(sizeThree_2);
//	allShips.push_back(sizeThree_5);
//	allShips.push_back(sizeTwo_1);
//	allShips.push_back(sizeOne_1);
//	allShips.push_back(sizeOne_2);
//	allShips.push_back(sizeOne_3);
//
//	tmpPlayer.attackedShips = allShips;
//
//	//create Set of options
//	for (int i = 1; i<10; i++)
//	{
//		for (int j = 1; j<10; j++)
//		{
//			for (int k = 1; k < 10; k++) {
//				tmpPlayer.attackOptions.insert(Coordinate(i, j, k));
//			}
//		}
//	}
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 9, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 8, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(1, 1, 1));
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 8, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 8, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 7, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 7, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 9, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 9, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 8, 7));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 8, 7));
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 8, 9));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 8, 9));
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 1, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 2, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 1, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 2, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 1, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 2, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 1, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 2, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 1, 3));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 2, 3));
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 4, 5));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 4, 6));
//	tmpPlayer.delCoorAttackOptions(Coordinate(1, 4, 5));
//	tmpPlayer.delCoorAttackOptions(Coordinate(1, 4, 6));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 4, 5));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 4, 6));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 3, 5));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 3, 6));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 5, 5));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 5, 6));
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 3, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 5, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 4, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 3, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 5, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 4, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 3, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 5, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 4, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 3, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 5, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 4, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 3, 3));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 5, 3));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 4, 3));
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 4, 7));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 4, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 4, 9));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 3, 7));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 3, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 3, 9));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 5, 7));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 5, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 5, 9));
//	tmpPlayer.delCoorAttackOptions(Coordinate(1, 4, 7));
//	tmpPlayer.delCoorAttackOptions(Coordinate(1, 4, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(1, 4, 9));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 4, 7));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 4, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 4, 9));
//}
//
//
//bool testPlayerSmart::compareShipsDetails(ShipInProcess& ship1, ShipInProcess& ship2) {
//
//	if (ship1.isVertical != ship2.isVertical) {
//		std::cout << "problem with isVertical " << std::endl;
//		return false;
//	}
//	if (ship1.isDimentional != ship2.isDimentional) {
//		std::cout << "problem with isDimentional " << std::endl;
//		return false;
//	}
//	if (ship1.isHorizontal != ship2.isHorizontal) {
//		std::cout << "problem with isHorizontal " << std::endl;
//		return false;
//	}
//
//	if (!compareCoordinates(ship1.constantCoors, ship2.constantCoors)) {
//		std::cout << "problem with constantCoors " << std::endl;
//		return false;
//	}
//
//	if (!compareCoordinates(ship1.firstCoordinate, ship2.firstCoordinate)) {
//		std::cout << "problem with firstCoordinate " << std::endl;
//		return false;
//	}
//
//	if (ship1.shipSize != ship2.shipSize) {
//		std::cout << "problem with shipSsize " << std::endl;
//		return false;
//	}
//
//	if (!compareVector(ship1.incrementalCoors, ship2.incrementalCoors)) {
//		std::cout << "problem with incrementalCoors " << std::endl;
//		return false;
//	}
//
//	return true;
//}
//
//bool testPlayerSmart::compareVector(std::vector<int> firstVec, std::vector<int> secVec)
//{
//
//	if (firstVec.size() != secVec.size()) {
//		return false;
//	}
//
//	for (int i = 0; i < firstVec.size(); i++) {
//		if (firstVec[i] != secVec[i]) {
//			return false;
//		}
//	}
//	return true;
//}
//
//void testPlayerSmart::printCoordinate(const Coordinate& coord)
//{
//	std::cout << " coordinate: " << "row: " << coord.row << " col: " << coord.col << " depth: " << coord.depth << std::endl;
//}
//
//int testPlayerSmart::testmergeShipDetails()
//{
//	PlayerSmart tmpPlayer;
//	setTempPlayer3(tmpPlayer);
//	PlayerSmart tmpPlayer_expected;
//	player3testMerge1(tmpPlayer_expected);
//
//	Coordinate nextPairTosearch(4, 2, 2);
//	tmpPlayer.mergeShipDetails(&nextPairTosearch, 1);// does one is the first index or second(i need second)
//
//													 // should have merged <4,3,2><4,4,2><4,5,2> with <4,1,2><4,2,2>
//	for (auto i = 0; i < tmpPlayer.attackedShips.size(); i++) {
//		if (!compareShipsDetails(tmpPlayer.attackedShips.at(i), tmpPlayer_expected.attackedShips.at(i))) {
//
//			std::cout << "error in 4,2,2 merge ships at index " << i << "arnt equal" << std::endl;
//		}
//	}
//
//	// shouldnt merge - ships supposed to remain the same
//
//	Coordinate nextPairTosearch2(4, 3, 2);
//	tmpPlayer.mergeShipDetails(&nextPairTosearch2, 2);// does one is the first index or second(i need second)
//
//	for (auto i = 0; i < tmpPlayer.attackedShips.size(); i++) {
//		if (!compareShipsDetails(tmpPlayer.attackedShips.at(i), tmpPlayer_expected.attackedShips.at(i))) {
//			std::cout << "error in 4,3,2  shouldnt have merged " << i << std::endl;
//		}
//	}
//
//
//	Coordinate nextPairTosearch3(2, 4, 6);
//	tmpPlayer.mergeShipDetails(&nextPairTosearch3, 0);// does one is the first index or second(i need second)
//
//	PlayerSmart tmpPlayer_expected_2;
//	player3testMerge2(tmpPlayer_expected_2);
//	for (auto i = 0; i < tmpPlayer.attackedShips.size(); i++) {
//		if (!compareShipsDetails(tmpPlayer.attackedShips.at(i), tmpPlayer_expected_2.attackedShips.at(i))) {
//			std::cout << "error in 2,4,6 merge ships at index " << i << "arnt equal" << std::endl;
//		}
//	}
//
//
//	Coordinate nextPairTosearch4(2, 4, 8);
//	tmpPlayer.mergeShipDetails(&nextPairTosearch4, 2);// does one is the first index or second(i need second)
//
//	for (auto i = 0; i < tmpPlayer.attackedShips.size(); i++) {
//		if (!compareShipsDetails(tmpPlayer.attackedShips.at(i), tmpPlayer_expected_2.attackedShips.at(i))) {
//			std::cout << "error in 2,4,8  shouldnt have merged " << i << std::endl;
//		}
//	}
//
//	std::cout << "Done testmergeShipDetails " << std::endl;
//	return 0;
//}
//
//
//// allready checked
//int testPlayerSmart::testisInAttackOptions()
//{
//	PlayerSmart tempPlayer;
//	Coordinate coorToInsert(0, 0, 0);
//
//	for (int i = 1; i < 6; i++) {
//		for (int j = 1; j < 6; j++) {
//			for (int k = 1; k < 6; k++) {
//				tempPlayer.attackOptions.insert(Coordinate(i, j, k));
//			}
//		}
//	}
//
//	for (int i = 1; i < 6; i++) {
//		for (int j = 1; j < 6; j++) {
//			for (int k = 1; k < 6; k++) {
//				if (!tempPlayer.isInAttackOptions(Coordinate(i, j, k))) {
//					std::cout << "missing from attack options" << std::endl;
//					printCoordinate(Coordinate(i, j, k));
//				}
//			}
//		}
//	}
//
//	if (tempPlayer.isInAttackOptions(Coordinate(6, 6, 6))) {
//		std::cout << "shouldnt be in attack options 6,6,6 " << std::endl;
//	}
//	if (tempPlayer.isInAttackOptions(Coordinate(0, 0, 0))) {
//		std::cout << "shouldnt be in attack options 0,0,0 " << std::endl;
//	}
//	if (tempPlayer.isInAttackOptions(Coordinate(7, 7, 7))) {
//		std::cout << "shouldnt be in attack options 6,6,6 " << std::endl;
//	}
//
//	std::cout << "Done testisInAttackOptions" << std::endl;
//	return 0;
//}
//
//
//
//int testPlayerSmart::testnextAttackFromCoors()
//{
//	{
//		PlayerSmart tmpPlayer;
//		std::vector<ShipInProcess> allShips;
//
//		//create Set of options
//		for (int i = 1; i < 10; i++)
//		{
//			for (int j = 1; j < 10; j++)
//			{
//				for (int k = 1; k < 10; k++) {
//					tmpPlayer.attackOptions.insert(Coordinate(i, j, k));
//
//				}
//			}
//		}
//
//		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(1, 1, 1)));
//		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 1, 1)));
//		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(3, 8, 1)));
//		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(7, 8, 1)));
//		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(8, 8, 1)));
//		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 3, 1)));
//		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 5, 1)));
//		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(4, 4, 1)));
//
//
//		// clear envirnment
//		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(7, 6, 1)));
//		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(8, 6, 1)));
//		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(7, 9, 1)));
//		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(8, 9, 1)));
//		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(3, 3, 1)));
//		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(3, 5, 1)));
//		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(3, 4, 1)));
//		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(5, 3, 1)));
//		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(5, 5, 1)));
//		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(Coordinate(5, 4, 1)));
//
//		// create ships
//		ShipInProcess sizeOne_1(1, 1, 1);
//		ShipInProcess sizeOne_2(3, 8, 1);
//		ShipInProcess sizeOne_3(9, 2, 1);
//
//
//		ShipInProcess sizeTwo_1(7, 8, 1);
//		sizeTwo_1.addCoordinate(8, 8, 1);
//
//		ShipInProcess sizeThree_1(4, 3, 1);
//		sizeThree_1.addCoordinate(4, 4, 1);
//		sizeThree_1.addCoordinate(4, 5, 1);
//
//		ShipInProcess sizeTwo_2(5, 8, 1);
//
//		allShips.push_back(sizeThree_1);
//		allShips.push_back(sizeTwo_1);
//		allShips.push_back(sizeTwo_2);
//		allShips.push_back(sizeOne_3);
//		allShips.push_back(sizeOne_1);
//		allShips.push_back(sizeOne_2);
//
//
//		tmpPlayer.attackedShips = allShips;
//
//
//		Coordinate nextCoor(-1, -1, -1);
//		nextCoor = tmpPlayer.nextAttackFromCoors(sizeThree_1, 3);
//
//		if ((nextCoor.row != 4) || (nextCoor.col != 2) || (nextCoor.depth != 1))
//		{
//			std::cout << "error <4,2,1>" << std::endl;
//			return -1;
//		}
//
//		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(nextCoor));
//		nextCoor = Coordinate(4, 1, 1);
//		tmpPlayer.delCoorAttackOptions(nextCoor);
//		nextCoor = Coordinate(3, 2, 1);
//		tmpPlayer.delCoorAttackOptions(nextCoor);
//		nextCoor = Coordinate(5, 2, 1);
//		tmpPlayer.delCoorAttackOptions(nextCoor);
//
//		nextCoor = tmpPlayer.nextAttackFromCoors(sizeThree_1, 4);
//		if ((nextCoor.row != 4) || (nextCoor.col != 6) || (nextCoor.depth != 1))
//		{
//			std::cout << "error <4,6,1>" << std::endl;
//			return -1;
//		}
//		tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(nextCoor));
//
//
//		nextCoor = tmpPlayer.nextAttackFromCoors(sizeTwo_1, 2);
//		if ((nextCoor.row != 6) || (nextCoor.col != 8) || (nextCoor.depth != 1))
//		{
//			std::cout << "error <6,8>" << std::endl;
//			return -1;
//		}
//	}
//	//dimentional///////////////////////////////////////////////////////////////////////////////////////////////////
//
//	{
//		PlayerSmart tmpPlayer2;
//		std::vector<ShipInProcess> allShips2;
//
//		//create Set of options
//		for (int i = 1; i < 10; i++)
//		{
//			for (int j = 1; j < 10; j++)
//			{
//				for (int k = 1; k < 10; k++) {
//					tmpPlayer2.attackOptions.insert(Coordinate(i, j, k));
//
//				}
//			}
//		}
//
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 1, 1));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 1));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 3, 8));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 7, 8));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 8, 8));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 3));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 5));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 4));
//
//
//		// clear envirnment
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 7, 6));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 8, 6));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 7, 9));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 8, 9));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 3, 3));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 3, 5));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 3, 4));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 5, 3));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 5, 5));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 5, 4));
//
//
//		// create ships
//		ShipInProcess sizeOne_1(2, 1, 1);
//		ShipInProcess sizeOne_2(2, 3, 8);
//		ShipInProcess sizeOne_3(2, 9, 2);
//
//
//		ShipInProcess sizeTwo_1(2, 7, 8);
//		sizeTwo_1.addCoordinate(2, 8, 8);
//
//		ShipInProcess sizeThree_1(2, 4, 3);
//		sizeThree_1.addCoordinate(2, 4, 4);
//		sizeThree_1.addCoordinate(2, 4, 5);
//
//		ShipInProcess sizeTwo_2(2, 5, 8);
//
//		allShips2.push_back(sizeThree_1);
//		allShips2.push_back(sizeTwo_1);
//		allShips2.push_back(sizeTwo_2);
//		allShips2.push_back(sizeOne_3);
//		allShips2.push_back(sizeOne_1);
//		allShips2.push_back(sizeOne_2);
//
//		tmpPlayer2.attackedShips = allShips2;
//
//
//
//		Coordinate nextCoor(-1, -1, -1);
//		nextCoor = tmpPlayer2.nextAttackFromCoors(sizeThree_1, 3);
//
//		if ((nextCoor.row != 2) || (nextCoor.col != 4) || (nextCoor.depth != 2))
//		{
//			std::cout << "error <2,4,2>" << std::endl;
//			return -1;
//		}
//
//		tmpPlayer2.delCoorAttackOptions(nextCoor);
//		nextCoor = Coordinate(2, 4, 1);
//		tmpPlayer2.delCoorAttackOptions(nextCoor);
//		nextCoor = Coordinate(2, 3, 2);
//		tmpPlayer2.delCoorAttackOptions(nextCoor);
//		nextCoor = Coordinate(2, 5, 2);
//		tmpPlayer2.delCoorAttackOptions(nextCoor);
//
//		nextCoor = tmpPlayer2.nextAttackFromCoors(sizeThree_1, 4);
//		if ((nextCoor.row != 2) || (nextCoor.col != 4) || (nextCoor.depth != 6))
//		{
//			std::cout << "error <2,4,6>" << std::endl;
//			return -1;
//		}
//		tmpPlayer2.delCoorAttackOptions(nextCoor);
//
//
//		nextCoor = tmpPlayer2.nextAttackFromCoors(sizeTwo_1, 2);
//		if ((nextCoor.row != 2) || (nextCoor.col != 6) || (nextCoor.depth != 8))
//		{
//			std::cout << "error <2,6,8>" << std::endl;
//			return -1;
//		}
//	}
//
//	std::cout << "Done testnextAttackFromCoors" << std::endl;
//	return 0;
//
//}
//
//void testPlayerSmart::testgetMinShipSize()
//{
//	PlayerSmart tmpPlayer;
//	std::vector<std::pair<int, int>> count; // vector of enemie's ship's: pair of <shipSize,count>
//
//	count.push_back(std::make_pair(1, 2));
//	count.push_back(std::make_pair(2, 3));
//	count.push_back(std::make_pair(3, 0));
//	count.push_back(std::make_pair(4, 1));
//
//	tmpPlayer.shipsCount = count;
//	int res = tmpPlayer.getMinShipSize();
//	if (res != 1) {
//		std::cout << "ho no min ship size should be 1 but we got " << res << " :(" << std::endl;
//	}
//
//	tmpPlayer.shipsCount.at(0).second = 0;
//	tmpPlayer.shipsCount.at(1).second = 0;
//
//	res = tmpPlayer.getMinShipSize();
//	if (res != 4) {
//		std::cout << "ho no min ship size should be 4 but we got " << res << " :(" << std::endl;
//	}
//
//	std::cout << "Done testgetMinShipSize" << std::endl;
//}
//
//int testPlayerSmart::testremoveSankFromReleventCoors()
//{
//	PlayerSmart tmpPlayer;
//	setTempPlayer1(tmpPlayer);
//
//	tmpPlayer.removePermementlyIncrementalDirection(0);
//	if (tmpPlayer.isInAttackOptions(Coordinate(4, 6, 1))) {
//		std::cout << " didnt remove 4,6,1 from attack options " << std::endl;
//	}
//	if (tmpPlayer.isInAttackOptions(Coordinate(4, 2, 1))) {
//		std::cout << " didnt remove 4,2,1 from attack options " << std::endl;
//	}
//	//comare ships vectors 
//	std::vector<ShipInProcess> expected_vector;
//	ShipInProcess sizeOne_1(1, 1, 1);
//	ShipInProcess sizeOne_2(3, 8, 1);
//	ShipInProcess sizeOne_3(9, 2, 1);
//	ShipInProcess sizeTwo_1(7, 8, 1);
//	sizeTwo_1.addCoordinate(8, 8, 1);
//	ShipInProcess sizeTwo_2(5, 8, 1);
//	sizeTwo_2.addCoordinate(5, 8, 2);
//	expected_vector.push_back(sizeTwo_1);
//	expected_vector.push_back(sizeTwo_2);
//	expected_vector.push_back(sizeOne_3);
//	expected_vector.push_back(sizeOne_1);
//	expected_vector.push_back(sizeOne_2);
//
//	for (auto i = 0; i < expected_vector.size(); i++) {
//		if (!compareShipsDetails(expected_vector.at(i), tmpPlayer.attackedShips.at(i))) {
//			std::cout << "different ships " << i << std::endl;
//		}
//	}
//
//	//check for dimentuonal
//	ShipInProcess newShip(7, 3, 1);
//	newShip.addCoordinate(7, 3, 2);
//	newShip.addCoordinate(7, 3, 3);
//
//	tmpPlayer.attackedShips.insert(tmpPlayer.attackedShips.begin(), newShip);
//	tmpPlayer.removePermementlyIncrementalDirection(0);
//
//	if (tmpPlayer.isInAttackOptions(Coordinate(7, 3, 4)))
//	{
//		std::cout << "not good!didnt delete 7,3,4! " << std::endl;
//	}
//
//	for (auto i = 0; i < expected_vector.size(); i++) {
//		if (!compareShipsDetails(expected_vector.at(i), tmpPlayer.attackedShips.at(i))) {
//			std::cout << "different ships 7,3,4 " << i << std::endl;
//		}
//	}
//
//	expected_vector.erase(expected_vector.begin() + 1);
//	tmpPlayer.removePermementlyIncrementalDirection(1);
//
//	if (tmpPlayer.isInAttackOptions(Coordinate(5, 8, 3)))
//	{
//		std::cout << "not good!didnt delete 5,8,3! " << std::endl;
//	}
//
//	for (auto i = 0; i < expected_vector.size(); i++) {
//		if (!compareShipsDetails(expected_vector.at(i), tmpPlayer.attackedShips.at(i))) {
//			std::cout << "different ships 5,8,3 " << i << std::endl;
//		}
//	}
//
//	std::cout << "Done testremoveSankFromReleventCoors" << std::endl;
//	return 0;
//}
//
//
//void testPlayerSmart::testpourImbalancedToAttackOptions()
//{
//	PlayerSmart tempPlayer;
//	for (int i = 1; i < 6; i++) {
//		for (int j = 1; j < 6; j++) {
//			for (int k = 1; k < 6; k++) {
//				tempPlayer.imbalancedAttackOptions.insert(Coordinate(i, j, k));
//			}
//		}
//	}
//
//	tempPlayer.pourImbalancedToAttackOptions();
//
//	for (int i = 1; i < 6; i++) {
//		for (int j = 1; j < 6; j++) {
//			for (int k = 1; k < 6; k++) {
//				if (!tempPlayer.isInAttackOptions(Coordinate(i, j, k))) {
//					std::cout << "bad bad bad bad bad bad news didnt pour ";
//					printCoordinate(Coordinate(i, j, k));
//					std::cout << "to attack options from Imbalanced" << std::endl;
//				}
//			}
//		}
//	}
//
//	std::cout << "Done pourImbalancedToAttackOptions" << std::endl;
//}
//
//
//void testPlayerSmart::testupdateShipsCount()
//{
//	PlayerSmart tmpPlayer;
//	std::vector<std::pair<int, int>> count; // vector of enemie's ship's: pair of <shipSize,count>
//
//	count.push_back(std::make_pair(1, 2));//1
//	count.push_back(std::make_pair(2, 3));
//	count.push_back(std::make_pair(3, 0));
//	count.push_back(std::make_pair(4, 1));//0
//
//	tmpPlayer.shipsCount = count;
//	tmpPlayer.updateShipsCount(1);
//	tmpPlayer.updateShipsCount(4);
//	if (tmpPlayer.shipsCount.at(0).second != 1) {
//		std::cout << "ho no didnt update the ships count properly index0 :(" << std::endl;
//	}
//	if (tmpPlayer.shipsCount.at(3).second != 0) {
//		std::cout << "ho no didnt update the ships count properly index3 :(" << std::endl;
//	}
//
//	for (int i = 1; i < 6; i++) {
//		for (int j = 1; j < 6; j++) {
//			for (int k = 1; k < 6; k++) {
//				tmpPlayer.imbalancedAttackOptions.insert(Coordinate(i, j, k));
//			}
//		}
//	}
//	tmpPlayer.updateShipsCount(4);
//	if (tmpPlayer.isBoardBalanced == true) {
//		std::cout << "omg didnt set imbalnced properly!!!!!1" << std::endl;
//	}
//
//	for (int i = 1; i < 6; i++) {
//		for (int j = 1; j < 6; j++) {
//			for (int k = 1; k < 6; k++) {
//				if (!tmpPlayer.isInAttackOptions(Coordinate(i, j, k))) {
//					std::cout << "bad bad bad bad bad bad news didnt pour ";
//					printCoordinate(Coordinate(i, j, k));
//					std::cout << "to attack options from Imbalanced" << std::endl;
//				}
//			}
//		}
//	}
//
//	std::cout << "Done updateShipsCount" << std::endl;
//}
//
//
////void testPlayerSmart::testclearFourAdjecentCoors(Coordinate attackedCoordinate, AttackResult res, int minIncCoor, int maxInCoor, bool isVertical, bool isHorizontal)
////{
////
////	PlayerSmart tempPlayer;
////	// create 10*10*10 board
////	for (int i = 1; i < 11; i++) {
////		for (int j = 1; j < 11; j++) {
////			for (int k = 1; k < 11; k++) {
////				tempPlayer.attackOptions.insert(Coordinate(i, j, k));
////			}
////		}
////	}
////
////	std::vector<std::pair<int, int>> count;
////	count.push_back(std::make_pair(10, 5));
////
////	// target coor will be 5,5,5
////	tempPlayer.delCoorAttackOptions(Coordinate(4,5,5));
////	tempPlayer.delCoorAttackOptions(Coordinate(3,5,5));
////	tempPlayer.delCoorAttackOptions(Coordinate(5,4,5));
////	tempPlayer.delCoorAttackOptions(Coordinate(5,3,5));
////	tempPlayer.delCoorAttackOptions(Coordinate(5,5,5));
////	// set attack options 
////	tempPlayer.shipsCount = count;
////
////	// target coor 5,5,5
////	tempPlayer.delCoorAttackOptions(Coordinate(5,5,5));
////	tempPlayer.checkConstantDirectionsForWalls(Coordinate(5,5,5),AttackResult::Hit,5,5,false,false);
////
////	std::set<Coordinate> imbalancedTest;
////	//4,5,5
////	imbalancedTest.insert(Coordinate(1,5,5));
////	imbalancedTest.insert(Coordinate(2, 5, 5));
////	imbalancedTest.insert(Coordinate(3, 5, 5));
////	imbalancedTest.insert(Coordinate(6, 5, 5));
////	imbalancedTest.insert(Coordinate(7, 5, 5));
////	imbalancedTest.insert(Coordinate(8, 5, 5));
////	imbalancedTest.insert(Coordinate(9, 5, 5));
////	imbalancedTest.insert(Coordinate(10, 5, 5));
////
////	imbalancedTest.insert(Coordinate(4, 1, 5));
////	imbalancedTest.insert(Coordinate(4, 2, 5));
////	imbalancedTest.insert(Coordinate(4, 3, 5));
////	imbalancedTest.insert(Coordinate(4, 4, 5));
////	imbalancedTest.insert(Coordinate(4, 6, 5));
////	imbalancedTest.insert(Coordinate(4, 7, 5));
////	imbalancedTest.insert(Coordinate(4, 8, 5));
////	imbalancedTest.insert(Coordinate(4, 9, 5));
////	imbalancedTest.insert(Coordinate(4, 10, 5));
////
////
////}
//
//void testPlayerSmart::testCheck6Util1()
//{
//
//	PlayerSmart tempPlayer;
//	// create 10*10*10 board
//	for (int i = 1; i < 11; i++) {
//		for (int j = 1; j < 11; j++) {
//			for (int k = 1; k < 11; k++) {
//				tempPlayer.attackOptions.insert(Coordinate(i, j, k));
//			}
//		}
//	}
//
//	std::vector<std::pair<int, int>> count;
//	count.push_back(std::make_pair(10, 5));
//	// target coor will be 2, 5, 4
//	tempPlayer.delCoorAttackOptions(Coordinate(2, 5, 4));
//	// create 'walls' around it
//	//horizontal
//	tempPlayer.delCoorAttackOptions(Coordinate(2, 1, 4));
//	tempPlayer.delCoorAttackOptions(Coordinate(2, 8, 4));
//	//vertical
//	tempPlayer.delCoorAttackOptions(Coordinate(6, 5, 4));
//	//coordinates.erase(coordinates.find(Coordinate(0, 5, 4))); already a wall
//	//deptical
//	//coordinates.erase(coordinates.find(Coordinate(2, 5, 0))); alreay a wall
//	tempPlayer.delCoorAttackOptions(Coordinate(2, 5, 8));
//
//	std::set<Coordinate> imbalancedTest;
//	// horizontal
//	imbalancedTest.insert(Coordinate(2, 2, 4));
//	imbalancedTest.insert(Coordinate(2, 3, 4));
//	imbalancedTest.insert(Coordinate(2, 4, 4));
//	imbalancedTest.insert(Coordinate(2, 6, 4));
//	imbalancedTest.insert(Coordinate(2, 7, 4));
//
//	//vertical
//	imbalancedTest.insert(Coordinate(3, 5, 4));
//	imbalancedTest.insert(Coordinate(4, 5, 4));
//	imbalancedTest.insert(Coordinate(5, 5, 4));
//	imbalancedTest.insert(Coordinate(1, 5, 4));
//
//	// deptical 
//	imbalancedTest.insert(Coordinate(2, 5, 1));
//	imbalancedTest.insert(Coordinate(2, 5, 2));
//	imbalancedTest.insert(Coordinate(2, 5, 3));
//	imbalancedTest.insert(Coordinate(2, 5, 6));
//	imbalancedTest.insert(Coordinate(2, 5, 7));
//
//	// set attack options 
//	tempPlayer.shipsCount = count;
//
//	// test function
//	tempPlayer.checkSixDirectionsForWalls(Coordinate(2, 5, 4));
//
//	for (auto coor : imbalancedTest) {
//		if (!tempPlayer.isInImbalancedOptions(coor)) {
//			std::cout << "missing coordinate in imbalanced horizontal";
//			printCoordinate(coor);
//		}
//
//		if (tempPlayer.isInAttackOptions(coor)) {
//			std::cout << "coordinate shouldnt be in attack options";
//			printCoordinate(coor);
//		}
//	}
//
//}
//
//void testPlayerSmart::testcheck6Util2()
//{
//
//	PlayerSmart tempPlayer;
//	// create 10*10*10 board
//	for (int i = 1; i < 11; i++) {
//		for (int j = 1; j < 11; j++) {
//			for (int k = 1; k < 11; k++) {
//				tempPlayer.attackOptions.insert(Coordinate(i, j, k));
//			}
//		}
//	}
//
//
//	std::vector<std::pair<int, int>> count;
//	count.push_back(std::make_pair(1, 5));
//
//	// target coor will be 2, 5, 4
//	tempPlayer.delCoorAttackOptions(Coordinate(2, 5, 4));
//
//	// create 'walls' around it
//	//horizontal
//	tempPlayer.delCoorAttackOptions(Coordinate(2, 1, 4));
//	tempPlayer.delCoorAttackOptions(Coordinate(2, 8, 4));
//
//	//vertical
//	tempPlayer.delCoorAttackOptions(Coordinate(6, 5, 4));
//	//coordinates.erase(coordinates.find(Coordinate(0, 5, 4))); already a wall
//
//	//deptical
//	//coordinates.erase(coordinates.find(Coordinate(2, 5, 0))); alreay a wall
//	tempPlayer.delCoorAttackOptions(Coordinate(2, 5, 8));
//
//	// set attack options 
//	tempPlayer.shipsCount = count;
//
//	// test function
//	tempPlayer.checkSixDirectionsForWalls(Coordinate(2, 5, 4));
//
//	if (tempPlayer.imbalancedAttackOptions.size() != 0) {
//		std::cout << "imbalanced should be of size 0";
//	}
//
//	std::set<Coordinate> coordinates;
//	for (int i = 1; i < 11; i++) {
//		for (int j = 1; j < 11; j++) {
//			for (int k = 1; k < 11; k++) {
//				coordinates.insert(Coordinate(i, j, k));
//			}
//		}
//	}
//	coordinates.erase(coordinates.find(Coordinate(2, 5, 4)));
//	coordinates.erase(coordinates.find(Coordinate(2, 8, 4)));
//	coordinates.erase(coordinates.find(Coordinate(2, 1, 4)));
//	coordinates.erase(coordinates.find(Coordinate(2, 5, 8)));
//	coordinates.erase(coordinates.find(Coordinate(6, 5, 4)));
//	for (auto coor : coordinates) {
//		if (tempPlayer.attackOptions.find(coor) == tempPlayer.attackOptions.end()) {
//			std::cout << "coordinate should be in attack options";
//			printCoordinate(coor);
//			std::cout << " fix this now!!!!!" << std::endl;
//		}
//	}
//
//}
//
//void testPlayerSmart::testCheck6Util3()
//{
//
//	PlayerSmart tempPlayer;
//	// create 10*10*10 board
//	for (int i = 1; i < 11; i++) {
//		for (int j = 1; j < 11; j++) {
//			for (int k = 1; k < 11; k++) {
//				tempPlayer.attackOptions.insert(Coordinate(i, j, k));
//			}
//		}
//	}
//
//
//	std::vector<std::pair<int, int>> count;
//	count.push_back(std::make_pair(2, 2));
//
//	// target coor will be 2, 5, 4
//	tempPlayer.delCoorAttackOptions(Coordinate(2, 5, 4));
//
//	// create 'walls' around it
//	//horizontal
//	tempPlayer.delCoorAttackOptions(Coordinate(2, 3, 4));
//	tempPlayer.delCoorAttackOptions(Coordinate(2, 8, 4));
//
//	//vertical
//	tempPlayer.delCoorAttackOptions(Coordinate(6, 5, 4));
//	//coordinates.erase(coordinates.find(Coordinate(0, 5, 4))); already a wall
//
//	//deptical
//	//coordinates.erase(coordinates.find(Coordinate(2, 5, 0))); alreay a wall
//	tempPlayer.delCoorAttackOptions(Coordinate(2, 5, 8));
//
//	std::set<Coordinate> imbalancedTest;
//	// horizontal
//	imbalancedTest.insert(Coordinate(2, 4, 4));
//
//	//vertical
//	imbalancedTest.insert(Coordinate(1, 5, 4));
//
//
//	// set attack options 
//	tempPlayer.shipsCount = count;
//
//	// test function
//	tempPlayer.checkSixDirectionsForWalls(Coordinate(2, 5, 4));
//
//	for (auto coor : imbalancedTest) {
//		if (!tempPlayer.isInImbalancedOptions(coor)) {
//			std::cout << "missing coordinate in imbalanced horizontal";
//			printCoordinate(coor);
//			std::cout << " fix this now!!!!!" << std::endl;
//		}
//
//		if (tempPlayer.isInAttackOptions(coor)) {
//			std::cout << "coordinate shoukdnt be in attack options";
//			printCoordinate(coor);
//			std::cout << " fix this now!!!!!" << std::endl;
//		}
//	}
//}
//
//void testPlayerSmart::testcheckSixDirections()
//{
//
//	testCheck6Util1();
//
//	//std::cout << "shouldnt remove anything from attack options " << std::endl;
//	testcheck6Util2();
//
//	//std::cout << "remove only from some directions " << std::endl;
//	testCheck6Util3();
//
//	std::cout << "Done checkSixDirectionsForWalls" << std::endl;
//}
//
//void testPlayerSmart::testtransferCoordinatesToSecondPoll()
//{
//	//// Horizontal !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!	
//	PlayerSmart tempPlayer;
//	for (int i = 1; i <11; i++) {
//		for (int j = 1; j < 11; j++) {
//			for (int k = 1; k < 11; k++) {
//				tempPlayer.attackOptions.insert(Coordinate(i, j, k));
//			}
//		}
//	}
//
//	tempPlayer.delCoorAttackOptions(Coordinate(2, 5, 4));
//	tempPlayer.delCoorAttackOptions(Coordinate(2, 1, 4));
//
//	tempPlayer.transferCoordinatesToSecondPoll(Coordinate(2, 5, 4), 3, 0, 1, -1);
//
//	std::set<Coordinate> imbalancedTest;
//	imbalancedTest.insert(Coordinate(2, 2, 4));
//	imbalancedTest.insert(Coordinate(2, 3, 4));
//	imbalancedTest.insert(Coordinate(2, 4, 4));
//
//	for (auto coor : imbalancedTest) {
//		if (!tempPlayer.isInImbalancedOptions(coor)) {
//			std::cout << "missing coordinate in imbalanced horizontal";
//			printCoordinate(coor);
//			std::cout << " fix this now!!!!!" << std::endl;
//		}
//		if (tempPlayer.isInAttackOptions(coor)) {
//			std::cout << "didnt remove coor from attack options";
//		}
//	}
//	if (!tempPlayer.isInAttackOptions(Coordinate(2, 6, 4))) {
//		std::cout << "missing coordinate from attack options 2,6,4";
//	}
//	//// Vertical !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//	PlayerSmart tempPlayer2;
//	for (int i = 1; i < 11; i++) {
//		for (int j = 1; j < 11; j++) {
//			for (int k = 1; k < 11; k++) {
//				tempPlayer2.attackOptions.insert(Coordinate(i, j, k));
//			}
//		}
//	}
//
//	tempPlayer2.delCoorAttackOptions(Coordinate(5, 3, 4));
//	tempPlayer2.delCoorAttackOptions(Coordinate(1, 3, 4));
//
//	tempPlayer2.transferCoordinatesToSecondPoll(Coordinate(1, 3, 4), 3, 1, 0, +1);
//
//	std::set<Coordinate> imbalancedTest2;
//	imbalancedTest2.insert(Coordinate(2, 3, 4));
//	imbalancedTest2.insert(Coordinate(3, 3, 4));
//	imbalancedTest2.insert(Coordinate(4, 3, 4));
//
//	for (auto coor : imbalancedTest2) {
//		if (!tempPlayer2.isInImbalancedOptions(coor)) {
//			std::cout << "missing coordinate in imbalanced vertical ";
//			printCoordinate(coor);
//			std::cout << " fix this now!!!!!" << std::endl;
//		}
//		if (tempPlayer2.isInAttackOptions(coor)) {
//			std::cout << "didnt remove coor from attack options";
//		}
//	}
//
//	//// deptical !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//	PlayerSmart tempPlayer3;
//	for (int i = 1; i < 11; i++) {
//		for (int j = 1; j < 11; j++) {
//			for (int k = 1; k < 11; k++) {
//				tempPlayer3.attackOptions.insert(Coordinate(i, j, k));
//			}
//		}
//	}
//
//
//	tempPlayer3.delCoorAttackOptions(Coordinate(7, 3, 1));
//	tempPlayer3.delCoorAttackOptions(Coordinate(7, 3, 8));
//	tempPlayer3.transferCoordinatesToSecondPoll(Coordinate(7, 3, 8), 6, 0, 0, -1);
//
//	std::set<Coordinate> imbalancedTest3;
//	imbalancedTest3.insert(Coordinate(7, 3, 2));
//	imbalancedTest3.insert(Coordinate(7, 3, 3));
//	imbalancedTest3.insert(Coordinate(7, 3, 4));
//	imbalancedTest3.insert(Coordinate(7, 3, 5));
//	imbalancedTest3.insert(Coordinate(7, 3, 6));
//	imbalancedTest3.insert(Coordinate(7, 3, 7));
//
//	for (auto coor : imbalancedTest3) {
//		if (!tempPlayer3.isInImbalancedOptions(coor)) {
//			std::cout << "missing coordinate in imbalanced deptical ";
//			printCoordinate(coor);
//			std::cout << " fix this now!!!!! deptical" << std::endl;
//		}
//		if (tempPlayer3.isInAttackOptions(coor)) {
//			std::cout << "didnt remove coor from attack options";
//		}
//	}
//
//	tempPlayer3.delCoorAttackOptions(Coordinate(10, 5, 1));
//	tempPlayer3.delCoorAttackOptions(Coordinate(10, 9, 1));
//	std::set<Coordinate> imbalancedTest4;
//	imbalancedTest3.insert(Coordinate(10, 6, 1));
//	imbalancedTest3.insert(Coordinate(10, 7, 1));
//	imbalancedTest3.insert(Coordinate(10, 8, 1));
//
//	tempPlayer3.transferCoordinatesToSecondPoll(Coordinate(10, 5, 1), 0, 0, 1, +1);
//	for (auto coor : imbalancedTest4) {
//		if (tempPlayer3.isInImbalancedOptions(coor)) {
//			std::cout << "shouldnt be in imbalanced  ";
//			printCoordinate(coor);
//			std::cout << " fix this now!!!!! " << std::endl;
//		}
//		if (!tempPlayer3.isInAttackOptions(coor)) {
//			std::cout << "removed coor from attack options";
//		}
//	}
//
//
//	std::cout << "Done testtransferCoordinatesToSecondPoll" << std::endl;
//}
//
//void testPlayerSmart::testcountDistance()
//{
//
//	{
//		PlayerSmart tempPlayer;
//		for (int i = 1; i < 6; i++) {
//			for (int j = 1; j < 6; j++) {
//				for (int k = 1; k < 6; k++) {
//					tempPlayer.attackOptions.insert(Coordinate(i, j, k));
//				}
//			}
//		}
//		int res;
//
//		//// Horizontal !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!	
//		tempPlayer.delCoorAttackOptions(Coordinate(2, 5, 4));
//		tempPlayer.delCoorAttackOptions(Coordinate(2, 1, 4));
//
//		res = tempPlayer.countDistance(Coordinate(2, 5, 4), 0, false, true, -1);
//		if (res != -1) {
//			std::cout << "1 the distance was supposed to be -1 !!!!  got " << res << " :(" << std::endl;
//		}
//
//		res = tempPlayer.countDistance(Coordinate(2, 5, 4), 4, false, true, -1);
//		if (res != 3) {
//			std::cout << " 1 the distance was supposed to be 3 (2,5,4) !!!!  got " << res << " :(" << std::endl;
//		}
//
//		res = tempPlayer.countDistance(Coordinate(2, 1, 4), 4, false, true, +1);
//		if (res != 3) {
//			std::cout << "1 the distance was supposed to be 3 (2,1,4)!!!!  got " << res << " :(" << std::endl;
//		}
//
//		// wall at 2,6,4
//		res = tempPlayer.countDistance(Coordinate(2, 5, 4), 5, false, true, +1);
//		if (res != 0) {
//			std::cout << "1 the distance was supposed to be 0 (2,6,4) !!!!  got " << res << " :(" << std::endl;
//		}
//
//	}
//
//	{
//		//// Vertical !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//		PlayerSmart tempPlayer;
//		for (int i = 1; i < 6; i++) {
//			for (int j = 1; j < 6; j++) {
//				for (int k = 1; k < 6; k++) {
//					tempPlayer.attackOptions.insert(Coordinate(i, j, k));
//				}
//			}
//		}
//		int res;
//		tempPlayer.attackOptions.erase(tempPlayer.attackOptions.find(Coordinate(5, 3, 4)));
//		tempPlayer.attackOptions.erase(tempPlayer.attackOptions.find(Coordinate(1, 3, 4)));
//
//		res = tempPlayer.countDistance(Coordinate(5, 3, 4), 0, true, false, -1);
//		if (res != -1) {
//			std::cout << "2 the distance was supposed to be -1 !!!!(vertical)  got " << res << " :(" << std::endl;
//		}
//
//		res = tempPlayer.countDistance(Coordinate(5, 3, 4), 5, true, false, -1);
//		if (res != 3) {
//			std::cout << "2 the distance was supposed to be 3 (5,3,4) !!!!  got " << res << " :(" << std::endl;
//		}
//
//		res = tempPlayer.countDistance(Coordinate(1, 3, 4), 5, true, false, +1);
//		if (res != 3) {
//			std::cout << "2 the distance was supposed to be 3 (1,3,4)!!!!  got " << res << " :(" << std::endl;
//		}
//
//		// wall at 6,3,4
//		res = tempPlayer.countDistance(Coordinate(5, 3, 4), 5, true, false, +1);
//		if (res != 0) {
//			std::cout << "2 the distance was supposed to be 0 (6,3,4) !!!!  got " << res << " :(" << std::endl;
//		}
//	}
//	{
//		//// deptical !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//		PlayerSmart tempPlayer;
//		for (int i = 1; i < 10; i++) {
//			for (int j = 1; j < 10; j++) {
//				for (int k = 1; k < 10; k++) {
//					tempPlayer.attackOptions.insert(Coordinate(i, j, k));
//				}
//			}
//		}
//		int res;
//
//		tempPlayer.attackOptions.erase(tempPlayer.attackOptions.find(Coordinate(7, 3, 1)));
//		tempPlayer.attackOptions.erase(tempPlayer.attackOptions.find(Coordinate(7, 3, 8)));
//
//		res = tempPlayer.countDistance(Coordinate(7, 3, 8), 0, false, false, -1);
//		if (res != -1) {
//			std::cout << "3 the distance was supposed to be -1 !!!!(horizontal)  got " << res << " :(" << std::endl;
//		}
//
//		res = tempPlayer.countDistance(Coordinate(7, 3, 8), 7, false, false, -1);
//		if (res != 6) {
//			std::cout << "3 the distance was supposed to be 6 (7,3,8) !!!!  got " << res << " :(" << std::endl;
//		}
//
//		res = tempPlayer.countDistance(Coordinate(7, 3, 1), 7, false, false, +1);
//		if (res != 6) {
//			std::cout << "3 the distance was supposed to be 6 (7,3,1)!!!!  got " << res << " :(" << std::endl;
//		}
//
//		// wall at 7,3,0
//		res = tempPlayer.countDistance(Coordinate(7, 3, 1), 10, false, false, -1);
//		if (res != 0) {
//			std::cout << "3 the distance was supposed to be  (7, 3, 1) wall !!!!  got " << res << " :(" << std::endl;
//		}
//	}
//	std::cout << "Done testcountDistance " << std::endl;
//
//}
//
//
//int testPlayerSmart::testnotifyOnAttackResult()
//{
//	{
//		PlayerSmart tmpPlayer;
//		setTempPlayer1(tmpPlayer);
//		tmpPlayer.shipsCount.clear();
//		tmpPlayer.shipsCount.push_back(std::make_pair(1, 8));
//		tmpPlayer.shipsCount.push_back(std::make_pair(2, 8));
//		//miss
//		tmpPlayer.notifyOnAttackResult(0, Coordinate(8, 2, 1), AttackResult::Miss);//miss 8,2,1
//		if (tmpPlayer.isInAttackOptions(Coordinate(8, 2, 1))) {
//			std::cout << "not good!didnt delete 8,2,1 to options ! " << std::endl;
//		}
//
//		//hit (merge one coor with one ship)
//		tmpPlayer.notifyOnAttackResult(0, Coordinate(4, 2, 1), AttackResult::Hit);//Hit 4,2
//		if (tmpPlayer.isInAttackOptions(Coordinate(4, 2, 1)))
//		{
//			std::cout << "not good!didnt deleted 4,2,1 to options ! " << std::endl;
//		}
//
//		std::vector<ShipInProcess> allShips;
//		// create ships
//		ShipInProcess sizeOne_1(1, 1, 1);
//		ShipInProcess sizeOne_2(3, 8, 1);
//		ShipInProcess sizeOne_3(9, 2, 1);
//
//		ShipInProcess sizeTwo_1(7, 8, 1);
//		sizeTwo_1.addCoordinate(8, 8, 1);
//
//		ShipInProcess sizeThree_1(4, 3, 1);
//		sizeThree_1.addCoordinate(4, 4, 1);
//		sizeThree_1.addCoordinate(4, 5, 1);
//		sizeThree_1.addCoordinate(4, 2, 1);
//
//		ShipInProcess sizeTwo_2(5, 8, 1);
//		sizeTwo_2.addCoordinate(5, 8, 2);
//
//		allShips.push_back(sizeThree_1);
//		allShips.push_back(sizeTwo_1);
//		allShips.push_back(sizeTwo_2);
//		allShips.push_back(sizeOne_3);
//		allShips.push_back(sizeOne_1);
//		allShips.push_back(sizeOne_2);
//
//		for (auto i = 0; i < tmpPlayer.attackedShips.size(); i++) {
//			if (!compareShipsDetails(allShips.at(i), tmpPlayer.attackedShips.at(i))) {
//				std::cout << "error in motify merge 4,2,1" << std::endl;
//			}
//		}
//
//		//sink
//		tmpPlayer.notifyOnAttackResult(0, Coordinate(2, 8, 1), AttackResult::Sink);
//
//		if (tmpPlayer.isInAttackOptions(Coordinate(2, 8, 1)))
//		{
//			std::cout << "not good!didnt deleted 2,8,1 to options ! " << std::endl;
//		}
//
//		allShips.erase(allShips.begin() + 5);
//		for (auto i = 0; i < tmpPlayer.attackedShips.size(); i++) {
//			if (!compareShipsDetails(allShips.at(i), tmpPlayer.attackedShips.at(i))) {
//				std::cout << "error in motify merge 4,2,1" << std::endl;
//			}
//		}
//
//		//hit (merge one coor with one ship)
//		tmpPlayer.notifyOnAttackResult(0, Coordinate(10, 2, 1), AttackResult::Hit);//Hit 2,1
//		if (tmpPlayer.isInAttackOptions(Coordinate(10, 2, 1)))
//		{
//			std::cout << "not good!didnt deleted 10,2,1 to options ! " << std::endl;
//		}
//
//		allShips.at(3).addCoordinate(10, 2, 1);
//		for (auto i = 0; i < tmpPlayer.attackedShips.size(); i++) {
//			if (!compareShipsDetails(allShips.at(i), tmpPlayer.attackedShips.at(i))) {
//				std::cout << "error in motify merge 10,2,1" << std::endl;
//			}
//		}
//
//
//	}
//
//
//	////for dimentuonal //////////////////////////////////////////////////////////////////////////////////////////
//	{
//		PlayerSmart tmpPlayer2;
//		std::vector<ShipInProcess> allShips2;
//		tmpPlayer2.shipsCount.push_back(std::make_pair(1, 1));
//		tmpPlayer2.shipsCount.push_back(std::make_pair(2, 1));
//		tmpPlayer2.shipsCount.push_back(std::make_pair(3, 1));
//		tmpPlayer2.shipsCount.push_back(std::make_pair(4, 1));
//		tmpPlayer2.shipsCount.push_back(std::make_pair(5, 1));
//		tmpPlayer2.shipsCount.push_back(std::make_pair(6, 0));
//		tmpPlayer2.shipsCount.push_back(std::make_pair(7, 0));
//
//		tmpPlayer2.boardCols = 10;
//		tmpPlayer2.boardDepth = 10;
//		tmpPlayer2.boardRows = 10;
//
//
//		//create Set of options
//		for (int i = 1; i < 11; i++)
//		{
//			for (int j = 1; j < 11; j++)
//			{
//				for (int k = 1; k < 11; k++) {
//					tmpPlayer2.attackOptions.insert(Coordinate(i, j, k));
//
//				}
//			}
//		}
//
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 1, 1));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 1));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 3, 8));
//
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 7, 8));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 8, 8));
//
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 3));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 5));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 4));
//
//
//		// clear envirnment
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 7, 7));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 8, 7));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 7, 9));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 8, 9));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(1, 7, 8));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(1, 8, 8));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(3, 7, 8));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(3, 8, 8));
//
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 3, 3));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 3, 5));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 3, 4));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 5, 3));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 5, 5));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 5, 4));
//
//		tmpPlayer2.delCoorAttackOptions(Coordinate(1, 4, 3));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(1, 4, 5));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(1, 4, 4));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(3, 4, 3));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(3, 4, 5));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(3, 4, 4));
//
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 5, 8));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 8));
//
//		tmpPlayer2.delCoorAttackOptions(Coordinate(1, 5, 8));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(1, 4, 8));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(3, 5, 8));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(3, 4, 8));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 5, 7));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 7));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 5, 9));
//		tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 9));
//
//		ShipInProcess sizeTwo_2(2, 5, 8);
//		sizeTwo_2.addCoordinate(2, 4, 8);
//		// create ships
//		ShipInProcess sizeOne_1(2, 1, 1);
//		ShipInProcess sizeOne_2(2, 4, 1);
//		ShipInProcess sizeOne_3(2, 10, 8);
//
//		ShipInProcess sizeTwo_1(2, 7, 8);
//		sizeTwo_1.addCoordinate(2, 8, 8);
//
//		ShipInProcess sizeThree_1(2, 4, 3);
//		sizeThree_1.addCoordinate(2, 4, 4);
//		sizeThree_1.addCoordinate(2, 4, 5);
//
//
//		allShips2.push_back(sizeThree_1);
//		allShips2.push_back(sizeTwo_1);
//		allShips2.push_back(sizeTwo_2);
//		allShips2.push_back(sizeOne_3);
//		allShips2.push_back(sizeOne_1);
//		allShips2.push_back(sizeOne_2);
//
//		tmpPlayer2.attackedShips = allShips2;
//		//miss
//		tmpPlayer2.notifyOnAttackResult(0, Coordinate(2, 8, 2), AttackResult::Miss);//miss 2,8,2
//		if (tmpPlayer2.isInAttackOptions(Coordinate(2, 8, 2)))
//		{
//			std::cout << "not good!didnt delete 2,8,2 to options ! " << std::endl;
//		}
//		for (auto i = 0; i < tmpPlayer2.attackedShips.size(); i++) {
//			if (!compareShipsDetails(allShips2.at(i), tmpPlayer2.attackedShips.at(i))) {
//				std::cout << "error in motify merge 2,8,2 depticl" << std::endl;
//			}
//		}
//
//		//hit (merge one coor with one ship)
//		tmpPlayer2.notifyOnAttackResult(0, Coordinate(2, 4, 2), AttackResult::Hit);//Hit 4,2
//		if (tmpPlayer2.isInAttackOptions(Coordinate(2, 4, 2)))
//		{
//			std::cout << "not good!didnt deleted 2,4,2, to options ! " << std::endl;
//		}
//
//		allShips2.at(0).addCoordinate(2, 4, 2);
//		allShips2.at(0).addCoordinate(2, 4, 1);
//		allShips2.erase(allShips2.begin() + 5);
//		for (auto i = 0; i < tmpPlayer2.attackedShips.size(); i++) {
//			if (!compareShipsDetails(allShips2.at(i), tmpPlayer2.attackedShips.at(i))) {
//				std::cout << "error in motify merge 2,4,2 depticl" << std::endl;
//			}
//		}
//
//
//
//
//		//hit (merge one coor with one ship)
//		tmpPlayer2.notifyOnAttackResult(0, Coordinate(2, 2, 1), AttackResult::Hit);//Hit 2,1
//		if ((tmpPlayer2.isInAttackOptions(Coordinate(2, 2, 1))))
//		{
//			std::cout << "not good!didnt deleted 2,2,1 to options ! " << std::endl;
//		}
//		allShips2.clear();
//
//		sizeThree_1.addCoordinate(2, 4, 2);
//		sizeThree_1.addCoordinate(2, 4, 1);
//		sizeOne_1.addCoordinate(2, 2, 1);
//
//		allShips2.push_back(sizeThree_1);
//		allShips2.push_back(sizeTwo_1);
//		allShips2.push_back(sizeTwo_2);
//		allShips2.push_back(sizeOne_1);
//		allShips2.push_back(sizeOne_3);
//
//		for (auto i = 0; i < tmpPlayer2.attackedShips.size(); i++) {
//			if (!compareShipsDetails(allShips2.at(i), tmpPlayer2.attackedShips.at(i))) {
//				std::cout << "error in motify merge 2,2,1 depticl" << std::endl;
//			}
//		}
//
//
//		//hit merge two vectors 
//		tmpPlayer2.notifyOnAttackResult(0, Coordinate(2, 6, 8), AttackResult::Hit);//Hit 6,8
//		if (tmpPlayer2.isInAttackOptions(Coordinate(2, 6, 8)))
//		{
//			std::cout << "not good!didnt deleted 2,6,8 to options ! " << std::endl;
//		}
//
//		allShips2.clear();
//		sizeTwo_1.addCoordinate(2, 6, 8);
//		sizeTwo_1.addCoordinate(2, 5, 8);
//		sizeTwo_1.addCoordinate(2, 4, 8);
//
//		allShips2.push_back(sizeThree_1);
//		allShips2.push_back(sizeTwo_1);
//		allShips2.push_back(sizeOne_1);
//		allShips2.push_back(sizeOne_3);
//
//		for (auto i = 0; i < tmpPlayer2.attackedShips.size(); i++) {
//			if (!compareShipsDetails(allShips2.at(i), tmpPlayer2.attackedShips.at(i))) {
//				std::cout << "error in motify merge 2,6,8" << std::endl;
//			}
//		}
//
//		//sink
//		tmpPlayer2.imbalancedAttackOptions.insert(Coordinate(9, 9, 9));
//
//		tmpPlayer2.notifyOnAttackResult(0, Coordinate(2, 9, 8), AttackResult::Sink);
//		if (tmpPlayer2.isInAttackOptions(Coordinate(2, 9, 8)))
//		{
//			std::cout << "not good!didnt deleted 2,9,8 to options ! " << std::endl;
//		}
//
//		allShips2.clear();
//		allShips2.push_back(sizeThree_1);
//		allShips2.push_back(sizeOne_1);
//
//		for (auto i = 0; i < tmpPlayer2.attackedShips.size(); i++) {
//			if (!compareShipsDetails(allShips2.at(i), tmpPlayer2.attackedShips.at(i))) {
//				std::cout << "error in motify merge 2,9,8" << std::endl;
//			}
//		}
//		if (tmpPlayer2.isBoardBalanced != false) {
//			std::cout << "board should be imbalanced" << std::endl;
//		}
//
//
//		if (!tmpPlayer2.isInAttackOptions(Coordinate(9, 9, 9))) {
//			std::cout << "imbalanced options should be in attack options" << std::endl;
//		}
//
//	}
//
//	{
//		////check for new terms
//		//////////////////////////////////////////////////////////////////////
//		PlayerSmart tmpPlayer;
//		std::vector<ShipInProcess> allShips;
//
//		//create Set of options
//		for (int i = 1; i < 5; i++)
//		{
//			for (int j = 1; j < 5; j++)
//			{
//				for (int k = 1; k < 5; k++) {
//					tmpPlayer.attackOptions.insert(Coordinate(i, j, k));
//
//				}
//			}
//		}
//
//		// create ships
//		tmpPlayer.delCoorAttackOptions(Coordinate(4, 2, 1));
//		tmpPlayer.delCoorAttackOptions(Coordinate(4, 3, 1));
//		tmpPlayer.delCoorAttackOptions(Coordinate(4, 4, 1));
//		tmpPlayer.delCoorAttackOptions(Coordinate(3, 2, 1));
//		tmpPlayer.delCoorAttackOptions(Coordinate(3, 3, 1));
//		tmpPlayer.delCoorAttackOptions(Coordinate(3, 4, 1));
//		tmpPlayer.delCoorAttackOptions(Coordinate(4, 2, 2));
//		tmpPlayer.delCoorAttackOptions(Coordinate(4, 3, 2));
//		tmpPlayer.delCoorAttackOptions(Coordinate(4, 4, 2));
//
//		ShipInProcess sizeThree_1(4, 2, 1);
//		sizeThree_1.addCoordinate(4, 3, 1);
//		sizeThree_1.addCoordinate(4, 4, 1);
//		allShips.push_back(sizeThree_1);
//		tmpPlayer.attackedShips = allShips;
//		tmpPlayer.shipsCount.push_back(std::make_pair(1, 0));
//		tmpPlayer.shipsCount.push_back(std::make_pair(2, 0));
//		tmpPlayer.shipsCount.push_back(std::make_pair(3, 0));
//		tmpPlayer.shipsCount.push_back(std::make_pair(4, 1));
//
//
//		std::set<Coordinate> expected_imbalanced;
//		expected_imbalanced.insert(Coordinate(1, 2, 1));
//		expected_imbalanced.insert(Coordinate(2, 1, 1));
//		expected_imbalanced.insert(Coordinate(2, 3, 1));
//		expected_imbalanced.insert(Coordinate(2, 4, 1));
//		expected_imbalanced.insert(Coordinate(2, 2, 2));
//		expected_imbalanced.insert(Coordinate(2, 2, 3));
//		expected_imbalanced.insert(Coordinate(2, 2, 4));
//
//		//miss
//		tmpPlayer.notifyOnAttackResult(0, Coordinate(2, 2, 1), AttackResult::Miss);//miss 2,2,1
//		if (tmpPlayer.isInAttackOptions(Coordinate(2, 2, 1)))
//		{
//			std::cout << "not good!didnt delete 2,2,1 to options ! " << std::endl;
//		}
//
//		for (auto& coor : expected_imbalanced) {
//			if (tmpPlayer.isInAttackOptions(coor)) {
//				std::cout << "didnt remove coor from attack options";
//				printCoordinate(coor);
//			}
//			if (!tmpPlayer.isInImbalancedOptions(coor)) {
//				std::cout << "missing coordinate in imbalanced options";
//				printCoordinate(coor);
//			}
//		}
//
//		//hit (merge one coor with one ship)
//		tmpPlayer.notifyOnAttackResult(0, Coordinate(4, 2, 1), AttackResult::Hit);//Hit 4,2
//		if (tmpPlayer.isInAttackOptions(Coordinate(4, 2, 1)))
//		{
//			std::cout << "not good!didnt deleted 4,2,1 to options ! " << std::endl;
//		}
//	}
//
//	{
//		////check for new terms
//		//////////////////////////////////////////////////////////////////////
//		PlayerSmart tmpPlayer;
//		std::vector<ShipInProcess> allShips;
//
//		//create Set of options
//		for (int i = 1; i < 5; i++)
//		{
//			for (int j = 1; j < 5; j++)
//			{
//				for (int k = 1; k < 5; k++) {
//					tmpPlayer.attackOptions.insert(Coordinate(i, j, k));
//
//				}
//			}
//		}
//
//		// create ships
//		tmpPlayer.delCoorAttackOptions(Coordinate(4, 2, 1));
//		tmpPlayer.delCoorAttackOptions(Coordinate(4, 3, 1));
//		tmpPlayer.delCoorAttackOptions(Coordinate(4, 4, 1));
//		tmpPlayer.delCoorAttackOptions(Coordinate(3, 2, 1));
//		tmpPlayer.delCoorAttackOptions(Coordinate(3, 3, 1));
//		tmpPlayer.delCoorAttackOptions(Coordinate(3, 4, 1));
//		tmpPlayer.delCoorAttackOptions(Coordinate(4, 2, 2));
//		tmpPlayer.delCoorAttackOptions(Coordinate(4, 3, 2));
//		tmpPlayer.delCoorAttackOptions(Coordinate(4, 4, 2));
//
//		ShipInProcess sizeThree_1(4, 2, 1);
//		sizeThree_1.addCoordinate(4, 3, 1);
//		sizeThree_1.addCoordinate(4, 4, 1);
//		allShips.push_back(sizeThree_1);
//		tmpPlayer.attackedShips = allShips;
//		tmpPlayer.shipsCount.push_back(std::make_pair(1, 0));
//		tmpPlayer.shipsCount.push_back(std::make_pair(2, 0));
//		tmpPlayer.shipsCount.push_back(std::make_pair(3, 0));
//		tmpPlayer.shipsCount.push_back(std::make_pair(4, 1));
//
//
//		std::set<Coordinate> expected_imbalanced;
//		expected_imbalanced.insert(Coordinate(1, 2, 1));
//		expected_imbalanced.insert(Coordinate(2, 1, 1));
//		expected_imbalanced.insert(Coordinate(2, 3, 1));
//		expected_imbalanced.insert(Coordinate(2, 4, 1));
//		expected_imbalanced.insert(Coordinate(2, 2, 2));
//		expected_imbalanced.insert(Coordinate(2, 2, 3));
//		expected_imbalanced.insert(Coordinate(2, 2, 4));
//
//		//miss
//		tmpPlayer.notifyOnAttackResult(0, Coordinate(2, 2, 1), AttackResult::Miss);//miss 2,2,1
//		if (tmpPlayer.isInAttackOptions(Coordinate(2, 2, 1)))
//		{
//			std::cout << "not good!didnt delete 2,2,1 to options ! " << std::endl;
//		}
//
//		for (auto& coor : expected_imbalanced) {
//			if (tmpPlayer.isInAttackOptions(coor)) {
//				std::cout << "didnt remove coor from attack options";
//				printCoordinate(coor);
//			}
//			if (!tmpPlayer.isInImbalancedOptions(coor)) {
//				std::cout << "missing coordinate in imbalanced options";
//				printCoordinate(coor);
//			}
//		}
//
//		//hit (merge one coor with one ship)
//		tmpPlayer.notifyOnAttackResult(0, Coordinate(4, 2, 1), AttackResult::Hit);//Hit 4,2
//		if (tmpPlayer.isInAttackOptions(Coordinate(4, 2, 1)))
//		{
//			std::cout << "not good!didnt deleted 4,2,1 to options ! " << std::endl;
//		}
//	}
//
//
//	{
//		PlayerSmart tmpPlayer;
//		std::vector<ShipInProcess> allShips;
//
//		//create Set of options
//		for (int i = 1; i < 5; i++)
//		{
//			for (int j = 1; j < 5; j++)
//			{
//				for (int k = 1; k < 5; k++) {
//					tmpPlayer.attackOptions.insert(Coordinate(i, j, k));
//
//				}
//			}
//		}
//
//		// create ships
//		tmpPlayer.delCoorAttackOptions(Coordinate(4, 2, 1));
//		tmpPlayer.delCoorAttackOptions(Coordinate(4, 3, 1));
//		tmpPlayer.delCoorAttackOptions(Coordinate(4, 4, 1));
//		tmpPlayer.delCoorAttackOptions(Coordinate(3, 2, 1));
//		tmpPlayer.delCoorAttackOptions(Coordinate(3, 3, 1));
//		tmpPlayer.delCoorAttackOptions(Coordinate(3, 4, 1));
//		tmpPlayer.delCoorAttackOptions(Coordinate(4, 2, 2));
//		tmpPlayer.delCoorAttackOptions(Coordinate(4, 3, 2));
//		tmpPlayer.delCoorAttackOptions(Coordinate(4, 4, 2));
//
//		ShipInProcess sizeThree_1(4, 2, 1);
//		sizeThree_1.addCoordinate(4, 3, 1);
//		sizeThree_1.addCoordinate(4, 4, 1);
//		allShips.push_back(sizeThree_1);
//		tmpPlayer.attackedShips = allShips;
//		tmpPlayer.shipsCount.push_back(std::make_pair(1, 0));
//		tmpPlayer.shipsCount.push_back(std::make_pair(2, 0));
//		tmpPlayer.shipsCount.push_back(std::make_pair(3, 0));
//		tmpPlayer.shipsCount.push_back(std::make_pair(4, 0));
//		tmpPlayer.shipsCount.push_back(std::make_pair(5, 1));
//
//		std::set<Coordinate> attackedShip;
//		std::set<Coordinate> expected_imbalanced;
//		std::set<Coordinate> expected_dead;
//
//		attackedShip.insert(Coordinate(4, 1, 1));
//		attackedShip.insert(Coordinate(4, 2, 1));
//		attackedShip.insert(Coordinate(4, 3, 1));
//		attackedShip.insert(Coordinate(4, 4, 1));
//
//		for (Coordinate coor : attackedShip) {
//			std::vector<Coordinate> serVec = findSurronding(coor);
//			for (auto ser : serVec) {
//				if (tmpPlayer.isInBoard(ser.row, ser.col, ser.depth)) {
//					expected_dead.insert(ser);
//				}
//			}
//		}
//
//		for (auto dead : expected_dead) {
//			std::vector<Coordinate> cut = shouldBeRemoved(dead, 4, expected_dead);
//			for (auto& ser : cut) {
//				if (tmpPlayer.isInBoard(ser.row, ser.col, ser.depth)) {
//					expected_imbalanced.insert(ser);
//				}
//
//			}
//		}
//
//		tmpPlayer.notifyOnAttackResult(0, Coordinate(4, 1, 1), AttackResult::Sink);//miss 4,1,1
//		for (auto& coor : expected_dead) {
//			if (tmpPlayer.isInAttackOptions(coor) || tmpPlayer.isInImbalancedOptions(coor))
//			{
//				std::cout << "not good!didnt delete from attack options|| imbalanced";
//				printCoordinate(coor);
//			}
//		}
//
//		for (auto& coor : expected_imbalanced) {
//			if (tmpPlayer.isInAttackOptions(coor)) {
//				std::cout << "didnt remove coor from attack options";
//				printCoordinate(coor);
//			}
//			if (!tmpPlayer.isInImbalancedOptions(coor)) {
//				std::cout << "missing coordinate in imbalanced options";
//				printCoordinate(coor);
//			}
//		}
//	}
//
//
//	{
//		PlayerSmart tmpPlayer;
//		std::vector<ShipInProcess> allShips;
//
//		//create Set of options
//		for (int i = 1; i < 5; i++)
//		{
//			for (int j = 1; j < 5; j++)
//			{
//				for (int k = 1; k < 5; k++) {
//					tmpPlayer.attackOptions.insert(Coordinate(i, j, k));
//
//				}
//			}
//		}
//
//		// create ships
//		tmpPlayer.delCoorAttackOptions(Coordinate(4, 2, 1));
//		tmpPlayer.delCoorAttackOptions(Coordinate(4, 3, 1));
//		tmpPlayer.delCoorAttackOptions(Coordinate(4, 4, 1));
//		tmpPlayer.delCoorAttackOptions(Coordinate(3, 2, 1));
//		tmpPlayer.delCoorAttackOptions(Coordinate(3, 3, 1));
//		tmpPlayer.delCoorAttackOptions(Coordinate(3, 4, 1));
//		tmpPlayer.delCoorAttackOptions(Coordinate(4, 2, 2));
//		tmpPlayer.delCoorAttackOptions(Coordinate(4, 3, 2));
//		tmpPlayer.delCoorAttackOptions(Coordinate(4, 4, 2));
//
//		ShipInProcess sizeThree_1(4, 2, 1);
//		sizeThree_1.addCoordinate(4, 3, 1);
//		sizeThree_1.addCoordinate(4, 4, 1);
//		allShips.push_back(sizeThree_1);
//		tmpPlayer.attackedShips = allShips;
//		tmpPlayer.shipsCount.push_back(std::make_pair(1, 1));
//		tmpPlayer.shipsCount.push_back(std::make_pair(2, 0));
//		tmpPlayer.shipsCount.push_back(std::make_pair(3, 0));
//		tmpPlayer.shipsCount.push_back(std::make_pair(4, 0));
//		tmpPlayer.shipsCount.push_back(std::make_pair(5, 1));
//
//		std::set<Coordinate> attackedShip;
//		std::set<Coordinate> expected_imbalanced;
//		std::set<Coordinate> expected_dead;
//
//		attackedShip.insert(Coordinate(4, 1, 1));
//		attackedShip.insert(Coordinate(4, 2, 1));
//		attackedShip.insert(Coordinate(4, 3, 1));
//		attackedShip.insert(Coordinate(4, 4, 1));
//
//		for (Coordinate coor : attackedShip) {
//			std::vector<Coordinate> serVec = findSurronding(coor);
//			for (auto ser : serVec) {
//				if (tmpPlayer.isInBoard(ser.row, ser.col, ser.depth)) {
//					expected_dead.insert(ser);
//				}
//			}
//		}
//
//		//for (auto dead : expected_dead) {
//		//	std::vector<Coordinate> cut = shouldBeRemoved(dead, 4, expected_dead);
//		//	for (auto& ser : cut) {
//		//		if (tmpPlayer.isInBoard(ser.row, ser.col, ser.depth)) {
//		//			expected_imbalanced.insert(ser);
//		//		}
//
//		//	}
//		//}
//
//		tmpPlayer.notifyOnAttackResult(0, Coordinate(4, 1, 1), AttackResult::Sink);//miss 4,1,1
//		for (auto& coor : expected_dead) {
//			if (tmpPlayer.isInAttackOptions(coor) || tmpPlayer.isInImbalancedOptions(coor))
//			{
//				std::cout << "not good!didnt delete from attack options|| imbalanced";
//				printCoordinate(coor);
//			}
//		}
//
//		if (tmpPlayer.imbalancedAttackOptions.size() != 0) {
//			std::cout << "error" << std::endl;
//		}
//		for (auto& coor : expected_imbalanced) {
//			if (tmpPlayer.isInAttackOptions(coor)) {
//				std::cout << "didnt remove coor from attack options";
//				printCoordinate(coor);
//			}
//			if (!tmpPlayer.isInImbalancedOptions(coor)) {
//				std::cout << "missing coordinate in imbalanced options";
//				printCoordinate(coor);
//			}
//		}
//	}
//	std::cout << "Done notify" << std::endl;
//	return 0;
//}
//
//std::vector<Coordinate> testPlayerSmart::shouldBeRemoved(Coordinate & dead, int boardSize, std::set<Coordinate> allDead) {
//	std::vector<Coordinate> surr = findSurronding(dead);
//	Coordinate temp(-1, -1, -1);
//	std::vector<Coordinate> res;
//	for (auto& adjecent : surr) {
//		int row = adjecent.row;
//		int col = adjecent.col;
//		int depth = adjecent.depth;
//
//		for (int i = 1; i <= boardSize; i++) {
//			PlayerSmart::updateCoordinates(temp, i, col, depth);
//			if (allDead.find(temp) == allDead.end()) {
//				res.push_back(temp);
//			}
//
//			PlayerSmart::updateCoordinates(temp, row, i, depth);
//			if (allDead.find(temp) == allDead.end()) {
//				res.push_back(temp);
//			}
//			PlayerSmart::updateCoordinates(temp, row, col, i);
//			if (allDead.find(temp) == allDead.end()) {
//				res.push_back(temp);
//			}
//		}
//
//	}
//	return res;
//}
//
//std::vector<Coordinate> testPlayerSmart::findSurronding(const Coordinate& target) {
//
//	Coordinate temp(-1, -1, -1);
//	std::vector<Coordinate> vic = PlayerSmart::setSixOptionsVector();
//	std::vector<Coordinate> res;
//	for (auto& coor : vic) {
//		PlayerSmart::updateCoordinates(temp, target.row + coor.row, target.col + coor.col, target.depth + coor.depth);
//		res.push_back(temp);
//	}
//	return res;
//}
//
//void testPlayerSmart::expectedTempPlayer1_afterAddCoor(PlayerSmart& tmpPlayer) {
//	std::vector<ShipInProcess> allShips;
//	tmpPlayer.boardRows = 10;
//	tmpPlayer.boardCols = 10;
//	tmpPlayer.boardDepth = 10;
//	// create ships
//	ShipInProcess sizeOne_1(1, 1, 1);
//	sizeOne_1.addCoordinate(2, 1, 1);
//
//	ShipInProcess sizeOne_2(3, 8, 1);
//	ShipInProcess sizeOne_3(9, 2, 1);
//
//	ShipInProcess sizeTwo_1(7, 8, 1);
//	sizeTwo_1.addCoordinate(8, 8, 1);
//
//	ShipInProcess sizeThree_1(4, 3, 1);
//	sizeThree_1.addCoordinate(4, 4, 1);
//	sizeThree_1.addCoordinate(4, 5, 1);
//
//	ShipInProcess sizeTwo_2(5, 8, 1);
//	sizeTwo_2.addCoordinate(5, 8, 2);
//
//	allShips.push_back(sizeThree_1);
//	allShips.push_back(sizeTwo_1);
//	allShips.push_back(sizeTwo_2);
//	allShips.push_back(sizeOne_3);
//	allShips.push_back(sizeOne_1);
//	allShips.push_back(sizeOne_2);
//	tmpPlayer.attackedShips = allShips;
//
//	//create Set of options
//	for (int i = 1; i < 11; i++)
//	{
//		for (int j = 1; j < 11; j++)
//		{
//			for (int k = 1; k < 11; k++) {
//				tmpPlayer.attackOptions.insert(Coordinate(i, j, k));
//
//			}
//		}
//	}
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(1, 1, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 1, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(1, 2, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 2, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(1, 1, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 1, 2));
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 8, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(9, 2, 1));
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 8, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 8, 1));
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 3, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 4, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 5, 1));
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 8, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 8, 2));
//
//	// clear envirnment
//	// ship of size 2 _1 
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 7, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 7, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 9, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 9, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 8, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 8, 2));
//
//	// ship of size 2 _2 
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 8, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 8, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(6, 8, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(6, 8, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 7, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 7, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 9, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 9, 2));
//
//	// ship of size 3 
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 3, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 5, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 4, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 3, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 5, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 4, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 3, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 5, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 4, 2));
//}
//
//
//
//void testPlayerSmart::expectedTempPlayer1_afterAddCoor2(PlayerSmart& tmpPlayer) {
//	std::vector<ShipInProcess> allShips;
//	tmpPlayer.boardRows = 10;
//	tmpPlayer.boardCols = 10;
//	tmpPlayer.boardDepth = 10;
//	// create ships
//	ShipInProcess sizeOne_1(1, 1, 1);
//	sizeOne_1.addCoordinate(2, 1, 1);
//	sizeOne_1.addCoordinate(3, 1, 1);
//
//	ShipInProcess sizeOne_2(3, 8, 1);
//	ShipInProcess sizeOne_3(9, 2, 1);
//
//	ShipInProcess sizeTwo_1(7, 8, 1);
//	sizeTwo_1.addCoordinate(8, 8, 1);
//
//	ShipInProcess sizeThree_1(4, 3, 1);
//	sizeThree_1.addCoordinate(4, 4, 1);
//	sizeThree_1.addCoordinate(4, 5, 1);
//
//	ShipInProcess sizeTwo_2(5, 8, 1);
//	sizeTwo_2.addCoordinate(5, 8, 2);
//
//	allShips.push_back(sizeThree_1);
//	allShips.push_back(sizeTwo_1);
//	allShips.push_back(sizeTwo_2);
//	allShips.push_back(sizeOne_3);
//	allShips.push_back(sizeOne_1);
//	allShips.push_back(sizeOne_2);
//	tmpPlayer.attackedShips = allShips;
//
//	//create Set of options
//	for (int i = 1; i < 11; i++)
//	{
//		for (int j = 1; j < 11; j++)
//		{
//			for (int k = 1; k < 11; k++) {
//				tmpPlayer.attackOptions.insert(Coordinate(i, j, k));
//
//			}
//		}
//	}
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(1, 1, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 1, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(1, 2, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 2, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(1, 1, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 1, 2));
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 8, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(9, 2, 1));
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 8, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 8, 1));
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 3, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 4, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 5, 1));
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 8, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 8, 2));
//
//	// clear envirnment
//	// ship of size 2 _1 
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 7, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 7, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 9, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 9, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 8, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 8, 2));
//
//	// ship of size 2 _2 
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 8, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 8, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(6, 8, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(6, 8, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 7, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 7, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 9, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 9, 2));
//
//	// ship of size 3 
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 3, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 5, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 4, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 3, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 5, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 4, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 3, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 5, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 4, 2));
//
//}
//
//void testPlayerSmart::expectedTempPlayer1_afterAddCoor3(PlayerSmart& tmpPlayer) {
//	std::vector<ShipInProcess> allShips;
//	// create ships
//	ShipInProcess sizeOne_1(1, 1, 1);
//	sizeOne_1.addCoordinate(2, 1, 1);
//	sizeOne_1.addCoordinate(3, 1, 1);
//
//	ShipInProcess sizeOne_2(3, 8, 1);
//	ShipInProcess sizeOne_3(9, 2, 1);
//
//	ShipInProcess sizeTwo_1(7, 8, 1);
//	sizeTwo_1.addCoordinate(8, 8, 1);
//
//	ShipInProcess sizeThree_1(4, 3, 1);
//	sizeThree_1.addCoordinate(4, 4, 1);
//	sizeThree_1.addCoordinate(4, 5, 1);
//	sizeThree_1.addCoordinate(4, 6, 1);
//
//	ShipInProcess sizeTwo_2(5, 8, 1);
//	sizeTwo_2.addCoordinate(5, 8, 2);
//
//	allShips.push_back(sizeThree_1);
//	allShips.push_back(sizeTwo_1);
//	allShips.push_back(sizeTwo_2);
//	allShips.push_back(sizeOne_3);
//	allShips.push_back(sizeOne_1);
//	allShips.push_back(sizeOne_2);
//	tmpPlayer.attackedShips = allShips;
//
//	//create Set of options
//	for (int i = 1; i < 10; i++)
//	{
//		for (int j = 1; j < 10; j++)
//		{
//			for (int k = 1; k < 10; k++) {
//				tmpPlayer.attackOptions.insert(Coordinate(i, j, k));
//
//			}
//		}
//	}
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(1, 1, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 1, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 1, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(1, 2, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 2, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 2, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(1, 1, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 1, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 1, 2));
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 8, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(9, 2, 1));
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 8, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 8, 1));
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 3, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 4, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 5, 1));
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 8, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 8, 2));
//
//	// clear envirnment
//	// ship of size 2 _1 
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 7, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 7, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 9, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 9, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 8, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 8, 2));
//
//	// ship of size 2 _2 
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 8, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 8, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(6, 8, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(6, 8, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 7, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 7, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 9, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 9, 2));
//
//	// ship of size 3 
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 3, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 5, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 4, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 3, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 5, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 4, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 3, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 5, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 4, 2));
//
//}
//
//void testPlayerSmart::expectedTempPlayer1_afterAddCoor4(PlayerSmart& tmpPlayer) {
//	std::vector<ShipInProcess> allShips;
//	// create ships
//	ShipInProcess sizeOne_1(1, 1, 1);
//	sizeOne_1.addCoordinate(2, 1, 1);
//	sizeOne_1.addCoordinate(3, 1, 1);
//
//	ShipInProcess sizeOne_2(3, 8, 1);
//	ShipInProcess sizeOne_3(9, 2, 1);
//
//	ShipInProcess sizeTwo_1(7, 8, 1);
//	sizeTwo_1.addCoordinate(8, 8, 1);
//
//	ShipInProcess sizeThree_1(4, 3, 1);
//	sizeThree_1.addCoordinate(4, 4, 1);
//	sizeThree_1.addCoordinate(4, 5, 1);
//	sizeThree_1.addCoordinate(4, 6, 1);
//
//	ShipInProcess sizeTwo_2(5, 8, 1);
//	sizeTwo_2.addCoordinate(5, 8, 2);
//
//	ShipInProcess sizeOne_4(7, 2, 1);
//
//	allShips.push_back(sizeThree_1);
//	allShips.push_back(sizeTwo_1);
//	allShips.push_back(sizeTwo_2);
//	allShips.push_back(sizeOne_3);
//	allShips.push_back(sizeOne_1);
//	allShips.push_back(sizeOne_2);
//	allShips.push_back(sizeOne_4);
//	tmpPlayer.attackedShips = allShips;
//
//	//create Set of options
//	for (int i = 1; i < 10; i++)
//	{
//		for (int j = 1; j < 10; j++)
//		{
//			for (int k = 1; k < 10; k++) {
//				tmpPlayer.attackOptions.insert(Coordinate(i, j, k));
//
//			}
//		}
//	}
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 2, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(1, 1, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 1, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 1, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(1, 2, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 2, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 2, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(1, 1, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(2, 1, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 1, 2));
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 8, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(9, 2, 1));
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 8, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 8, 1));
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 3, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 4, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 5, 1));
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 8, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 8, 2));
//
//	// clear envirnment
//	// ship of size 2 _1 
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 7, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 7, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 9, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 9, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 8, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 8, 2));
//
//	// ship of size 2 _2 
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 8, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 8, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(6, 8, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(6, 8, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 7, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 7, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 9, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 9, 2));
//
//	// ship of size 3 
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 3, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 5, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 4, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 3, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 5, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 4, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 3, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 5, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 4, 2));
//
//}
//
//void testPlayerSmart::expectedTempPlayer2_afterAddCoor(PlayerSmart& tmpPlayer2) {
//	std::vector<ShipInProcess> allShips2;
//
//	// create ships
//	ShipInProcess sizeOne_1(2, 1, 1);
//	sizeOne_1.addCoordinate(2, 2, 1);
//
//	ShipInProcess sizeOne_2(2, 3, 8);
//	ShipInProcess sizeOne_3(2, 9, 2);
//
//	ShipInProcess sizeTwo_1(2, 7, 8);
//	sizeTwo_1.addCoordinate(2, 8, 8);
//
//	ShipInProcess sizeThree_1(2, 4, 3);
//	sizeThree_1.addCoordinate(2, 4, 4);
//	sizeThree_1.addCoordinate(2, 4, 5);
//
//	ShipInProcess sizeTwo_2(2, 5, 8);
//	sizeTwo_2.addCoordinate(2, 4, 9);
//
//	allShips2.push_back(sizeThree_1);
//	allShips2.push_back(sizeTwo_1);
//	allShips2.push_back(sizeTwo_2);
//	allShips2.push_back(sizeOne_3);
//	allShips2.push_back(sizeOne_1);
//	allShips2.push_back(sizeOne_2);
//
//	tmpPlayer2.attackedShips = allShips2;
//
//	//create Set of options
//	for (int i = 1; i < 10; i++)
//	{
//		for (int j = 1; j < 10; j++)
//		{
//			for (int k = 1; k < 10; k++) {
//				tmpPlayer2.attackOptions.insert(Coordinate(i, j, k));
//
//			}
//		}
//	}
//	//
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 1, 1));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 2, 1));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 1, 1));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 2, 1));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 1, 1));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 2, 1));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 1, 2));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 2, 2));
//
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 3, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 9, 2));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 7, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 8, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 3));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 5));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 4));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 5, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 5, 9));
//
//	// clear envirnment
//	//sizeTwo_1
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 7, 7));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 8, 7));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 7, 9));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 8, 9));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 7, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 8, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 7, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 8, 8));
//
//	//sizeThree_1
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 3, 3));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 3, 5));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 3, 4));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 5, 3));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 5, 5));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 5, 4));
//
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 4, 3));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 4, 4));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 4, 5));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 4, 3));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 4, 4));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 4, 5));
//
//	//sizeTwo_2 
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 5, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 5, 9));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 5, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 5, 9));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 6, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 6, 9));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 9));
//
//}
//
//void testPlayerSmart::expectedTempPlayer2_afterAddCoor2(PlayerSmart& tmpPlayer2) {
//	std::vector<ShipInProcess> allShips2;
//
//	// create ships
//	ShipInProcess sizeOne_1(2, 1, 1);
//	sizeOne_1.addCoordinate(2, 2, 1);
//
//	ShipInProcess sizeOne_2(2, 3, 8);
//	ShipInProcess sizeOne_3(2, 9, 2);
//
//	ShipInProcess sizeTwo_1(2, 7, 8);
//	sizeTwo_1.addCoordinate(2, 8, 8);
//
//	ShipInProcess sizeThree_1(2, 4, 3);
//	sizeThree_1.addCoordinate(2, 4, 4);
//	sizeThree_1.addCoordinate(2, 4, 5);
//	sizeThree_1.addCoordinate(2, 4, 6);
//
//	ShipInProcess sizeTwo_2(2, 5, 8);
//	sizeTwo_2.addCoordinate(2, 4, 9);
//
//	allShips2.push_back(sizeThree_1);
//	allShips2.push_back(sizeTwo_1);
//	allShips2.push_back(sizeTwo_2);
//	allShips2.push_back(sizeOne_3);
//	allShips2.push_back(sizeOne_1);
//	allShips2.push_back(sizeOne_2);
//
//	tmpPlayer2.attackedShips = allShips2;
//
//	//create Set of options
//	for (int i = 1; i < 10; i++)
//	{
//		for (int j = 1; j < 10; j++)
//		{
//			for (int k = 1; k < 10; k++) {
//				tmpPlayer2.attackOptions.insert(Coordinate(i, j, k));
//
//			}
//		}
//	}
//	//
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 1, 1));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 2, 1));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 1, 1));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 2, 1));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 1, 1));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 2, 1));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 1, 2));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 2, 2));
//
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 3, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 9, 2));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 7, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 8, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 3));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 5));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 4));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 5, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 5, 9));
//
//	// clear envirnment
//	//sizeTwo_1
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 7, 7));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 8, 7));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 7, 9));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 8, 9));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 7, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 8, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 7, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 8, 8));
//
//	//sizeThree_1
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 3, 3));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 3, 5));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 3, 4));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 5, 3));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 5, 5));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 5, 4));
//
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 6));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 4, 6));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 4, 6));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 7));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 4, 3));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 4, 4));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 4, 5));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 4, 3));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 4, 4));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 4, 5));
//
//	//sizeTwo_2 
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 5, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 5, 9));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 5, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 5, 9));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 6, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 6, 9));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 9));
//
//}
//
//void testPlayerSmart::expectedTempPlayer2_afterAddCoor3(PlayerSmart& tmpPlayer2) {
//	std::vector<ShipInProcess> allShips2;
//
//	// create ships
//	ShipInProcess sizeOne_1(2, 1, 1);
//	sizeOne_1.addCoordinate(2, 2, 1);
//
//	ShipInProcess sizeOne_4(2, 7, 2);
//
//	ShipInProcess sizeOne_2(2, 3, 8);
//	ShipInProcess sizeOne_3(2, 9, 2);
//
//	ShipInProcess sizeTwo_1(2, 7, 8);
//	sizeTwo_1.addCoordinate(2, 8, 8);
//
//	ShipInProcess sizeThree_1(2, 4, 3);
//	sizeThree_1.addCoordinate(2, 4, 4);
//	sizeThree_1.addCoordinate(2, 4, 5);
//	sizeThree_1.addCoordinate(2, 4, 6);
//
//	ShipInProcess sizeTwo_2(2, 5, 8);
//	sizeTwo_2.addCoordinate(2, 4, 9);
//
//	allShips2.push_back(sizeThree_1);
//	allShips2.push_back(sizeTwo_1);
//	allShips2.push_back(sizeTwo_2);
//	allShips2.push_back(sizeOne_3);
//	allShips2.push_back(sizeOne_1);
//	allShips2.push_back(sizeOne_2);
//	allShips2.push_back(sizeOne_4);
//
//	tmpPlayer2.attackedShips = allShips2;
//
//	//create Set of options
//	for (int i = 1; i < 10; i++)
//	{
//		for (int j = 1; j < 10; j++)
//		{
//			for (int k = 1; k < 10; k++) {
//				tmpPlayer2.attackOptions.insert(Coordinate(i, j, k));
//
//			}
//		}
//	}
//	//
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 1, 1));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 2, 1));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 1, 1));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 2, 1));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 1, 1));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 2, 1));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 1, 2));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 2, 2));
//
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 7, 2));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 3, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 9, 2));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 7, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 8, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 3));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 5));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 4));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 5, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 5, 9));
//
//	// clear envirnment
//	//sizeTwo_1
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 7, 7));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 8, 7));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 7, 9));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 8, 9));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 7, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 8, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 7, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 8, 8));
//
//	//sizeThree_1
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 3, 3));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 3, 5));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 3, 4));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 5, 3));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 5, 5));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 5, 4));
//
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 6));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 4, 6));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 4, 6));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 7));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 4, 3));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 4, 4));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 4, 5));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 4, 3));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 4, 4));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 4, 5));
//
//	//sizeTwo_2 
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 5, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 5, 9));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 5, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 5, 9));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 6, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 6, 9));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 9));
//
//}
//int testPlayerSmart::testaddCoorToShipsInProcess()
//{
//
//	PlayerSmart tmpPlayer;
//	setTempPlayer1(tmpPlayer);
//
//	PlayerSmart expectedTmp;
//	expectedTempPlayer1_afterAddCoor(expectedTmp);
//
//	int res;
//	Coordinate output(-1, -1, -1);
//	res = tmpPlayer.addCoorToShipInProcess(Coordinate(2, 1, 1), &output, AttackResult::Hit);
//	if (res != 4)
//	{
//		std::cout << "error in addCoorToShipsInProcess <2,1,1> - wasnt placed in the third place in attacek ships ";
//	}
//
//	for (auto i = 0; i < tmpPlayer.attackedShips.size(); i++) {
//		if (!compareShipsDetails(tmpPlayer.attackedShips.at(i), expectedTmp.attackedShips.at(i))) {
//			std::cout << "not equal ships !!! ";
//		}
//	}
//
//	PlayerSmart expectedTmp2;
//	expectedTempPlayer1_afterAddCoor2(expectedTmp2);
//	res = tmpPlayer.addCoorToShipInProcess(Coordinate(3, 1, 1), &output, AttackResult::Sink);
//	if (res != 4)
//	{
//		std::cout << "error in addCoorToShipsInProcess (3,1,1) ";
//	}
//	for (auto i = 0; i < tmpPlayer.attackedShips.size(); i++) {
//		if (!compareShipsDetails(tmpPlayer.attackedShips.at(i), expectedTmp2.attackedShips.at(i))) {
//			std::cout << "not equal ships !!! ";
//		}
//	}
//
//	PlayerSmart expectedTmp3;
//	expectedTempPlayer1_afterAddCoor3(expectedTmp3);
//	res = tmpPlayer.addCoorToShipInProcess(Coordinate(4, 6, 1), &output, AttackResult::Sink);
//	if (res != 0)
//	{
//		std::cout << "error in addCoorToShipsInProcess (4,6,1) ";
//	}
//	for (auto i = 0; i < tmpPlayer.attackedShips.size(); i++) {
//		if (!compareShipsDetails(tmpPlayer.attackedShips.at(i), expectedTmp3.attackedShips.at(i))) {
//			std::cout << "not equal ships !!! ";
//		}
//	}
//	if (!compareCoordinates(output, Coordinate(4, 7, 1))) {
//		std::cout << "bad next coor to look for " << std::endl;
//	}
//
//	//	"should be the same as before" << std::endl;
//	res = tmpPlayer.addCoorToShipInProcess(Coordinate(3, 8, 1), &output, AttackResult::Hit);
//	if (res != -1)
//	{
//		std::cout << "error in addCoorToShipInProcess(Coordinate(sInProcess  <3,8,1> as new" << std::endl;
//		return -1;
//	}
//	for (auto i = 0; i < tmpPlayer.attackedShips.size(); i++) {
//		if (!compareShipsDetails(tmpPlayer.attackedShips.at(i), expectedTmp3.attackedShips.at(i))) {
//			std::cout << "not equal ships !!! ";
//		}
//	}
//
//
//	PlayerSmart expectedTmp4;
//	expectedTempPlayer1_afterAddCoor4(expectedTmp4);
//	res = tmpPlayer.addCoorToShipInProcess(Coordinate(7, 2, 1), &output, AttackResult::Hit);
//	if (res != -1)
//	{
//		std::cout << "error in 7, 2, 1 addCoorToShipsInProcess ";
//		return -1;
//	}
//	for (auto i = 0; i < tmpPlayer.attackedShips.size(); i++) {
//		if (!compareShipsDetails(tmpPlayer.attackedShips.at(i), expectedTmp4.attackedShips.at(i))) {
//			std::cout << "not equal ships !!! ";
//		}
//	}
//
//	////dimentional///////////////////////////////////////////////////////////////////////////////////
//
//	PlayerSmart tmpPlayer2;
//	setTempPlayer2(tmpPlayer2);
//
//	Coordinate output2(-1, -1, -1);
//
//	res = tmpPlayer2.addCoorToShipInProcess(Coordinate(2, 2, 1), &output2, AttackResult::Hit);
//	if (res != 4)
//	{
//		std::cout << "error in addCoorToShipsInProcess <2,2,1> ";
//		return -1;
//	}
//
//	PlayerSmart tmpPlayer2_expected;
//	expectedTempPlayer2_afterAddCoor(tmpPlayer2_expected);
//	for (auto i = 0; i < tmpPlayer2.attackedShips.size(); i++) {
//		if (!compareShipsDetails(tmpPlayer2.attackedShips.at(i), tmpPlayer2_expected.attackedShips.at(i))) {
//			std::cout << "not equal ships 2 !!! " << std::endl;
//		}
//	}
//
//	if (!compareCoordinates(output2, Coordinate(2, 3, 1))) {
//		std::cout << "bad next coordinate !!! " << std::endl;
//	}
//
//	PlayerSmart tmpPlayer2_expected2;
//	expectedTempPlayer2_afterAddCoor2(tmpPlayer2_expected2);
//	res = tmpPlayer2.addCoorToShipInProcess(Coordinate(2, 4, 6), &output2, AttackResult::Sink);
//	if (res != 0)
//	{
//		std::cout << "error in addCoorToShipsInProcess (2,4,6) ";
//		return -1;
//	}
//
//	for (auto i = 0; i < tmpPlayer2.attackedShips.size(); i++) {
//		if (!compareShipsDetails(tmpPlayer2.attackedShips.at(i), tmpPlayer2_expected2.attackedShips.at(i))) {
//			std::cout << "not equal ships 2 !!! " << std::endl;
//		}
//	}
//
//	if (!compareCoordinates(output2, Coordinate(2, 4, 7))) {
//		std::cout << "bad next coordinate 2,4,7 !!! " << std::endl;
//	}
//
//
//	res = tmpPlayer2.addCoorToShipInProcess(Coordinate(2, 3, 8), &output2, AttackResult::Hit);
//	if (res != -1)
//	{
//		std::cout << "error in addCoorToShipsInProcess  <2,3,8>";
//		return -1;
//	}
//	// shouldnt change vector 
//	for (auto i = 0; i < tmpPlayer2.attackedShips.size(); i++) {
//		if (!compareShipsDetails(tmpPlayer2.attackedShips.at(i), tmpPlayer2_expected2.attackedShips.at(i))) {
//			std::cout << "not equal ships 2 !!! " << std::endl;
//		}
//	}
//	if (!compareCoordinates(output2, Coordinate(2, 4, 7))) {
//		std::cout << "bad next coordinate 2,4,7 !!! " << std::endl;
//	}
//
//	PlayerSmart tmpPlayer2_expected3;
//	expectedTempPlayer2_afterAddCoor3(tmpPlayer2_expected3);
//	res = tmpPlayer2.addCoorToShipInProcess(Coordinate(2, 7, 2), &output2, AttackResult::Sink);
//	if (res != -1)
//	{
//		std::cout << "error in addCoorToShipsInProcess (2,7,2) ";
//	}
//
//	for (auto i = 0; i < tmpPlayer2.attackedShips.size(); i++) {
//		if (!compareShipsDetails(tmpPlayer2.attackedShips.at(i), tmpPlayer2_expected3.attackedShips.at(i))) {
//			std::cout << "not equal ships 2 !!! " << std::endl;
//		}
//	}
//
//	if (!compareCoordinates(output2, Coordinate(2, 4, 7))) {
//		std::cout << "bad next coordinate 2,4,7 !!! " << std::endl;
//	}
//	std::cout << "Done addOnecoordinate" << std::endl;
//	return 0;
//}
//
//
//// create set of attack options + ships for tmplayer
//void testPlayerSmart::setTempPlayer1(PlayerSmart & tmpPlayer)
//{
//	tmpPlayer.boardRows = 10;
//	tmpPlayer.boardCols = 10;
//	tmpPlayer.boardDepth = 10;
//
//	std::vector<ShipInProcess> allShips;
//	// create ships
//	ShipInProcess sizeOne_1(1, 1, 1);
//	ShipInProcess sizeOne_2(3, 8, 1);
//	ShipInProcess sizeOne_3(9, 2, 1);
//
//	ShipInProcess sizeTwo_1(7, 8, 1);
//	sizeTwo_1.addCoordinate(8, 8, 1);
//
//	ShipInProcess sizeThree_1(4, 3, 1);
//	sizeThree_1.addCoordinate(4, 4, 1);
//	sizeThree_1.addCoordinate(4, 5, 1);
//
//	ShipInProcess sizeTwo_2(5, 8, 1);
//	sizeTwo_2.addCoordinate(5, 8, 2);
//
//	allShips.push_back(sizeThree_1);
//	allShips.push_back(sizeTwo_1);
//	allShips.push_back(sizeTwo_2);
//	allShips.push_back(sizeOne_3);
//	allShips.push_back(sizeOne_1);
//	allShips.push_back(sizeOne_2);
//	tmpPlayer.attackedShips = allShips;
//
//	//create Set of options
//	for (int i = 1; i < 11; i++)
//	{
//		for (int j = 1; j < 11; j++)
//		{
//			for (int k = 1; k < 11; k++) {
//				tmpPlayer.attackOptions.insert(Coordinate(i, j, k));
//
//			}
//		}
//	}
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(1, 1, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 8, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(9, 2, 1));
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 8, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 8, 1));
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 3, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 4, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 5, 1));
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 8, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 8, 2));
//
//	// clear envirnment
//	// ship of size 2 _1 
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 7, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 7, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 9, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 9, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 8, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 8, 2));
//
//	// ship of size 2 _2 
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 8, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 8, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(6, 8, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(6, 8, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 7, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 7, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 9, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 9, 2));
//
//	// ship of size 3 
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 3, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 5, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 4, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 3, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 5, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 4, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 3, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 5, 2));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 4, 2));
//
//}
//
//void testPlayerSmart::setTempPlayer2(PlayerSmart& tmpPlayer2) {
//	std::vector<ShipInProcess> allShips2;
//	tmpPlayer2.boardRows = 10;
//	tmpPlayer2.boardCols = 10;
//	tmpPlayer2.boardDepth = 10;
//	// create ships
//	ShipInProcess sizeOne_1(2, 1, 1);
//	ShipInProcess sizeOne_2(2, 3, 8);
//	ShipInProcess sizeOne_3(2, 9, 2);
//
//	ShipInProcess sizeTwo_1(2, 7, 8);
//	sizeTwo_1.addCoordinate(2, 8, 8);
//
//	ShipInProcess sizeThree_1(2, 4, 3);
//	sizeThree_1.addCoordinate(2, 4, 4);
//	sizeThree_1.addCoordinate(2, 4, 5);
//
//	ShipInProcess sizeTwo_2(2, 5, 8);
//	sizeTwo_2.addCoordinate(2, 4, 9);
//
//	allShips2.push_back(sizeThree_1);
//	allShips2.push_back(sizeTwo_1);
//	allShips2.push_back(sizeTwo_2);
//	allShips2.push_back(sizeOne_3);
//	allShips2.push_back(sizeOne_1);
//	allShips2.push_back(sizeOne_2);
//
//	tmpPlayer2.attackedShips = allShips2;
//
//	//create Set of options
//	for (int i = 1; i < 11; i++)
//	{
//		for (int j = 1; j < 11; j++)
//		{
//			for (int k = 1; k < 11; k++) {
//				tmpPlayer2.attackOptions.insert(Coordinate(i, j, k));
//
//			}
//		}
//	}
//	//
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 1, 1));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 3, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 9, 2));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 7, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 8, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 3));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 5));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 4));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 5, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 5, 9));
//
//	// clear envirnment
//	//sizeTwo_1
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 7, 7));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 8, 7));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 7, 9));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 8, 9));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 7, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 8, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 7, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 8, 8));
//
//	//sizeThree_1
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 3, 3));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 3, 5));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 3, 4));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 5, 3));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 5, 5));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 5, 4));
//
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 4, 3));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 4, 4));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 4, 5));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 4, 3));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 4, 4));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 4, 5));
//
//	//sizeTwo_2 
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 5, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(1, 5, 9));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 5, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(3, 5, 9));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 6, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 6, 9));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 8));
//	tmpPlayer2.delCoorAttackOptions(Coordinate(2, 4, 9));
//
//}
//
//int testPlayerSmart::testsizeOneAttack()
//{
//	PlayerSmart tmpPlayer;
//
//	for (int i = 1; i < 11; i++)
//	{
//		for (int j = 1; j < 11; j++)
//		{
//			for (int k = 1; k < 11; k++) {
//				tmpPlayer.attackOptions.insert(Coordinate(i, j, k));
//			}
//
//		}
//	}
//
//	// check all sides
//	Coordinate res(-1, -1, -1);
//	Coordinate target(2, 3, 3);
//	tmpPlayer.delCoorAttackOptions(target);
//	std::set<Coordinate> removedRes;
//	std::set<Coordinate> removedExp;
//
//
//	res = tmpPlayer.sizeOneAttack(target);
//	removedRes.insert(res);
//	tmpPlayer.delCoorAttackOptions(res);;
//	removedExp.insert(Coordinate(1, 3, 3));
//
//	res = tmpPlayer.sizeOneAttack(target);
//	removedRes.insert(res);
//	tmpPlayer.delCoorAttackOptions(res);;
//	removedExp.insert(Coordinate(3, 3, 3));
//
//	res = tmpPlayer.sizeOneAttack(target);
//	removedRes.insert(res);
//	tmpPlayer.delCoorAttackOptions(res);;
//	removedExp.insert(Coordinate(2, 2, 3));
//
//	res = tmpPlayer.sizeOneAttack(target);
//	removedRes.insert(res);
//	tmpPlayer.delCoorAttackOptions(res);;
//	removedExp.insert(Coordinate(2, 4, 3));
//
//	res = tmpPlayer.sizeOneAttack(target);
//	removedRes.insert(res);
//	tmpPlayer.delCoorAttackOptions(res);;
//	removedExp.insert(Coordinate(2, 3, 2));
//
//	res = tmpPlayer.sizeOneAttack(target);
//	removedRes.insert(res);
//	tmpPlayer.delCoorAttackOptions(res);;
//	removedExp.insert(Coordinate(2, 3, 4));
//
//	for (auto& coor : removedExp) {
//		if (removedRes.find(coor) == removedRes.end()) {
//			std::cout << "missing from removed res" << std::endl;;
//			printCoordinate(coor);
//		}
//	}
//
//	for (auto& coor : removedRes) {
//		if (removedExp.find(coor) == removedExp.end()) {
//			std::cout << "missing from removed exp" << std::endl;;
//			printCoordinate(coor);
//		}
//	}
//
//	//should return <-1, -1> none
//	res = tmpPlayer.sizeOneAttack(target);
//	if (!compareCoordinates(Coordinate(-1, -1, -1), res))
//	{
//		std::cout << "error -1,-1,-1" << std::endl;
//		return -1;
//	}
//
//
//
//	///////////////////////////////////////////////////////////////////////////////check rightest edge 
//	target = Coordinate(9, 10, 10);
//	tmpPlayer.attackOptions.erase(tmpPlayer.attackOptions.find(target));
//	target = Coordinate(10, 10, 10);
//
//	removedExp.clear();
//	removedRes.clear();
//
//	res = tmpPlayer.sizeOneAttack(target);
//	removedRes.insert(res);
//	tmpPlayer.delCoorAttackOptions(res);;
//	removedExp.insert(Coordinate(10, 9, 10));
//
//	res = tmpPlayer.sizeOneAttack(target);
//	removedRes.insert(res);
//	tmpPlayer.delCoorAttackOptions(res);;
//	removedExp.insert(Coordinate(10, 10, 9));
//
//	for (auto& coor : removedExp) {
//		if (removedRes.find(coor) == removedRes.end()) {
//			std::cout << "missing from removed res" << std::endl;;
//			printCoordinate(coor);
//		}
//	}
//
//	for (auto& coor : removedRes) {
//		if (removedExp.find(coor) == removedExp.end()) {
//			std::cout << "missing from removed exp" << std::endl;;
//			printCoordinate(coor);
//		}
//	}
//
//	//none left
//	res = tmpPlayer.sizeOneAttack(target);
//	if (!compareCoordinates(Coordinate(-1, -1, -1), res))
//	{
//		std::cout << "error -1,-1,-1" << std::endl;
//		return -1;
//	}
//
//
//	//// check the leftest 
//	//target = Coordinate(1, 1, 1);
//	//res = tmpPlayer.sizeOneAttack(target);
//	//if (!compareCoordinates(Coordinate(2, 1, 1), res))
//	//{
//	//	std::cout << "error 2,1, 1" << std::endl;
//	//	return -1;
//	//}
//	//tmpPlayer.delCoorAttackOptions(res);
//	std::cout << "Done testsizeOneAttack " << std::endl;
//	return 0;
//}
//
//int testPlayerSmart::testattack()
//{
//	PlayerSmart tmpPlayer;
//	//check the case that attack options is empty and imbalanced options is empty
//	Coordinate nextCoordinate = tmpPlayer.attack();
//	if (!compareCoordinates(nextCoordinate, Coordinate(-1, -1, -1))) {
//		std::cout << "error in case that both pool's are empty" << std::endl;
//	}
//
//	// in case that imbalanced not empty should pour the new options to attack options
//	tmpPlayer.imbalancedAttackOptions.insert(Coordinate(5, 5, 5));
//	nextCoordinate = tmpPlayer.attack();
//	if (!compareCoordinates(nextCoordinate, Coordinate(5, 5, 5))) {
//		std::cout << " error in the case attackoptions is empty but imbalanced isnt empty" << std::endl;
//	}
//	tmpPlayer.imbalancedAttackOptions.clear();
//
//	///////////////////////////////////////////////////
//	std::vector<ShipInProcess> allShips;
//	//create Set of options
//	for (int i = 1; i<11; i++)
//	{
//		for (int j = 1; j<11; j++)
//		{
//			for (int k = 1; k < 11; k++) {
//				tmpPlayer.attackOptions.insert(Coordinate(i, j, k));
//			}
//
//		}
//	}
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(1, 5, 1));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 5, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 6, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 6, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 2, 3));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 2, 5));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 2, 4));
//
//	// create ships
//	ShipInProcess sizeOne_1(1, 5, 1);
//	ShipInProcess sizeOne_2(3, 5, 8);
//
//	ShipInProcess sizeTwo_1(7, 6, 8);
//	sizeTwo_1.addCoordinate(8, 6, 8);
//
//	ShipInProcess sizeThree_1(4, 2, 3);
//	sizeThree_1.addCoordinate(4, 2, 4);
//	sizeThree_1.addCoordinate(4, 2, 5);
//
//	allShips.push_back(sizeThree_1);
//	allShips.push_back(sizeTwo_1);
//	allShips.push_back(sizeOne_1);
//	allShips.push_back(sizeOne_2);
//
//	// clear envirnment
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 6, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 6, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 6, 9));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 6, 9));
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 7, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 7, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 5, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 5, 8));
//	tmpPlayer.delCoorAttackOptions(Coordinate(7, 6, 7));
//	tmpPlayer.delCoorAttackOptions(Coordinate(8, 6, 7));
//
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 2, 3));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 2, 4));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 2, 5));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 2, 3));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 2, 3));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 1, 3));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 3, 3));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 2, 4));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 2, 4));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 1, 4));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 3, 4));
//	tmpPlayer.delCoorAttackOptions(Coordinate(3, 2, 5));
//	tmpPlayer.delCoorAttackOptions(Coordinate(5, 2, 5));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 1, 5));
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 3, 5));
//
//	tmpPlayer.attackedShips = allShips;
//	nextCoordinate = tmpPlayer.attack();
//
//	if (!compareCoordinates(Coordinate(4, 2, 2), nextCoordinate))
//	{
//		std::cout << "error <4,2,2> " << std::endl;
//		printCoordinate(nextCoordinate);
//		return -1;
//	}
//
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 2, 2));
//
//	nextCoordinate = tmpPlayer.attack();
//	if (!compareCoordinates(Coordinate(4, 2, 6), nextCoordinate))
//	{
//		std::cout << "error <4,2,6> " << std::endl;
//		return -1;
//	}
//	tmpPlayer.delCoorAttackOptions(Coordinate(4, 2, 6));
//	tmpPlayer.attackedShips.erase(tmpPlayer.attackedShips.begin(), tmpPlayer.attackedShips.end());
//
//	// in case there are no ships in process return random element 
//	nextCoordinate = tmpPlayer.attack();
//	if (!tmpPlayer.isInAttackOptions(nextCoordinate))
//	{
//		std::cout << "last " << std::endl;
//		return -1;
//	}
//
//	std::cout << "Done testAttack" << std::endl;
//	return 0;
//}
//
//bool testPlayerSmart::compareCoordinates(Coordinate coor1, Coordinate coor2)
//
//{
//	return (coor1.col == coor2.col && coor1.row == coor2.row && coor1.depth == coor2.depth);
//}
//
//
//int testPlayerSmart::testremoveAllIrreleventCoordinates()
//{
//	PlayerSmart originPlayer;
//
//	for (int i = 1; i < 11; i++) {
//		for (int j = 1; j < 11; j++) {
//			for (int k = 1; k < 11; k++) {
//				originPlayer.attackOptions.insert(Coordinate(i, j, k));
//			}
//		}
//	}
//
//	PlayerSmart expectedPlayer;
//	for (int i = 1; i < 11; i++) {
//		for (int j = 1; j < 11; j++) {
//			for (int k = 1; k < 11; k++) {
//				expectedPlayer.attackOptions.insert(Coordinate(i, j, k));
//			}
//		}
//	}
//
//
//	//case of in edge(shuold remove only one side) vertical
//	originPlayer.removePermanentlyConstDirections(Coordinate(1, 1, 1), true, false, false);
//	expectedPlayer.delCoorAttackOptions(Coordinate(1, 2, 1));
//	expectedPlayer.delCoorAttackOptions(Coordinate(1, 1, 2));
//
//	for (auto& coor : originPlayer.attackOptions) {
//		if (!expectedPlayer.isInAttackOptions(coor)) {
//			std::cout << "redundent coor in attackoptions 1,1,1: ";
//			printCoordinate(coor);
//		}
//	}
//	for (auto& coor : expectedPlayer.attackOptions) {
//		if (!originPlayer.isInAttackOptions(coor)) {
//			std::cout << "missing coor in attackoptions 1,1,1: ";
//			printCoordinate(coor);
//		}
//	}
//
//
//	//case of in edge(shuold remove only one side) horizontal
//	originPlayer.removePermanentlyConstDirections(Coordinate(10, 10, 10), false, true, false);
//	expectedPlayer.delCoorAttackOptions(Coordinate(9, 10, 10));
//	expectedPlayer.delCoorAttackOptions(Coordinate(10, 10, 9));
//	for (auto& coor : originPlayer.attackOptions) {
//		if (!expectedPlayer.isInAttackOptions(coor)) {
//			std::cout << "redundent coor in attackoptions 10,10,10: ";
//			printCoordinate(coor);
//		}
//	}
//	for (auto& coor : expectedPlayer.attackOptions) {
//		if (!originPlayer.isInAttackOptions(coor)) {
//			std::cout << "missing coor in attackoptions 10,10,10: ";
//			printCoordinate(coor);
//		}
//	}
//
//	//case of in middle(shuold remove two side) vertical
//	originPlayer.removePermanentlyConstDirections(Coordinate(3, 3, 3), true, false, false);
//	expectedPlayer.delCoorAttackOptions(Coordinate(3, 2, 3));
//	expectedPlayer.delCoorAttackOptions(Coordinate(3, 4, 3));
//	expectedPlayer.delCoorAttackOptions(Coordinate(3, 3, 2));
//	expectedPlayer.delCoorAttackOptions(Coordinate(3, 3, 4));
//	for (auto& coor : originPlayer.attackOptions) {
//		if (!expectedPlayer.isInAttackOptions(coor)) {
//			std::cout << "redundent coor in attackoptions 3,3,3: ";
//			printCoordinate(coor);
//		}
//	}
//	for (auto& coor : expectedPlayer.attackOptions) {
//		if (!originPlayer.isInAttackOptions(coor)) {
//			std::cout << "missing coor in attackoptions 3,3,3: ";
//			printCoordinate(coor);
//		}
//	}
//
//
//	//case of in middle(shuold remove two side) horizontal
//	originPlayer.removePermanentlyConstDirections(Coordinate(6, 6, 6), false, true, false);
//	expectedPlayer.delCoorAttackOptions(Coordinate(5, 6, 6));
//	expectedPlayer.delCoorAttackOptions(Coordinate(7, 6, 6));
//	expectedPlayer.delCoorAttackOptions(Coordinate(6, 6, 5));
//	expectedPlayer.delCoorAttackOptions(Coordinate(6, 6, 7));
//	for (auto& coor : originPlayer.attackOptions) {
//		if (!expectedPlayer.isInAttackOptions(coor)) {
//			std::cout << "redundent coor in attackoptions 6,6,6: ";
//			printCoordinate(coor);
//		}
//	}
//	for (auto& coor : expectedPlayer.attackOptions) {
//		if (!originPlayer.isInAttackOptions(coor)) {
//			std::cout << "missing coor in attackoptions 6,6,6: ";
//			printCoordinate(coor);
//		}
//	}
//
//	//case of in middle(shuold remove two side) dimentional
//	originPlayer.removePermanentlyConstDirections(Coordinate(6, 6, 6), false, false, true);
//	expectedPlayer.delCoorAttackOptions(Coordinate(5, 6, 6));
//	expectedPlayer.delCoorAttackOptions(Coordinate(7, 6, 6));
//	expectedPlayer.delCoorAttackOptions(Coordinate(6, 5, 6));
//	expectedPlayer.delCoorAttackOptions(Coordinate(6, 7, 6));
//
//	for (auto& coor : originPlayer.attackOptions) {
//		if (!expectedPlayer.isInAttackOptions(coor)) {
//			std::cout << "dim redundent coor in attackoptions 6,6,6: ";
//			printCoordinate(coor);
//		}
//	}
//	for (auto& coor : expectedPlayer.attackOptions) {
//		if (!originPlayer.isInAttackOptions(coor)) {
//			std::cout << "dim missing coor in attackoptions 6,6,6: ";
//			printCoordinate(coor);
//		}
//	}
//
//	std::cout << "Done testremoveFourIrreleventCoordinates " << std::endl;
//	return 0;
//
//}