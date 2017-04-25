#pragma once
#include "Player.h"
#include "Ship.h"

class PlayerFromFile : public Player
{
public:
	PlayerFromFile() : Player() {};
	~PlayerFromFile() { Ship::deleteShipMatrix(pBoard);  }

	std::pair<int, int> attack() override;

	void notifyOnAttackResult(int player, int row, int col, AttackResult result) = 0;	// notify on last move result



};