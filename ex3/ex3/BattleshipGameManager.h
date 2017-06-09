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
	//BattleshipGameManager(BattleshipGameManager&&);//todo - move constractor

	bool isGameSuccessfullyCreated()const { return gameSuccessfullyCreated; }				/* we will check the variable in the main */
	StandingsTableEntryData Run();																				/* given a game object, run's the game and outputs the results */



private:

	static const char A = 'A';																/* player char for player A - for printing */
	static const char B = 'B';																/* player char for player B */
	BattleshipBoard mainBoard;
	GamePlayerData playerA;																	/* an object that keeps all relevant data of playerA in the game */
	GamePlayerData playerB;																	/* an object that keeps all relevant data of playerB in the game */

	IBattleshipGameAlgo* playerAlgoA;														/* pointer to the algo of playerA - will deleted in **this** class destructor */
	IBattleshipGameAlgo* playerAlgoB;														/* pointer to the algo of playerB - will deleted in **this** class destructor */

	static const int WON = 1;
	static const int LOST = 0;

	bool gameSuccessfullyCreated;
	/* the output result will always be from the perspective of playerA, the name of the player is unknown
	in the scope of this function ie the player's name in the return value will be the empty string
	the function wich invokes Run, will update the player's name to be PlayersA name
	*/
	static StandingsTableEntryData outputGameResult(GamePlayerData* currPlayer, GamePlayerData* otherPlayer);
	
	
	bool initGamePlayers(const std::string& dllPathPlayerA, const std::string& dllPathPlayerB);

	bool BattleshipGameManager::loadAndInitPlayerDll(const std::string & dllPathPlayer, IBattleshipGameAlgo* &player, int playerId, HINSTANCE& hDll, Ship*** &shipsMatrix, size_t& shipsCnt)const;

	void sendAttackForPrint(std::pair<int, int> nextAttack, AttackResult attackRes)const;
};
