#pragma once
#include "PlayerSmart.h"
#include <algorithm>
#include "BattleshipBoard.h"


void PlayerSmart::setBoard(const BoardData& board)
{
	/*todo: maybe need to check id id != -1 ???? */
	currSunkShipSize = -1;
	isBoardBalanced = true;
	attackedShips.clear();
	attackOptions.clear();
	shipsCount.clear();
	imbalancedAttackOptions.clear();

	boardRows = board.rows();
	boardCols = board.cols();
	boardDepth = board.depth();

	std::set<Coordinate> result; // insert all pairs that we arnt allow to attack
	std::set<std::pair<char, std::set<Coordinate>>> setOfShipsDetails; //wiil contain pairs <char , {coordinates os ship}>
	Coordinate coorToInsert(0, 0, 0);
	BattleshipBoard boardTemp(board); // create  

									  // board created successfuly
	setOfShipsDetails = boardTemp.ExtractShipsDetails();

	//creat the ship count vector
	boardTemp.countShipsTypes(setOfShipsDetails, shipsCount);

	auto it = setOfShipsDetails.begin();

	// foreach shipDetail add all its surroundings to the not allowed coors to attack 
	while (it != setOfShipsDetails.end())
	{
		for (auto coord : it->second) {//for every ship we add each of her coord and around it
			result.insert(coord);
			if (coord.row + 1 <= boardRows) {//x
				updateCoordinates(coorToInsert, coord.row + 1, coord.col, coord.depth);
				result.insert(coorToInsert);
			}
			if (coord.row - 1 > 0) {//x
				updateCoordinates(coorToInsert, coord.row - 1, coord.col, coord.depth);
				result.insert(coorToInsert);
			}
			if (coord.col + 1 <= boardCols) {//y
				updateCoordinates(coorToInsert, coord.row, coord.col + 1, coord.depth);
				result.insert(coorToInsert);
			}
			if (coord.col - 1 > 0) {//y
				updateCoordinates(coorToInsert, coord.row, coord.col - 1, coord.depth);
				result.insert(coorToInsert);
			}
			if (coord.depth + 1 <= boardDepth) {//z
				updateCoordinates(coorToInsert, coord.row, coord.col, coord.depth + 1);
				result.insert(coorToInsert);
			}
			if (coord.depth - 1 > 0) {//z
				updateCoordinates(coorToInsert, coord.row, coord.col, coord.depth - 1);
				result.insert(coorToInsert);
			}
		}
		++it;
	}

	for (int i = 0; i <boardRows; i++) {
		for (int j = 0; j <boardCols; j++) {
			for (int p = 0; p < boardDepth; p++) {
				updateCoordinates(coorToInsert, i, j, p);
				if (result.find(coorToInsert) == result.end()) {//checking it's not my ship/around it = it's not in result
					updateCoordinates(coorToInsert, i + 1, j + 1, p + 1);
					attackOptions.insert(coorToInsert);//adding to the set of option for attack						
				}
			}

		}
	}
}

void PlayerSmart::setPlayer(int player)
{
	id = player;
}

Coordinate PlayerSmart::attack()
{
	if (attackOptions.size() == 0) {
		if (imbalancedAttackOptions.size() == 0) {
			return Coordinate(-1, -1, -1);
		}
		else {
			pourImbalancedToAttackOptions();
			isBoardBalanced = false;
		}
	}
	if (size(attackedShips) == 0) // no ships in process 
	{
		// return random coordinate
		return *BattleshipGameUtils::randomElement(attackOptions.begin(), attackOptions.end());

	}
	// already have ships in shipsInProcess
	return nextAttackFromCoors(attackedShips[0], attackedShips[0].shipSize);
}

void PlayerSmart::pourImbalancedToAttackOptions() {
	for (auto& coor : imbalancedAttackOptions) {
		attackOptions.insert(coor);
	}
}


