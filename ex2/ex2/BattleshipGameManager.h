#pragma once

#include "IBattleshipGameAlgo.h"
#include "Ship.h"
#include "BattleshipBoard.h"
#include "Constants.h"
#include <windows.h>

typedef IBattleshipGameAlgo *(*GetAlgoFuncType)();
//GetAlgoFuncType getShapeFunc;

class BattleshipGameManager
{
	/*keep all current algo details*/
	class UtilGamePlayer {
		friend class BattleshipGameManager;
	private:
		int id;
		IBattleshipGameAlgo* playerAlgo;
		bool hasMoreMoves;
		int score;
		Ship*** shipsMatrix;
		int currShipsCount;

		UtilGamePlayer() : id(-1), playerAlgo(nullptr), hasMoreMoves(true), score(0), shipsMatrix(nullptr), currShipsCount(0) {}
		UtilGamePlayer(int playerID, IBattleshipGameAlgo* inputPlayerAlgo, Ship*** inputShipsMatrix, int shipsCount) : id(playerID), playerAlgo(inputPlayerAlgo), hasMoreMoves(true), score(0), shipsMatrix(inputShipsMatrix), currShipsCount(shipsCount){}

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


public:
	
	BattleshipGameManager() = delete;														/* deletes empty constructor */
	BattleshipGameManager(const BattleshipGameManager& otherGame) = delete;					/* deletes copy constructor */	
	BattleshipGameManager& operator=(const BattleshipGameManager& otherGame) = delete;		/* deletes assignment constructor */

	/*	isGameSuccessfullyCreated - true if constructor succeded, false otherwise
	boardPath- path to the location of the game board
	*/
	BattleshipGameManager(std::string boardPath, bool& isGameSuccessfullyCreated);

	~BattleshipGameManager();

	
	void Run() const;			/* given a game instance run's the game and outputs the results */

private:

	std::vector<std::tuple<int, HINSTANCE, GetAlgoFuncType>> dll_vec; // vector of <playerID, dll handle, GetAlgorithm function ptr>

	UtilGamePlayer* playerA;
	UtilGamePlayer* playerB;
	
	std::string inputdirPath;
	std::string boardFilePath;
	
	BattleshipBoard mainBoard;

	static void switchCurrPlayer(UtilGamePlayer** curr, UtilGamePlayer** other);
	static void outputGameResult(UtilGamePlayer* currPlayer, UtilGamePlayer* otherPlayer);
	
};
