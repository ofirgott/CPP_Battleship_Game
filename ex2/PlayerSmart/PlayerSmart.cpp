#include "PlayerSmart.h"
#include <algorithm>
#include "../ex2/BattleshipGameUtils.h"


void PlayerSmart::setBoard(int player, const char ** board, int numRows, int numCols)
{
	std::set<std::pair<int, int>> result;
	std::set<std::pair<char, std::set<std::pair<int, int>>>> setOfShipsDetails;

	id = player;
	boardRows = numRows;
	boardCols = numCols;
	BattleshipBoard boardTemp(board, numRows, numCols);
	if (!boardTemp.isSuccessfullyCreated()) {
		id = -1;
	}
	if (id != -1) {

		setOfShipsDetails = boardTemp.ExtractShipsDetails();
		std::set<std::pair<int, int>> coordOfCurrentShip;
		auto it = setOfShipsDetails.begin();
		while (it != setOfShipsDetails.end())
		{
			for (auto coord : it->second) {//for every ship we add each of her coord and around it
				result.insert(coord);
				if (coord.first + 1 <= numRows) {//down
					result.insert(std::make_pair(coord.first + 1, coord.second));
				}
				if (coord.first - 1 > 0) {//up
					result.insert(std::make_pair(coord.first - 1, coord.second));
				}
				if (coord.second + 1 <= numCols) {//right
					result.insert(std::make_pair(coord.first, coord.second + 1));
				}
				if (coord.second - 1 > 0) {//left
					result.insert(std::make_pair(coord.first, coord.second - 1));
				}
			}
			++it;
		}
		for (int i = 0; i < numRows; i++) {
			for (int j = 0; j < numCols; j++) {
				if (result.find(std::make_pair(i, j)) == result.end()) {//checking it's not my ship/around it = it's not in result
					attackOptions.insert(std::make_pair(i + 1, j + 1));//adding to the set of option for attack 
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
			if (( 1<= nextPairTosearch.first <= numOfRows) && (1 <= nextPairTosearch.second <= numOfCols))
			{
				mergeShipDetails(&nextPairTosearch, mergeResult);

				if (attackedShips[mergeResult].getSize() == 2)
				{
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

	for (auto details : attackedShips)
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


//
//void PlayerSmart::removeDetails(std::pair<int, int>& nextPair, int merge_result)
//{
//	std::pair<int, int> removePair(-1, -1);
//	std::vector<int> rows;
//	std::vector<int> cols;
//
//	// finds where the last coordinate is 
//	decltype(shipsInProcess)::iterator shipsInprocessIter;
//	? shipsInProcess.begin();
//	// the iterator doesnt sta\rt from the cooerct place 
//	for (int i = merge_result; i< size(shipsInProcess); i++)
//	{
//		auto it = shipsInProcess[i].find(nextPair);
//		if (it != shipsInProcess[i].end())
//		{
//			shipsInProcess[merge_result].insert(nextPair);
//			shipsInProcess.erase(shipsInprocessIter);
//			break;
//		}
//		++shipsInprocessIter;
//	}
//
//	when i merge 2 sets need to remove vertical / horizontal for all the members
//		updateDetailsAboutShip(shipsInProcess[merge_result], &rows, &cols);
//	if (isHorizontal)
//	{
//		updateCoordinates(removePair, rows[0], cols[0] - 1);
//		removeOneCoordinate(removePair);
//		updateCoordinates(removePair, rows[0], cols[size(cols) - 1] + 1);
//		removeOneCoordinate(removePair);
//	}
//
//	else if (isVertical)
//	{
//		updateCoordinates(removePair, rows[0] - 1, cols[0]);
//		removeOneCoordinate(removePair);
//		updateCoordinates(removePair, rows[size(rows)] + 1, cols[0]);
//		removeOneCoordinate(removePair);
//	}
//
//
//
//	? shipsInprocessIter->begin();
//	//erase the ship from vector
//
//
//}




//
//
//void PlayerSmart::updateDetailsAboutShip(const std::set<std::pair<int, int>>&allCoors, std::vector<int>* rowCoors, std::vector<int>* colCoors)
//{
//	int shipsSize = size(allCoors);
//	// extract all rows && columns coordinates
//	for (auto& coor : allCoors) {
//		rowCoors->push_back(coor.first);
//		colCoors->push_back(coor.second);
//	}
//	// sort the vectors
//	std::sort(rowCoors->begin(), rowCoors->end());
//	std::sort(colCoors->begin(), colCoors->end());
//
//	//check if ship is Horizontal
//	if (isConstantCoors(*rowCoors, shipsSize)) {
//		if (isIncrementalCoors(*colCoors, shipsSize)) {
//			isHorizontal = true;
//		}
//	}
//
//	//check if ship is vertical
//	if (isConstantCoors(*colCoors, shipsSize)) {
//		if (isIncrementalCoors(*rowCoors, shipsSize)) {
//			isVertical = true;
//		}
//	}
//}


bool PlayerSmart::isInAttackOptions(const std::pair<int, int>& coors) const
{
	auto it = attackOptions.find(coors);
	if (it != attackOptions.end())
	{
		return true;
	}

	return false;
}

bool PlayerSmart::isConstantCoors(const std::vector<int>& coors, int size)
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

bool PlayerSmart::isIncrementalCoors(const std::vector<int>& coors, int size)
{
	int prevCoor;
	if (size < 1) { // invalid number of cordinates
		return false;
	}

	//check if the coordinates are incremental 
	prevCoor = coors[0];
	for (auto i = 1; i < size; i++) {
		if (coors[i] != (prevCoor + 1)) {
			return false;
		}
		prevCoor += 1;
	}
	return true;
}



///*check if the rows, and colsrepresent a legal ship if so , check from which side the coordinates of the ships
//* are forming a sequence. and update  nextPair to hold the other side of the attacked coordinate
//* and return true, otherwise return false
//*/
//bool PlayerSmart::produceNextPair(std::vector<int>& rows, std::vector<int>& cols,
//	int currRow, int currCol, std::pair<int, int>* nextPair) const
//{
//	int shipSize = size(rows);
//
//	// ship must contain at least 1 coordinate to exist
//	if (shipSize< 1) {
//		return false;
//	}
//
//	//check if ship is Horizontal
//	if (isHorizontal) {
//		if (cols[0] == currCol) // the new coordinate added on the left of the ship
//		{
//			updateCoordinates(*nextPair, currRow, currCol - 1);
//			//nextPair->first = currRow;
//			//nextPair->second = currCol - 1;
//		}
//		else {
//			updateCoordinates(*nextPair, currRow, cols[shipSize - 1] + 1);
//			//nextPair->first = currRow;
//			//nextPair->second = cols[shipSize-1] +1 ; // the new coordinate is from the right side of the vctor
//		}
//		return true;
//	}
//
//	//check if ship is vertical
//	if (isVertical) {
//		if (rows[0] == currRow) // the new coordinate is from the top of the ship
//		{
//			updateCoordinates(*nextPair, currRow - 1, currCol);
//			//nextPair->first = currRow - 1;
//			//nextPair->second = currCol;
//
//		}
//		else
//		{
//			updateCoordinates(*nextPair, rows[shipSize - 1] + 1, currCol);
//			//nextPair->first = rows[shipSize - 1] + 1;  // the new coordinate is from the bottom
//			//nextPair->second = currCol;
//		}
//
//		return true;
//	}
//	return false;
//
//}


void PlayerSmart::removeOneCoordinate(std::pair<int, int>& pairToDelete)
{
	auto it = attackOptions.find(pairToDelete);
	if (it != attackOptions.end())
	{
		attackOptions.erase(it);
	}
}