Coordinate PlayerSmart::sizeOneAttack(const Coordinate& candidate) const
{
	Coordinate attackCandidate(-1, -1, -1);
	std::vector<Coordinate> allOptions = setSixOptionsVector(); //contains (1,0,0), (0,1,0), (0,0,1), (-1,0,0), (0,-1,0), (0,0,-1)

	for (auto& vic : allOptions) {
		updateCoordinates(attackCandidate, candidate.row + vic.row, candidate.col + vic.col, candidate.depth + vic.depth);
		if (isInAttackOptions(attackCandidate)) {
			return attackCandidate;
		}
	}
	// shouldnt get here
	updateCoordinates(attackCandidate, -1, -1, -1);
	return attackCandidate;
}

Coordinate PlayerSmart::nextAttackFromCoors(ShipInProcess& shipDetails, int numOfCoors) const
{
	Coordinate attackCandidate(-1, -1, -1);

	if (numOfCoors < 1) {
		return attackCandidate;
	}

	if (numOfCoors == 1) {//in case of one size ship
		return sizeOneAttack(shipDetails.firstCoordinate);
	}

	//is ship is vertical 
	if (shipDetails.isVertical) {
		updateCoordinates(attackCandidate, shipDetails.getMinCoor() - 1, shipDetails.getConstCoors().col, shipDetails.getConstCoors().depth); // check up 
		if (isInAttackOptions(attackCandidate))
		{
			return attackCandidate;
		}
		updateCoordinates(attackCandidate, shipDetails.getMaxCoor() + 1, shipDetails.getConstCoors().col, shipDetails.getConstCoors().depth); // check down
		if (isInAttackOptions(attackCandidate)) { // highest posible coor
			return attackCandidate;
		}
	}

	if (shipDetails.isHorizontal) {
		updateCoordinates(attackCandidate, shipDetails.getConstCoors().row, shipDetails.getMinCoor() - 1, shipDetails.getConstCoors().depth);
		if (isInAttackOptions(attackCandidate)) //check left
		{
			return attackCandidate;
		}

		updateCoordinates(attackCandidate, shipDetails.getConstCoors().row, shipDetails.getMaxCoor() + 1, shipDetails.getConstCoors().depth);
		if (isInAttackOptions(attackCandidate)) { // check right
			return attackCandidate;
		}
	}
	if (shipDetails.isDimentional) {
		updateCoordinates(attackCandidate, shipDetails.getConstCoors().row, shipDetails.getConstCoors().col, shipDetails.getMinCoor() - 1);
		if (isInAttackOptions(attackCandidate)) //check left
		{
			return attackCandidate;
		}

		updateCoordinates(attackCandidate, shipDetails.getConstCoors().row, shipDetails.getConstCoors().col, shipDetails.getMaxCoor() + 1);
		if (isInAttackOptions(attackCandidate)) { // check right
			return attackCandidate;
		}
	}

	//no attack option
	updateCoordinates(attackCandidate, -1, -1, -1);
	return attackCandidate;
}


