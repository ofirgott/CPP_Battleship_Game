#include "Ship.h"
#include <ctype.h>


Ship::Ship(const std::pair<char, std::set<std::pair<int, int>>>& input)
{
	symbol = toupper(input.first);

	if (symbol == RUBBER_BOAT) {
		setFields(1, 2, input.second);
	}
	else if (symbol == ROCKET_SHIP) {
		setFields(2, 3, input.second);
	}
	else if (symbol == SUBMARINE) {
		setFields(3, 7, input.second);
	}
	else if (symbol == DESTROYER) {
		setFields(4, 8, input.second);
	}
	else
	{
		setFields(-1, -1, input.second);
	}
}

Ship::~Ship()
{
	body.clear();
}

int Ship::getPoints()const
{
	return points;
}

int Ship::getNotHit()const
{
	return notHit;
}

bool Ship::isAlive()const
{
	if (notHit > 0) {
		return true;
	}
	return false;
}

const std::vector<std::pair<int, int>> Ship::getCoordinates()
{
	std::vector <std::pair<int, int>> coors;
	for (auto& part : body)
	{
		coors.push_back(part.first);
	}
	return coors;
}


bool Ship::isValidShipLen(char id, int setSize)
{
	char letter = toupper(id);
	if (letter == RUBBER_BOAT) {
		if (setSize != 1) {
			return false;
		}
	}
	else if (letter == ROCKET_SHIP) {
		if (setSize != 2) {
			return false;
		}
	}
	else if (letter == SUBMARINE) {
		if (setSize != 3) {
			return false;
		}
	}
	else if (letter == DESTROYER) {
		if (setSize != 4) {
			return false;
		}
	}
	else { // in any other case 
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
	for (auto coor : coordinates) {
		body.insert(std::make_pair(coor, 0));
	}
}

bool Ship::isConstantCoors(const std::vector<int>& coors, int size)
{
	int firstCoor;
	if (size < 1) { // invlid number of coordinates
		return false;
	}
	// compare all cordinated to the first coordinate
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
	if (size < 1) { // invalid number of cordinates
		return false;
	}

	//check if the coordinates are incremental 
	prevCoor = coors[0];
	for (int i = 1; i < size; i++) {
		if (coors[i] != (prevCoor + 1)) {
			return false;
		}
		prevCoor += 1;
	}
	return true;
}

Ship *** Ship::createShipMatrix(std::set <Ship*> allShips)
{
	Ship *** matrix = new Ship**[ROWS];

	// init matrix pointers no NULL
	for (int i = 0; i < ROWS; i++) {
		matrix[i] = new Ship*[COLS];
		for (int j = 0; j < COLS; j++) {
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

void Ship::deleteShipMatrix(Ship *** matrix)
{
	std::vector <std::pair<int, int>> currCoor;

	if (matrix == nullptr) {
		return;
	}

	// release the ship's matrix
	for (auto i = 0; i < ROWS; i++) {
		for (auto j = 0; j < COLS; j++) {
			if (matrix[i][j] != nullptr) { // release ship exactly once 
				currCoor.clear();
				currCoor = matrix[i][j]->getCoordinates();
				delete matrix[i][j];
				// set all the pointers to this ship to nullptr
				for (auto& coor : currCoor) {
					matrix[coor.first][coor.second] = nullptr;
				}
			}
		}
		delete[] matrix[i];
	}
	delete[] matrix;
}

std::set<Ship*> Ship::createShipSet(const std::set<std::pair<char, std::set<std::pair<int, int>>>>& allPairs)
{
	std::set<Ship*> allBattleships;

	for (auto& elem : allPairs) {
		Ship* shipPtr = new Ship(elem);
		allBattleships.insert(shipPtr);
	}
	return allBattleships;
}
