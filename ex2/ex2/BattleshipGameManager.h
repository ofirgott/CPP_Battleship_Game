#pragma once

#include "IBattleshipGameAlgo.h"
#include "Ship.h"
#include "BattleshipBoard.h"
#include "Constants.h"

class BattleshipGameManager
{
	/*keep all current algo details*/
	class UtilGamePlayer {
		friend class BattleshipGameManager;
	private:
		IBattleshipGameAlgo* playerAlgo;
		bool hasMoreMoves;
		int score;
		Ship*** shipsMatrix;
		int currShipsCount;

		UtilGamePlayer() : playerAlgo(nullptr), hasMoreMoves(true), score(0), shipsMatrix(nullptr), currShipsCount(0) {}
		UtilGamePlayer(IBattleshipGameAlgo* inputPlayerAlgo, Ship*** inputShipsMatrix, int shipsCount) : playerAlgo(inputPlayerAlgo), hasMoreMoves(true), score(0), shipsMatrix(inputShipsMatrix), currShipsCount(shipsCount){}

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
		void incrementScore(int value) { score += value; }
	
	};

private: 
	UtilGamePlayer* playerA;
	UtilGamePlayer* playerB;
	
	std::string inputdirPath;
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