int PlayerSmart::addCoorToShipInProcess(const Coordinate& targetCoor, Coordinate* nextCoorTosearch, AttackResult result) {

	int ret = -1;
	int i = 0;
	//ShipInProcess tempShip(targetCoor.row, targetCoor.col, targetCoordepth);

	for (auto& details : attackedShips)
	{
		ret = details.addCoordinate(targetCoor.row, targetCoor.col, targetCoor.depth);
		if (ret == 1) // the coordinate was added to ship at index i the ship, 
		{
			if (details.isVertical) // col, depth
			{
				if (details.getMaxCoor() == targetCoor.row) // the new coordinate was added from bottom
				{
					nextCoorTosearch->row = targetCoor.row + 1;
					nextCoorTosearch->col = targetCoor.col;
					nextCoorTosearch->depth = targetCoor.depth;
				}
				else // the new coordinate was added from the top
				{
					nextCoorTosearch->row = targetCoor.row - 1;
					nextCoorTosearch->col = targetCoor.col;
					nextCoorTosearch->depth = targetCoor.depth;
				}
			}
			else if (details.isHorizontal) // the ship is horizontal the rows are constant
			{
				if (details.getMaxCoor() == targetCoor.col) // the new coordinate was added on the right
				{
					nextCoorTosearch->row = targetCoor.row;
					nextCoorTosearch->col = targetCoor.col + 1;
					nextCoorTosearch->depth = targetCoor.depth;
				}
				else // the new coordinate was added ont the left
				{
					nextCoorTosearch->row = targetCoor.row;
					nextCoorTosearch->col = targetCoor.col - 1;
					nextCoorTosearch->depth = targetCoor.depth;
				}
			}
			else {//is Dimentional
				if (details.getMaxCoor() == targetCoor.depth) // the new coordinate was added on the in
				{
					nextCoorTosearch->row = targetCoor.row;
					nextCoorTosearch->col = targetCoor.col;
					nextCoorTosearch->depth = targetCoor.depth + 1;
				}
				else // the new coordinate was added ont the out
				{
					nextCoorTosearch->row = targetCoor.row;
					nextCoorTosearch->col = targetCoor.col;
					nextCoorTosearch->depth = targetCoor.depth - 1;
				}

			}
			return i;
		}
		i++;
	}
	// the coordinate was alreay part of the one of the ship's/ didnt belong to none of them
	if (ret == -1) {
		if (result != AttackResult::Sink) { // start a new ship
			attackedShips.push_back(ShipInProcess(targetCoor.row, targetCoor.col, targetCoor.depth));
		}
		else { // sunk, i.e the ship is of size 1, doesnt need to add it  
			currSunkShipSize = 1;
		}
	}

	return -1;
}

void PlayerSmart::checkIncrementalDirectionsForWalls(Coordinate attackedCoordinate, ShipInProcess& attackedShip) {

	if (!isBoardBalanced) {
		return;
	}
	Coordinate tempCoordinate(-1, -1, -1);
	if (attackedShip.isVertical)
	{
		updateCoordinates(tempCoordinate, attackedShip.getMinCoor() - 1, attackedCoordinate.col, attackedCoordinate.depth);
		checkSixDirectionsForWalls(tempCoordinate);
		updateCoordinates(tempCoordinate, attackedShip.getMaxCoor() + 1, attackedCoordinate.col, attackedCoordinate.depth);
		checkSixDirectionsForWalls(tempCoordinate);
		return;
	}

	if (attackedShip.isHorizontal)
	{
		updateCoordinates(tempCoordinate, attackedShip.getMinCoor() - 1, attackedCoordinate.col, attackedCoordinate.depth);
		checkSixDirectionsForWalls(tempCoordinate);
		updateCoordinates(tempCoordinate, attackedShip.getMaxCoor() + 1, attackedCoordinate.col, attackedCoordinate.depth);
		checkSixDirectionsForWalls(tempCoordinate);
		return;
	}

	if (attackedShip.isDimentional)
	{
		updateCoordinates(tempCoordinate, attackedShip.getMinCoor() - 1, attackedCoordinate.col, attackedCoordinate.depth);
		checkSixDirectionsForWalls(tempCoordinate);
		updateCoordinates(tempCoordinate, attackedShip.getMaxCoor() + 1, attackedCoordinate.col, attackedCoordinate.depth);
		checkSixDirectionsForWalls(tempCoordinate);
		return;

	}
}


