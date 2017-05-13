#pragma once
#include "../ex2/Player.h"
//#include "BattleshipGameUtils.h"
#include "ShipInProcess.h"
#include <vector>
#include <set>



class PlayerSmart : public Player
{
		friend class testPlayerSmart;//////////////////////////////////////////////////////////////delete!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

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


	/* given a coordinate search all ships in process and check if it belongs to one of them.
	* if so , add it to the ship's details and return the index of the ship (in the vector) it was added to.
	* if doesnt belong to any of them and the ship didnt sink add a new ship of size 1 to shipsinprocess && return -1
	*/
	int PlayerSmart::addCoorToShipsInProcess(int coorRow, int coorCol, std::pair<int, int>* nextPairTosearch, AttackResult result);

	/* given a coordinate check all the coordinates (up/down/lwft/rgiht) and attack them if werent attacked yet.*/
	std::pair<int, int> PlayerSmart::sizeOneAttack(const std::pair<int, int>& candidate) const;


	/*util function for attack
	* given a set of coordinates that belong to 1 ship return the next coordinate to attack
	*/
	std::pair<int, int>  PlayerSmart::nextAttackFromCoors(ShipInProcess& shipDetails, int numOfCoors) const;

	/* given start index and pair. look for pair in all sets starting from index, if found, add pair
	* to the ship at index and delete the ship that holds the matching pair
	*/
	void PlayerSmart::mergeShipDetails(std::pair<int, int>* pair, int indexToupdate);

	/* given pair and start index, check if pair belongs to any of the attacked ships
	 * if found return 1, else -1.
	 */
	int PlayerSmart::findPairInAttackedShips(const std::pair<int, int>& pairToSearch, int startIndex = 0);

	/* given origin update its coordinates to <row,col>*/
	static std::pair <int, int> updateCoordinates(std::pair<int, int>& origin, int row, int col) { origin.first = row; origin.second = col; return origin; }

	/*return true if the input pair is in attackoptions, false- otherwise
	* util function for attack
	*/
	bool PlayerSmart::isInAttackOptions(const std::pair<int, int>& coors) const;
	
	/* given a coordinate removefrom attackOptions is exists*/
	void PlayerSmart::removeOneCoordinate(std::pair<int, int>& pairToDelete);

	/*remove the adjecent coordinates to pair. i.e if ship isvertical remove left,right coordinates to pair etc..  */
	void  PlayerSmart::removeAllIrreleventCoordinates(const std::pair<int, int>& pair, bool isVertical, bool isHorizontal);

	/* assume the ships handked here are of size at least 2*/
	void PlayerSmart::removeSankFromReleventCoors(int indexOfPair);
};

