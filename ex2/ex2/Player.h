#pragma once
//this is a class that 3 dll (players algo) overrides
#include "IBattleshipGameAlgo.h"
#include "Ship.h"

static std::vector<IBattleshipGameAlgo *> _instancesVec; //our player collection

class Player : public IBattleshipGameAlgo
{

public:
	Player() : id(UNDEFINED_PLAYERID), cShips(0) {};					// todo: we need to give the player his ID in the init function, and not in the cto'r
	Player(const Player& otherPlayer) = delete;							/* deletes copy constructor */
	virtual ~Player();
	Player& operator=(const Player& otherPlayer) = delete;				/* deletes the assignment operator - we want a player to be a Non Copyable object */
	

	void setBoard(int player, const char** board, int numRows, int numCols) override;

	/* @ returns how much ships player has*/
	int getShipsCount()const { return cShips; }	//todo: maybe we want to delete this funtion???

	/* return player ID */
	int getID()const { return id; }				//todo: maybe we want to delete this funtion???


protected:
	int id;					// players id , if id == -1 player is invalid or undefined
	Ship***  shipsBoard;	// matrix of pointers to ships  
	int cShips;				// number of ships player has todo: check if needed, or we want this only in the game manager


};