void PlayerSmart::checkConstantDirectionsForWalls(Coordinate attackedCoordinate, bool isVertical, bool isHorizontal, bool isDimentional)
{
	if (isBoardBalanced == false) {
		return;
	}
	Coordinate tempCoordinate(-1, -1, -1);
	std::vector<Coordinate> vert;
	std::vector<Coordinate> horiz;
	std::vector<Coordinate> dimen;
	mergeVector(vert, setDimentionalOptionsVector());
	mergeVector(vert, setHorizontalOptionsVector());
	mergeVector(horiz, setDimentionalOptionsVector());
	mergeVector(horiz, setVerticalOptionsVector());
	mergeVector(dimen, setVerticalOptionsVector());
	mergeVector(dimen, setHorizontalOptionsVector());

	if (isVertical)
	{
		for (auto& vic : vert) {
			updateCoordinates(tempCoordinate, attackedCoordinate.row + vic.row, attackedCoordinate.col + vic.col, attackedCoordinate.depth + vic.depth);
			checkSixDirectionsForWalls(tempCoordinate);
		}
	}

	if (isHorizontal)
	{
		for (auto& vic : horiz) {
			updateCoordinates(tempCoordinate, attackedCoordinate.row + vic.row, attackedCoordinate.col + vic.col, attackedCoordinate.depth + vic.depth);
			checkSixDirectionsForWalls(tempCoordinate);
		}
	}

	if (isDimentional)
	{
		for (auto& vic : dimen) {
			updateCoordinates(tempCoordinate, attackedCoordinate.row + vic.row, attackedCoordinate.col + vic.col, attackedCoordinate.depth + vic.depth);
			checkSixDirectionsForWalls(tempCoordinate);
		}
	}
}


void PlayerSmart::checkSixDirectionsForWalls(Coordinate deadCoordinate) {

	int distance = 0;
	int minShipSize = getMinShipSize();
	std::vector<Coordinate> allOptions = setVectorForCheckSixDirections();
	for (auto& vic : allOptions) {
		distance = countDistance(deadCoordinate, minShipSize, vic.row, vic.col, vic.depth);
		if (distance > 0) {
			transferCoordinatesToSecondPoll(deadCoordinate, distance, vic.row, vic.col, vic.depth);
		}
	}
}

void PlayerSmart::transferCoordinatesToSecondPoll(Coordinate startCoordinate, int numOfCoors, int vertical, int horizontal, int direction) {
	int start = 0;
	int count = 0;
	Coordinate tempCoor(-1, -1, -1);
	if (vertical == 1) {
		start = startCoordinate.row;
		for (int j = 1; j <= numOfCoors; j++) {
			updateCoordinates(tempCoor, start + direction*j, startCoordinate.col, startCoordinate.depth);
			if (isInAttackOptions(tempCoor)) {
				delOneCoorPermanentlyAttackOptions(tempCoor);
				imbalancedAttackOptions.insert(tempCoor);
			}
		}
	}
	else if (horizontal == 1) {
		start = startCoordinate.col;
		for (int j = 1; j <= numOfCoors; j++) {
			updateCoordinates(tempCoor, startCoordinate.row, start + direction*j, startCoordinate.depth);
			if (isInAttackOptions(tempCoor)) {
				delOneCoorPermanentlyAttackOptions(tempCoor);
				imbalancedAttackOptions.insert(tempCoor);
			}
		}
	}
	else {//dimentional
		start = startCoordinate.depth;
		for (int j = 1; j <= numOfCoors; j++) {
			updateCoordinates(tempCoor, startCoordinate.row, startCoordinate.col, start + direction*j);
			if (isInAttackOptions(tempCoor)) {
				delOneCoorPermanentlyAttackOptions(tempCoor);
				imbalancedAttackOptions.insert(tempCoor);
			}
		}
	}
}

