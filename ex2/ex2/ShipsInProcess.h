#pragma once
#include <vector>

/*
*calss to represent the attacked opponent's ship's
*<row,col>
*utility class for smart player to reduce sorting and searching
*/
class ShipInProcess
{
	bool isVertical;
	int constantCoor;
	std::vector<int> incrementalCoors;
	friend class PlayerSmart;

public:
	/*todo:delete = and copy constructor*/
	ShipInProcess();
	~ShipInProcess();
	int getSize() const;
	bool getIsVertical() const;
	bool isExentionOfShip(int row, int col);
	bool isPartOfShip(int row, int col);
	void addCoordinate(int row, int col);
};