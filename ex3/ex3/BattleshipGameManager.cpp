#include "BattleshipGameManager.h"
#include "BattleshipGameUtils.h"
#include "GamePlayerData.h"
#include <iostream>
#include "StandingsTableEntryData.h"
#include "BoardDataImpl.h"

// pass unique_ptr by value as described here - https://stackoverflow.com/a/8114913
BattleshipGameManager::BattleshipGameManager(const BattleshipBoard & board, std::unique_ptr<IBattleshipGameAlgo> algoA, std::unique_ptr<IBattleshipGameAlgo> algoB) : mainBoard(board), successfullyCreated(true)
{
	std::set<std::pair<char, std::set<Coordinate>>> shipDetailsA, shipDetailsB;
	mainBoard.ExtractShipsDetailsOfGamePlayers(shipDetailsA, shipDetailsB);
	
	ShipsBoard tmpPlayersShipsBoard;
	initPlayerData(PLAYERID_A, std::move(algoA), shipDetailsA, tmpPlayersShipsBoard);
	playerA = std::move(GamePlayerData(PLAYERID_A, std::move(algoA), std::move(tmpPlayersShipsBoard), shipDetailsA.size()));

	initPlayerData(PLAYERID_B, std::move(algoB), shipDetailsB, tmpPlayersShipsBoard);
	playerB = std::move(GamePlayerData(PLAYERID_B, std::move(algoB), std::move(tmpPlayersShipsBoard), shipDetailsB.size()));

	if (!playerA.isSet() || !playerB.isSet())
		successfullyCreated = false;
}

void BattleshipGameManager::initPlayerData(int playerId, std::unique_ptr<IBattleshipGameAlgo> playerAlgo, std::set<std::pair<char, std::set<Coordinate>>>& shipsDetails, ShipsBoard& playerShipBoard)const
{
	BoardDataImpl boardData(playerId, mainBoard);
	
	playerAlgo->setPlayer(playerId);
	playerAlgo->setBoard(boardData);
	
	playerShipBoard = ShipsBoard(Ship::createShipSet(shipsDetails), mainBoard.getRows(), mainBoard.getCols(), mainBoard.getDepth());
}

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

	int currScore = currPlayer->score;
	int otherScore = otherPlayer->score;


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

	//its a tie
	if (currPlayer->id == PLAYERID_A) {
		return StandingsTableEntryData("", LOST, LOST, currScore, otherScore);
	}
	else {
		return StandingsTableEntryData("", LOST, LOST, otherScore, currScore);
	}

}

