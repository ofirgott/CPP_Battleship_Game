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

	std::set<Coordinate> result; // insert all pairs that we arnt allow to attack
	std::set<std::pair<char, std::set<Coordinate>>> setOfShipsDetails; //wiil contain pairs <char , {coordinates os ship}>
	Coordinate coorToInsert(0, 0, 0);
	boardRows = board.rows();
	boardCols = board.cols();
	boardDepth = board.depth();
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
				updateCoordinates(coorToInsert, coord.row + 1, coord.col,coord.depth);
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
				updateCoordinates(coorToInsert, coord.row, coord.col, coord.depth +1);
				result.insert(coorToInsert);
			}
			if (coord.depth - 1 > 0) {//z
				updateCoordinates(coorToInsert, coord.row, coord.col, coord.depth-1);
				result.insert(coorToInsert);
			}
		}
		++it;
	}

	for (int i = 0; i < boardRows; i++) {
		for (int j = 0; j < boardCols; j++) {
			for (int p = 0; j < boardDepth; p++) {
				updateCoordinates(coorToInsert, i, j ,p);
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
	// check x/y/z  both sides - option for attack for single coordinate

	updateCoordinates(attackCandidate, candidate.row - 1, candidate.col, candidate.depth); // check x 
	if (isInAttackOptions(attackCandidate))
	{
		return attackCandidate;
	}
	updateCoordinates(attackCandidate, candidate.row + 1, candidate.col, candidate.depth); // check x
	if (isInAttackOptions(attackCandidate)) {
		return attackCandidate;
	}
	updateCoordinates(attackCandidate, candidate.row, candidate.col - 1, candidate.depth);
	if (isInAttackOptions(attackCandidate)) //check y
	{
		return attackCandidate;
	}

	updateCoordinates(attackCandidate, candidate.row, candidate.col + 1, candidate.depth);
	if (isInAttackOptions(attackCandidate)) { // check y
		return attackCandidate;
	}

	updateCoordinates(attackCandidate, candidate.row, candidate.col, candidate.depth - 1);
	if (isInAttackOptions(attackCandidate)) //check z
	{
		return attackCandidate;
	}

	updateCoordinates(attackCandidate, candidate.row, candidate.col, candidate.depth + 1);
	if (isInAttackOptions(attackCandidate)) { // check z
		return attackCandidate;
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

	// the ship has more then 1 coordinate - Vertical or Horizontal
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

int PlayerSmart::addCoorToShipsInProcess(int row, int col, int depth, Coordinate* nextCoorTosearch, AttackResult result) {

	int ret = -1;
	int i = 0;
	ShipInProcess tempShip(row, col,depth);

	for (auto& details : attackedShips)
	{
		ret = details.addCoordinate(row, col, depth);
		if (ret == 1) // the coordinate was added to the ship, 
		{
			if (details.isVertical) // cols are constant
			{
				if (details.getMaxCoor() == row) // the new coordinate was added from bottom
				{
					nextCoorTosearch->row = row + 1;
					nextCoorTosearch->col = col;
					nextCoorTosearch->depth = depth;
				}
				else // the new coordinate was added from the top
				{
					nextCoorTosearch->row = row - 1;
					nextCoorTosearch->col = col;
					nextCoorTosearch->depth = depth;
				}
			}
			else if(details.isHorizontal) // the ship is horizontal the rows are constant
			{
				if (details.getMaxCoor() == col) // the new coordinate was added on the right
				{
					nextCoorTosearch->row = row;
					nextCoorTosearch->col = col + 1;
					nextCoorTosearch->depth = depth;
				}
				else // the new coordinate was added ont the left
				{
					nextCoorTosearch->row = row;
					nextCoorTosearch->col = col - 1;
					nextCoorTosearch->depth = depth;
				}
			}
			else {//is Dimentional
				if (details.getMaxCoor() == depth) // the new coordinate was added on the in
				{
					nextCoorTosearch->row = row;
					nextCoorTosearch->col = col;
					nextCoorTosearch->depth = depth+1;
				}
				else // the new coordinate was added ont the out
				{
					nextCoorTosearch->row = row;
					nextCoorTosearch->col = col;
					nextCoorTosearch->depth = depth -1;
				}

			}
			return i;
		}
		i++;
	}
	// if the coordinate doesnt belong to any of the ships in process add a new ship only if didnt sink
	if (result != AttackResult::Sink && ret == -1)
	{
		attackedShips.push_back(tempShip);
	}
	if (result == AttackResult::Sink && ret == -1)
	{
		currSunkShipSize = 1;
	}

	return -1;
}

void PlayerSmart::clearFourAdjecentCoors(Coordinate attackedCoordinate, AttackResult res,int minIncCoor, int maxIncCoor, bool isVertical, bool isHorizontal)
{
	if (isBoardBalanced == false) {
		return;
	}
	Coordinate tempCoordinate(-1,-1,-1);

	if (isVertical)
	{
		updateCoordinates(tempCoordinate, attackedCoordinate.row, attackedCoordinate.col, attackedCoordinate.depth -1);
		checkSixDirections(tempCoordinate);

		updateCoordinates(tempCoordinate, attackedCoordinate.row, attackedCoordinate.col, attackedCoordinate.depth + 1);
		checkSixDirections(tempCoordinate);

		updateCoordinates(tempCoordinate, attackedCoordinate.row, attackedCoordinate.col -1, attackedCoordinate.depth );
		checkSixDirections(tempCoordinate);

		updateCoordinates(tempCoordinate, attackedCoordinate.row, attackedCoordinate.col + 1, attackedCoordinate.depth );
		checkSixDirections(tempCoordinate);

		if (res == AttackResult::Sink)
		{
			updateCoordinates(tempCoordinate, minIncCoor - 1, attackedCoordinate.col, attackedCoordinate.depth);
			checkSixDirections(tempCoordinate);

			updateCoordinates(tempCoordinate, maxIncCoor + 1, attackedCoordinate.col, attackedCoordinate.depth);
			checkSixDirections(tempCoordinate);

			return;
		}
	}

	if (isHorizontal)
	{
		updateCoordinates(tempCoordinate, attackedCoordinate.row -1, attackedCoordinate.col, attackedCoordinate.depth );
		checkSixDirections(tempCoordinate);

		updateCoordinates(tempCoordinate, attackedCoordinate.row +1, attackedCoordinate.col, attackedCoordinate.depth );
		checkSixDirections(tempCoordinate);

		updateCoordinates(tempCoordinate, attackedCoordinate.row, attackedCoordinate.col , attackedCoordinate.depth -1 );
		checkSixDirections(tempCoordinate);

		updateCoordinates(tempCoordinate, attackedCoordinate.row, attackedCoordinate.col , attackedCoordinate.depth +1);
		checkSixDirections(tempCoordinate);
	
		if (res == AttackResult::Sink)
		{
			updateCoordinates(tempCoordinate, attackedCoordinate.row, minIncCoor - 1, attackedCoordinate.depth);
			checkSixDirections(tempCoordinate);

			updateCoordinates(tempCoordinate, attackedCoordinate.row, maxIncCoor + 1, attackedCoordinate.depth);
			checkSixDirections(tempCoordinate);

			return;
		}
	}
	else
	{
		updateCoordinates(tempCoordinate, attackedCoordinate.row -1, attackedCoordinate.col, attackedCoordinate.depth);
		checkSixDirections(tempCoordinate);

		updateCoordinates(tempCoordinate, attackedCoordinate.row + 1, attackedCoordinate.col, attackedCoordinate.depth);
		checkSixDirections(tempCoordinate);

		updateCoordinates(tempCoordinate, attackedCoordinate.row, attackedCoordinate.col -1, attackedCoordinate.depth );
		checkSixDirections(tempCoordinate);

		updateCoordinates(tempCoordinate, attackedCoordinate.row, attackedCoordinate.col + 1, attackedCoordinate.depth );
		checkSixDirections(tempCoordinate);

		if (res == AttackResult::Sink)
		{
			updateCoordinates(tempCoordinate, attackedCoordinate.row, attackedCoordinate.col,  minIncCoor - 1);
			checkSixDirections(tempCoordinate);

			updateCoordinates(tempCoordinate, attackedCoordinate.row, attackedCoordinate.col, maxIncCoor + 1);
			checkSixDirections(tempCoordinate);
			return;
		}
	}
}

void PlayerSmart::checkSixDirections(Coordinate deadCoordinate) {
	int distance = 0;
	int minShipSize = getMinShipSize();
	distance = countDistance(deadCoordinate, minShipSize, true, false, 1);//vectical right
	if (distance != -1) {
		transferCoordinatesToSecondPoll(deadCoordinate, distance, true, false, 1);
	}
	distance = countDistance(deadCoordinate, minShipSize, true, false, -1);//vectical left
	if (distance != -1) {
		transferCoordinatesToSecondPoll(deadCoordinate, distance, true, false, -1);
	}
	distance = countDistance(deadCoordinate, minShipSize, false, true, 1);//horizontal right
	if (distance != -1) {
		transferCoordinatesToSecondPoll(deadCoordinate, distance, false, true, 1);
	}
	distance = countDistance(deadCoordinate, minShipSize, false, true, 1);//horizontal left
	if (distance != -1) {
		transferCoordinatesToSecondPoll(deadCoordinate, distance, false, true, 1);
	}
	distance = countDistance(deadCoordinate, minShipSize, false, false, 1);//dimentional right
	if (distance != -1) {
		transferCoordinatesToSecondPoll(deadCoordinate, distance, false, false, 1);
	}
	distance = countDistance(deadCoordinate, minShipSize, false, false, -1);//dimentional left
	if (distance != -1) {
		transferCoordinatesToSecondPoll(deadCoordinate, distance, false, false, -1);
	}

}

void PlayerSmart::transferCoordinatesToSecondPoll(Coordinate startCoordinate, int numOfCoors, bool isVertical, bool isHorizontal, int direction) {
	int i = 0;
	int count = 0;
	Coordinate tempCoor(-1, -1, -1);
	if (isVertical) {
		i = startCoordinate.row ;
		for (int j = 1; j <= numOfCoors; j++) {
			updateCoordinates(tempCoor, i+ direction*j, startCoordinate.col, startCoordinate.depth);
			removeOneCoordinate(tempCoor);
			imbalancedAttackOptions.insert(tempCoor);
		}

	}
	else if (isHorizontal) {
		i = startCoordinate.col;
		for (int j = 1; j <= numOfCoors; j++) {
			updateCoordinates(tempCoor, startCoordinate.row, i + direction*j, startCoordinate.depth);
			removeOneCoordinate(tempCoor);
			imbalancedAttackOptions.insert(tempCoor);
		}
	}
	else {//dimentional
		i = startCoordinate.depth;
		for (int j = 1; j <= numOfCoors; j++) {
			updateCoordinates(tempCoor, startCoordinate.row, startCoordinate.col, i + direction*j);
			removeOneCoordinate(tempCoor);
			imbalancedAttackOptions.insert(tempCoor);
		}
	}
}

int PlayerSmart::countDistance(Coordinate startCoordinate, int minShipSize, bool isVertical, bool isHorizontal,int direction ) {
	int i = 0; 
	int count = 0;
	Coordinate tempCoor(-1, -1, -1);
	
	// go along the vertical direction up/down according to the direction input parameter
	if (isVertical) {
		i= startCoordinate.row+ direction;
		updateCoordinates(tempCoor, i, startCoordinate.col, startCoordinate.depth);
		while (isInAttackOptions(tempCoor) && count < minShipSize) {		
			i += direction;
			count += 1;
			updateCoordinates(tempCoor, i, startCoordinate.col, startCoordinate.depth);
		}
		if (count >= minShipSize) {//no need to update AttackOptions
			return -1;
		}
		return count;
	}
	else if (isHorizontal) {
		i = startCoordinate.col + direction;
		updateCoordinates(tempCoor, startCoordinate.row, i, startCoordinate.depth);

		while (isInAttackOptions(tempCoor) && count < minShipSize) {

			i += direction;
			count += 1;
			updateCoordinates(tempCoor, startCoordinate.row, i, startCoordinate.depth);
		}
		if (count >= minShipSize) {//no need to update AttackOptions
			return -1;
		}
		return count;
	}
	else {//dimentional
		i = startCoordinate.depth + direction;
		updateCoordinates(tempCoor, startCoordinate.row, startCoordinate.col, i);

		while (isInAttackOptions(tempCoor) && count < minShipSize) {

			i += direction;
			count += 1;
			updateCoordinates(tempCoor, startCoordinate.row, startCoordinate.col, i);
		}
		if (count >= minShipSize) {//no need to update AttackOptions
			return -1;
		}
		return count;
	}

}

bool  PlayerSmart::isInBoard(int row, int col, int depth) const
{
	return (row > boardRows || row< 1 || col>boardCols || col < 1 || depth>boardDepth || depth < 1);
}

void PlayerSmart::updateShipsCount(int sunkShipSize) {
	auto it = shipsCount.begin()+ sunkShipSize-1;
	it->second -= 1;
	if (it->second == -1) { // the boeard is imbalanced - number of ships in this size doesnt exist anymore in balanced board
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
	std::vector<ShipInProcess>::iterator originalShipIndex = attackedShips.begin() + startIndex;

	// make sure that the nextPair to search is in board limits

	if (isInBoard(coor->col, coor->row, coor->depth))
	{
		index = findCoorInAttackedShips(*coor, startIndex + 1);
	}

	if (index != -1)
	{
		// add to the ship at startIndex the coordinates of the ship at index 
		originalShipIndex->megreShipsInProcess(attackedShips.at(index));
		// remove from vecotr of ships the ship containing pair
		originalShipIndex = attackedShips.begin() + index;
		attackedShips.erase(originalShipIndex);
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

void PlayerSmart::removeAllIrreleventCoordinates(const Coordinate& coor, bool isVertical, bool isHorizontal , bool isDimentional)
{
	Coordinate removeCandidate(-1, -1, -1);
	if (isVertical)
	{
		// remove y coordinate from attackOptions
		updateCoordinates(removeCandidate, coor.col, coor.row - 1, coor.depth);
		removeOneCoordinate(removeCandidate);
		// remove y coordinate from attackOptions
		updateCoordinates(removeCandidate, coor.col, coor.row + 1, coor.depth);
		removeOneCoordinate(removeCandidate);
		// remove z coordinate from attackOptions
		updateCoordinates(removeCandidate, coor.col, coor.row , coor.depth -1);
		removeOneCoordinate(removeCandidate);
		// remove z coordinate from attackOptions
		updateCoordinates(removeCandidate, coor.col, coor.row , coor.depth +1);
		removeOneCoordinate(removeCandidate);

	}

	if (isHorizontal)
	{
		// remove x coordinate from attackOptions
		updateCoordinates(removeCandidate, coor.col - 1, coor.row, coor.depth);
		removeOneCoordinate(removeCandidate);
		// remove x coordinate from attackOptions
		updateCoordinates(removeCandidate, coor.col + 1, coor.row, coor.depth);
		removeOneCoordinate(removeCandidate);
		// remove z coordinate from attackOptions
		updateCoordinates(removeCandidate, coor.col, coor.row, coor.depth - 1);
		removeOneCoordinate(removeCandidate);
		// remove z coordinate from attackOptions
		updateCoordinates(removeCandidate, coor.col, coor.row, coor.depth + 1);
		removeOneCoordinate(removeCandidate);

	}
	if (isDimentional)
	{
		// remove x coordinate from attackOptions
		updateCoordinates(removeCandidate, coor.col - 1, coor.row, coor.depth);
		removeOneCoordinate(removeCandidate);
		// remove x coordinate from attackOptions
		updateCoordinates(removeCandidate, coor.col + 1, coor.row, coor.depth);
		removeOneCoordinate(removeCandidate);
		// remove y coordinate from attackOptions
		updateCoordinates(removeCandidate, coor.col, coor.row - 1, coor.depth);
		removeOneCoordinate(removeCandidate);
		// remove y coordinate from attackOptions
		updateCoordinates(removeCandidate, coor.col, coor.row + 1, coor.depth);
		removeOneCoordinate(removeCandidate);
	}
}

void PlayerSmart::removeOneCoordinate(Coordinate& coorToDelete)
{
	auto it = attackOptions.find(coorToDelete);
	if (it != attackOptions.end())//coordinate was found in attackOptions and now we can erase it
	{
		attackOptions.erase(it);
	}
}


void PlayerSmart::notifyOnAttackResult(int player, Coordinate move, AttackResult result)
{
	int mergeResult;
	Coordinate nextCoorTosearch(-1,-1,-1); // the candidate coor to merge with.( merging ships that already in the attackedShips after adding <row,col>)
	Coordinate attackedCoor(move.row, move.col, move.depth);
	Coordinate tmpCoor(-1, -1 ,-1);
	currSunkShipSize = -1;

	
	if (!isInAttackOptions(attackedCoor)) { // the coordinate is mine/ already was handeld
		return;
	}

	if (result == AttackResult::Miss)
	{
		removeOneCoordinate(attackedCoor);
		return;
	}

	// in case of sink / hit, find the cooresponding ship, merge coordinate with relevent ship and then 
	// remove irrelevent coordinates from attackOptions

	mergeResult = addCoorToShipsInProcess(move.row, move.col, move.depth, &nextCoorTosearch, result);
	//check if there is another ship in shipinprocess that belong's to the same ship we just updated
	if (mergeResult != -1)// the coordinate is added to one of the ships that are already in process 
	{
		mergeShipDetails(&nextCoorTosearch, mergeResult);
		//remove all irrelevnt coordinates for future attack 
		for (int i = 0; i <attackedShips[mergeResult].shipSize; i++) {
			int minCoor = attackedShips[mergeResult].getMinCoor();
			int maxCoor = attackedShips[mergeResult].getMaxCoor();
			// remove environment of attack ship
			if (attackedShips[mergeResult].isVertical)
			{ // remove left, right
				updateCoordinates(tmpCoor, attackedShips[mergeResult].incrementalCoors[i], move.col, move.depth);
				removeAllIrreleventCoordinates(tmpCoor, true, false,false);
				clearFourAdjecentCoors(tmpCoor, result, minCoor, maxCoor, true, false);
			}
			else if(attackedShips[mergeResult].isHorizontal)
			{// remove up,down
				updateCoordinates(tmpCoor, move.row, attackedShips[mergeResult].incrementalCoors[i], move.depth);
				removeAllIrreleventCoordinates(tmpCoor, false, true,false);
				clearFourAdjecentCoors(tmpCoor, result, minCoor, maxCoor, false, true);
			}
			else {
				updateCoordinates(tmpCoor, move.row, move.col, attackedShips[mergeResult].incrementalCoors[i]);
				removeAllIrreleventCoordinates(tmpCoor, false, false, true);
				clearFourAdjecentCoors(tmpCoor, result, minCoor, maxCoor, false, false);

			}
		}
	}

	if (result == AttackResult::Sink)
	{
		updateShipsCount(currSunkShipSize);
		if (mergeResult == -1) // the ship wasnt in process >> ship of size 1  
		{
			removeAllIrreleventCoordinates(attackedCoor, true, true,true);
			checkSixDirections(attackedCoor);
		}

		else {//ship of size>1 we remove unreleventCoors
			removeSankFromReleventCoors(mergeResult);
		}
	}
	removeOneCoordinate(attackedCoor);

	// sort vector of attackedShips by size of the ship from largest ship to smallest ship - to create priority for larger ships 
	std::sort(attackedShips.begin(), attackedShips.end(),
		[](const ShipInProcess & a, const ShipInProcess & b) { return a.shipSize > b.shipSize; });

}


void PlayerSmart::removeSankFromReleventCoors(int indexOfCoor)
{
	Coordinate coorsToDelete(0, 0, 0);
	std::vector<ShipInProcess>::iterator ShipIndex;

	// for the second ship detail 
	if (attackedShips.at(indexOfCoor).isVertical) {
		//remove edges of ship
		updateCoordinates(coorsToDelete, attackedShips.at(indexOfCoor).getMinCoor() - 1, attackedShips.at(indexOfCoor).getConstCoors().col, attackedShips.at(indexOfCoor).getConstCoors().depth);
		removeOneCoordinate(coorsToDelete);

		updateCoordinates(coorsToDelete, attackedShips.at(indexOfCoor).getMaxCoor() + 1, attackedShips.at(indexOfCoor).getConstCoors().col, attackedShips.at(indexOfCoor).getConstCoors().depth);
		removeOneCoordinate(coorsToDelete);
	}

	if (attackedShips.at(indexOfCoor).isHorizontal) {
		//remove edges of ship
		updateCoordinates(coorsToDelete, attackedShips.at(indexOfCoor).getConstCoors().row, attackedShips.at(indexOfCoor).getMinCoor() - 1, attackedShips.at(indexOfCoor).getConstCoors().depth);
		removeOneCoordinate(coorsToDelete);

		updateCoordinates(coorsToDelete, attackedShips.at(indexOfCoor).getConstCoors().row, attackedShips.at(indexOfCoor).getMaxCoor() + 1, attackedShips.at(indexOfCoor).getConstCoors().depth);
		removeOneCoordinate(coorsToDelete);
	}
	if (attackedShips.at(indexOfCoor).isDimentional) {
		//remove edges of ship
		updateCoordinates(coorsToDelete, attackedShips.at(indexOfCoor).getConstCoors().row, attackedShips.at(indexOfCoor).getConstCoors().col, attackedShips.at(indexOfCoor).getMinCoor() - 1);
		removeOneCoordinate(coorsToDelete);

		updateCoordinates(coorsToDelete, attackedShips.at(indexOfCoor).getConstCoors().row, attackedShips.at(indexOfCoor).getConstCoors().col, attackedShips.at(indexOfCoor).getMaxCoor() + 1);
		removeOneCoordinate(coorsToDelete);
	
	}
	if (currSunkShipSize == -1) {
		currSunkShipSize = attackedShips[0].shipSize;
	}
	// remove ships from vector
	ShipIndex = attackedShips.begin() + indexOfCoor;
	attackedShips.erase(ShipIndex);

}

ALGO_API IBattleshipGameAlgo* GetAlgorithm()
{
	IBattleshipGameAlgo* algoPtr = new PlayerSmart();
	return algoPtr;
}