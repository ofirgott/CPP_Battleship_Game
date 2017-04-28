#pragma once
#include "Player.h"


class PlayerFromFile : public Player
{
public:
	PlayerFromFile() : Player(), cAttack(0), isDone(false) {};	//todo: i want to use iterator instead

	std::pair<int, int> attack() override;

	bool init(const std::string& path) override;

	void notifyOnAttackResult(int player, int row, int col, AttackResult result) override {} //empty implementaion


private:
	int cAttack; // index of the next attack in pMoves		todo: maybe we want an iterator instead
	std::vector<std::pair<int, int>> pMoves; // vector of moves
	bool isDone; // if false player has more moves; true - no more moves	todo: maybe we want an iterator instead


};