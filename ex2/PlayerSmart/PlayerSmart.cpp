#include "PlayerSmart.h"
#include <algorithm>
#include "../ex2/BattleshipGameUtils.h"


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
					updateCoordinates(pairToInsert, coord.first, coord.second +1);
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
				updateCoordinates(pairToInsert,i,j);
				result.insert(pairToInsert);

				if (result.find(pairToInsert) == result.end()) {//checking it's not my ship/around it = it's not in result
					updateCoordinates(pairToInsert, i+1, j+1);
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
		return BattleshipGameUtils::randomElement(attackOptions.begin(), attackOptions.end());
	}
	// already have ships in shipsInProcess
	return nextAttackFromCoors(attackedShips[0], attackedShips[0].getSize());
}



std::pair<int, int>  PlayerSmart::nextAttackFromCoors(ShipInProcess& shipDetails, int numOfCoors) const
{
	std::pair<int, int> attackCandidate(-1, -1);

	if (numOfCoors < 1) {
		// shouldnt get here 
		return attackCandidate;
	}

	if (numOfCoors == 1)
	{ // check up/down/left/right
		attackCandidate = shipDetails.getFirstPair();
		updateCoordinates(attackCandidate, attackCandidate.first - 1, attackCandidate.second); // check down 
		if (isInAttackOptions(attackCandidate))
		{
			return attackCandidate;
		}
		updateCoordinates(attackCandidate, attackCandidate.first + 1, attackCandidate.second); // check up
		if (isInAttackOptions(attackCandidate)) { // highest posible coor
			return attackCandidate;
		}
		updateCoordinates(attackCandidate, attackCandidate.first, attackCandidate.second - 1);
		if (isInAttackOptions(attackCandidate)) //check left
		{
			return attackCandidate;
		}

		updateCoordinates(attackCandidate, attackCandidate.first, attackCandidate.second + 1);
		if (isInAttackOptions(attackCandidate)) { // check right
			return attackCandidate;
		}
	}

	// the ship has more then 1 coordinate
	if (shipDetails.isVertical) {
		updateCoordinates(attackCandidate, shipDetails.getMinCoor() - 1, shipDetails.getConstCoor()); // check down 
		if (isInAttackOptions(attackCandidate))
		{
			return attackCandidate;
		}
		updateCoordinates(attackCandidate, shipDetails.getMinCoor() + 1, shipDetails.getConstCoor()); // check up
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

	// shouldnt get here
	updateCoordinates(attackCandidate, -1, -1);
	return attackCandidate;
}


void PlayerSmart::notifyOnAttackResult(int player, int row, int col, AttackResult result)
{
	int mergeResult;
	std::pair<int, int> nextPairTosearch; // the candidate coor to merge with. 	
	//( merging ships that already in the attackedShips after adding the new coor)
	std::pair <int, int> attackedPair(row, col);

	if (!isInAttackOptions(attackedPair)) { // the coordinate is mine/ already was handeld
		return;
	}

	if (result == AttackResult::Hit)
	{
		mergeResult = addCoorToShipsInProcess(row, col, &nextPairTosearch, false);
		if (mergeResult != -1)// the coordinate is added to one of the ships that are already in process 
		{ // try to chekc if there is another shipdetails in process that belong to the same ship i just added.
			// make sure that the nextPair to search os in board limits
			if (( 1<= nextPairTosearch.first <= boardRows) && (1 <= nextPairTosearch.second <= boardCols))
			{
				mergeShipDetails(&nextPairTosearch, mergeResult);

				if (attackedShips[mergeResult].getSize() == 2)
				{
					// remove vertical/ horizontal like int the sink
					removeAllIrreleventCoordinates(attackedShips[mergeResult].getFirstPair(), attackedShips[mergeResult].getIsVertical(),
							attackedShips[mergeResult].getIsHorizontal());
				}
				
				removeAllIrreleventCoordinates(attackedPair, attackedShips[mergeResult].getIsVertical(),
													attackedShips[mergeResult].getIsHorizontal());
			}
		}

		removeOneCoordinate(attackedPair);
	}

	else if (result == AttackResult::Sink)
	{
		????if ((1 <=  nex tPairTosearch.first <= boardRows) && (1 <= nextPairTosearch.second <= boardCols))
		// find to whom it belongs and delete the set+ envi
		mergeResult = addCoorToShipsInProcess(row, col, &nextPairTosearch, true);
		if (mergeResult == -1) // the ship wasnt in process >> ship of size 1  
		{
			removeAllIrreleventCoordinates(attackedPair , true , true);
		}
		else
		{
			removeSankFromReleventCoors(mergeResult, &nextPairTosearch , attackedPair);

		}

		removeOneCoordinate(attackedPair);

	}
	else // result == AttackResult::Miss
	{
		removeOneCoordinate(attackedPair);
	}

	// sort vector of attackedShips by size of the ship from largest ship to smallest ship - to create priority for larger ships 
	std::sort(attackedShips.begin(), attackedShips.end(),
		[](const ShipInProcess & a, const ShipInProcess & b) { return a.getSize() > b.getSize(); });

}


int PlayerSmart::findPairInAttackedShips(const std::pair<int, int>& pairToSearch, int startIndex = 0) 
{
	int cnt = 0;
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

/* assume the ships handked here are of size at least 2*/
void PlayerSmart::removeSankFromReleventCoors(int firstIndex, std::pair<int, int>* pair, std::pair<int, int>& attackedPair)
{
	int indexOfPair = 0;
	std::pair <int, int> coorsToDelete (0,0);
	std::vector<ShipInProcess>::iterator ShipIndex;

	// find the index of the ship containing the pair(if there is such ) 
	indexOfPair = findPairInAttackedShips(*pair, firstIndex +1);

	if (attackedShips.at(firstIndex).getSize() == 2)
	{
		removeAllIrreleventCoordinates(attackedPair, true, true);
		removeAllIrreleventCoordinates(*pair, true, true);
		return;
	}

	// for ships that are of size  > 2 
	if (attackedShips.at(firstIndex).isVertical) {
		//remove edges of ship
		updateCoordinates(coorsToDelete, attackedShips.at(firstIndex).getMinCoor() - 1, attackedShips.at(firstIndex).getConstCoor());
		removeOneCoordinate(coorsToDelete);

		updateCoordinates(coorsToDelete, attackedShips.at(firstIndex).getMaxCoor() + 1, attackedShips.at(firstIndex).getConstCoor());
		removeOneCoordinate(coorsToDelete);

	}

	if (attackedShips.at(firstIndex).getIsHorizontal()) {
		//remove edges of ship
		updateCoordinates(coorsToDelete, attackedShips.at(firstIndex).getConstCoor() , attackedShips.at(firstIndex).getMinCoor() - 1);
		removeOneCoordinate(coorsToDelete);

		updateCoordinates(coorsToDelete, attackedShips.at(firstIndex).getConstCoor(), attackedShips.at(firstIndex).getMinCoor() + 1);
		removeOneCoordinate(coorsToDelete);

	}

	if (indexOfPair != -1)
	{
		// for the second ship detail 
		if (attackedShips.at(indexOfPair).isVertical) {
			//remove edges of ship
			updateCoordinates(coorsToDelete, attackedShips.at(indexOfPair).getMinCoor() - 1, attackedShips.at(indexOfPair).getConstCoor());
			removeOneCoordinate(coorsToDelete);

			updateCoordinates(coorsToDelete, attackedShips.at(indexOfPair).getMaxCoor() + 1, attackedShips.at(indexOfPair).getConstCoor());
			removeOneCoordinate(coorsToDelete);
		}

		if (attackedShips.at(indexOfPair).getIsHorizontal()) {
			//remove edges of ship
			updateCoordinates(coorsToDelete, attackedShips.at(indexOfPair).getConstCoor(), attackedShips.at(indexOfPair).getMinCoor() - 1);
			removeOneCoordinate(coorsToDelete);

			updateCoordinates(coorsToDelete, attackedShips.at(indexOfPair).getConstCoor(), attackedShips.at(indexOfPair).getMinCoor() + 1);
			removeOneCoordinate(coorsToDelete);

		}
		
	}


	if (indexOfPair != -1)
	{
		// remove ships from vector
		ShipIndex = attackedShips.begin() + indexOfPair;
		attackedShips.erase(ShipIndex);
	}

	ShipIndex = attackedShips.begin() + firstIndex;
	attackedShips.erase(ShipIndex);
}


void PlayerSmart::mergeShipDetails(std::pair<int, int>* pair, int indexToupdate)
{
	int index;
	std::vector<ShipInProcess>::iterator originalShipIndex = attackedShips.begin() + indexToupdate;
	
	index = findPairInAttackedShips(*pair , indexToupdate +1);
	if (index != -1)
	{

		originalShipIndex->megreShipsInProcess(attackedShips[index]);
		originalShipIndex = attackedShips.begin() + index;
		attackedShips.erase(originalShipIndex);
	}
}


/* given a coordinate search all ships in process and check if it belongs to one of the ships already in process
* if so , add it to the ship's details and return the index of the ship it was added to.
* if doesnt belong to non of them add a new ship of size 1 to shipsin process
*/
int PlayerSmart::addCoorToShipsInProcess(int row, int col, std::pair<int, int>* nextPairTosearch,bool sink) {

	int ret;
	int i = 0;
	ShipInProcess tempShip(row, col);

	for (auto& details : attackedShips)
	{
		ret = details.addCoordinate(row, col);
		if (ret != -1) // the coordinate was added to the ship, 
		{
			if (details.isVertical) // const columns
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
	// if the coordinate doesnt belong to any of the ships in process add a new ship
	if (sink == false)
	{
		attackedShips.push_back(tempShip);
	}

	return -1;
}


void PlayerSmart::removeAllIrreleventCoordinates(const std::pair<int, int>& pair, bool isVertical, bool isHorizontal)
{
	std::pair<int, int> removeCandidate;
	if (isVertical)
	{
		updateCoordinates(removeCandidate, pair.first, pair.second - 1);
		removeOneCoordinate(removeCandidate);
		updateCoordinates(removeCandidate, pair.first, pair.second + 1);
		removeOneCoordinate(removeCandidate);
	}

	if (isHorizontal)
	{
		updateCoordinates(removeCandidate, pair.first - 1, pair.second);
		removeOneCoordinate(removeCandidate);
		updateCoordinates(removeCandidate, pair.first + 1, pair.second);
		removeOneCoordinate(removeCandidate);

	}
}



bool PlayerSmart::isInAttackOptions(const std::pair<int, int>& coors) const
{
	auto it = attackOptions.find(coors);
	if (it != attackOptions.end())
	{
		return true;
	}

	return false;
}


void PlayerSmart::removeOneCoordinate(std::pair<int, int>& pairToDelete)
{
	auto it = attackOptions.find(pairToDelete);
	if (it != attackOptions.end())
	{
		attackOptions.erase(it);
	}
}

