#pragma once
#include "PlayerSmart.h"
#include <algorithm>
#include "BattleshipBoard.h"

void PlayerSmart::setBoard(const BoardData& board)
{
	cleanMembers();// reset all members
	boardRows = board.rows();
	boardCols = board.cols();
	boardDepth = board.depth();
	Coordinate tmpCoor(0, 0, 0);
	Coordinate target(0, 0, 0);
	std::set<std::pair<char, std::set<Coordinate>>> allShipsDetails; // pairs <char , {coordinates of ship}>
	BattleshipBoard boardTemp(board); // create 
	std::vector<Coordinate> standardBase = setSixOptionsVector(); // to remove the adjesent coors to the attacked coor
	standardBase.push_back(tmpCoor); // to remove the attacked coor itself
	//standardBase vector contains {(1,0,0), (0,1,0), (0,0,1), (-1,0,0), (0,-1,0), (0,0,-1)} U {(0,0,0)}
	//extract all shipsDetails from board
	allShipsDetails = boardTemp.ExtractShipsDetails();

	//create the ship's count vector
	boardTemp.countShipsTypes(allShipsDetails, shipsCount);

	// create Permenantly dead coordinates, shouldnt attak this coordinates
	for (auto& shipDetail : allShipsDetails) { // for each ship
		for (auto& coor : shipDetail.second) { // for each coordinate
			updateCoordinates(target, coor.row + 1, coor.col + 1, coor.depth + 1); // move 0-9 to 1-10
			for (auto& vic : standardBase) { // add to the curr vector
				updateCoordinates(tmpCoor, target.row + vic.row, target.col + vic.col,target.depth + vic.depth);
				if (isInBoard(tmpCoor.row, tmpCoor.col, tmpCoor.depth)) {
					permanentlyDeadCoordinates.insert(tmpCoor);
				}
			}
		}
	}

	// create attackOptions
	for (int i = 1; i <= boardRows; i++) {
		for (int j = 1; j <= boardCols; j++) {
			for (int k = 1; k <= boardDepth; k++) {
				if (isInBoard(i,j,k)) { // is in board and not in the surroundings my ships 
					updateCoordinates(tmpCoor, i, j, k); //candidate attack 
					if (!isInSet(permanentlyDeadCoordinates,tmpCoor)) {
						attackOptions.insert(tmpCoor);
					}
				}

			}
		}
	}

	transferAllWallsToImbalanced(); // remove all coordinates which are between walls.
}

void PlayerSmart::setPlayer(int player)
{
	id = player;
}

Coordinate PlayerSmart::attack()
{
	if (attackOptions.size() == 0) {
		if (imbalancedAttackOptions.size() == 0) { // no coordinates left to attack
			return Coordinate(-1, -1, -1);
		}
		else { // didnt win and no more attack options>> the board imbalanced
			pourImbalancedToAttackOptions();
			isBoardBalanced = false;
		}
	}
	if (attackedShips.size() == 0) // no ships in process 
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

	// for each neighbor of the attacked coordinate check if is candidate
	for (auto& vic : allOptions) {
		// iterate over all possibilities to add 1/ -1 to each coordinate
		updateCoordinates(attackCandidate, candidate.row + vic.row, candidate.col + vic.col, candidate.depth + vic.depth);
		if (isInSet(attackOptions,attackCandidate)) {
			return attackCandidate;
		}
	}
	// shouldnt get here
	updateCoordinates(attackCandidate, -1, -1, -1);
	return attackCandidate;
}

void PlayerSmart::checkSixDirectionsForWalls(const Coordinate& deadCoordinate) {

	int distance = 0;
	int minShipSize = getMinShipSize();
	// allOptions will contain (1,0,1), (1,0,-1), (0,1,1), (0,1,-1), (0,0,1), (0,0,-1)
	std::vector<Coordinate> allOptions = setVectorForCheckSixDirections();
	for (auto& vic : allOptions) {
		//count distance fron dead coordinate to next "wall"
		distance = countDistance(deadCoordinate, minShipSize, vic.row, vic.col, vic.depth);
		if (distance > 0) { // in smaller then smallest ship transfer coordinates
			transferCoordinatesToSecondPoll(deadCoordinate, distance, vic.row, vic.col, vic.depth);
		}
	}
}