int PlayerSmart::countDistance(Coordinate deadCoordinate, int minShipSize, int vertical, int horizontal, int direction) {
	int start = 0;
	int count = 0;
	Coordinate tempCoor(-1, -1, -1);

	// go along the vertical direction up/down according to the direction input parameter
	if (vertical == 1) {
		start = deadCoordinate.row + direction;
		updateCoordinates(tempCoor, start, deadCoordinate.col, deadCoordinate.depth);
		while ((isInAttackOptions(tempCoor) || isInImbalancedOptions(tempCoor)) && count < minShipSize) {
			start += direction;
			count += 1;
			updateCoordinates(tempCoor, start, deadCoordinate.col, deadCoordinate.depth);
		}
		if (count >= minShipSize) {//no need to update AttackOptions
			return -1;
		}
		return count;
	}
	else if (horizontal == 1) {
		start = deadCoordinate.col + direction;
		updateCoordinates(tempCoor, deadCoordinate.row, start, deadCoordinate.depth);

		while (isInAttackOptions(tempCoor) && count < minShipSize) {

			start += direction;
			count += 1;
			updateCoordinates(tempCoor, deadCoordinate.row, start, deadCoordinate.depth);
		}
		if (count >= minShipSize) {//no need to update AttackOptions
			return -1;
		}
		return count;
	}
	else {//dimentional
		start = deadCoordinate.depth + direction;
		updateCoordinates(tempCoor, deadCoordinate.row, deadCoordinate.col, start);

		while (isInAttackOptions(tempCoor) && count < minShipSize) {

			start += direction;
			count += 1;
			updateCoordinates(tempCoor, deadCoordinate.row, deadCoordinate.col, start);
		}
		if (count >= minShipSize) {//no need to update AttackOptions
			return -1;
		}
		return count;
	}
}

bool  PlayerSmart::isInBoard(int row, int col, int depth) const
{
	return (row <= boardRows && row >= 1 && col <= boardCols && col >= 1 && depth <= boardDepth && depth >= 1);
}

void PlayerSmart::updateShipsCount(int sunkShipSize) {

	auto it = shipsCount.begin() + sunkShipSize - 1;
	it->second -= 1;

	// if the board is imbalanced 
	if (it->second == -1) { //this ship size doesnt exist in balanced board
		isBoardBalanced = false;
		pourImbalancedToAttackOptions();
	}


}

int PlayerSmart::getMinShipSize() {
	for (auto& detail : shipsCount) {
		if (detail.second>0) {
			return detail.first;
		}
	}
	return -1;
}


void PlayerSmart::mergeShipDetails(Coordinate* coor, int startIndex)
{
	int index = -1;
	std::vector<ShipInProcess>::iterator shipsIndex = attackedShips.begin() + startIndex;

	// make sure that the nextPair to search is in board limits
	if (isInBoard(coor->row, coor->col, coor->depth))
	{
		index = findCoorInAttackedShips(*coor, startIndex + 1);
	}

	if (index != -1)
	{
		// merge 2 ships, the ship at start index with the ship at the found index
		shipsIndex->megreShipsInProcess(attackedShips.at(index));
		// remove from attackships the ship at index(it's details alreay merged)
		shipsIndex = attackedShips.begin() + index;
		attackedShips.erase(shipsIndex);
	}
}

int PlayerSmart::findCoorInAttackedShips(const Coordinate& coorToSearch, int startIndex)
{
	int cnt = startIndex;
	std::vector<ShipInProcess>::iterator findShipIndex = attackedShips.begin() + startIndex;

	// iterate on the vector starting from the vector[ startIndex]
	while (findShipIndex != attackedShips.end()) {

		if (findShipIndex->isPartOfShip(coorToSearch.row, coorToSearch.col, coorToSearch.depth)) // added to the ship i.e found match
		{
			return cnt;
		}
		++findShipIndex;
		cnt++;
	}
	return -1;

}

bool PlayerSmart::isInAttackOptions(const Coordinate& coors) const
{
	auto it = attackOptions.find(coors);
	if (it != attackOptions.end())//coordinate was found in attackOptions
	{
		return true;
	}

	return false;
}

