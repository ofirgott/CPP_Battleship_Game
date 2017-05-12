#pragma once
#include "../ex2/Player.h"
//#include "BattleshipGameUtils.h"
#include "ShipInProcess.h"
#include <vector>
#include <set>



class PlayerSmart : public Player
{

public:

	PlayerSmart():Player() {};
	~PlayerSmart() = default;
	PlayerSmart& operator=(const PlayerSmart& otherSmartPlayer) = delete;
	PlayerSmart(const PlayerSmart& otherSmartPlayer) = delete;

	void setBoard(int player, const char** board, int numRows, int numCols) override;
	bool init(const std::string& path) override{return (id != -1);}
	std::pair<int, int> attack() override;													// ask player for his move
	void notifyOnAttackResult(int player, int row, int col, AttackResult result) override;	// notify on last move result




private:

	std::vector<ShipInProcess> attackedShips;
	std::set<std::pair<int, int>> attackOptions;

	/*util function for attack
	* given a set of coordinates that belong to 1 ship return the next coordinate to attack
	*/
	std::pair<int, int> nextAttackFromCoors(ShipInProcess& shipDetails, int numOfCoors) const;
	int PlayerSmart::findPairInAttackedShips(const std::pair<int, int>& pairToSearch, int startIndex = 0);

	void removeAllIrreleventCoordinates(const std::pair<int, int>& pair, bool isVertical, bool isHorizontal);
	/*util functions for attack*/

	/*
	*given origin update its coordinates to <row,col>
	*/
	static std::pair <int, int> updateCoordinates(std::pair<int, int>& origin, int row, int col){ origin.first = row;origin.second = col;return origin;}

	/*return true if the input pair is in attackoptions, false- otherwise
	* util function for: nextAttackFromOneCoor,
	*/
	bool isInAttackOptions(const std::pair<int, int>& coors) const;

	int PlayerSmart::addCoorToShipsInProcess(int coorRow, int coorCol, std::pair<int, int>* nextPairTosearch, bool sink);

	/* given index and pair. look for pair in all sets starting from index, if found, add pair
	* to the set in index indexToupdate and delete the set that holds the matching pair
	*/
	void PlayerSmart::mergeShipDetails(std::pair<int, int>* pair, int indexToupdate);
	void PlayerSmart::removeOneCoordinate(std::pair<int, int>& pairToDelete);
	void removeSankFromReleventCoors(int merge_result, std::pair<int, int>* pair , std::pair<int, int>& attackedPair);
};

