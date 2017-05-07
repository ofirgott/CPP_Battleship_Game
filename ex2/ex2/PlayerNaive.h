#pragma once
#include "Player.h"

class PlayerNaive : public Player
{
public:
	std::pair<int, int> attack() override;
	bool init(const std::string& path) override;
	void notifyOnAttackResult(int player, int row, int col, AttackResult result) override {} //empty implementaion
	void setBoard(int player, const char** board, int numRows, int numCols) override;
private:
	std::vector<std::pair<int, int>> movesVector; // vector of moves
	std::vector<std::pair<int, int>>::const_iterator movesVectorItr;

};