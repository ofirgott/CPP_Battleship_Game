//#pragma once
//#include"PlayerSmart.h"
//#include  <iostream>
//
//
//class testPlayerSmart {
//public:
//	testPlayerSmart() {};
//	~testPlayerSmart() {};
//
//	static int testfindPairInAttackedShips();
//	static int testremoveOneCoordinate();
//	static int testisInAttackOptions();
//
//
//	// print & compare functions 
//	static void printCoordinate(const Coordinate& coord);
//	static bool compareCoordinates(Coordinate coor1, Coordinate coor2);
//	static bool compareShipsDetails(ShipInProcess & ship1, ShipInProcess & ship2);
//	static bool compareVector(std::vector<int> firstVec, std::vector<int> secVec);
//
//	// players
//	static void setTempPlayer1(PlayerSmart& tmpPlayer);
//	static void setTempPlayer2(PlayerSmart & tmpPlayer2);
//	// player 3 variations 
//	static void setTempPlayer3(PlayerSmart& tmpPlayer);
//	static void player3testMerge1(PlayerSmart & tmpplayer);
//	static void player3testMerge2(PlayerSmart & tmpPlayer);
//
//	//tests
//	static int testmergeShipDetails();
//
//
//	static void testpourImbalancedToAttackOptions();
//	static void testupdateShipsCount();
//
//
//	static 	void testgetMinShipSize();
//
//
//	//static void testclearFourAdjecentCoors(Coordinate attackedCoordinate,AttackResult res, int minIncCoor, int maxInCoor, bool isVertical, bool isHorizontal);
//
//	static void testCheck6Util1();
//
//	static void testcheck6Util2();
//
//	static void testCheck6Util3();
//
//	static void testcheckSixDirections();
//
//	static void testtransferCoordinatesToSecondPoll();
//
//	static void testcountDistance();
//
//	static int testremoveAllIrreleventCoordinates();
//	//done
//
//	//done
//	static int testremoveSankFromReleventCoors();
//	//done
//	static int testnotifyOnAttackResult();
//	static std::vector<Coordinate> shouldBeRemoved(Coordinate & dead, int boardSize, std::set<Coordinate> allDead);
//	static std::vector<Coordinate> findSurronding(const Coordinate & target);
//	static void expectedTempPlayer1_afterAddCoor(PlayerSmart & tmpPlayer);
//	static void expectedTempPlayer1_afterAddCoor2(PlayerSmart & tmpPlayer);
//	static void expectedTempPlayer1_afterAddCoor3(PlayerSmart & tmpPlayer);
//	static void expectedTempPlayer1_afterAddCoor4(PlayerSmart & tmpPlayer);
//	static void expectedTempPlayer2_afterAddCoor(PlayerSmart & tmpPlayer2);
//	static void expectedTempPlayer2_afterAddCoor2(PlayerSmart & tmpPlayer2);
//	static void expectedTempPlayer2_afterAddCoor3(PlayerSmart & tmpPlayer2);
//	static int testaddCoorToShipsInProcess();
//
//	//done
//	static int testnextAttackFromCoors();
//	//done
//
//	//
//	static int testsizeOneAttack();
//
//	//
//	static int testattack();
//
//	//	static int testsetBoard();
//
//};