void PlayerSmart::removePermanentlyConstDirections(const Coordinate& coor, bool isVertical, bool isHorizontal, bool isDimentional)
{
	Coordinate removeCandidate(-1, -1, -1);
	std::vector<Coordinate> vert;
	std::vector<Coordinate> horiz;
	std::vector<Coordinate> dimen;

	mergeVector(vert, setHorizontalOptionsVector());
	mergeVector(vert, setDimentionalOptionsVector());

	mergeVector(horiz, setVerticalOptionsVector());
	mergeVector(horiz, setDimentionalOptionsVector());

	mergeVector(dimen, setVerticalOptionsVector());
	mergeVector(dimen, setHorizontalOptionsVector());


	if (isVertical)
	{
		for (auto& vic : vert) {
			updateCoordinates(removeCandidate, coor.row + vic.row, coor.col + vic.col, coor.depth + vic.depth);
			delOneCoorPermanentlyAttackOptions(removeCandidate);
			delOneCoorPermanentlyImbalancedOptions(removeCandidate);
		}
	}

	if (isHorizontal)
	{
		for (auto& vic : horiz) {
			updateCoordinates(removeCandidate, coor.row + vic.row, coor.col + vic.col, coor.depth + vic.depth);
			delOneCoorPermanentlyAttackOptions(removeCandidate);
			delOneCoorPermanentlyImbalancedOptions(removeCandidate);
		}
	}

	if (isDimentional)
	{
		for (auto& vic : dimen) {
			updateCoordinates(removeCandidate, coor.row + vic.row, coor.col + vic.col, coor.depth + vic.depth);
			delOneCoorPermanentlyAttackOptions(removeCandidate);
			delOneCoorPermanentlyImbalancedOptions(removeCandidate);
		}
	}
}

void PlayerSmart::delOneCoorPermanentlyAttackOptions(Coordinate& coorToDelete)
{
	auto it = attackOptions.find(coorToDelete);
	if (it != attackOptions.end())//coordinate was found in attackOptions and now we can erase it
	{
		attackOptions.erase(it);
	}
}

void PlayerSmart::delOneCoorPermanentlyImbalancedOptions(Coordinate & coorToDelete)
{
	auto it = imbalancedAttackOptions.find(coorToDelete);
	if (it != imbalancedAttackOptions.end())//coordinate was found in attackOptions and now we can erase it
	{
		imbalancedAttackOptions.erase(it);
	}
}

void PlayerSmart::cleanAttackOptions(ShipInProcess& shipToClean, const Coordinate& attacked) {

	int minCoor = shipToClean.getMinCoor();
	int maxCoor = shipToClean.getMaxCoor();
	Coordinate tmpCoor(-1, -1, -1);

	// for each coordinate of the shipToClean
	for (int i = 0; i <shipToClean.shipSize; i++) {

		if (shipToClean.isVertical)
		{ // remove left, right
			updateCoordinates(tmpCoor, shipToClean.incrementalCoors[i], attacked.col, attacked.depth);
			removePermanentlyConstDirections(tmpCoor, true, false, false);
			checkConstantDirectionsForWalls(tmpCoor, true, false, false);
		}

		if (shipToClean.isHorizontal)
		{// remove up,down
			updateCoordinates(tmpCoor, attacked.row, shipToClean.incrementalCoors[i], attacked.depth);
			removePermanentlyConstDirections(tmpCoor, false, true, false);
			checkConstantDirectionsForWalls(tmpCoor, false, true, false);
		}

		if (shipToClean.isDimentional) {
			updateCoordinates(tmpCoor, attacked.row, attacked.col, shipToClean.incrementalCoors[i]);
			removePermanentlyConstDirections(tmpCoor, false, false, true);
			checkConstantDirectionsForWalls(tmpCoor, false, false, true);

		}
	}
}

std::vector<Coordinate> PlayerSmart::setSixOptionsVector() {
	std::vector<Coordinate> allOptions;
	mergeVector(allOptions, setHorizontalOptionsVector());
	mergeVector(allOptions, setVerticalOptionsVector());
	mergeVector(allOptions, setDimentionalOptionsVector());
	return allOptions;
}

std::vector<Coordinate> PlayerSmart::setVectorForCheckSixDirections()
{
	std::vector<Coordinate> allOptions;
	allOptions.push_back(Coordinate(1, 0, 1));
	allOptions.push_back(Coordinate(1, 0, -1));
	allOptions.push_back(Coordinate(0, 1, 1));
	allOptions.push_back(Coordinate(0, 1, -1));
	allOptions.push_back(Coordinate(0, 0, 1));
	allOptions.push_back(Coordinate(0, 0, -1));
	return allOptions;
}

