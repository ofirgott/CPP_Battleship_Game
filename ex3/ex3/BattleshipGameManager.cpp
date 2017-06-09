#include "BattleshipGameManager.h"
#include "BattleshipGameUtils.h"
#include "GamePlayerData.h"
#include <iostream>
#include "StandingsTableEntryData.h"


StandingsTableEntryData BattleshipGameManager::Run()
{
	Coordinate nextAttack(-1,-1,-1);
	std::pair<AttackResult, int> attackRes;

	GamePlayerData* currPlayer = &playerA;
	GamePlayerData* otherPlayer = &playerB;


	// as long as one of the players has more moves and no one won
	while (currPlayer->hasMoreMoves || otherPlayer->hasMoreMoves) {

		if (!currPlayer->hasMoreMoves) {
			// if current player doesnt have anymore moves continue to next player
			std::swap(currPlayer, otherPlayer);
			continue;
		}

		nextAttack = currPlayer->getAlgoNextAttack();
		if (nextAttack.row == -1 && nextAttack.col == -1 && nextAttack.depth == -1) {
			// current player finished
			currPlayer->hasMoreMoves = false;
			continue;
		}
		// if got here the attack coordinates are in the board 

		// attack other player 
		attackRes = otherPlayer->realAttack(nextAttack);

		if (attackRes.first == AttackResult::Miss) {
			// the opponent doesnt have a ship in this coordinates; check if attacked myself
			attackRes = currPlayer->realAttack(nextAttack);

			sendAttackForPrint(nextAttack, attackRes.first);

			if (attackRes.first != AttackResult::Miss) { // currPlayer attacked himself
														 // the other player gets points
				otherPlayer->incrementScore(attackRes.second);
			}

			currPlayer->playerAlgo->notifyOnAttackResult(currPlayer->id, nextAttack, attackRes.first);
			otherPlayer->playerAlgo->notifyOnAttackResult(currPlayer->id, nextAttack, attackRes.first);
			// pass turn to other player- if missed || if attacked myself

			std::swap(currPlayer, otherPlayer);
			//check if someone won
			if ((currPlayer->currShipsCount == 0) || (otherPlayer->currShipsCount == 0)) {
				break;
			}
		}
		else {
			sendAttackForPrint(nextAttack, attackRes.first);


			if (attackRes.second == -1) {	// hit opponents ship but not in a new coordinate; switch turns

				std::swap(currPlayer, otherPlayer);
			}
			else {
				currPlayer->incrementScore(attackRes.second);
				currPlayer->playerAlgo->notifyOnAttackResult(currPlayer->id, nextAttack, attackRes.first);
				otherPlayer->playerAlgo->notifyOnAttackResult(currPlayer->id, nextAttack, attackRes.first);
				// keep my turn 
			}

			//check if someone won
			if ((currPlayer->currShipsCount == 0) || (otherPlayer->currShipsCount == 0)) { 
				break;
			}
		}

	}

	// prints game results 
	
	return outputGameResult(currPlayer, otherPlayer);

}


StandingsTableEntryData BattleshipGameManager::outputGameResult(GamePlayerData* currPlayer, GamePlayerData* otherPlayer)
{

	int currScore;
	int otherScore;


	if (currPlayer->currShipsCount == 0) {
		if (currPlayer->id == PLAYERID_A) { // currPlayer is playerA
		//	 "Player B won" 
			return StandingsTableEntryData("", LOST, WON, currScore, otherScore);
		}
		else { // otherPlayer is playerA
		//	 "Player A won" 
			return StandingsTableEntryData("", WON, LOST, otherScore, currScore);
		}
	}

	if (otherPlayer->currShipsCount == 0) {
		if (otherPlayer->id == PLAYERID_A) { // otherPlayer is playerA
			//	 "Player B won" 
			return StandingsTableEntryData("", LOST, WON, otherScore, currScore);
		}
		else {// currPlayer is playerA
			//	 "Player A won" 
			return StandingsTableEntryData("", WON, LOST, currScore, otherScore);
		}
	}

}


