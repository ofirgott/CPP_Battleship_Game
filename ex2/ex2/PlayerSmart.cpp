#include "PlayerSmart.h"
#include <algorithm>
#include "BattleshipGameUtils.h"
#include "BattleshipBoard.h"


void PlayerSmart::setBoard(int player, const char ** board, int numRows, int numCols)
{
	std::set<std::pair<int, int>> result; // insert all pairs that we arnt allow to attack
	std::set<std::pair<char, std::set<std::pair<int, int>>>> setOfShipsDetails; //wiil contain pairs <char , {coordinates os ship}>
	std::pair<int, int> pairToInsert(0, 0);

	id = player;
	boardRows = numRows;
	boardCols = numCols;
	BattleshipBoard boardTemp(board, numRows, numCols); // create  

	if (!boardTemp.isSuccessfullyCreated()) {
		id = -1;
	}
	// board created successfuly
	if (id != -1) {

		setOfShipsDetails = boardTemp.ExtractShipsDetails();
		std::set<std::pair<int, int>> coordOfCurrentShip;
		auto it = setOfShipsDetails.begin();

		// foreach shipDetail add all its surroundings to the not allowed coors to attack 
		while (it != setOfShipsDetails.end())
		{
			for (auto coord : it->second) {//for every ship we add each of her coord and around it
				result.insert(coord);
				if (coord.first + 1 <= numRows) {//down
					updateCoordinates(pairToInsert, coord.first + 1, coord.second);
					result.insert(pairToInsert);
				}
				if (coord.first - 1 > 0) {//up
					updateCoordinates(pairToInsert, coord.first - 1, coord.second);
					result.insert(pairToInsert);
				}
				if (coord.second + 1 <= numCols) {//right
					updateCoordinates(pairToInsert, coord.first, coord.second + 1);
					result.insert(pairToInsert);
				}
				if (coord.second - 1 > 0) {//left
					updateCoordinates(pairToInsert, coord.first, coord.second - 1);
					result.insert(pairToInsert);
				}
			}
			++it;
		}

		for (int i = 0; i < numRows; i++) {
			for (int j = 0; j < numCols; j++) {
				updateCoordinates(pairToInsert, i, j);
				if (result.find(pairToInsert) == result.end()) {//checking it's not my ship/around it = it's not in result
					updateCoordinates(pairToInsert, i + 1, j + 1);
					attackOptions.insert(pairToInsert);//adding to the set of option for attack 
				}
			}
		}
	}

}

std::pair<int, int> PlayerSmart::attack()
{
	if (size(attackedShips) == 0) // no ships in process 
	{
		// return random coordinate
		return *BattleshipGameUtils::randomElement(attackOptions.begin(), attackOptions.end());

	}
	// already have ships in shipsInProcess
	return nextAttackFromCoors(attackedShips[0], attackedShips[0].shipSize);
}

std::pair<int, int> PlayerSmart::sizeOneAttack(const std::pair<int, int>& candidate) const
{
	std::pair<int, int> attackCandidate(-1, -1);
	// check up/down/left/right - option for attack for single coordinate

	updateCoordinates(attackCandidate, candidate.first - 1, candidate.second); // check up 
	if (isInAttackOptions(attackCandidate))
	{
		return attackCandidate;
	}
	updateCoordinates(attackCandidate, candidate.first + 1, candidate.second); // check down
	if (isInAttackOptions(attackCandidate)) {
		return attackCandidate;
	}
	updateCoordinates(attackCandidate, candidate.first, candidate.second - 1);
	if (isInAttackOptions(attackCandidate)) //check left
	{
		return attackCandidate;
	}

	updateCoordinates(attackCandidate, candidate.first, candidate.second + 1);
	if (isInAttackOptions(attackCandidate)) { // check right
		return attackCandidate;
	}

	// shouldnt get here
	updateCoordinates(attackCandidate, -1, -1);
	return attackCandidate;

}