void PlayerSmart::transferCoordinatesToSecondPoll(const Coordinate& startCoordinate, int numOfCoors, int vertical, int horizontal, int direction) {
	int count = 0;
	Coordinate tempCoor(-1, -1, -1);
	int dim = 0;

	if (vertical == 0 && horizontal == 0) {
		dim = 1;
	}
	// iterate over all the poosibilities to go in the given direction verticaly||horizontaly||dimentionaly
	for (int j = 1; j <= numOfCoors; j++) { 
		updateCoordinates(tempCoor, startCoordinate.row + direction*j*vertical, 
							startCoordinate.col + direction*j*horizontal, startCoordinate.depth + direction*j*dim);
		if (isInSet(attackOptions, tempCoor)) {
			delFromSet(attackOptions,tempCoor);
			imbalancedAttackOptions.insert(tempCoor);
		}
	}
}

bool  PlayerSmart::isInBoard(int row, int col, int depth) const
{
	return (row <= boardRows && row >= 1 && col <= boardCols && col >= 1 && depth <= boardDepth && depth >= 1);
}

void PlayerSmart::delFromSet(std::set<Coordinate>& data, const Coordinate & coors)
{
	auto it = data.find(coors);
	if (it != data.end()){data.erase(it);}
}

bool PlayerSmart::isInSet(const std::set<Coordinate>& data, const Coordinate & coors)
{
	if (data.find(coors) != data.end()) { return true; }
	return false;
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

int PlayerSmart::getMinShipSize() const {
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
		if (findShipIndex->isPartOfShip(coorToSearch.row, coorToSearch.col, coorToSearch.depth))
		{// added to the ship i.e found match
			return cnt;
		}
		++findShipIndex;
		cnt++;
	}
	return -1;
}

void PlayerSmart::cleanMembers()
{
	currSunkShipSize = -1;
	isBoardBalanced = true;
	attackedShips.clear();
	attackOptions.clear();
	shipsCount.clear();
	imbalancedAttackOptions.clear();
	permanentlyDeadCoordinates.clear();
}

void PlayerSmart::transferAllWallsToImbalanced()
{
	Coordinate tmpCoor(-1, -1, -1);
	std::vector<Coordinate> vic = setSixOptionsVector(); // <1,0,0>, <0,1,0> <0,0,1> <-1,0,0> <0,-1,0> <0,0,-1>
	for (auto& dead : permanentlyDeadCoordinates) {
		for (auto& coor : vic) {
			// iterate over all possibilities to add 1/ -1 to each coordinate
			updateCoordinates(tmpCoor, dead.row + coor.row, dead.col + coor.col, dead.depth + coor.depth);
			if (isInBoard(tmpCoor.row, tmpCoor.col, tmpCoor.depth)) {
				// try to transfer coors from attack options to imbalanced options
				checkSixDirectionsForWalls(tmpCoor);
			}
		}
	}
}

void PlayerSmart::cleanAttackOptions(const Coordinate& targetCoor) {

	Coordinate tmpCoor(-1, -1, -1);
	std::vector<Coordinate> allOptions = setSixOptionsVector();
	for (auto& vic : allOptions) {
		// iterate over all possibilities to add 1/ -1 to each coordinate
		updateCoordinates(tmpCoor, targetCoor.row + vic.row, targetCoor.col + vic.col, targetCoor.depth + vic.depth);
		checkSixDirectionsForWalls(tmpCoor);
	}
}

