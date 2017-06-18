#pragma once

#include "IBattleshipGameAlgo.h"
#include "Ship.h"
#include "BattleshipBoard.h"
#include "GamePlayerData.h"
#include "PlayerGameResultData.h"
#include <memory>
#include "BoardDataImpl.h"


typedef IBattleshipGameAlgo *(*GetAlgoFuncType)();

class BattleshipGameManager
{

public:

	static const int PLAYERID_A = 0;														/* default id for player A */
	static const int PLAYERID_B = 1;														/* default id for player B */
	static const int UNDEFINED_PLAYERID = -1;												/* default id for undefined or invalid player */

	
	BattleshipGameManager() = delete;														/* deletes empty constructor */

	
	BattleshipGameManager(const BattleshipBoard& board, std::unique_ptr<IBattleshipGameAlgo> algoA, std::unique_ptr<IBattleshipGameAlgo> algoB);
	~BattleshipGameManager() = default;

	BattleshipGameManager(const BattleshipGameManager& otherGame) = delete;					/* deletes copy constructor */
	BattleshipGameManager& operator=(const BattleshipGameManager& otherGame) = delete;		/* deletes assignment constructor */
	
	PlayerGameResultData Run();																/* given a game object, run's the game and outputs the results */

private:

	const BattleshipBoard& mainBoard;
	GamePlayerData playerA;																	/* an object that keeps all relevant data of playerA in the game */
	GamePlayerData playerB;																	/* an object that keeps all relevant data of playerB in the game */
	std::unique_ptr<IBattleshipGameAlgo> algorithmA;										/* unique ptr for this algoA instance. will deleted in destructor of this class */
	std::unique_ptr<IBattleshipGameAlgo> algorithmB;										/* unique ptr for this algoB instance. will deleted in destructor of this class */
	

	static const char A = 'A';																/* player char for player A - for printing */
	static const char B = 'B';																/* player char for player B */
	static const int WON = 1;
	static const int LOST = 0;

	
	/* the output result will always be from the perspective of playerA, the name of the player is unknown
	in the scope of this function ie the player's name in the return value will be the empty string
	the function wich invokes Run, will update the player's name to be PlayersA name
	*/
	static PlayerGameResultData outputGameResult(GamePlayerData* currPlayer, GamePlayerData* otherPlayer);
	
	
	/**
	 * \brief given playerId and player's boardData, call to algo setPlayer and setBoard. in addition, create the ships list and the shipsBoard of this player,
	 *  given the set of his shipsDetails 
	 */
	void initPlayerData(int playerId, IBattleshipGameAlgo* playerAlgo, std::set<std::pair<char,  std::set<Coordinate>>>& shipsDetails, ShipsBoard& playerShipBoard, const BoardDataImpl& playerBoardData)const;
};
