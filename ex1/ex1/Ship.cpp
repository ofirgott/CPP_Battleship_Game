#include "Ship.h"
#include <ctype.h>



//Battleship::Battleship(char letter, std::set<std::pair<int, int>> coordinates)

Ship::Ship(const std::pair<char, std::set<std::pair<int, int>>>& input)
{
	symbol = toupper(input.first);

	if (symbol == 'B') {
		setFields(1, 2, input.second);
	}
	else if (symbol == 'P') {
		setFields(2, 3, input.second);
	}
	else if (symbol == 'M') {
		setFields(3, 7, input.second);
	}
	else if (symbol == 'D') {
		setFields(4, 8, input.second);
	}
	else
	{ // shouldnt get here !!!! 
		setFields(-1, -1, input.second);
	}
}

//Battleship & Battleship::operator=(const Battleship & ship)
//{
//if (this != &ship) {
//	delete &ship.body; // make sure there is no memory leaks here
// get the new string
//	this->body .insert (&ship.body.begin(), &ship.body.end()) ; // make sure it really copies the map 
//	this->symbol = ship.symbol;
//	this->len = ship.len;
//	this->points = ship.points;
//	this->notHit = ship.notHit;
//	}
//	return *this;
//}

//Battleship::Battleship(const Battleship & ship)
//{
//	if (this != &ship) {
//	delete &ship.body; // make sure there is no memory leaks here
// get the new string
//	this->body.insert(&ship.body.begin(), &ship.body.end()); // make sure it really copies the map 
//this->symbol = ship.symbol;
//this->len = ship.len;
//this->points = ship.points;
//this->notHit = ship.notHit;
//}
//}


Ship::~Ship()
{
	body.clear(); // ??? 
}

int Ship::getPoints()
{
	return points;
}

int Ship::getNotHit()
{
	return notHit;
}

bool Ship::isAlive()
{
	if (notHit > 0) {
		return true;
	}
	return false;
}



bool Ship::isValidShipLen(char id, int setSize)
{
	char letter = toupper(id);
	if (letter == 'B') {
		if (setSize != 1) {
			return false;
		}
	}
	else if (letter == 'P') {
		if (setSize != 2) {
			return false;
		}
	}
	else if (letter == 'M') {
		if (setSize != 3) {
			return false;
		}
	}
	else if (letter == 'D') {
		if (setSize != 4) {
			return false;
		}
	}
	else { // shouldnt get here !!!! 
		return false;
	}

	return true;
}


bool Ship::isValidShipCoordinates(const std::set<std::pair<int, int>>& coordinates)
{
	int shipSize = (int)size(coordinates);

	std::vector<int> rows;
	std::vector<int> cols;

	// ship must contain at least 1 coordinate to exist
	if (shipSize< 1) {
		return false;
	}

	// extract all rows && columns coordinates
	for (auto& coor : coordinates) {
		rows.push_back(coor.first);
		cols.push_back(coor.second);
	}

	// sort the vecors
	std::sort(rows.begin(), rows.end());
	std::sort(cols.begin(), cols.end());

	//check if ship is Horizontal
	if (isConstantCoors(rows, shipSize)) {
		if (isIncrementalCoors(cols, shipSize)) {
			return true;
		}
	}

	//check if ship is vertical
	if (isConstantCoors(cols, shipSize)) {
		if (isIncrementalCoors(rows, shipSize)) {
			return true;
		}
	}

	return false;
}



int Ship::updateAttack(int row, int col)
{
	for (auto& coor : body) {
		// if the coordinates attackd belong to me 
		if ((coor.first.first == row) && (coor.first.second == col)) {

			if (coor.second == 0) { // no hit yet
				coor.second = 1; // update body
				notHit -= 1;
				return 0; // succesful attack
			}

			else { // my coordinates but already hit before
				return 1;
			}
		}
	}
	return -1; // not my coordinates
}


bool Ship::isValidShipDetails(std::pair<char, std::set<std::pair<int, int>>> input)
{
	if (!isValidShipLen(input.first, (int)size(input.second))) {
		return false;
	}
	if (!isValidShipCoordinates(input.second)) {
		return false;
	}
	return true;
}


void Ship::setFields(int length, int sPoints, std::set<std::pair<int, int>> coordinates)
{
	len = length;
	points = sPoints;
	notHit = length;
	// make sure a copy created and inserted to the map !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	for (auto coor : coordinates) {
		body.insert(std::make_pair(coor, 0));
	}
}

bool Ship::isConstantCoors(const std::vector<int>& coors, int size)
{
	int firstCoor;
	if (size < 1) {
		return false; // shouldnt get here!!!
	}

	firstCoor = coors[0];
	for (int i = 1; i < size; i++) {
		if (coors[i] != firstCoor) {
			return false;
		}
	}
	return true;
}

bool Ship::isIncrementalCoors(const std::vector<int>& coors, int size)
{
	int prevCoor;
	if (size < 1) {
		return false; // shouldnt get here!!!
	}

	prevCoor = coors[0];
	for (int i = 1; i < size; i++) {
		if (coors[i] != (prevCoor + 1)) {
			return false;
		}
		prevCoor += 1;
	}
	return true;
}

std::set<Ship*> Ship::createShipSet(const std::set<std::pair<char, std::set<std::pair<int, int>>>>& allPairs) // !!!!!!!!!!!!!!!!!!!!!!!!!!!
{
	std::set<Ship*> allBattleships; // might be a problem with the address of allBattleships!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	for (auto& elem : allPairs) {
		Ship* shipPtr = new Ship(elem);
		allBattleships.insert(shipPtr);
	}
	return allBattleships;
}

/*
std::set<Ship> Ship::createShipSet(const std::set<std::pair<char, std::set<std::pair<int, int>>>>& allPairs) // !!!!!!!!!!!!!!!!!!!!!!!!!!!
{
std::set<Ship> allBattleships; // might be a problem with the address of allBattleships!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

for (auto& elem : allPairs) {
Ship shipPtr = Ship(elem);
allBattleships.insert(shipPtr);
}
return allBattleships;
}
*/

Ship *** Ship::createShipMatrix(std::set <Ship*> allShips)
{

	Ship *** matrix = new Ship**[NROWS];

	// init matrix pointers no NULL
	for (int i = 0; i < NROWS; i++) {
		matrix[i] = new Ship*[NCOLS];
		for (int j = 0; j < NCOLS; j++) {
			matrix[i][j] = nullptr;
		}
	}

	// for each ship in the set. go overall its coordinates and put a pointer in the matrix
	for (auto shipPtr : allShips) {
		for (auto& part : shipPtr->body) {
			matrix[part.first.first][part.first.second] = shipPtr;
		}
	}

	return matrix;
}



/*
Ship *** Ship::createShipMatrix(std::set <Ship> allShips)
{

Ship *** matrix = new Ship** [NROWS] ;

// init matrix pointers no NULL
for (int i = 0; i < NROWS; i++) {
matrix[i] = new Ship*[NCOLS];
for (int j = 0; j < NCOLS; j++) {
matrix[i][j] = nullptr;
}
}

// for each ship in the set. go overall its coordinates and put a pointer in the matrix
for (auto& ship : allShips) {
for (auto& part : ship.body) {
matrix[part.first.first ][part.first.second ] = ship;
}
}

return matrix;
}
*/