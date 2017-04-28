#pragma once
//this is a class that 3 dll (players algo) overrides
#include "IBattleshipGameAlgo.h"
#include "Ship.h"

static std::vector<IBattleshipGameAlgo *> _instancesVec; //our player collection

class Player : public IBattleshipGameAlgo
{

public:
	Player() : id(UNDEFINED_PLAYERID), shipsBoardRows(0), shipsBoardCols(0) {};					// todo: we need to give the player his ID in the init function, and not in the cto'r
	Player(const Player& otherPlayer) = delete;							/* deletes copy constructor */
	virtual ~Player();
	Player& operator=(const Player& otherPlayer) = delete;				/* deletes the assignment operator - we want a player to be a Non Copyable object */
	

	void setBoard(int player, const char** board, int numRows, int numCols) override;


protected:
	int id;					// players id , if id == -1 player is invalid or undefined
	Ship***  shipsBoard;	// matrix of pointers to ships  
	int shipsBoardRows;
	int shipsBoardCols;

};

