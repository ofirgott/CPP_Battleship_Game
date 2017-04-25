#pragma once
//this is a class that 3 dll (players algo) overrides
#include "IBattleshipGameAlgo.h"
#include "Ship.h"

class Player : public IBattleshipGameAlgo
{

	static std::vector<IBattleshipGameAlgo *> _instancesVec; //our player collection

public:
	Player(int playerId = -1) : id(playerId) {};//todo: enter the other members to the init list!!!!!!!!!
	virtual ~Player();
	bool init(const std::string& path) override { return id != -1; }
	void setBoard(int player, const char** board, int numRows, int numCols) override;

protected:
	int id;				// players id , if id == -1 player is invalid 
	int tScore;			// how much score the player gained this far
	Ship***  pBoard;	// matrix of pointers to ships  
	int cShips;			// number of ships player has
};

