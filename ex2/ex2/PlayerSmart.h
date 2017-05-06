#pragma once
#include "Player.h"
#include "BattleshipGameUtils.h"

class PlayerSmart: public Player
{
	
public:
	
	PlayerSmart();
	~PlayerSmart(); 
	bool init(const std::string& path) override;	
	std::pair<int, int> attack() override;													// ask player for his move



	void notifyOnAttackResult(int player, int row, int col, AttackResult result) override;	// notify on last move result

private:

	std::set<std::pair<int, int>> attackOptions;
	std::vector<std::set<std::pair<int, int>>> shipsInProcess;

	void PlayerSmart::mergeShipDetails(std::pair<int, int>* pair, int indexToupdate);
	std::pair<int, int> nextAttackFromOneCoor(const std::pair<int, int>& coordinates) const;
	/*todo: this function is too long and has code repetitions fix it!!! */
	std::pair<int, int> nextAttackFromFewCoors(const std::set<std::pair<int, int>>& hitCoordinates , int numOfCoors) const;

	/*create a new pair with one coordinate duffront from origin*/
	static std::pair <int, int> createLeft(const std::pair<int, int> origin)
	{
		return std::make_pair(origin.first, (origin.second - 1));
	}

	static std::pair <int, int> createRight(const std::pair<int, int> origin)
	{
		return std::make_pair(origin.first, (origin.second + 1));
	}

	static std::pair <int, int> createUp(const std::pair<int, int> origin)
	{
		return std::make_pair((origin.first +1), origin.second);
	}

	static std::pair <int, int> createDown(const std::pair<int, int> origin)
	{
		return std::make_pair((origin.first -1), origin.second);
	}

	/*true if the input pair is in attackoptions set, false- otherwise*/
	bool isInAttackOptions(const std::pair<int, int>& coors) const;

	int PlayerSmart::addCoorToShipsInProcess(int coorRow, int coorCol, std::pair<int, int>* nextPairTosearch);

	/*todo: delete this functions from ship.h and from here && put it in utils calss and maybe change isValidShipCoors*/
	static bool isConstantCoors(const std::vector<int>& coors, int size);
	static bool isIncrementalCoors(const std::vector<int>& coors, int size);
	bool PlayerSmart::isValidShipCoordinates(const std::set<std::pair<int, int>>& coordinates, int newRow, int newCol, std::pair<int, int>*) const;

	void PlayerSmart::removeOneIrreleventCoordinate(std::pair<int, int>& pairToDelete);
};

