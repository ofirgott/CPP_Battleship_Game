#pragma once

#include "Ship.h"
#include "IBattleshipGameAlgo.h"

/*keeps all current algo details*/
class GamePlayerData {
	
	friend class BattleshipGameManager;

private:
	
	int id;
	IBattleshipGameAlgo* playerAlgo;
	bool hasMoreMoves;
	int score;
	Ship*** shipsMatrix;
	size_t currShipsCount;
	int boardRows;
	int boardCols;


	GamePlayerData() : id(UNDEFINED_PLAYERID), playerAlgo(nullptr), hasMoreMoves(true), score(0), shipsMatrix(nullptr), currShipsCount(0), boardRows(0), boardCols(0){}
	GamePlayerData(int playerID, IBattleshipGameAlgo* inputPlayerAlgo, Ship*** inputShipsMatrix, size_t shipsCount, int boardrows, int boardcols) : id(playerID), playerAlgo(inputPlayerAlgo), hasMoreMoves(true), score(0), shipsMatrix(inputShipsMatrix), currShipsCount(shipsCount), boardRows(boardrows), boardCols(boardcols) {}

	~GamePlayerData()
	{
		// todo: free the ship matrix here		
	}
	/*get next valid attack coordinates,if player doesnt have more moves return <-1,-1>*/
	std::pair<int, int> getAlgoNextAttack() const;

	/* given coordinates  player updates number of ships he has got left&& updates the attack in his ships details.
	return the attack result and the number of pointes the attack scored
	if player attacked the same coordinate in the second time return <Hit, -1> to indicate that the player shoudnt keep his turn
	*/
	std::pair<AttackResult, int> realAttack(std::pair<int, int> coor);

	/* update players score to the prev score + num
	assume- num >= 0
	*/
	void incrementScore(int value) { if(value > 0) score += value; }

	bool isSet()const { return (id >= 0 && playerAlgo && shipsMatrix && currShipsCount > 0 && boardRows > 0 && boardCols > 0); }

};