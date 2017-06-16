#include "BattleshipGameManager.h"
#include "BattleshipGameUtils.h"
#include "GamePlayerData.h"
#include <iostream>
#include "PlayerGameResultData.h"
#include "BoardDataImpl.h"

// pass unique_ptr by value as described here - https://stackoverflow.com/a/8114913
BattleshipGameManager::BattleshipGameManager(const BattleshipBoard & board, std::unique_ptr<IBattleshipGameAlgo> algoA, std::unique_ptr<IBattleshipGameAlgo> algoB) : mainBoard(board), algorithmA(std::move(algoA)), algorithmB(std::move(algoB)), successfullyCreated(true)
{
	
	std::set<std::pair<char, std::set<Coordinate>>> shipDetailsA, shipDetailsB;
	mainBoard.ExtractShipsDetailsOfGamePlayers(shipDetailsA, shipDetailsB);
	
	ShipsBoard shipsBoardA, shipsBoardB;
	BoardDataImpl boardDataA(PLAYERID_A, mainBoard);
	
	initPlayerData(PLAYERID_A, algorithmA.get(), shipDetailsA, shipsBoardA, boardDataA);

	playerA = std::move(GamePlayerData(PLAYERID_A, algorithmA.get(), std::move(shipsBoardA), shipDetailsA.size()));
	
	BoardDataImpl boardDataB(PLAYERID_B, mainBoard);
	initPlayerData(PLAYERID_B, algorithmB.get(), shipDetailsB, shipsBoardB, boardDataB);
	
	playerB = std::move(GamePlayerData(PLAYERID_B, algorithmB.get(), std::move(shipsBoardB), shipDetailsB.size()));

	if (!playerA.isSet() || !playerB.isSet())
		successfullyCreated = false;
}

void BattleshipGameManager::initPlayerData(int playerId, IBattleshipGameAlgo* playerAlgo,  std::set<std::pair<char, std::set<Coordinate>>>& shipsDetails, ShipsBoard& playerShipBoard, BoardDataImpl& playerBoardData)const
{
	
	playerAlgo->setPlayer(playerId);
	playerAlgo->setBoard(playerBoardData);
	auto playerShipsList = Ship::createShipsList(shipsDetails);
	playerShipBoard = ShipsBoard(playerShipsList, mainBoard.getRows(), mainBoard.getCols(), mainBoard.getDepth());
	//playerA = GamePlayerData(playerId, playerAlgo, std::move(playerShipBoard), shipsDetails.size());
}

PlayerGameResultData BattleshipGameManager::Run()
{
	Coordinate nextAttack(-1,-1,-1);
	std::pair<AttackResult, int> attackRes;

	GamePlayerData* currPlayer = &playerA;
	GamePlayerData* otherPlayer = &playerB;


	// as long as one of the players has more moves and no one won
	while (currPlayer->hasMoreMoves || otherPlayer->hasMoreMoves) {
		//std::cout << "now!";
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
	//std::cout << currPlayer->id << ": " << currPlayer->score << ", " << otherPlayer->id << ": " << otherPlayer->score << std::endl;
	return outputGameResult(currPlayer, otherPlayer);

}


PlayerGameResultData BattleshipGameManager::outputGameResult(GamePlayerData* currPlayer, GamePlayerData* otherPlayer)
{

	int currScore = currPlayer->score;
	int otherScore = otherPlayer->score;

	//std::cout << "*************************curr score: " << currScore << ", and otherScore: " << otherScore << std::endl;
	if (currPlayer->currShipsCount == 0) {
		if (currPlayer->id == PLAYERID_A) { // currPlayer is playerA
		//	 "Player B won" 
			//std::cout << " B WON! " << std::endl;
			return PlayerGameResultData("", LOST, WON, currScore, otherScore);
		}
		else { // otherPlayer is playerA
		//	 "Player A won" 
			//std::cout << " A WON! " << std::endl;
			return PlayerGameResultData("", WON, LOST, otherScore, currScore);
		}
	}

	if (otherPlayer->currShipsCount == 0) {
		if (otherPlayer->id == PLAYERID_A) { // otherPlayer is playerA
			//	 "Player B won" 
			//std::cout << " B WON! " << std::endl;
			return PlayerGameResultData("", LOST, WON, otherScore, currScore);
		}
		else {// currPlayer is playerA
			//	 "Player A won" 
			//std::cout << " A WON! " << std::endl;
			return PlayerGameResultData("", WON, LOST, currScore, otherScore);
		}
	}

	//its a tie
	if (currPlayer->id == PLAYERID_A) {
		//std::cout << " TIE! " << std::endl;
		return PlayerGameResultData("", LOST, LOST, currScore, otherScore);
	}
	else {
		//std::cout << " TIE! " << std::endl;
		return PlayerGameResultData("", LOST, LOST, otherScore, currScore);
	}
	
}

