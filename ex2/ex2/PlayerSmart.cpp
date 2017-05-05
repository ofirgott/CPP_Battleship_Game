#include "PlayerSmart.h"
#include <algorithm>

std::pair<int, int> PlayerSmart::attack()
{
	decltype(attackOptions)::iterator it; 
	std::pair<int, int> attackCandidate;
	std::set<std::pair<int, int>> currShip;
	int currShipSize; 

	if (size(shipsInProcess) ==0) // no ships in process 
	{

		return BattleshipGameUtils::randomElement(attackOptions.begin(), attackOptions.end());
		//do
		//{
		//	attackCandidate = getRandomCoordinatesInBoard();
		//	it = attackOptions.find(attackCandidate);
		//}
		//while (it == attackOptions.end()); // as long as attackCandidate not in attackOptions - find another coordinate/ 

		//return ;
	}

	// already have ships in shipsInProcess
	currShip = shipsInProcess[0];
	currShipSize = size(currShip);
	if (currShipSize == 1)
	{
		/* todo: check how to change this next lines!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
		it = currShip.begin();
		++it;
		return nextAttackFromOneCoor(*it);
	}

	return nextAttackFromFewCoors(currShip, currShipSize);
}

void PlayerSmart::notifyOnAttackResult(int player, int row, int col, AttackResult result)
{
	int mergeResult;
	std::pair<int, int> nextPairTosearch;
	std::pair <int,int> attackedPair =std::make_pair(row, col) ;

	if (result == AttackResult::Hit)
	{
		mergeResult = addCoorToShipsInProcess(row,col , &nextPairTosearch);
		if (mergeResult != -1)
		{
			mergeShipDetails(&nextPairTosearch, mergeResult);
			removeAllIrreleventCoordinates(attackedPair);
		}

		else{
			removeOneIrreleventCoordinate(attackedPair);
		}
		

	}

	else if (result == AttackResult::Sink)
	{
		
	}
	else // result == AttackResult::Miss
	{
		
	}
}

void PlayerSmart::mergeShipDetails(std::pair<int, int>* pair , int indexToupdate)
{
	/* todo: the for is on changing size!!! mayby change that*/
	decltype(shipsInProcess)::iterator shipsInprocessIter;

	for(int i =0 ; i< size(shipsInProcess);i++)
	{
		auto it = shipsInProcess[i].find(*pair);
		if (it != shipsInProcess[i].end())
		{
			shipsInProcess[indexToupdate].insert(std::make_pair(pair->first, pair->second));
			shipsInProcess.erase(shipsInprocessIter);
			break;
		}
		++shipsInprocessIter;
	}

}

std::pair<int, int> PlayerSmart::nextAttackFromOneCoor(const std::pair<int, int>& coordinates) const
{
	
	std::pair<int, int> attackCandidate;

	if (isInAttackOptions(attackCandidate = createLeft(coordinates))) // check left
	{
		return attackCandidate;
	}

	if (isInAttackOptions(attackCandidate = createRight(coordinates))) // check right
	{
		return attackCandidate;
	}

	if (isInAttackOptions(attackCandidate = createUp(coordinates))) //check up
	{
		return attackCandidate;
	}

	if (isInAttackOptions(attackCandidate = createDown(coordinates))) // check down
	{
		return attackCandidate;
	}

	// shouldnt get here
	return std::make_pair(-1,-1);


}

std::pair<int, int> PlayerSmart::nextAttackFromFewCoors(const std::set<std::pair<int, int>>& hitCoordinates, int numOfCoors) const
{
	std::pair<int, int> attackCandidate;
	std::vector<int> rows;
	std::vector<int> cols;

	if (numOfCoors< 1) { // shouldnt get here 
		return std::make_pair(-1, -1);
	}

	// extract all rows && columns coordinates
	for (auto& coor : hitCoordinates) {
		rows.push_back(coor.first);
		cols.push_back(coor.second);
	}

	// sort the vectors
	std::sort(rows.begin(), rows.end());
	std::sort(cols.begin(), cols.end());

	//check if ship is Horizontal
	if (isConstantCoors(rows, numOfCoors)) {
		if (isIncrementalCoors(cols, numOfCoors)) {
			if (isInAttackOptions(attackCandidate = std::make_pair(rows[0], cols[0] - 1))) // lowst possible coor
			{
				return attackCandidate;
			}

			if (isInAttackOptions(attackCandidate = std::make_pair(rows[0], cols[numOfCoors -1] + 1))){ // highest possible coor
				return attackCandidate;
			}

			return std::make_pair(-1, -1); // shouldnt get here
		}
	}

	//check if ship is vertical
	if (isConstantCoors(cols, numOfCoors)) {
		if (isIncrementalCoors(rows, numOfCoors)) {
			if (isInAttackOptions(attackCandidate = std::make_pair(rows[0]-1, cols[0]))) // lowst posible coor
			{
				return attackCandidate;
			}

			if (isInAttackOptions(attackCandidate = std::make_pair(rows[numOfCoors-1]+1, cols[0]))) { // highest posible coor
				return attackCandidate;
			}

			return std::make_pair(-1, -1); // shouldnt get here
		}
	}

	return std::make_pair(-1, -1); // shouldnt get here
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

bool PlayerSmart::isValidShipCoordinates(const std::set<std::pair<int, int>>& coordinates , int newRow , int newCol ,std::pair<int, int>* nextPair) const
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

		rows.push_back(newRow);
		cols.push_back(newCol);

		// sort the vecors
		std::sort(rows.begin(), rows.end());
		std::sort(cols.begin(), cols.end());

		//check if ship is Horizontal
		if (isConstantCoors(rows, shipSize)) {
			if (isIncrementalCoors(cols, shipSize)) {
				if (cols[0]==newCol) // the new coordinate is from the left side of the vector
				{
					nextPair->first = newRow;
					nextPair->second = newCol - 1;
				}
				else
				{
					nextPair->first = newRow;
					nextPair->second = cols[shipSize-1] +1 ; // the new coordinate is from the right side of the vctor
				}
				return true;
			}
		}

		//check if ship is vertical
		if (isConstantCoors(cols, shipSize)) {
			if (isIncrementalCoors(rows, shipSize)) {
				if (rows[0] == newRow) // the new coordinate is from the botton of the ship
				{
					nextPair->first = newRow -1;
					nextPair->second = newCol;
				}
				else
				{
					nextPair->first = rows[shipSize -1] +1;  // the new coordinate is on top of the vctor
					nextPair->second = newCol;
				}

				return true;
			}
		}

		return false;
}


void PlayerSmart::removeOneIrreleventCoordinate(std::pair<int,int>& pairToDelete)
{
	auto it = attackOptions.find(pairToDelete);
	if (it != attackOptions.end())
	{
		attackOptions.erase(it);
	}
}

int PlayerSmart::addCoorToShipsInProcess(int coorRow, int coorCol , std::pair<int, int>* nextPairTosearch )
{
	int i = 0;
	std::set<std::pair<int, int>> newSet;

	for (auto& details: shipsInProcess)
	{
		/*todo:  make sure details is a new copy and doesnt change the state os shipsInprocess */
		if (isValidShipCoordinates(details ,coorRow,coorCol, nextPairTosearch))
		{
			shipsInProcess[i].insert(std::make_pair(coorRow, coorCol));
			return i;
		}
		i++;
	}

	/*todo: make sure the newSet is really added to the vector*/
	// if got here the newPair doesnt belong to the ships that are processed now.
	newSet.insert(std::make_pair(coorRow, coorCol));
	shipsInProcess.push_back(newSet);
	return -1;
}



