#pragma once

#include "IBattleshipGameAlgo.h"
#include "Ship.h"
#include "BattleshipBoard.h"
#include <windows.h>
#include "GamePlayerData.h"

typedef IBattleshipGameAlgo *(*GetAlgoFuncType)();

class BattleshipGameManager
{

public:

	static const int PLAYERID_A = 0;														/* default id for player A */
	static const int PLAYERID_B = 1;														/* default id for player B */
	static const int UNDEFINED_PLAYERID = -1;												/* default id for undefined or invalid player */

	/* todo: see if gamesucc bool is nessceary*/
	BattleshipGameManager(const BattleshipBoard& board, IBattleshipGameAlgo* algoA, IBattleshipGameAlgo* algoB) : mainBoard(board), playerAlgoA(algoA), playerAlgoB(algoB), gameSuccessfullyCreated(true) {}
	~BattleshipGameManager() = default;

	BattleshipGameManager() = delete;														/* deletes empty constructor */
	BattleshipGameManager(const BattleshipGameManager& otherGame) = delete;					/* deletes copy constructor */
	BattleshipGameManager& operator=(const BattleshipGameManager& otherGame) = delete;		/* deletes assignment constructor */


	bool isGameSuccessfullyCreated()const { return gameSuccessfullyCreated; }				/* we will check the variable in the main */
	void Run();																				/* given a game object, run's the game and outputs the results */



private:

	static const char A = 'A';																/* player char for player A - for printing */
	static const char B = 'B';																/* player char for player B */

	GamePlayerData playerA;																	/* an object that keeps all relevant data of playerA in the game */
	GamePlayerData playerB;																	/* an object that keeps all relevant data of playerB in the game */

	IBattleshipGameAlgo* playerAlgoA;														/* pointer to the algo of playerA - will deleted in **this** class destructor */
	IBattleshipGameAlgo* playerAlgoB;														/* pointer to the algo of playerB - will deleted in **this** class destructor */

	BattleshipBoard mainBoard;
	bool gameSuccessfullyCreated;

	static void outputGameResult(GamePlayerData* currPlayer, GamePlayerData* otherPlayer);
	

	bool initGamePlayers(const std::string& dllPathPlayerA, const std::string& dllPathPlayerB);

	bool BattleshipGameManager::loadAndInitPlayerDll(const std::string & dllPathPlayer, IBattleshipGameAlgo* &player, int playerId, HINSTANCE& hDll, Ship*** &shipsMatrix, size_t& shipsCnt)const;

	void sendAttackForPrint(std::pair<int, int> nextAttack, AttackResult attackRes)const;
};