std::vector<Coordinate> PlayerSmart::setHorizontalOptionsVector()
{

	std::vector<Coordinate> allOptions;
	allOptions.push_back(Coordinate(0, 1, 0));
	allOptions.push_back(Coordinate(0, -1, 0));
	return allOptions;

}

std::vector<Coordinate> PlayerSmart::setVerticalOptionsVector()
{
	std::vector<Coordinate> allOptions;
	allOptions.push_back(Coordinate(-1, 0, 0));
	allOptions.push_back(Coordinate(1, 0, 0));
	return allOptions;
}

std::vector<Coordinate> PlayerSmart::setDimentionalOptionsVector()
{
	std::vector<Coordinate> allOptions;
	allOptions.push_back(Coordinate(0, 0, -1));
	allOptions.push_back(Coordinate(0, 0, 1));

	return allOptions;
}

void PlayerSmart::mergeVector(std::vector<Coordinate>& allOptions, const std::vector<Coordinate>& tempOptions)
{
	for (auto& option : tempOptions) {
		allOptions.push_back(option);
	}
}


void PlayerSmart::cleanAttackOptions(const Coordinate& targetCoor) {

	Coordinate tmpCoor(-1, -1, -1);
	std::vector<Coordinate> allOptions = setSixOptionsVector();

	for (auto& vic : allOptions) {
		updateCoordinates(tmpCoor, targetCoor.row + vic.row, targetCoor.col + vic.col, targetCoor.depth + vic.depth);
		checkSixDirectionsForWalls(tmpCoor);
	}
}

void PlayerSmart::notifyOnAttackResult(int player, Coordinate move, AttackResult result)
{
	int mergeResult;
	Coordinate nextCoorTosearch(-1, -1, -1); // the candidate coor to merge with.
	currSunkShipSize = -1;

	if (!isInAttackOptions(move)) { // the coordinate is mine/ already was handeld?????????????????????????
		return;
	}

	if (result == AttackResult::Miss)
	{
		delOneCoorPermanentlyAttackOptions(move);
		delOneCoorPermanentlyImbalancedOptions(move);
		checkSixDirectionsForWalls(move);
		return;
	}

	/*in both sink||hit, find the first occurence of a ship move belongs to, merge move with relevent ship
	remove permanently dead coors from attackoptions and imbalancedoptions and add possibly
	dead coors to imbalancedoptions*/
	mergeResult = addCoorToShipInProcess(Coordinate(move.row, move.col, move.depth), &nextCoorTosearch, result);
	if (mergeResult > -1) /* found a ship to merge with*/
	{
		/*look for another ship move might belong to*/
		mergeShipDetails(&nextCoorTosearch, mergeResult);
		/*remove all surroundings of the attacked ship's permamently, transfer possible dead coors*/
		cleanAttackOptions(attackedShips[mergeResult], move);
	}

	if (result == AttackResult::Sink)
	{
		if (currSunkShipSize == 1) // the ship wasnt in process >> ship of size 1  
		{
			removePermanentlyConstDirections(move, true, true, true); // removes all 6 adject coors from attack options 
																	  // for each of the coors in the surronding check all 6 directions 
			cleanAttackOptions(move);
		}
		else {//ship of size>1 
			  // remove incremental walls
			checkIncrementalDirectionsForWalls(move, attackedShips[mergeResult]);
			//remove adjecent incremental coordinates and remove ship from attacked ships
			removePermementlyIncrementalDirection(mergeResult);
		}
		/*if ship was of size 1 addCoorToShipsInProcess updated currSunkshipsize to 1
		if ship's size > 1 removePermementlyIncrementalDirection updates currSunkShipSize to the actual size*/
		updateShipsCount(currSunkShipSize);
	}
	delOneCoorPermanentlyAttackOptions(move);
	delOneCoorPermanentlyImbalancedOptions(move);

	// sort vector of attackedShips by size of the ship from largest ship to smallest ship - to create priority for larger ships 
	std::sort(attackedShips.begin(), attackedShips.end(),
		[](const ShipInProcess & a, const ShipInProcess & b) { return a.shipSize > b.shipSize; });

	//clean all board in all cases from 

}


