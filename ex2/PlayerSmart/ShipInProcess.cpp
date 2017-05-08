#pragma once
#include "ShipInProcess.h"


ShipInProcess::ShipInProcess()
{
	isVertical = false;
	constantCoor = -1;
}

ShipInProcess::~ShipInProcess()
{
	incrementalCoors.clear();
}

int ShipInProcess::getSize() const
{
	return incrementalCoors.size();
}

bool ShipInProcess::getIsVertical() const
{
	return isVertical;
}

bool ShipInProcess::isExentionOfShip(int row, int col)
{

	if (isVertical)
	{
		// the columns should be constant
		if (col != constantCoors[0])
		{
			return false;
		}

		// the rows should be incremental
		if ((row != incrementalCoors[getSize() - 1] + 1) && (row != incrementalCoors[0] - 1))
		{
			return false;
		}
	}
	else
	{ // the ship is horizontal
	  // the rows should be constant
		if (row != constantCoors[0])
		{
			return false;
		}
		if ((col != incrementalCoors[getSize() - 1] + 1) && (col != incrementalCoors[0] - 1))
		{
			return false;
		}

	}
	return true;
}

bool ShipInProcess::isPartOfShip(int row, int col)
{
	if (isVertical)
	{
		if (col != constantCoor)
		{
			return false;
		}
		if (row < (incrementalCoors[0]))
		{
			return false;
		}
		if (row >(incrementalCoors[getSize() - 1]))
		{
			return false;
		}
	}

	else
	{
		if (row != constantCoor)
		{
			return false;
		}

		if (col < (incrementalCoors[0]))
		{
			return false;
		}

		if (col >(incrementalCoors[getSize() - 1]))
		{
			return false;
		}
	}

	return true;
}

void ShipInProcess::addCoordinate(int row, int col)
{
	if (isVertical)
	{
		if (row == incrementalCoors[0] - 1)
		{
			std::vector<int>::iterator it;
			it = incrementalCoors.begin();
			incrementalCoors.insert(it, row);
		}
		if (row == incrementalCoors[getSize() - 1] + 1)
		{
			incrementalCoors.push_back(row);
		}
	}

	else // the ship is horizontal
	{
		if (col == incrementalCoors[0] - 1)
		{
			std::vector<int>::iterator it;
			it = incrementalCoors.begin();
			incrementalCoors.insert(it, col);
		}
		if (col == incrementalCoors[getSize() - 1] + 1)
		{
			incrementalCoors.push_back(col);
		}
	}
}
