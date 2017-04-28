#pragma once
#include "Player.h"


class PlayerFromFile : public Player
{
public:
	PlayerFromFile() : Player(), isDone(false) {};	//todo: i want to use iterator instead

	std::pair<int, int> attack() override;

	bool init(const std::string& path) override;

	void notifyOnAttackResult(int player, int row, int col, AttackResult result) override {} //empty implementaion


private:
	std::vector<std::pair<int, int>> movesVector; // vector of moves
	std::vector<std::pair<int, int>>::const_iterator movesVectorItr;
	bool isDone; // if false player has more moves; true - no more moves	


};