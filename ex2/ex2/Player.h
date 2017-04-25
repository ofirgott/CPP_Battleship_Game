#pragma once
//this is a class that 3 dll (players algo) overrides
#include "IBattleshipGameAlgo.h"
#include "Ship.h"

class Player : public IBattleshipGameAlgo
{

	static std::vector<IBattleshipGameAlgo *> _instancesVec; //our player collection

public:
	Player() : id(-1), tScore(0), cShips(0) {};					//todo: we need to give the player his ID in the init function, and not in the cto'r
	virtual ~Player();
	Player& operator=(const Player& otherPlayer) = delete;			/* deletes the assignment operator - we want a player to be a Non Copyable object */

	bool init(const std::string& path) override { return id != -1; }
	void setBoard(int player, const char** board, int numRows, int numCols) override;

	/* @return total score gained by player
	*/
	int getTScore()const { return tScore;  }

	/* @ return how much ships player has
	*/
	int getShipsCount()const { return cShips; }

	/*@ return - players id
	*/
	int getID()const { return id; }

	/* update players score to the prev score + num
	* @assume- num >= 0
	*/
	void updateScore(int points) { if(points > 0) tScore += points; }


protected:
	int id;				// players id , if id == -1 player is invalid or undefined
	int tScore;			// how much score the player gained this far
	Ship***  pBoard;	// matrix of pointers to ships  
	int cShips;			// number of ships player has


};