bool BattleshipGameManager::loadAndInitPlayerDll(const std::string & dllPathPlayer, IBattleshipGameAlgo* &player, int playerId, HINSTANCE& hDll, Ship*** &shipsMatrix, size_t& shipsCnt)const
{
	hDll = LoadLibraryA(dllPathPlayer.c_str()); // Notice: Unicode compatible version of LoadLibrary
	if (!hDll)
	{
		std::cout << "Cannot load dll: " << dllPathPlayer << std::endl;
		return false;
	}
	// Get function pointer
	auto getAlgoFunc = (GetAlgoFuncType)GetProcAddress(hDll, "GetAlgorithm");
	if (!getAlgoFunc)
	{
		std::cout << "Cannot load dll: " << dllPathPlayer << std::endl;
		return false;
	}
	player = getAlgoFunc();
	const char** tmpPlayerMat = mainBoard.createPlayerBoard(playerId);

	BattleshipBoard tmpBoardForPlayer(tmpPlayerMat, mainBoard.getRows(), mainBoard.getCols());

	if (!tmpBoardForPlayer.isSuccessfullyCreated()) return false;

	player->setBoard(playerId, tmpPlayerMat, tmpBoardForPlayer.getRows(), tmpBoardForPlayer.getCols());

	// create a set containing all ships details i.e letter and coordinated for each ship (extract from board)
	auto allShipsDetails = tmpBoardForPlayer.ExtractShipsDetails();

	BattleshipBoard::deleteMatrix(tmpPlayerMat, tmpBoardForPlayer.getRows(), tmpBoardForPlayer.getCols());

	shipsCnt = allShipsDetails.size();
	// for each ship detail in allShipsDetails allocate a new ship with this details
	std::set<Ship*> shipsSet = Ship::createShipSet(allShipsDetails);

	// create matrix of pointers to the ships allocated for this player
	shipsMatrix = Ship::createShipMatrix(shipsSet, mainBoard.getRows(), mainBoard.getCols());

	if (!player->init(inputDirPath)) {
		std::cout << "Algorithm initialization failed for dll: " << dllPathPlayer << std::endl;
		return false;
	}
	return true;
}

void BattleshipGameManager::sendAttackForPrint(std::pair<int, int> nextAttack, AttackResult attackRes)const
{
	char currAttackedChar = mainBoard.getCoordValue(nextAttack.first - 1, nextAttack.second - 1);

	int playerAttackedId = (mainBoard.isPlayerShip(PLAYERID_A, currAttackedChar) ? PLAYERID_A : PLAYERID_B);
	if (currAttackedChar != ' ') attackRes = AttackResult::Hit;
	else playerAttackedId = UNDEFINED_PLAYERID;
	PrintGameBoard::printCurrentAttack(playerAttackedId, std::make_pair(nextAttack.first - 1, nextAttack.second - 1), currAttackedChar, attackRes);
}

bool BattleshipGameManager::initGamePlayers(const std::string & dllPathPlayerA, const std::string & dllPathPlayerB)
{

	Ship*** shipsMatA = nullptr;
	Ship*** shipsMatB = nullptr;
	size_t shipsCntA = 0, shipsCntB = 0;

	HINSTANCE hDllA, hDllB;


	/* PlayerA init */
	if (!loadAndInitPlayerDll(dllPathPlayerA, playerAlgoA, PLAYERID_A, hDllA, shipsMatA, shipsCntA))
		return false;

	playerA = std::move(GamePlayerData(PLAYERID_A, playerAlgoA, shipsMatA, shipsCntA, mainBoard.getRows(), mainBoard.getCols()));

	if (!playerA.isSet()) return false;

	dll_vec.push_back(std::make_pair(PLAYERID_A, hDllA));

	/* PlayerB init */
	if (!loadAndInitPlayerDll(dllPathPlayerB, playerAlgoB, PLAYERID_B, hDllB, shipsMatB, shipsCntB))
		return false;

	playerB = std::move(GamePlayerData(PLAYERID_B, playerAlgoB, shipsMatB, shipsCntB, mainBoard.getRows(), mainBoard.getCols()));

	if (!playerB.isSet()) return false;

	dll_vec.push_back(std::make_pair(PLAYERID_B, hDllB));


	return true;
}