void PlayerSmart::removePermementlyIncrementalDirection(int shipToDelIndex)
{
	Coordinate coorsToDelete(0, 0, 0);
	std::vector<ShipInProcess>::iterator ShipIndex;

	// for the second ship detail 
	if (attackedShips.at(shipToDelIndex).isVertical) {
		//remove edges of ship
		updateCoordinates(coorsToDelete, attackedShips.at(shipToDelIndex).getMinCoor() - 1, attackedShips.at(shipToDelIndex).getConstCoors().col, attackedShips.at(shipToDelIndex).getConstCoors().depth);
		delOneCoorPermanentlyAttackOptions(coorsToDelete);
		delOneCoorPermanentlyImbalancedOptions(coorsToDelete);

		updateCoordinates(coorsToDelete, attackedShips.at(shipToDelIndex).getMaxCoor() + 1, attackedShips.at(shipToDelIndex).getConstCoors().col, attackedShips.at(shipToDelIndex).getConstCoors().depth);
		delOneCoorPermanentlyAttackOptions(coorsToDelete);
		delOneCoorPermanentlyImbalancedOptions(coorsToDelete);
	}

	if (attackedShips.at(shipToDelIndex).isHorizontal) {
		//remove edges of ship
		updateCoordinates(coorsToDelete, attackedShips.at(shipToDelIndex).getConstCoors().row, attackedShips.at(shipToDelIndex).getMinCoor() - 1, attackedShips.at(shipToDelIndex).getConstCoors().depth);
		delOneCoorPermanentlyAttackOptions(coorsToDelete);
		delOneCoorPermanentlyImbalancedOptions(coorsToDelete);

		updateCoordinates(coorsToDelete, attackedShips.at(shipToDelIndex).getConstCoors().row, attackedShips.at(shipToDelIndex).getMaxCoor() + 1, attackedShips.at(shipToDelIndex).getConstCoors().depth);
		delOneCoorPermanentlyAttackOptions(coorsToDelete);
		delOneCoorPermanentlyImbalancedOptions(coorsToDelete);
	}
	if (attackedShips.at(shipToDelIndex).isDimentional) {
		//remove edges of ship
		updateCoordinates(coorsToDelete, attackedShips.at(shipToDelIndex).getConstCoors().row, attackedShips.at(shipToDelIndex).getConstCoors().col, attackedShips.at(shipToDelIndex).getMinCoor() - 1);
		delOneCoorPermanentlyAttackOptions(coorsToDelete);
		delOneCoorPermanentlyImbalancedOptions(coorsToDelete);

		updateCoordinates(coorsToDelete, attackedShips.at(shipToDelIndex).getConstCoors().row, attackedShips.at(shipToDelIndex).getConstCoors().col, attackedShips.at(shipToDelIndex).getMaxCoor() + 1);
		delOneCoorPermanentlyAttackOptions(coorsToDelete);
		delOneCoorPermanentlyImbalancedOptions(coorsToDelete);

	}

	if (currSunkShipSize == -1) { // to update the shipsCount vector 
		currSunkShipSize = attackedShips[shipToDelIndex].shipSize; // the sunk ship size
	}
	// remove ships from vector
	ShipIndex = attackedShips.begin() + shipToDelIndex;
	attackedShips.erase(ShipIndex);

}

bool PlayerSmart::isInImbalancedOptions(const Coordinate & coors) const
{
	auto it = imbalancedAttackOptions.find(coors);
	if (it != imbalancedAttackOptions.end())//coordinate was found in attackOptions
	{
		return true;
	}

	return false;
}

ALGO_API IBattleshipGameAlgo* GetAlgorithm()
{
	IBattleshipGameAlgo* algoPtr = new PlayerSmart();
	return algoPtr;
}