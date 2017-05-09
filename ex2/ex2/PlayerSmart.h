#pragma once
#include "Player.h"
#include "BattleshipGameUtils.h"
#include <vector>
#include <set>
#include "ShipInProcess.h"




class PlayerSmart : public Player
{

public:

	PlayerSmart();
	~PlayerSmart();
	bool init(const std::string& path) override;
	std::pair<int, int> attack() override;													// ask player for his move
	void notifyOnAttackResult(int player, int row, int col, AttackResult result) override;	// notify on last move result

private:

	std::set<std::pair<int, int>> attackOptions;
	std::vector<ShipInProcess> attackedShips;
	int myId;

	/*util function for attack
	* given a set of coordinates that belong to 1 ship return the next coordinate to attack
	*/
	std::pair<int, int> nextAttackFromCoors(ShipInProcess& shipDetails, int numOfCoors) const;



	void PlayerSmart::removeDetails(std::pair<int, int>& nextPair, int merge_result);
	void removeAllIrreleventCoordinates(const std::pair<int, int>& pair);
	/*util functions for attack*/

	///*given a ship with only one attacked coordinate, get the next candidate for attack
	// * assumes the given coordinate is not of a sank ship
	// */
	//std::pair<int, int> nextAttackFromOneCoor(const std::pair<int, int>& coordinates) const;

	/*
	*given origin update its coordinates to <row,col>
	*/
	static std::pair <int, int> updateCoordinates(std::pair<int, int>& origin, int row, int col)
	{
		origin.first = row;
		origin.second = col;
		return origin;
	}

	/*return true if the input pair is in attackoptions, false- otherwise
	* util function for: nextAttackFromOneCoor,
	*/
	bool isInAttackOptions(const std::pair<int, int>& coors) const;



	/*get details for ship , updates
	* updates rowcoors to point to a sorted vector of the ship's colnm coordinates
	*  updates colCoors to point to a sorted vector of the ship's row coordinates
	*  is_vertical = true if ship is vetical
	*  is_hotrizontal = true if ship is horizontal
	*/
	void updateDetailsAboutShip(const std::set<std::pair<int, int>>& allCoors, std::vector<int>* rowCoors,
		std::vector<int>* colCoors);
	bool produceNextPair(std::vector<int>& rows, std::vector<int>& cols, int currRow, int currCol, std::pair<int, int>* nextPair) const;
	int PlayerSmart::addCoorToShipsInProcess(int coorRow, int coorCol, std::pair<int, int>* nextPairTosearch, int sink);

	/* given index and pair. look for pair in all sets starting from index, if found, add pair
	* to the set in index indexToupdate and delete the set that holds the matching pair
	*/
	void PlayerSmart::mergeShipDetails(std::pair<int, int>* pair, int indexToupdate);
	void PlayerSmart::removeOneCoordinate(std::pair<int, int>& pairToDelete);

	/*todo: delete this functions from ship.h and from here && put it in utils calss and maybe change isValidShipCoors*/
	static bool isConstantCoors(const std::vector<int>& coors, int size);
	static bool isIncrementalCoors(const std::vector<int>& coors, int size);

	void removeSankShip();
};