std::pair<int, int>  PlayerSmart::nextAttackFromCoors(ShipInProcess& shipDetails, int numOfCoors) const
{
	std::pair<int, int> attackCandidate(-1, -1);

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

int PlayerSmart::addCoorToShipsInProcess(int row, int col, std::pair<int, int>* nextPairTosearch, AttackResult result) {

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

bool  PlayerSmart::isInBoard(int row, int col) const
{
	return (row > boardRows || row< 1 || col>boardCols || col < 1);
}

void PlayerSmart::mergeShipDetails(std::pair<int, int>* pair, int startIndex)
{
	int index = -1;
	std::vector<ShipInProcess>::iterator originalShipIndex = attackedShips.begin() + startIndex;

	// make sure that the nextPair to search is in board limits

	if (isInBoard(pair->first, pair->second))
	{
		index = findPairInAttackedShips(*pair, startIndex + 1);
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

bool PlayerSmart::isInAttackOptions(const std::pair<int, int>& coors) const
{
	auto it = attackOptions.find(coors);
	if (it != attackOptions.end())//coordinate was found in attackOptions
	{
		return true;
	}

	return false;
}

void PlayerSmart::removeAllIrreleventCoordinates(const std::pair<int, int>& pair, bool isVertical, bool isHorizontal)
{
	std::pair<int, int> removeCandidate;
	if (isVertical)
	{
		// remove left coordinate from attackOptions
		updateCoordinates(removeCandidate, pair.first, pair.second - 1);
		removeOneCoordinate(removeCandidate);
		// remove right coordinate from attackOptions
		updateCoordinates(removeCandidate, pair.first, pair.second + 1);
		removeOneCoordinate(removeCandidate);
	}

	if (isHorizontal)
	{
		// remove up coordinate
		updateCoordinates(removeCandidate, pair.first - 1, pair.second);
		removeOneCoordinate(removeCandidate);
		// remove down coordinate
		updateCoordinates(removeCandidate, pair.first + 1, pair.second);
		removeOneCoordinate(removeCandidate);

	}
}

void PlayerSmart::removeOneCoordinate(std::pair<int, int>& pairToDelete)
{
	auto it = attackOptions.find(pairToDelete);
	if (it != attackOptions.end())//coordinate was found in attackOptions and now we can erase it
	{
		attackOptions.erase(it);
	}
}


void PlayerSmart::notifyOnAttackResult(int player, int row, int col, AttackResult result)
{
	int mergeResult;
	std::pair<int, int> nextPairTosearch; // the candidate coor to merge with.( merging ships that already in the attackedShips after adding <row,col>)
	std::pair <int, int> attackedPair(row, col);
	std::pair<int, int> tmpPair(-1, -1);

	if (!isInAttackOptions(attackedPair)) { // the coordinate is mine/ already was handeld
		return;
	}

	if (result == AttackResult::Miss)
	{
		removeOneCoordinate(attackedPair);
		return;
	}

	// in case of sink / hit, find the cooresponding ship, merge coordinate with relevent ship and then 
	// remove irrelevent coordinates from attackOptions

	mergeResult = addCoorToShipsInProcess(row, col, &nextPairTosearch, result);
	//check if there is another ship in shipinprocess that belong's to the same ship we just updated
	if (mergeResult != -1)// the coordinate is added to one of the ships that are already in process 
	{
		mergeShipDetails(&nextPairTosearch, mergeResult);
		//remove all irrelevnt coordinates for future attack 
		for (int i = 0; i <attackedShips[mergeResult].shipSize; i++) {

			// remove environment of attack ship
			if (attackedShips[mergeResult].isVertical)
			{ // remove left, right
				updateCoordinates(tmpPair, attackedShips[mergeResult].incrementalCoors[i], col);
				removeAllIrreleventCoordinates(tmpPair, true, false);
			}
			else
			{// remove up,down
				updateCoordinates(tmpPair, row, attackedShips[mergeResult].incrementalCoors[i]);
				removeAllIrreleventCoordinates(tmpPair, false, true);
			}
		}
	}

	if (result == AttackResult::Sink)
	{
		if (mergeResult == -1) // the ship wasnt in process >> ship of size 1  
		{
			removeAllIrreleventCoordinates(attackedPair, true, true);
		}

		else {//ship of size>1 we remove unreleventCoors
			removeSankFromReleventCoors(mergeResult);
		}
	}
	removeOneCoordinate(attackedPair);

	// sort vector of attackedShips by size of the ship from largest ship to smallest ship - to create priority for larger ships 
	std::sort(attackedShips.begin(), attackedShips.end(),
		[](const ShipInProcess & a, const ShipInProcess & b) { return a.shipSize > b.shipSize; });

}


void PlayerSmart::removeSankFromReleventCoors(int indexOfPair)
{
	std::pair <int, int> coorsToDelete(0, 0);
	std::vector<ShipInProcess>::iterator ShipIndex;

	// for the second ship detail 
	if (attackedShips.at(indexOfPair).isVertical) {
		//remove edges of ship
		updateCoordinates(coorsToDelete, attackedShips.at(indexOfPair).getMinCoor() - 1, attackedShips.at(indexOfPair).getConstCoor());
		removeOneCoordinate(coorsToDelete);

		updateCoordinates(coorsToDelete, attackedShips.at(indexOfPair).getMaxCoor() + 1, attackedShips.at(indexOfPair).getConstCoor());
		removeOneCoordinate(coorsToDelete);
	}

	if (attackedShips.at(indexOfPair).isHorizontal) {
		//remove edges of ship
		updateCoordinates(coorsToDelete, attackedShips.at(indexOfPair).getConstCoor(), attackedShips.at(indexOfPair).getMinCoor() - 1);
		removeOneCoordinate(coorsToDelete);

		updateCoordinates(coorsToDelete, attackedShips.at(indexOfPair).getConstCoor(), attackedShips.at(indexOfPair).getMaxCoor() + 1);
		removeOneCoordinate(coorsToDelete);
	}

	// remove ships from vector
	ShipIndex = attackedShips.begin() + indexOfPair;
	attackedShips.erase(ShipIndex);

}


IBattleshipGameAlgo* GetAlgorithm()
{
	_instancesVec.push_back(new PlayerSmart());  // Create new instance and keep it in vector 
	return _instancesVec[_instancesVec.size() - 1];  // Return last instance
}