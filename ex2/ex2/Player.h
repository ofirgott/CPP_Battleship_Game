#pragma once
//this is a class that 3 dll (players algo) overrides
#include "IBattleshipGameAlgo.h"
#include <vector>

static std::vector<IBattleshipGameAlgo *> _instancesVec; //our player collection

class Player : public IBattleshipGameAlgo
{

public:
	static const int UNDEFINED_PLAYERID = -1;
	

	Player() : id(UNDEFINED_PLAYERID), boardRows(-1), boardCols(-1) {};
	Player(const Player& otherPlayer) = delete;	/* deletes copy constructor */
	virtual ~Player() = default; 
	Player& operator=(const Player& otherPlayer) = delete;	/* deletes the assignment operator - we want a player to be a Non Copyable object */


protected:
	int id;					// players id , if id == -1 player is invalid or undefined
	int boardRows;
	int boardCols;
	static const int PLAYERID_A = 0;
	static const int PLAYERID_B  = 1;

};