int PlayerSmart::addCoorToShipInProcess(const Coordinate& targetCoor, Coordinate* nextCoorTosearch, AttackResult result) {

	int ret = -1;
	int i = 0;
	for (auto& details : attackedShips)
	{
		ret = details.addCoordinate(targetCoor.row, targetCoor.col, targetCoor.depth);
		// the coordinate was added to ship at index i
		if (ret == 1) {
			if (details.isVertical) {
				if (details.getMaxCoor() == targetCoor.row) // the new coordinate was added from bottom
				{
					updateCoordinates(*nextCoorTosearch, targetCoor.row + 1, targetCoor.col, targetCoor.depth);
				}
				else // the new coordinate was added from the top
				{
					updateCoordinates(*nextCoorTosearch, targetCoor.row - 1, targetCoor.col, targetCoor.depth);
				}
			}
			else if (details.isHorizontal) // the ship is horizontal the rows are constant
			{
				if (details.getMaxCoor() == targetCoor.col) // the new coordinate was added on the right
				{
					updateCoordinates(*nextCoorTosearch, targetCoor.row, targetCoor.col + 1, targetCoor.depth);
				}
				else // the new coordinate was added ont the left
				{
					updateCoordinates(*nextCoorTosearch, targetCoor.row, targetCoor.col - 1, targetCoor.depth);
				}
			}
			else {//is Dimentional
				if (details.getMaxCoor() == targetCoor.depth) // the new coordinate was added on the in
				{
					updateCoordinates(*nextCoorTosearch, targetCoor.row, targetCoor.col, targetCoor.depth + 1);
				}
				else // the new coordinate was added ont the out
				{
					updateCoordinates(*nextCoorTosearch, targetCoor.row, targetCoor.col, targetCoor.depth - 1);
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

void PlayerSmart::removePermementlyIncrementalDirection(int shipToDelIndex)
{

	std::vector<ShipInProcess>::iterator ShipIndex;
	std::set<Coordinate> coorsToCheck;

	if (attackedShips.at(shipToDelIndex).isVertical) { updateToVerticalIncCoors(attackedShips.at(shipToDelIndex), coorsToCheck); }
	if (attackedShips.at(shipToDelIndex).isHorizontal) { updateToHorizIncCoors(attackedShips.at(shipToDelIndex), coorsToCheck); }
	if (attackedShips.at(shipToDelIndex).isDimentional) { updateToDimenIncCoors(attackedShips.at(shipToDelIndex), coorsToCheck); }

	for (auto& coor : coorsToCheck) {
		delFromSet(attackOptions, coor);
		delFromSet(imbalancedAttackOptions, coor);
		permanentlyDeadCoordinates.insert(coor);
	}

	if (currSunkShipSize == -1) { // to update the shipsCount vector 
		currSunkShipSize = attackedShips[shipToDelIndex].shipSize; // the sunk ship size
	}
	// remove ships from vector
	ShipIndex = attackedShips.begin() + shipToDelIndex;
	attackedShips.erase(ShipIndex);
}


void PlayerSmart::updateToVerticalIncCoors(const ShipInProcess& targetShip, std::set<Coordinate>& setToUpdate)
{
	Coordinate tempCoordinate(-1, -1, -1);
	int c = targetShip.getConstCoors().col;
	int d = targetShip.getConstCoors().depth;
	updateCoordinates(tempCoordinate, targetShip.getMinCoor() - 1,c ,d );
	setToUpdate.insert(tempCoordinate);
	updateCoordinates(tempCoordinate, targetShip.getMaxCoor() + 1, c,d);
	setToUpdate.insert(tempCoordinate);
	return;
}

void PlayerSmart::updateToHorizIncCoors(const ShipInProcess& targetShip, std::set<Coordinate>& setToUpdate)
{
	Coordinate tempCoordinate(-1, -1, -1);
	int d = targetShip.getConstCoors().depth;
	int r = targetShip.getConstCoors().row;
	updateCoordinates(tempCoordinate, r, targetShip.getMinCoor() - 1, d);
	setToUpdate.insert(tempCoordinate);
	updateCoordinates(tempCoordinate,r, targetShip.getMaxCoor() + 1, d);
	setToUpdate.insert(tempCoordinate);
	return;
}

void PlayerSmart::updateToDimenIncCoors(const ShipInProcess& targetShip, std::set<Coordinate>& setToUpdate)
{
	Coordinate tempCoordinate(-1, -1, -1);
	int c = targetShip.getConstCoors().col;
	int r = targetShip.getConstCoors().row;
	updateCoordinates(tempCoordinate, r,c, targetShip.getMinCoor() - 1);
	setToUpdate.insert(tempCoordinate);
	updateCoordinates(tempCoordinate, r,c, targetShip.getMaxCoor() + 1);
	setToUpdate.insert(tempCoordinate);
	return;
}

Coordinate PlayerSmart::nextAttackFromCoors(const ShipInProcess& shipDetails, int numOfCoors) const
{
	Coordinate attackCandidate(-1, -1, -1);

	if (numOfCoors < 1) {
		return attackCandidate;
	}

	if (numOfCoors == 1) {//in case of one size ship
		return sizeOneAttack(shipDetails.firstCoordinate);
	}

	std::set<Coordinate> coorsToCheck;
	if (shipDetails.isVertical) { updateToVerticalIncCoors(shipDetails, coorsToCheck); }
	if (shipDetails.isHorizontal) { updateToHorizIncCoors(shipDetails, coorsToCheck); }
	if (shipDetails.isDimentional) { updateToDimenIncCoors(shipDetails, coorsToCheck); }

	for (auto& coor : coorsToCheck) {
		if (isInSet(attackOptions, coor)){return coor;}
	}

	return attackCandidate;
}


void PlayerSmart::checkIncrementalDirectionsForWalls(const Coordinate& attackedCoordinate, ShipInProcess& attackedShip) {

	if (!isBoardBalanced) {
		return;
	}
	std::set<Coordinate> coorsToCheck;
	if (attackedShip.isVertical) {updateToVerticalIncCoors(attackedShip, coorsToCheck);}
	if (attackedShip.isHorizontal) { updateToHorizIncCoors(attackedShip, coorsToCheck); }
	if (attackedShip.isDimentional) { updateToDimenIncCoors(attackedShip, coorsToCheck); }
	
	for (auto& coor : coorsToCheck) {
		checkSixDirectionsForWalls(coor);
	}
	return;
}

void PlayerSmart::checkConstantDirectionsForWalls(const Coordinate& attackedCoordinate, bool isVertical, bool isHorizontal, bool isDimentional)
{
	if (isBoardBalanced == false) {
		return;
	}
	Coordinate tempCoordinate(-1, -1, -1);
	std::vector<Coordinate> vert;
	std::vector<Coordinate> horiz;
	std::vector<Coordinate> dimen;

	if (isVertical)
	{
		mergeVector(vert, setDimentionalOptionsVector());
		mergeVector(vert, setHorizontalOptionsVector());
		for (auto& vic : vert) {// iterate over all options to add +/-1 to the col/depth
			updateCoordinates(tempCoordinate, attackedCoordinate.row + vic.row, attackedCoordinate.col + vic.col, attackedCoordinate.depth + vic.depth);
			checkSixDirectionsForWalls(tempCoordinate);
		}
	}

	if (isHorizontal)
	{
		mergeVector(horiz, setDimentionalOptionsVector());
		mergeVector(horiz, setVerticalOptionsVector());
		for (auto& vic : horiz) { // iterate over all options to add +/-1 to the row/col
			updateCoordinates(tempCoordinate, attackedCoordinate.row + vic.row, attackedCoordinate.col + vic.col, attackedCoordinate.depth + vic.depth);
			checkSixDirectionsForWalls(tempCoordinate);
		}
	}

	if (isDimentional)
	{
		mergeVector(dimen, setVerticalOptionsVector());
		mergeVector(dimen, setHorizontalOptionsVector());
		for (auto& vic : dimen) { // iterate over all options to add +/-1 to the col/row
			updateCoordinates(tempCoordinate, attackedCoordinate.row + vic.row, attackedCoordinate.col + vic.col, attackedCoordinate.depth + vic.depth);
			checkSixDirectionsForWalls(tempCoordinate);
		}
	}
}

int PlayerSmart::countDistance(const Coordinate& deadCoordinate, int minShipSize, int vertical, int horizontal, int direction) {
	int start = 0;
	int count = 0;
	Coordinate tempCoor(-1, -1, -1);

	if (vertical == 1) {
		start = deadCoordinate.row + direction;
		updateCoordinates(tempCoor, start, deadCoordinate.col, deadCoordinate.depth);
		// while didnt encounter permanent dead coordinate && and no room for ship contnue counting
		while ((isInSet(attackOptions, tempCoor) || isInSet(imbalancedAttackOptions, tempCoor)) && count < minShipSize) {
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
		// while didnt encounter permanent dead coordinate && and no room for ship contnue counting
		while ((isInSet(attackOptions, tempCoor) || isInSet(imbalancedAttackOptions, tempCoor)) && count < minShipSize) {
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
		// while didnt encounter permanent dead coordinate && and no room for ship contnue counting
		while ((isInSet(attackOptions, tempCoor) || isInSet(imbalancedAttackOptions, tempCoor)) && count < minShipSize) {
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

void PlayerSmart::removePermanentlyConstDirections(const Coordinate& coor, bool isVertical, bool isHorizontal, bool isDimentional)
{
	Coordinate removeCandidate(-1, -1, -1);
	std::vector<Coordinate> vert;
	std::vector<Coordinate> horiz;
	std::vector<Coordinate> dimen;

	if (isVertical)
	{
		mergeVector(vert, setHorizontalOptionsVector());
		mergeVector(vert, setDimentionalOptionsVector());
		for (auto& vic : vert) { //vert = (0, 1, 0) , (0, -1, 0) (0, 0, -1) (0, 0, 1)
			updateCoordinates(removeCandidate, coor.row + vic.row, coor.col + vic.col, coor.depth + vic.depth);
			delFromSet(attackOptions,removeCandidate);
			delFromSet(imbalancedAttackOptions,removeCandidate);
			permanentlyDeadCoordinates.insert(removeCandidate);
		}
	}

	if (isHorizontal)
	{
		mergeVector(horiz, setVerticalOptionsVector());
		mergeVector(horiz, setDimentionalOptionsVector());
		for (auto& vic : horiz) { //horiz = (1, 0, 0) , (-1, 0, 0) (0, 0, -1) (0, 0, 1)
			updateCoordinates(removeCandidate, coor.row + vic.row, coor.col + vic.col, coor.depth + vic.depth);
			delFromSet(attackOptions,removeCandidate);
			delFromSet(imbalancedAttackOptions,removeCandidate);
			permanentlyDeadCoordinates.insert(removeCandidate);
		}
	}

	if (isDimentional)
	{
		mergeVector(dimen, setVerticalOptionsVector());
		mergeVector(dimen, setHorizontalOptionsVector());
		for (auto& vic : dimen) {//dimen = (1, 0, 0) , (-1, 0, 0) (0, 1, 0) , (0, -1, 0)
			updateCoordinates(removeCandidate, coor.row + vic.row, coor.col + vic.col, coor.depth + vic.depth);
			delFromSet(attackOptions,removeCandidate);
			delFromSet(imbalancedAttackOptions,removeCandidate);
			permanentlyDeadCoordinates.insert(removeCandidate);
		}
	}
}

void PlayerSmart::cleanAttackOptions(const ShipInProcess& shipToClean, const Coordinate& attacked) {

	int minCoor = shipToClean.getMinCoor();
	int maxCoor = shipToClean.getMaxCoor();
	Coordinate tmpCoor(-1, -1, -1);

	// for each coordinate of the shipToClean
	for (int i = 0; i <shipToClean.shipSize; i++) {

		if (shipToClean.isVertical) { // remove left, right
			updateCoordinates(tmpCoor, shipToClean.incrementalCoors[i], attacked.col, attacked.depth);
			removePermanentlyConstDirections(tmpCoor, true, false, false);
			checkConstantDirectionsForWalls(tmpCoor, true, false, false);
		}

		if (shipToClean.isHorizontal) {// remove up,down
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

void PlayerSmart::notifyOnAttackResult(int player, Coordinate move, AttackResult result)
{
	int mergeResult;
	Coordinate nextCoorTosearch(-1, -1, -1);
	currSunkShipSize = -1;

	if (!isInSet(attackOptions, move)) {
		return;
	}

	if (result == AttackResult::Miss) {
		delFromSet(attackOptions,move);
		delFromSet(imbalancedAttackOptions,move);
		permanentlyDeadCoordinates.insert(move);
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

	if (result == AttackResult::Sink) {
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
	delFromSet(attackOptions,move);
	delFromSet(imbalancedAttackOptions,move);
	permanentlyDeadCoordinates.insert(move);

	// sort vector of attackedShips by size of the ship from largest ship to smallest ship - to create priority for larger ships 
	std::sort(attackedShips.begin(), attackedShips.end(),
		[](const ShipInProcess & a, const ShipInProcess & b) { return a.shipSize > b.shipSize; });

	//clean all board in all cases from 
	transferAllWallsToImbalanced();
}


/*utils**************************************************************************************************************/

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

/*utils***************************************************************************************************************/

ALGO_API IBattleshipGameAlgo* GetAlgorithm()
{
	IBattleshipGameAlgo* algoPtr = new PlayerSmart();
	return algoPtr;
}