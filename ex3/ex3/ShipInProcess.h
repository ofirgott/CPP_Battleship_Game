#pragma once
#include <vector>
# include "IBattleshipGameAlgo.h"

/*
*class to represent the attacked opponent's ship's
*<row,col,depth>
*if the row is not constant the ship is vertical
*if the col is not constant the ship is horizontal
*if the din is not constant the ship is dimentional
*utility class for smart player to reduce sorting and searching
*/
class ShipInProcess
{

	friend class PlayerSmart;

	bool isVertical;
	bool isHorizontal;
	bool isDimentional;
	Coordinate constantCoors; //for shipInProcess of size>1 we have 2 const coordinates , the non constant coor will be set to -1
	Coordinate firstCoordinate; // first Coordinate added to the ship (in case of size one ship- representes the entire ship)
	std::vector<int> incrementalCoors;//ship coordinates (only the non const part of every Coordinate)
	int shipSize;//current ship size

	/* update the state of the inner Fields of the shipinproccess.assumes ship has 1 coordinate and firstcoor<secondCoor*/
	void ShipInProcess::updateInnerFields(bool vertical, bool horizontal, bool dimensional, int firstCoor, int secondCoor);

	/* assumes the ship is of size 1, if coordinate belongs to the ship add and return 1, else return -1*/
	int addToSizeOneShip(int row, int col, int depth);

	/* merge Ships Vectors, assumse mainVector size>1 */
	static std::vector<int> mergeShipsVectors(const std::vector<int>& mainVector, const Coordinate& addCoor, bool horizontal, bool vertical);

	/* given Coordinate add it to the ship's internal representation if the coordinates
	* belongs to this ship. return 1 if added Coordinate to the Ship, else return -1*/
	int addCoordinate(int row, int col, int depth);

	/* return true if coordinate(row,col,depth) belongs to ship, elsereturn false*/
	bool isPartOfShip(int row, int col, int depth) const;

	/* given other ship that it's coordinates belong to this ship, add its details to this ship*/
	void megreShipsInProcess(ShipInProcess& otherShip);

	/* assumes called for ships with size bigger then 1*/
	int getMaxCoor() const { return incrementalCoors[shipSize - 1]; };
	int getMinCoor() const { return incrementalCoors[0]; };
	Coordinate getConstCoors() const { return constantCoors; };

public:
	ShipInProcess() = delete; // dont allow ships with no coordinates
	ShipInProcess(int row, int col, int depth) : isVertical(true), isHorizontal(true), isDimentional(true), constantCoors(-1, -1, -1), firstCoordinate(row, col, depth), shipSize(1) {}
	~ShipInProcess() = default;
};
