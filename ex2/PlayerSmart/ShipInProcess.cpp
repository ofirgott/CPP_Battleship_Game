#pragma once

#include "ShipInProcess.h"
#include <algorithm>


void ShipInProcess::updateInnerFields(bool vertical , bool horizontal , int constCoor , int firstCoor, int secondCoor)
{
	isVertical = vertical;
	isHorizontal = horizontal;
	constantCoor = constCoor;
	incrementalCoors.push_back(firstCoor);
	incrementalCoors.push_back(secondCoor);
	shipSize += 1;
}

int ShipInProcess::addToSizeOneShip(int row, int col)
{
	// check if ship is horizontal and if so update inner state
	if (row == firstPair.first)
	{
		if (col == firstPair.second + 1) {
			updateInnerFields(false, true, row, firstPair.second, col);
			return 1;
		}

		if (col == firstPair.second - 1)
		{
			updateInnerFields(false, true, row, col, firstPair.second);
			return 1;
		}
	}

	// check if ship is vertical and if so update inner state
	if (col == firstPair.second)
	{
		if (row == firstPair.first + 1) { // ship is vertical
			updateInnerFields(true, false, col, firstPair.first, row);
			return 1;
		}

		if (row == firstPair.first - 1)
		{
			updateInnerFields(true, false, col,row, firstPair.first);
			return 1;
		}
	}

	return -1;
}

bool ShipInProcess::isPartOfShip(int row, int col) const
{
	if (shipSize == 1)
	{
		return ((row == firstPair.first) && (col == firstPair.second));
	}

	if (isVertical)
	{
		return ( (col == constantCoor) &&   (row <= incrementalCoors[shipSize - 1]) && ( row >= incrementalCoors[0]));
	}

	// ship is horizontal
	return ((row == constantCoor) && (col <= incrementalCoors[shipSize - 1]) && (col >= incrementalCoors[0]));
}

int ShipInProcess::addCoordinate(int row, int col)
{
	if (shipSize == 1)
	{
		return addToSizeOneShip(row, col);
	}

	// ship is larger then 1
	if (isVertical)
	{
		if (row == incrementalCoors[0] - 1) // is up
		{
			incrementalCoors.insert(incrementalCoors.begin(), row);
			shipSize += 1;
			return 1;
		}
		if (row == incrementalCoors[shipSize - 1] + 1) // is down
		{
			incrementalCoors.push_back(row);
			shipSize += 1;
			return 1;
		}
	}

	if (isHorizontal) 
	{
		if (col == incrementalCoors[0] - 1)
		{
			incrementalCoors.insert(incrementalCoors.begin(), col);
			shipSize += 1;
			return 1;
		}
		if (col == incrementalCoors[shipSize - 1] + 1)
		{
			incrementalCoors.push_back(col);
			shipSize += 1;
			return 1;
		}
	}

	// the given coordinate doesnt belong to this ship
	return -1;
}



std::vector<int> ShipInProcess::mergeShipsVectors(const std::vector<int>& mainVector, const std::pair<int, int>& addPair , bool vertical)
{
	std::vector<int> tmpVector = mainVector;

	if (vertical)
	{
		if (addPair.first < tmpVector[0])
		{
			tmpVector.insert(tmpVector.begin(), addPair.first);
		}
		else
		{
			tmpVector.push_back(addPair.first);
		}
	}

	else
	{ // ship is horizontal
		if (addPair.second < tmpVector[0])
		{
			tmpVector.insert(tmpVector.begin(), addPair.second);
		}
		else
		{
			tmpVector.push_back(addPair.second);
		}
	}

	return tmpVector;

}

void ShipInProcess::megreShipsInProcess(ShipInProcess& otherShip)
{

	std::vector<int> mergedVector;

	if (shipSize == 1)
	{
		if (otherShip.shipSize == 1)
		{ 
			addToSizeOneShip(otherShip.firstPair.first, otherShip.firstPair.second);
		}
		else
		{	// add many coordinates to ship of size one
			incrementalCoors = mergeShipsVectors(otherShip.incrementalCoors, firstPair , otherShip.isVertical );
			shipSize = shipSize + otherShip.shipSize;
			constantCoor = otherShip.constantCoor;
			isVertical = otherShip.isVertical;
			isHorizontal = otherShip.isHorizontal;
		}
	}

	if (otherShip.shipSize == 1)
	{// add one coordinate to large ship
		incrementalCoors = mergeShipsVectors(incrementalCoors, otherShip.firstPair, isVertical );
		shipSize = shipSize + otherShip.shipSize;
	}

	//add many coordinates to many coordinates.
	if (incrementalCoors[shipSize -1] < otherShip.incrementalCoors[0])
	{// first vector has larger coordinates
		incrementalCoors.insert(incrementalCoors.end(), otherShip.incrementalCoors.begin(), otherShip.incrementalCoors.end());
	}
	else
	{ // second vector has larger coordinates
		mergedVector.insert(mergedVector.begin(), otherShip.incrementalCoors.begin(), otherShip.incrementalCoors.end());
		mergedVector.insert(mergedVector.end(), incrementalCoors.begin(), incrementalCoors.end());
		incrementalCoors = mergedVector;
	}
	// update size
	shipSize += otherShip.shipSize;
}


