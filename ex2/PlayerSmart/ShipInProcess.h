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
	int constantCoor;//for a specific ship in size>2 we have a const coordinate (first/second)
	std::vector<int> incrementalCoors;//ship coordinates (only the none const part of every pair)
	std::pair<int, int> firstPair;//first pair added to ship (in case of size one ship- representes the ship)
	int shipSize;//current ship size

	/* update the states of the inner Fields of the shipinproccess*/
	void ShipInProcess::updateInnerFields(bool vertical, bool horizontal, int constCoor, int firstCoor, int secondCoor);

	/* assumes the ship is of size 1, if belongs to the ship add and return 1, else return -1*/
	int addToSizeOneShip(int row, int col);

	/* merge Ships Vectors, assumse mainVector size>1 */
	static std::vector<int> mergeShipsVectors(const std::vector<int>& mainVector, const std::pair<int, int>& addPair, bool vertical);

	friend class PlayerSmart;
public:

	ShipInProcess(int row, int col) : isVertical(true), isHorizontal(true), constantCoor(-1), firstPair(row, col), shipSize(1) {}
	~ShipInProcess() {}
	ShipInProcess() = delete;

	/* given <row,col> add it to the ship's internal representation if the coordinates
	* belong to this ship and return 1, else return -1
	*/
	int addCoordinate(int row, int col);

	/* return true if coordinate <row,col> belongs to ship, elsereturn false*/
	bool isPartOfShip(int row, int col) const;


	/* given another ship the it'scoordinates belong to be, add its details to my ship*/
	void megreShipsInProcess(ShipInProcess& otherShip);

	/* assumes called for ships larger then 1 coordinate*/
	int getMaxCoor() const { return incrementalCoors[shipSize - 1]; };
	int getMinCoor() const { return incrementalCoors[0]; };
	int getConstCoor() const { return constantCoor; };




};