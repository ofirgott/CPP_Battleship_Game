#pragma once

#include "IBattleshipGameAlgo.h"
#include "Ship.h"
#include "BattleshipBoard.h"
#include "Constants.h"

/* todo: 1.change the run() function to access the mainBoard. 2. the constructor shoul init utilGamePlayer ang not ibattelship game algo*/
class BattleshipGameManager
{
	/*keep all current algo details*/
	class UtilGamePlayer {
		friend class BattleshipGameManager;
		IBattleshipGameAlgo* attackAlgo;
		bool hasMoreMoves;
		int score;
		Ship *** shipsMatrix;
		int id;
		int shipsCount;
		int Rows;
		int Cols;

		UtilGamePlayer()
		{
			id = -1;
			hasMoreMoves = true;
			score = 0;
			shipsMatrix = nullptr;
			attackAlgo = nullptr;
			shipsCount = NUM_OF_PLAYER_SHIPS;
			Rows = -1;
			Cols = -1;
		}

		~UtilGamePlayer()
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
		void incrementScore(int value)
		{
			score += value;
		}

	};

	UtilGamePlayer* playerA;
	UtilGamePlayer* playerB;

	std::string boardFilePath;
	BattleshipBoard mainBoard;

	static void switchCurrPlayer(UtilGamePlayer** curr, UtilGamePlayer** other);

	static void outputGameResult(UtilGamePlayer* currPlayer, UtilGamePlayer* otherPlayer);

public:
	/*dont want empty constructor*/
	BattleshipGameManager() = delete;
	
	/*dont want copy constructor */
	BattleshipGameManager(const BattleshipGameManager& otherGame) = delete;
	
	/*dont want '=' operator*/
	BattleshipGameManager& operator=(const BattleshipGameManager& otherGame) = delete;
	
	/*	isGameSuccessfullyCreated - true if constructor succeded, false otherwise
		boardPath- path to the location of the game board
		probably should recive the dll's as well to construct the IBattelshupGameAlgo instances
	*/
	BattleshipGameManager(std::string boardPath ,bool& isGameSuccessfullyCreated);

	~BattleshipGameManager();

	/*given a game instance run's the game and outputs the results*/
	void Run() const;

	
};
