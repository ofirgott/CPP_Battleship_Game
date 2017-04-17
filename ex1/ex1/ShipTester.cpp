//#pragma once
//#include "Ship.h"
//#include "Player.h"
//#include <utility> //  std::pair
//#include <set> // std::set
//
//
//// create details of goodBoard0
//std::set<std::pair<char, std::set<std::pair<int, int>>>> createGoodSetZeroPlayerA() {
//
//	std::set<std::pair<char, std::set<std::pair<int, int>>>> ships;
//
//	// insert <B, {(1,4)}>
//	std::set<std::pair<int, int>> set1;
//	set1.insert(std::make_pair(4, 1));
//	ships.insert(std::make_pair('B', set1));
//
//	// insert <P, {(2,8),(2,9)}>
//	std::set<std::pair<int, int>> set2;
//	set2.insert(std::make_pair(2, 8));
//	set2.insert(std::make_pair(2,9));
//	ships.insert(std::make_pair('P', set2));
//
//	set1.clear();
//	set2.clear();
//
//	// insert <B, {(9,1)}>
//	set1.insert(std::make_pair(9, 1));
//	ships.insert(std::make_pair('B', set1));
//
//	// insert <P, {(10,9),(10,10)}>
//	set2.insert(std::make_pair(10, 10));
//	set2.insert(std::make_pair(10, 9));
//	ships.insert(std::make_pair('P', set2));
//
//	// insert <M, {(4,6),(4,7),(4,8)}>
//	std::set<std::pair<int, int>> set3;
//	set3.insert(std::make_pair(4, 8));
//	set3.insert(std::make_pair(4, 7));
//	set3.insert(std::make_pair(4, 6));
//	ships.insert(std::make_pair('M', set3));
//
//	set1.clear();
//	set2.clear();
//	set3.clear();
//
//	return ships;
//
//}
//
//std::set<std::pair<char, std::set<std::pair<int, int>>>> createGoodSetZeroPlayerB() {
//
//	std::set<std::pair<char, std::set<std::pair<int, int>>>> ships;
//
//	// insert <b, {(6,10)}>
//	std::set<std::pair<int, int>> set1;
//	set1.insert(std::make_pair(6, 10));
//	ships.insert(std::make_pair('b', set1));
//
//	// insert <p, {(2,2),(3,2)}>
//	std::set<std::pair<int, int>> set2;
//	set2.insert(std::make_pair(2, 2));
//	set2.insert(std::make_pair(3, 2));
//	ships.insert(std::make_pair('p', set2));
//
//	set1.clear();
//	set2.clear();
//
//	// insert <b, {(10,4)}>
//	set1.insert(std::make_pair(10, 4));
//	ships.insert(std::make_pair('b', set1));
//
//	// insert <d, {(5,3), (6,3) , (7,3), (8,3)}>
//	set2.insert(std::make_pair(5, 3));
//	set2.insert(std::make_pair(6, 3));
//	set2.insert(std::make_pair(7, 3));
//	set2.insert(std::make_pair(8, 3));
//	ships.insert(std::make_pair('d', set2));
//
//
//	// insert <m, {(5,1),(6,1),(7,1)}>
//	std::set<std::pair<int, int>> set3;
//	set3.insert(std::make_pair(5, 1));
//	set3.insert(std::make_pair(6, 1));
//	set3.insert(std::make_pair(7, 1));
//	ships.insert(std::make_pair('m', set3));
//
//	set1.clear();
//	set2.clear();
//	set3.clear();
//
//	return ships;
//
//}
//
//void testIsValidShipDetail() {
//
//	// 4 coordinates ships
//	// insert <d, {(5,3), (6,3) , (7,3), (8,3)}>
//	std::set<std::pair<int, int>> set2;
//	set2.insert(std::make_pair(5, 3));
//	set2.insert(std::make_pair(6, 3));
//	set2.insert(std::make_pair(7, 3));
//	set2.insert(std::make_pair(8, 3));
//
//	if (!Ship::isValidShipDetails(std::make_pair('d', set2))) {
//		printf("invalid return value for ship1\n");
//	}
//
//	set2.clear();
//
//	set2.insert(std::make_pair(3,5));
//	set2.insert(std::make_pair(3,6));
//	set2.insert(std::make_pair(3,7));
//	set2.insert(std::make_pair(3,8));
//
//	if (!Ship::isValidShipDetails(std::make_pair('D', set2))) {
//		printf("invalid return value for ship2\n");
//	}
//
//	// insert <D, {(5,3), (6,3) , (7,3)}>
//	set2.insert(std::make_pair(5, 3));
//	set2.insert(std::make_pair(6, 3));
//	set2.insert(std::make_pair(7, 3));
//
//	if (Ship::isValidShipDetails(std::make_pair('D', set2))) {
//		printf("invalid return value for ship3\n");
//	}
//
//	set2.clear();
//
//	// insert <d, {(5,3), (6,3) , (7,3), (8,3) , (9,3)}>
//	set2.insert(std::make_pair(5, 3));
//	set2.insert(std::make_pair(6, 3));
//	set2.insert(std::make_pair(7, 3));
//	set2.insert(std::make_pair(8, 3));
//	set2.insert(std::make_pair(9, 3));
//
//	if (Ship::isValidShipDetails(std::make_pair('d', set2))) {
//		printf("invalid return value for ship4\n");
//	}
//
//	set2.clear();
//
//	// insert <d, {(5,3), (6,3) , (7,3), (8,3) , (9,3)}>
//	set2.insert(std::make_pair(5, 3));
//	set2.insert(std::make_pair(6, 3));
//	set2.insert(std::make_pair(7, 3));
//	set2.insert(std::make_pair(8, 3));
//	set2.insert(std::make_pair(9, 3));
//	set2.insert(std::make_pair(5, 4));
//	set2.insert(std::make_pair(5, 5));
//	set2.insert(std::make_pair(5, 6));
//	set2.insert(std::make_pair(5, 7));
//	set2.insert(std::make_pair(5, 8));
//
//	if (Ship::isValidShipDetails(std::make_pair('d', set2))) {
//		printf("invalid return value for ship5\n");
//	}
//	set2.clear();
//
//	// insert <c, {(5,3), (6,3) , (7,3), (8,3)}>
//	set2.insert(std::make_pair(5, 3));
//	set2.insert(std::make_pair(6, 3));
//	set2.insert(std::make_pair(7, 3));
//	set2.insert(std::make_pair(8, 3));
//
//	if (Ship::isValidShipDetails(std::make_pair('c', set2))) {
//		printf("invalid return value for ship6\n");
//	}
//
//	set2.clear();
//
//	// insert <d, {(5,3) }>
//	set2.insert(std::make_pair(5, 3));
//
//	if (Ship::isValidShipDetails(std::make_pair('d', set2))) {
//		printf("invalid return value for ship7\n");
//	}
//
//	set2.clear();
//
//	set2.insert(std::make_pair(5, 3));
//	set2.insert(std::make_pair(6, 3));
//	set2.insert(std::make_pair(7, 3));
//	set2.insert(std::make_pair(8, 3));
//	set2.insert(std::make_pair(5, 4));
//	set2.insert(std::make_pair(6, 4));
//	set2.insert(std::make_pair(7, 4));
//	set2.insert(std::make_pair(8, 4));
//	if (Ship::isValidShipDetails(std::make_pair('d', set2))) {
//		printf("invalid return value for ship8\n");
//
//	}
//
//	set2.clear();
//
//	// 3 coordinates ships
//
//	// insert <m, {(5,1),(6,1),(7,1)}>
//	std::set<std::pair<int, int>> set3;
//	set3.insert(std::make_pair(5, 1));
//	set3.insert(std::make_pair(6, 1));
//	set3.insert(std::make_pair(7, 1));
//	if (!Ship::isValidShipDetails(std::make_pair('M', set3))) {
//		printf("invalid return value for ship9\n");
//
//	}
//	set3.clear();
//
//	//
//
//	set3.insert(std::make_pair(1,5));
//	set3.insert(std::make_pair(1,6));
//	set3.insert(std::make_pair(1,7));
//	if (!Ship::isValidShipDetails(std::make_pair('m', set3))) {
//		printf("invalid return value for ship10\n");
//
//	}
//	set3.clear();
//
//	// insert <m, {(5,1),(6,1),(7,1)}>
//
//	set3.insert(std::make_pair(5, 1));
//	set3.insert(std::make_pair(6, 1));
//	set3.insert(std::make_pair(7, 1));
//	set3.insert(std::make_pair(5, 2));
//	set3.insert(std::make_pair(6, 2));
//	set3.insert(std::make_pair(7, 2));
//	if (Ship::isValidShipDetails(std::make_pair('M', set3))) {
//		printf("invalid return value for ship11\n");
//
//	}
//	set3.clear();
//
//
//	set3.insert(std::make_pair(1, 2));
//	set3.insert(std::make_pair(1, 6));
//	set3.insert(std::make_pair(1, 7));
//	if (Ship::isValidShipDetails(std::make_pair('m', set3))) {
//		printf("invalid return value for ship12\n");
//
//	}
//	set3.clear();
//
//	set3.insert(std::make_pair(1, 5));
//	set3.insert(std::make_pair(1, 6));
//	set3.insert(std::make_pair(1, 7));
//	set3.insert(std::make_pair(2, 6));
//	set3.insert(std::make_pair(3, 6));
//	set3.insert(std::make_pair(4, 6));
//
//
//	if (Ship::isValidShipDetails(std::make_pair('m', set3))) {
//		printf("invalid return value for ship13\n");
//
//	}
//	set3.clear();
//
//	set3.insert(std::make_pair(1, 5));
//	set3.insert(std::make_pair(1, 6));
//	set3.insert(std::make_pair(1, 7));
//	set3.insert(std::make_pair(2, 6));
//	set3.insert(std::make_pair(3, 5));
//	set3.insert(std::make_pair(4, 6));
//
//
//	if (Ship::isValidShipDetails(std::make_pair('M', set3))) {
//		printf("invalid return value for ship14\n");
//
//	}
//	set3.clear();
//
//	set3.insert(std::make_pair(1, 5));
//	set3.insert(std::make_pair(1, 6));
//	set3.insert(std::make_pair(1, 7));
//	set3.insert(std::make_pair(2, 6));
//	set3.insert(std::make_pair(2, 7));
//	if (Ship::isValidShipDetails(std::make_pair('m', set3))) {
//		printf("invalid return value for ship15\n");
//
//	}
//	set3.clear();
//
//	// ship of size 2 
//
//
//	set3.insert(std::make_pair(1, 5));
//	set3.insert(std::make_pair(1, 6));
//	if (!Ship::isValidShipDetails(std::make_pair('P', set3))) {
//		printf("invalid return value for ship16\n");
//
//	}
//	set3.clear();
//
//	set3.insert(std::make_pair(5,1));
//	set3.insert(std::make_pair(6,1));
//	if (!Ship::isValidShipDetails(std::make_pair('p', set3))) {
//		printf("invalid return value for ship17\n");
//
//	}
//	set3.clear();
//
//	set3.insert(std::make_pair(5, 1));
//	set3.insert(std::make_pair(6, 3));
//	if (Ship::isValidShipDetails(std::make_pair('p', set3))) {
//		printf("invalid return value for ship18\n");
//
//	}
//	set3.clear();
//
//	set3.insert(std::make_pair(5, 1));
//	set3.insert(std::make_pair(7, 3));
//	if (Ship::isValidShipDetails(std::make_pair('p', set3))) {
//		printf("invalid return value for ship19\n");
//
//	}
//	set3.clear();
//
//	set3.insert(std::make_pair(1, 5));
//	set3.insert(std::make_pair(1, 6));
//	set3.insert(std::make_pair(2, 5));
//	set3.insert(std::make_pair(2, 6));
//	if (Ship::isValidShipDetails(std::make_pair('p', set3))) {
//		printf("invalid return value for ship20\n");
//
//	}
//	set3.clear();
//
//	set3.insert(std::make_pair(4, 5));
//	set3.insert(std::make_pair(1, 6));
//	if (Ship::isValidShipDetails(std::make_pair('p', set3))) {
//		printf("invalid return value for ship21\n");
//
//	}
//	set3.clear();
//
//	set3.insert(std::make_pair(5, 5));
//	set3.insert(std::make_pair(6, 6));
//	if (Ship::isValidShipDetails(std::make_pair('P', set3))) {
//		printf("invalid return value for ship22\n");
//
//	}
//	set3.clear();
//
//	set3.insert(std::make_pair(4, 5));
//	set3.insert(std::make_pair(4, 6));
//	set3.insert(std::make_pair(5, 5));
//	set3.insert(std::make_pair(6, 5));
//	if (Ship::isValidShipDetails(std::make_pair('P', set3))) {
//		printf("invalid return value for ship23\n");
//
//	}
//	set3.clear();
//
//	// 1 coor ship
//	set3.insert(std::make_pair(4, 5));
//	if (!Ship::isValidShipDetails(std::make_pair('b', set3))) {
//		printf("invalid return value for ship24\n");
//
//	}
//	set3.clear();
//
//	set3.insert(std::make_pair(5, 5));
//	if (!Ship::isValidShipDetails(std::make_pair('B', set3))) {
//		printf("invalid return value for ship25\n");
//
//	}
//	set3.clear();
//
//	set3.insert(std::make_pair(5, 5));
//	set3.insert(std::make_pair(5, 6));
//	if (Ship::isValidShipDetails(std::make_pair('b', set3))) {
//		printf("invalid return value for ship26\n");
//
//	}
//	set3.clear();
//	printf("isValidShip is ok\n");
//	return;
//}
//
//void testCreateBattleshipSet() {
//	std::set<std::pair<char, std::set<std::pair<int, int>>>> shipsDetailsSet = createGoodSetZeroPlayerB();
//	std::set<Ship*> setOfBattleships = Ship::createShipSet(shipsDetailsSet);
//
//	for (auto& ship : setOfBattleships) {
//		printf("not hit = %d\n",ship->getNotHit());
//		printf("points = %d\n", ship->getPoints());
//		printf("len = %d\n", ship->getLength());
//		printf("symbol = %c\n", ship->getSymbol());
//		printf("alive: %s\n", (ship->isAlive() ? true : "true", "false"));
//		ship->printBody();
//		printf("///////\n");
//	}
//
//	for (auto& det : shipsDetailsSet) {
//		printf("symbol = %c\n", det.first);
//		for (auto& coor : det.second) {
//			printf("row = %d, col = %d\n", coor.first, coor.second);
//		}
//		printf("///////\n");
//	}
//
//}
//
//void testCreateBattleshipMatrix() {
//	std::set<std::pair<char, std::set<std::pair<int, int>>>> shipsDetailsSet = createGoodSetZeroPlayerB();
//	std::set<Ship*> setOfBattleships = Ship::createShipSet(shipsDetailsSet);
//	Ship *** matrix = Ship::createShipMatrix(setOfBattleships);
//	
//
//	for (int i = 0; i < 10; i++) {
//		for (int j = 0; j < 10; j++) {
//			if (matrix[i][j] != nullptr) {
//				printf("%c ", matrix[i][j]->getSymbol());
//			}
//			else {
//				printf("%d ", 0);
//			}
//		}
//		printf("\n");
//	}
//}
//
//void testUpdateAttack() {
//
//	// 4 coordinates ships
//	// insert <d, {(5,3), (6,3) , (7,3), (8,3)}>
//	std::set<std::pair<int, int>> set2;
//	set2.insert(std::make_pair(5, 3));
//	set2.insert(std::make_pair(6, 3));
//	set2.insert(std::make_pair(7, 3));
//	set2.insert(std::make_pair(8, 3));
//
//	Ship ship = Ship::Ship(std::make_pair('d', set2));
//	printf("shipSymbol= %c\n", ship.getSymbol());
//	printf("not hit = %d\n", ship.getNotHit());
//	printf("points = %d\n", ship.getPoints());
//	printf("len = %d\n", ship.getLength());
//	if (ship.isAlive()) {
//		printf("alive = true\n");
//	}
//	else {
//		printf("alive = false\n");
//	}
//	printf("shipsBody:\n");
//	ship.printBody();
//	printf("\n");
//
//	printf("attckREsult: = %d\n", ship.updateAttack(1, 1));
//
//	//print ship again 
//	printf("shipSymbol= %c\n", ship.getSymbol());
//	printf("not hit = %d\n", ship.getNotHit());
//	printf("points = %d\n", ship.getPoints());
//	printf("len = %d\n", ship.getLength());
//	if (ship.isAlive()) {
//		printf("alive = true\n");
//	}
//	else {
//		printf("alive = false\n");
//	}
//	printf("shipsBody:\n");
//	ship.printBody();
//	printf("\n");
//
//	printf("attckREsult2: = %d\n", ship.updateAttack(5, 3));
//	//print ship again 
//	printf("shipSymbol= %c\n", ship.getSymbol());
//	printf("not hit = %d\n", ship.getNotHit());
//	printf("points = %d\n", ship.getPoints());
//	printf("len = %d\n", ship.getLength());
//	if (ship.isAlive()) {
//		printf("alive = true\n");
//	}
//	else {
//		printf("alive = false\n");
//	}
//	printf("shipsBody:\n");
//	ship.printBody();
//	printf("\n");
//
//	printf("attckREsult2: = %d\n", ship.updateAttack(5, 3));
//	//print ship again 
//	printf("shipSymbol= %c\n", ship.getSymbol());
//	printf("not hit = %d\n", ship.getNotHit());
//	printf("points = %d\n", ship.getPoints());
//	printf("len = %d\n", ship.getLength());
//	if (ship.isAlive()) {
//		printf("alive = true\n");
//	}
//	else {
//		printf("alive = false\n");
//	}
//	printf("shipsBody:\n");
//	ship.printBody();
//	printf("\n");
//
//	printf("attckREsult2: = %d\n", ship.updateAttack(6, 3));
//	printf("attckREsult2: = %d\n", ship.updateAttack(7, 3));
//	printf("attckREsult2: = %d\n", ship.updateAttack(8, 3));
//
//	//print ship again 
//	printf("shipSymbol= %c\n", ship.getSymbol());
//	printf("not hit = %d\n", ship.getNotHit());
//	printf("points = %d\n", ship.getPoints());
//	printf("len = %d\n", ship.getLength());
//	if (ship.isAlive()) {
//		printf("alive = true\n");
//	}
//	else {
//		printf("alive = false\n");
//	}
//	printf("shipsBody:\n");
//	ship.printBody();
//	printf("\n");
//
//	return;
//}
//
//
//
//int main() {
//
//	testIsValidShipDetail();
//	testCreateBattleshipSet();
//	testCreateBattleshipMatrix();
//	testUpdateAttack();
//	system("pause");
//	return 0;
//}
