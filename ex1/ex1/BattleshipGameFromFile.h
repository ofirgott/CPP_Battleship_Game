#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "IBattleshipGameAlgo.h"


class BattleshipGameFromFile: public IBattleshipGameAlgo {
private:
	int current_score;
	std::string* battle_board;
	std::ifstream attack_file;

public:
	BattleshipGameFromFile(const std::string &dir_path);
	virtual ~BattleshipGameFromFile() = default;
	virtual void setBoard(const char** board, int numRows, int numCols) override; // called once to notify player on his board
	virtual std::pair<int, int> attack() override; // ask player for his move
	virtual void notifyOnAttackResult(int player, int row, int col, AttackResult result) override; // notify on last move result
};