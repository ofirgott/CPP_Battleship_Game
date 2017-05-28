#pragma once
#include "PlayerSmart.h"
#include <algorithm>
#include "BattleshipGameUtils.h"
#include "BattleshipBoard.h"
#include <vector>

void PlayerSmart::setBoard(const BoardData& board)
{
	std::set<Coordinate> result; // insert all pairs that we arnt allow to attack
	std::set<std::pair<char, std::set<Coordinate>>> setOfShipsDetails; //wiil contain pairs <char , {coordinates os ship}>
	Coordinate coorToInsert(0, 0, 0);
	boardRows = board.rows();
	boardCols = board.cols();
	boardDepth = board.depth();
	BattleshipBoard boardTemp(board); // create  

	// board created successfuly
	setOfShipsDetails = boardTemp.ExtractShipsDetails();
//	std::set<std::pair<int, int>> coordOfCurrentShip;
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



Coordinate PlayerSmart::attack()
{
	if (size(attackedShips) == 0) // no ships in process 
	{
		// return random coordinate
		return *BattleshipGameUtils::randomElement(attackOptions.begin(), attackOptions.end());

	}
	// already have ships in shipsInProcess
	return nextAttackFromCoors(attackedShips[0], attackedShips[0].shipSize);
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
		return sizeOneAttack(shipDetails.firstPair);
	}

	// the ship has more then 1 coordinate - Vertical or Horizontal
	if (shipDetails.isVertical) {
		updateCoordinates(attackCandidate, shipDetails.getMinCoor() - 1, shipDetails.getConstCoor()); // check up 
		if (isInAttackOptions(attackCandidate))
		{
			return attackCandidate;
		}
		updateCoordinates(attackCandidate, shipDetails.getMaxCoor() + 1, shipDetails.getConstCoor()); // check down
		if (isInAttackOptions(attackCandidate)) { // highest posible coor
			return attackCandidate;
		}
	}

	if (shipDetails.isHorizontal) {
		updateCoordinates(attackCandidate, shipDetails.getConstCoor(), shipDetails.getMinCoor() - 1);
		if (isInAttackOptions(attackCandidate)) //check left
		{
			return attackCandidate;
		}

		updateCoordinates(attackCandidate, shipDetails.getConstCoor(), shipDetails.getMaxCoor() + 1);
		if (isInAttackOptions(attackCandidate)) { // check right
			return attackCandidate;
		}
	}
	//no attack option
	updateCoordinates(attackCandidate, -1, -1);
	return attackCandidate;
}

int PlayerSmart::addCoorToShipsInProcess(int row, int col, int depth, Coordinate* nextPairTosearch, AttackResult result) {

	int ret = -1;
	int i = 0;
	ShipInProcess tempShip(row, col);

	for (auto& details : attackedShips)
	{
		ret = details.addCoordinate(row, col);
		if (ret == 1) // the coordinate was added to the ship, 
		{
			if (details.isVertical) // cols are constant
			{
				if (details.getMaxCoor() == row) // the new coordinate was added from bottom
				{
					nextPairTosearch->first = row + 1;
					nextPairTosearch->second = col;
				}
				else // the new coordinate was added from the top
				{
					nextPairTosearch->first = row - 1;
					nextPairTosearch->second = col;
				}
			}
			else // the ship is horizontal the rows are constant
			{
				if (details.getMaxCoor() == col) // the new coordinate was added on the right
				{
					nextPairTosearch->first = row;
					nextPairTosearch->second = col + 1;
				}
				else // the new coordinate was added ont the left
				{
					nextPairTosearch->first = row;
					nextPairTosearch->second = col - 1;
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

	return -1;
}

bool  PlayerSmart::isInBoard(int row, int col, int depth) const
{
	return (row > boardRows || row< 1 || col>boardCols || col < 1 || depth>boardDepth || depth < 1);
}

void PlayerSmart::mergeShipDetails(Coordinate* coor, int startIndex)
{
	int index = -1;
	std::vector<ShipInProcess>::iterator originalShipIndex = attackedShips.begin() + startIndex;

	// make sure that the nextPair to search is in board limits

	if (isInBoard(coor->col, coor->row, coor->depth))
	{
		index = findPairInAttackedShips(*coor, startIndex + 1);
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

int PlayerSmart::findPairInAttackedShips(const std::pair<int, int>& pairToSearch, int startIndex)
{
	int cnt = startIndex;
	std::vector<ShipInProcess>::iterator findShipIndex = attackedShips.begin() + startIndex;
	// iterate on the vector starting from the vector[ startIndex]
	while (findShipIndex != attackedShips.end()) {

		if (findShipIndex->isPartOfShip(pairToSearch.first, pairToSearch.second)) // added to the ship i.e found match
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
		updateCoordinates(removeCandidate, coor.col, coor.row , coor.depth +!);
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

			// remove environment of attack ship
			if (attackedShips[mergeResult].isVertical)
			{ // remove left, right
				updateCoordinates(tmpCoor, attackedShips[mergeResult].incrementalCoors[i], move.col, move.depth);
				removeAllIrreleventCoordinates(tmpCoor, true, false,false);
			}
			else if(attackedShips[mergeResult].isHorizontal)
			{// remove up,down
				updateCoordinates(tmpCoor, move.row, attackedShips[mergeResult].incrementalCoors[i], move.depth);
				removeAllIrreleventCoordinates(tmpCoor, false, true,false);
			}
			else {
				updateCoordinates(tmpCoor, move.row, move.col, attackedShips[mergeResult].incrementalCoors[i]);
				removeAllIrreleventCoordinates(tmpCoor, false, false, true);
			}
		}
	}

	if (result == AttackResult::Sink)
	{
		if (mergeResult == -1) // the ship wasnt in process >> ship of size 1  
		{
			removeAllIrreleventCoordinates(attackedCoor, true, true,true);
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
		updateCoordinates(coorsToDelete, attackedShips.at(indexOfCoor).getMinCoor() - 1, attackedShips.at(indexOfCoor).getConstCoor());
		removeOneCoordinate(coorsToDelete);

		updateCoordinates(coorsToDelete, attackedShips.at(indexOfCoor).getMaxCoor() + 1, attackedShips.at(indexOfCoor).getConstCoor());
		removeOneCoordinate(coorsToDelete);
	}

	if (attackedShips.at(indexOfCoor).isHorizontal) {
		//remove edges of ship
		updateCoordinates(coorsToDelete, attackedShips.at(indexOfCoor).getConstCoor(), attackedShips.at(indexOfCoor).getMinCoor() - 1);
		removeOneCoordinate(coorsToDelete);

		updateCoordinates(coorsToDelete, attackedShips.at(indexOfCoor).getConstCoor(), attackedShips.at(indexOfCoor).getMaxCoor() + 1);
		removeOneCoordinate(coorsToDelete);
	}

	// remove ships from vector
	ShipIndex = attackedShips.begin() + indexOfCoor;
	attackedShips.erase(ShipIndex);

}


IBattleshipGameAlgo* GetAlgorithm()
{
	_instancesVec.push_back(new PlayerSmart());  // Create new instance and keep it in vector 
	return _instancesVec[_instancesVec.size() - 1];  // Return last instance
}