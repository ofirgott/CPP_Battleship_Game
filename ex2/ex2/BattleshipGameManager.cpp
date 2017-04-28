#include "BattleshipGameManager.h"



void BattleshipGameManager::Run() const
{
	std::pair<int, int> nextAttack;
	std::pair<AttackResult, int> attackRes;

	UtilGamePlayer* currPlayer = playerA;
	UtilGamePlayer* otherPlayer = playerB;

	// as long as one of the players has more moves and no one won
	while (currPlayer->hasMoreMoves || otherPlayer->hasMoreMoves ) { 
		if (!currPlayer->hasMoreMoves) {
			// if current player doesnt have anymore moves continue to next player
			switchCurrPlayer(&currPlayer, &otherPlayer);
			continue;
		}

		nextAttack = currPlayer->getAlgoNextAttack();
		if (nextAttack.first == -1 && nextAttack.second == -1) {
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

			currPlayer->attackAlgo->notifyOnAttackResult(currPlayer->id, nextAttack.first, nextAttack.second, attackRes.first);
			otherPlayer->attackAlgo->notifyOnAttackResult(currPlayer->id, nextAttack.first, nextAttack.second, attackRes.first);
			// pass turn to other player- if missed || if attacked myself
		
			switchCurrPlayer(&currPlayer, &otherPlayer);

			//check if someone won
			if ((currPlayer->shipsCount== 0) || (otherPlayer->shipsCount == 0)) {
				break;
			}
		}
		else { // attacked opponents ship
			if (attackRes.second == -1) {	// hit opponents ship but not in a new coordinate; switch turns
				switchCurrPlayer(&currPlayer,& otherPlayer);
			}
			else {
				currPlayer->incrementScore(attackRes.second);
				currPlayer->attackAlgo->notifyOnAttackResult(currPlayer->id, nextAttack.first, nextAttack.second, attackRes.first);
				otherPlayer->attackAlgo->notifyOnAttackResult(currPlayer->id, nextAttack.first, nextAttack.second, attackRes.first);
				// keep my turn 
			}

			if ((currPlayer->shipsCount == 0) || (otherPlayer->shipsCount == 0)) { //check if someone won
				break;
			}
		}
	}

	// prints game results 
	outputGameResult(currPlayer, otherPlayer);

	return;

}

void BattleshipGameManager::switchCurrPlayer(UtilGamePlayer ** currPlayer , UtilGamePlayer ** otherPlayer )
{
	UtilGamePlayer* tmp;

	// switch players
	tmp = *currPlayer;
	*currPlayer = *otherPlayer;
	*otherPlayer = tmp;
}


std::pair<int, int> BattleshipGameManager::UtilGamePlayer::getAlgoNextAttack() const
{

	std::pair<int, int> tmpAttack = attackAlgo->attack();

	// todo : maybe use const numbers and not -1 ?? 
	if (tmpAttack.first == -1 && tmpAttack.second == -1) { // player doesnt have anymore moves
		return tmpAttack;
	}

	// while the given coordinates are not in the board && the player has more moves
	while (tmpAttack.first < Rows, tmpAttack.second >Cols)
	{
		tmpAttack = attackAlgo->attack();
		if (tmpAttack.first == -1 && tmpAttack.second == -1) { // player doesnt have anymore moves
			return tmpAttack;
		}

	}
	return tmpAttack;
}

std::pair<AttackResult, int> BattleshipGameManager::UtilGamePlayer::realAttack(std::pair<int, int> coor)
{
	if (coor.first > Rows || coor.first < 1 || coor.second < 1 || coor.second > Cols) {
		return std::pair<AttackResult, int>(AttackResult::Miss, 0);
	}

	int attackRes;
	Ship* shipPtr = shipsMatrix[coor.first - 1][coor.second - 1];
	std::pair<AttackResult, int> retPair;

	if (shipPtr == nullptr) {// doesnt have a ship in this coordinates
		retPair = std::pair<AttackResult, int>(AttackResult::Miss, 0);
	}
	else { // have a ship in this coordinates 
		if (shipPtr->isAlive()) {// not sank yet
			attackRes = shipPtr->updateAttack(coor.first - 1, coor.second - 1);
			if (attackRes == 0) { // successful attack
				if (shipPtr->isAlive()) { // not sank yet 
					retPair = std::make_pair(AttackResult::Hit, 0);
				}
				else
				{ // the ship sank after the last attack
					retPair = std::make_pair(AttackResult::Sink, shipPtr->getPoints());
				}
			}
			else if (attackRes == 1)
			{ // already hit this part- no points given
				retPair = std::pair<AttackResult, int>(AttackResult::Hit, -1);
			}
			else
			{ // attackRes == -1  
				retPair = std::pair<AttackResult, int>(AttackResult::Miss, 0);
			}
		}
		else { // this ship is mine but already sank
			retPair = std::pair<AttackResult, int>(AttackResult::Miss, 0);
		}
	}

	if (retPair.first == AttackResult::Sink) { //  update number ships left for player
			shipsCount = shipsCount - 1;
	}

	return retPair;
}


void BattleshipGameManager::outputGameResult(UtilGamePlayer* currPlayer, UtilGamePlayer* otherPlayer)
{

	int currScore;
	int otherScore;

	if (currPlayer->shipsCount == 0) {
		if (currPlayer->id  == PLAYERID_A) {
			std::cout << "Player B won" << std::endl;
		}
		else {
			std::cout << "Player A won" << std::endl;
		}
	}

	if (otherPlayer->shipsCount == 0) {
		if (otherPlayer->id  == PLAYERID_A) {
			std::cout << "Player B won" << std::endl;
		}
		else {
			std::cout << "Player A won" << std::endl;
		}
	}

	currScore = currPlayer->score;
	otherScore = otherPlayer->score;
	std::cout << "Points:" << std::endl;

	if (currPlayer->id == PLAYERID_A) {
		std::cout << "Player A: " << currScore << std::endl;
		std::cout << "Player B: " << otherScore << std::endl;
	}
	else {
		std::cout << "Player A: " << otherScore << std::endl;
		std::cout << "Player B: " << currScore << std::endl;
	}
}