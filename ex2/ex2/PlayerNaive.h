#pragma once
#include "Player.h"


class PlayerNaive : public Player
{
public:
	PlayerNaive() : Player() {};
	~PlayerNaive() = default;

	std::pair<int, int> attack() override;
	bool init(const std::string& path) override;
	void notifyOnAttackResult(int player, int row, int col, AttackResult result) override {} //empty implementaion
	void setBoard(int player, const char** board, int numRows, int numCols) override;
	
private:
	std::vector<std::pair<int, int>> movesVector; // vector of moves
	std::vector<std::pair<int, int>>::const_iterator movesVectorItr;
	/* given origin update its coordinates to <row,col>*/
	static std::pair <int, int> updateCoordinatesNaive(std::pair<int, int>& origin, int row, int col) { origin.first = row; origin.second = col; return origin; }


};