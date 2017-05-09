#pragma once
#include "ShipInProcess.h"


ShipInProcess::ShipInProcess(int row, int col)
{
	isVertical = true;
	isHorizontal = true;
	constantCoor = -1;
	firstPair.first = row;
	firstPair.second = col;
	shipSize = 1;
}

ShipInProcess::~ShipInProcess()
{
	incrementalCoors.clear();
}

int ShipInProcess::getSize() const
{
	return shipSize;
}

bool ShipInProcess::getIsVertical() const
{
	return isVertical;
}

bool ShipInProcess::getIsHorizontal() const
{
	return isHorizontal;
}

//bool ShipInProcess::isExentionOfShip(int row, int col) const
//{
//	if (shipSize ==1)
//	{
//		if (row == firstPair.first)
//		{
//			if((col == firstPair.second +1) || (col == firstPair.second -1))
//			{
//				return true;
//			}
//		}
//
//		else if (col == firstPair.second)
//		{
//			if ((row == firstPair.first + 1) || (row == firstPair.first - 1))
//			{
//				return true;
//			}
//			
//		}
//		else
//		{
//			return false;
//		}
//	}
//	// for ship larger then 1 its vertical || horizontal
//
//	if (isVertical)
//	{
//		// the columns should be constant
//		if (col != constantCoor)
//		{
//			return false;
//		}
//
//		// the rows should be incremental
//		if ((row != incrementalCoors[getSize() - 1] + 1) && (row != incrementalCoors[0] - 1))
//		{
//			return false;
//		}
//	}
//	else
//	{ // the ship is horizontal
//	  // the rows should be constant
//		if (row != constantCoor)
//		{
//			return false;
//		}
//		if ((col != incrementalCoors[getSize() - 1] + 1) && (col != incrementalCoors[0] - 1))
//		{
//			return false;
//		}
//
//	}
//	return true;
//}
//
//bool ShipInProcess::isPartOfShip(int row, int col) const
//{
//	if (isVertical)
//	{
//		if (col != constantCoor)
//		{
//			return false;
//		}
//		if (row < (incrementalCoors[0]))
//		{
//			return false;
//		}
//		if (row >(incrementalCoors[getSize() - 1]))
//		{
//			return false;
//		}
//	}
//
//	else
//	{
//		if (row != constantCoor)
//		{
//			return false;
//		}
//
//		if (col < (incrementalCoors[0]))
//		{
//			return false;
//		}
//
//		if (col >(incrementalCoors[getSize() - 1]))
//		{
//			return false;
//		}
//	}
//
//	return true;
//}

int ShipInProcess::addCoordinate(int row, int col)
{
	if (shipSize == 1)
	{
		// check if ship is horizontal and if so update inner state
		if (row == firstPair.first)
		{
			if (col == firstPair.second + 1) {
				isVertical = false;
				isHorizontal = true;
				constantCoor = row;
				incrementalCoors.push_back(firstPair.second);
				incrementalCoors.push_back(col);
				shipSize += 1;
				return 1;
			}

			if (col == firstPair.second - 1)
			{
				isVertical = false;
				isHorizontal = true;
				shipSize += 1;
				constantCoor = row;
				incrementalCoors.push_back(col);
				incrementalCoors.push_back(firstPair.second);
				return 1;
			}

		}

		if (col == firstPair.first)
		{
			if (row == firstPair.first + 1) { // ship is vertical
				isVertical = true;
				isHorizontal = false;
				constantCoor = col;
				incrementalCoors.push_back(firstPair.first);
				incrementalCoors.push_back(row);
				shipSize += 1;
				return 1;
			}

			if (row == firstPair.second - 1)
			{
				isVertical = true;
				isHorizontal = false;
				constantCoor = col;
				incrementalCoors.push_back(row); // the new row is smaller then the existing
				incrementalCoors.push_back(firstPair.first);
				shipSize += 1;
				return 1;
			}
		}

		return -1;
	}

	// ship is larger then 1
	if (isVertical)
	{
		if (row == incrementalCoors[0] - 1)
		{
			std::vector<int>::iterator it;
			it = incrementalCoors.begin();
			incrementalCoors.insert(it, row);
			shipSize += 1;
			return 1;
		}
		if (row == incrementalCoors[getSize() - 1] + 1)
		{
			incrementalCoors.push_back(row);
			shipSize += 1;
			return 1;
		}
	}

	if (isHorizontal) // the ship is horizontal
	{
		if (col == incrementalCoors[0] - 1)
		{
			std::vector<int>::iterator it;
			it = incrementalCoors.begin();
			incrementalCoors.insert(it, col);
			shipSize += 1;
			return 1;
		}
		if (col == incrementalCoors[getSize() - 1] + 1)
		{
			incrementalCoors.push_back(col);
			shipSize += 1;
			return 1;
		}
	}

	// the given coordinate doesnt belong to this ship
	return -1;
}


int ShipInProcess::getMaxCoor() const
{

	return incrementalCoors[getSize() - 1];
}

int ShipInProcess::getMinCoor() const
{
	return incrementalCoors[0];
}



int ShipInProcess::getConstCoor() const
{
	return constantCoor;
}
