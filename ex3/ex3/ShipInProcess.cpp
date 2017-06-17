#pragma once
#include "ShipInProcess.h"

void ShipInProcess::updateInnerFields(bool vertical, bool horizontal, bool dimensional, int firstCoor, int secondCoor)
{
	isVertical = vertical;
	isHorizontal = horizontal;
	isDimentional = dimensional;

	// insert to incrementalCoors vector<firstCoor,secondCoor>
	incrementalCoors.push_back(firstCoor);
	incrementalCoors.push_back(secondCoor);
	shipSize += 1;

	if (isVertical)
	{ // col & depth are constant
		constantCoors.col = firstCoordinate.col;
		constantCoors.depth = firstCoordinate.depth;
		return;
	}

	if (isHorizontal)
	{ // row & depth are constant
		constantCoors.row = firstCoordinate.row;
		constantCoors.depth = firstCoordinate.depth;
		return;
	}

	if (isDimentional)
	{
		// row & col are constant
		constantCoors.row = firstCoordinate.row;
		constantCoors.col = firstCoordinate.col;
		return;
	}
}

int ShipInProcess::addToSizeOneShip(int row, int col, int depth)
{
	if ((row == firstCoordinate.row) && depth == firstCoordinate.depth) // if horizontal
	{
		if (col == firstCoordinate.col + 1) {// if incremental
			updateInnerFields(false, true, false, firstCoordinate.col, col);
			return 1;
		}

		if (col == firstCoordinate.col - 1) // decremental
		{
			updateInnerFields(false, true, false, col, firstCoordinate.col);
			return 1;
		}
	}

	if ((col == firstCoordinate.col) && (depth == firstCoordinate.depth)) //vertical
	{
		if (row == firstCoordinate.row + 1) { //  incremental
			updateInnerFields(true, false, false, firstCoordinate.row, row);
			return 1;
		}

		if (row == firstCoordinate.row - 1) // decremental
		{
			updateInnerFields(true, false, false, row, firstCoordinate.row);
			return 1;
		}
	}

	if ((col == firstCoordinate.col) && (row == firstCoordinate.row)) // dimentional
	{
		if (depth == firstCoordinate.depth + 1) { // incremental
			updateInnerFields(false, false, true, firstCoordinate.depth, depth);
			return 1;
		}

		if (depth == firstCoordinate.depth - 1) // decremental
		{
			updateInnerFields(false, false, true, depth, firstCoordinate.depth);
			return 1;
		}
	}
	return -1;
}

bool ShipInProcess::isPartOfShip(int row, int col, int depth) const
{
	if (shipSize == 1)
	{
		return ((row == firstCoordinate.row) && (col == firstCoordinate.col) && (depth == firstCoordinate.depth));
	}
	if (isVertical)
	{ // col and depth are constant
		return ((col == constantCoors.col) && (depth == constantCoors.depth) && (row <= incrementalCoors[shipSize - 1]) && (row >= incrementalCoors[0]));
	}
	if (isDimentional)
	{ // row and col are constant
		return ((col == constantCoors.col) && (row == constantCoors.row) && (depth <= incrementalCoors[shipSize - 1]) && (depth >= incrementalCoors[0]));
	}
	// ship is horizontal - only case left
	//row and deppth are constant
	return ((depth == constantCoors.depth) && (row == constantCoors.row) && (col <= incrementalCoors[shipSize - 1]) && (col >= incrementalCoors[0]));
}

int ShipInProcess::addCoordinate(int row, int col, int depth)
{
	//if coor alredy exists in ship
	if (isPartOfShip(row, col, depth)) {
		return 0;
	}

	if (shipSize == 1)
	{
		return addToSizeOneShip(row, col, depth);
	}

	// ship is larger then 1
	if (isVertical)
	{
		if ((col == constantCoors.col) && (depth == constantCoors.depth))
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
	}

	if (isHorizontal)
	{
		if ((row == constantCoors.row) && (depth == constantCoors.depth))
		{
			if (col == incrementalCoors[0] - 1) //left
			{
				incrementalCoors.insert(incrementalCoors.begin(), col);
				shipSize += 1;
				return 1;
			}
			if (col == incrementalCoors[shipSize - 1] + 1) //right
			{
				incrementalCoors.push_back(col);
				shipSize += 1;
				return 1;
			}
		}

	}

	if (isDimentional)
	{
		if ((row == constantCoors.row) && (col == constantCoors.col))
		{
			if (depth == incrementalCoors[0] - 1) //left
			{
				incrementalCoors.insert(incrementalCoors.begin(), depth);
				shipSize += 1;
				return 1;
			}
			if (depth == incrementalCoors[shipSize - 1] + 1) //right
			{
				incrementalCoors.push_back(depth);
				shipSize += 1;
				return 1;
			}
		}

	}

	// the given coordinate doesnt belong to this ship
	return -1;
}

std::vector<int> ShipInProcess::mergeShipsVectors(const std::vector<int>& mainVector, const Coordinate& addCoor, bool horizontal, bool vertical)
{
	std::vector<int> tmpVector = mainVector;

	if (vertical)
	{
		if (addCoor.row == tmpVector[0] - 1)
		{
			tmpVector.insert(tmpVector.begin(), addCoor.row);
		}
		if (addCoor.row == tmpVector[tmpVector.size() - 1] + 1) {
			tmpVector.push_back(addCoor.row);//merging the vectores
		}
	}

	else if (horizontal)
	{ // ship is horizontal
		if (addCoor.col == tmpVector[0] - 1)
		{
			tmpVector.insert(tmpVector.begin(), addCoor.col);
		}
		if (addCoor.col == tmpVector[tmpVector.size() - 1] + 1)
		{
			tmpVector.push_back(addCoor.col);//merging the vectores
		}
	}

	else
	{
		if (addCoor.depth == tmpVector[0] - 1)
		{
			tmpVector.insert(tmpVector.begin(), addCoor.depth);
		}
		if (addCoor.depth == tmpVector[tmpVector.size() - 1] + 1)
		{
			tmpVector.push_back(addCoor.depth);//merging the vectores
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
			addToSizeOneShip(otherShip.firstCoordinate.row, otherShip.firstCoordinate.col, otherShip.firstCoordinate.depth);
		}
		else
		{	// add many coordinates to ship of size one
			incrementalCoors = mergeShipsVectors(otherShip.incrementalCoors, firstCoordinate, otherShip.isHorizontal, otherShip.isVertical);
			shipSize = shipSize + otherShip.shipSize;
			constantCoors = otherShip.constantCoors;
			isVertical = otherShip.isVertical;
			isHorizontal = otherShip.isHorizontal;
		}
		return;
	}

	if (otherShip.shipSize == 1)
	{// add one coordinate to large ship
		incrementalCoors = mergeShipsVectors(incrementalCoors, otherShip.firstCoordinate, isHorizontal, isVertical);
		shipSize = shipSize + otherShip.shipSize;
		return;
	}

	//add many coordinates to many coordinates.
	if (incrementalCoors[shipSize - 1] < otherShip.incrementalCoors[0])
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