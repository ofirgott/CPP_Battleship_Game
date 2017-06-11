#include "Ship.h"
//#include <ctype.h>
#include <algorithm>    // std::sort 

Ship::Ship(const std::pair<char, std::set<Coordinate>>& input)
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
	body.clear();				//todo: Ofir: why we need it?
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

const std::vector<Coordinate> Ship::getCoordinates()	//todo: Ofir: Resharper don't like the const in the return value, is it necessary?
{
	std::vector <Coordinate> coors;
	for (auto& part : body)
	{
		coors.push_back(part.first);
	}
	return coors;
}


bool Ship::isValidShipLen(char id, size_t setSize)
{
	char letter = toupper(id);
	if (letter == RUBBER_BOAT) {
		if (setSize != RUBBER_BOAT_LEN) {
			return false;
		}
	}
	else if (letter == ROCKET_SHIP) {
		if (setSize != ROCKET_SHIP_LEN) {
			return false;
		}
	}
	else if (letter == SUBMARINE) {
		if (setSize != SUBMARINE_LEN) {
			return false;
		}
	}
	else if (letter == DESTROYER) {
		if (setSize != DESTROYER_LEN) {
			return false;
		}
	}
	else { // in any other case 
		return false;
	}

	return true;
}


bool Ship::isValidShipCoordinates(const std::set<Coordinate>& coordinates)
{
	auto shipSize = coordinates.size();

	std::vector<int> rows;
	std::vector<int> cols;
	std::vector<int> depths;

	// ship must contain at least 1 coordinate to exist
	if (shipSize< 1) {
		return false;
	}

	// extract all rows && columns coordinates
	for (auto& coor : coordinates) {
		rows.push_back(coor.row);
		cols.push_back(coor.col);
		depths.push_back(coor.depth);
	}

	// sort the vecors
	std::sort(rows.begin(), rows.end());
	std::sort(cols.begin(), cols.end());
	std::sort(depths.begin(), depths.end());

	//check if ship is Horizontal
	if (isConstantCoors(rows, shipSize) && isConstantCoors(depths, shipSize) && isIncrementalCoors(cols, shipSize)) {
		return true;
	}

	//check if ship is vertical
	if (isConstantCoors(cols, shipSize) && isConstantCoors(depths, shipSize) && isIncrementalCoors(rows, shipSize)) {
		return true;
	}
	//check if ship is dimantional
	if (isConstantCoors(rows, shipSize) && isConstantCoors(cols, shipSize) && isIncrementalCoors(depths, shipSize)) {
		return true;
	}

	return false;
}



int Ship::updateAttack(int row, int col,int depth)
{
	for (auto& coor : body) {
		// if the coordinates attackd belong to me 
		if ((coor.first.row == row) && (coor.first.col == col) && (coor.first.depth == depth)) {

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


bool Ship::isValidShipDetails(std::pair<char, std::set<Coordinate>> input)
{
	if (!isValidShipLen(input.first, input.second.size())) {
		return false;
	}
	if (!isValidShipCoordinates(input.second)) {
		return false;
	}
	return true;
}


void Ship::setFields(int length, int sPoints, std::set<Coordinate> coordinates)
{
	Coordinate coorToInsert(0, 0, 0);
	len = length;
	points = sPoints;
	notHit = length;
	for (auto coor : coordinates) {
		coorToInsert.row = coor.row;
		coorToInsert.col = coor.col;
		coorToInsert.depth = coor.depth;
		body.insert(std::make_pair(coorToInsert, 0));
	}
}

bool Ship::isConstantCoors(const std::vector<int>& coors, size_t size)		//todo: Ofir: why we pass the size argument seperatly? this is the size of the first argument?
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


bool Ship::isIncrementalCoors(const std::vector<int>& coors, size_t size)
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


std::set<Ship*> Ship::createShipSet(const std::set<std::pair<char, std::set<Coordinate>>>& allPairs)
{
	std::set<Ship*> allBattleships;

	for (auto& elem : allPairs) {
		Ship* shipPtr = new Ship(elem);
		allBattleships.insert(shipPtr);
	}
	return allBattleships;
}