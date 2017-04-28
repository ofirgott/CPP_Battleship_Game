#pragma once
//this is a class that 3 dll (players algo) overrides
#include "IBattleshipGameAlgo.h"
#include "BattleshipBoard.h"
#include <vector>

static std::vector<IBattleshipGameAlgo *> _instancesVec; //our player collection

class Player : public IBattleshipGameAlgo
{

public:
	Player() : id(UNDEFINED_PLAYERID) {};					
	Player(const Player& otherPlayer) = delete;							/* deletes copy constructor */
	virtual ~Player() { for (auto it = _instancesVec.begin(); it != _instancesVec.end(); ++it) delete(*it); }
	Player& operator=(const Player& otherPlayer) = delete;				/* deletes the assignment operator - we want a player to be a Non Copyable object */
	

	void setBoard(int player, const char** board, int numRows, int numCols) override { id = player; playerBoard = BattleshipBoard(board, numRows, numCols); }

protected:
	int id;					// players id , if id == -1 player is invalid or undefined
	BattleshipBoard playerBoard;	// matrix of pointers to ships  
};

