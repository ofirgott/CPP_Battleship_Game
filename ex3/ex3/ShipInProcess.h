#pragma once
#include <vector>
# include "IBattleshipGameAlgo.h" // for Coordinate

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

	bool isVertical; 
	bool isHorizontal; 
	bool isDimentional; 
	Coordinate constantCoors; //for shipInProcess of size>1 we have 2 const coordinates , the non constant coor will be set to -1
	Coordinate firstCoordinate; // first COordinate added to the ship (in case of size one ship- representes the ship)
	std::vector<int> incrementalCoors;//ship coordinates (only the non const part of every Coordinate)
	int shipSize;//current ship size

	/* update the state of the inner Fields of the shipinproccess
	 * assumes ship has 1 coordinate
	 */
	//todo: assume firstcoor<secondCoor
	void ShipInProcess::updateInnerFields(bool vertical, bool horizontal, bool dimensional, int firstCoor, int secondCoor);


	/* assumes the ship is of size 1, if belongs to the ship add and return 1, else return -1*/
	int addToSizeOneShip(int row, int col,int dimention);
//
//	/* merge Ships Vectors, assumse mainVector size>1 */
//	static std::vector<int> mergeShipsVectors(const std::vector<int>& mainVector, const std::pair<int, int>& addPair, bool vertical);

	friend class PlayerSmart;
public:

	ShipInProcess() = delete; // dont allow ships with no coordinates
	ShipInProcess(int row, int col, int depth) : isVertical(true), isHorizontal(true),isDimentional(true), constantCoors(-1,-1,-1), firstCoordinate(row, col,depth), shipSize(1) {}
	~ShipInProcess() {} //todo: maybe need to free Coordinate? 


	///* given Coordinate add it to the ship's internal representation if the coordinates
	//* belongs to this ship. return 1 if added Coordinate to the Ship, else return -1
	//*/
	//int addCoordinate(int row, int col);

	///* return true if coordinate <row,col> belongs to ship, elsereturn false*/
	//bool isPartOfShip(int row, int col) const;


	///* given another ship the it'scoordinates belong to be, add its details to my ship*/
	//void megreShipsInProcess(ShipInProcess& otherShip);

	/* assumes called for ships with size bigger then 1*/
	int getMaxCoor() const { return incrementalCoors[shipSize - 1]; };
	int getMinCoor() const { return incrementalCoors[0]; };
	Coordinate getConstCoor() const { return constantCoors; };
	//std::pair<int, int> getConstCoor() const { return constantCoor; }; // do we need to edit the returned coordinate? 



}; 
