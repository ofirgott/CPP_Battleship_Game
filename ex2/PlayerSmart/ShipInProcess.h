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
	bool isHorizontal;
	int constantCoor;
	std::vector<int> incrementalCoors;
	std::pair<int, int> firstPair;
	int shipSize;
	friend class PlayerSmart;

	int addToSizeOneShip(int row, int col);
public:
	/*todo:delete = and copy constructor*/

	ShipInProcess() = delete;
	ShipInProcess(int row, int col);
	~ShipInProcess();

	int getSize() const;

	const std::pair<int, int>& getFirstPair()const
	{
		return firstPair;
	}

	bool getIsVertical() const;
	bool getIsHorizontal() const;
	//bool isExentionOfShip(int row, int col) const;

	bool isPartOfShip(int row, int col) const;

	int addCoordinate(int row, int col);

	/* assumes called for ships larger then 1 coordinate*/
	int getMaxCoor() const;
	int getMinCoor() const;
	int getConstCoor() const;

	/* for ships of size 1*/
	std::pair<int, int> getFirstPair() const
	{
		return firstPair;
	}

	/* given another ship, add its details to my ship*/
	void megreShipsInProcess(ShipInProcess otherShip);
};