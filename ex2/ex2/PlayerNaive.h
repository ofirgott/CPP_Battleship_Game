#pragma once
#include "Player.h"


class PlayerNaive : public Player
{
public:
	PlayerNaive() : Player() {};
	~PlayerNaive() = default;

	/* ask player for his move, the attacked pair returned, if no more attackes the pair (-1,-1) is returned*/
	std::pair<int, int> attack() override;

	/* checking the initialization of the board was successful */
	bool init(const std::string& path) override;

	/* notify on last move result*/
	void notifyOnAttackResult(int player, int row, int col, AttackResult result) override {} //empty implementaion

	/* given a board update the vector attackOptions with all the options for attack ordered from left to right, 
	first line till last- attack by this order */
	void setBoard(int player, const char** board, int numRows, int numCols) override;
	
private:

	/*a vector of all the coordinates that are optional for attack by order*/
	std::vector<std::pair<int, int>> movesVector; 

	/*iterator for movesVector*/
	std::vector<std::pair<int, int>>::const_iterator movesVectorItr;

	/* given origin update its coordinates to <row,col>*/
	static std::pair <int, int> updateCoordinatesNaive(std::pair<int, int>& origin, int row, int col) { origin.first = row; origin.second = col; return origin; }
};