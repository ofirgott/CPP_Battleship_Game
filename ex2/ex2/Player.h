#pragma once
//this is a class that 3 dll (players algo) overrides
#include "IBattleshipGameAlgo.h"
#include "BattleshipBoard.h"
#include <vector>

static std::vector<IBattleshipGameAlgo *> _instancesVec; //our player collection

class Player : public IBattleshipGameAlgo
{

public:
	Player() : id(UNDEFINED_PLAYERID), boardRows(-1), boardCols(-1) {};
	Player(const Player& otherPlayer) = delete;	/* deletes copy constructor */
	virtual ~Player() = default; 
	Player& operator=(const Player& otherPlayer) = delete;	/* deletes the assignment operator - we want a player to be a Non Copyable object */


protected:
	int id;					// players id , if id == -1 player is invalid or undefined
	int boardRows;
	int boardCols;
};

