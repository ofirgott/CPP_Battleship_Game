#include "BattleshipGameManager.h"
#include <set>




BattleshipGameManager::BattleshipGameManager(std::string boardPath, std::string attackFilePath_a, std::string attackFilePath_b, bool& isGameSuccessfullyCreated) :
	boardFilePath(boardPath), attackFilePath_A(attackFilePath_a), attackFilePath_B(attackFilePath_b), mainBoard(BattleshipBoard(boardFilePath, ROWS, COLS)),
	playerA(Player(PLAYERID_A, attackFilePath_A)), playerB(Player(PLAYERID_B, attackFilePath_B)), currPlayer(nullptr), otherPlayer(nullptr)
{
	/* (note that we init all game class member in the init list) */

	if (mainBoard.getRows() == -1 || !checkBoardValidity(mainBoard))		/* checks if the main board successfully created, and it is valid according to the game rules */
	{																		/* if not, we immediately exit from the game constructor */
		isGameSuccessfullyCreated = false;								
		return;
	}
	
	if (playerA.getID() == -1 || playerB.getID() == -1) {					/* checks if we have empty player or problem in creating player */
		isGameSuccessfullyCreated = false;									/* if so, we immediately exit from the game constructor */
		return;
	}

	auto playerBoardA = mainBoard.createPlayerBoard(PLAYERID_A);							/* createPlayerBoard allocates new copy of matrix for player, so we need to delete it*/
	playerA.setBoard(playerBoardA, mainBoard.getRows(), mainBoard.getCols());									/* creates the Ship*** for this player */
	BattleshipBoard::deleteMatrix(const_cast<char**>(playerBoardA), mainBoard.getRows(), mainBoard.getCols());	/* we don't need this copy of char** matrix anymore, so delete */

	auto playerBoardB = mainBoard.createPlayerBoard(PLAYERID_B);
	playerB.setBoard(playerBoardB, mainBoard.getRows(), mainBoard.getCols());
	BattleshipBoard::deleteMatrix(const_cast<char**>(playerBoardB), mainBoard.getRows(), mainBoard.getCols());
	

	isGameSuccessfullyCreated = true;
}


void BattleshipGameManager::Run()
{

	std::pair<int, int> nextAttack;
	std::pair<AttackResult, int> attackRes;

	currPlayer = &playerA;
	otherPlayer = &playerB;

	while (currPlayer->getHasMoreMoves() || otherPlayer->getHasMoreMoves()) { // as long as one of the players has more moves and no one won
		if (!(currPlayer->getHasMoreMoves())) {
			// if current player doesnt have anymore moves continue to next player
			updateCurrPlayer();
			continue;
		}

		nextAttack = currPlayer->attack();
		// attack other player 
		attackRes = otherPlayer->realAttack(nextAttack);
		if (attackRes.first == AttackResult::Miss) {
			// the opponent doesnt have a ship in this coordinates; check if attacked myself
			attackRes = currPlayer->realAttack(nextAttack);
			if (attackRes.first != AttackResult::Miss) { // currPlayer attacked himself
				otherPlayer->updateScore(attackRes.second); // the other player gets points
			}
			// notifyOnAttackResult(); - empty implementation
			// pass turn to other player- if missed || if attacked myself
			updateCurrPlayer();

			//check if someone won
			if ((currPlayer->getShipsCount() == 0) || (otherPlayer->getShipsCount() == 0)) {
				break;
			}
		}
		else { // attacked opponents ship
			if (attackRes.second == -1) { // hit opponents ship but not in a new coordinate; switch turns
				updateCurrPlayer();
			}
			else {
				currPlayer->updateScore(attackRes.second);
				// notifyOnAttackResult(); - empty implementation
				// keep my turn 
			}

			if ((currPlayer->getShipsCount() == 0) || (otherPlayer->getShipsCount() == 0)) { //check if someone won
				break;
			}
		}

	}
	// print game results 
	outputGameResult();

	return;
}



std::pair<size_t, std::set<char>> BattleshipGameManager::FindNumberOfValidShipsInBoard(const char** matrix, int rows, int cols)
{
	std::set<std::pair<char, std::set<std::pair<int, int>>>> setOfShipsDetails;					/* set of ships details - for example:
																								 {<'m', {<1,2>,<1,3>}> , <'P', {<8,5>, <8,6> , <8,7>}> } */

	std::set<char> invalidShips;																 /* set of the invalid ships (to avoid duplicated ships in error messages) */
	
	char** matrixCopy = BattleshipBoard::copyMatrix(const_cast<char**>(matrix), rows, cols);     /* we need to send copy of the matrix to ExtractShipsDetails function*/
	
	setOfShipsDetails = BattleshipBoard::ExtractShipsDetails(matrixCopy, rows, cols);	         /* after this row, we have set of ships, maybe some of them invalid -  this function will 																							  be called also when we will create the player */
	
	BattleshipBoard::deleteMatrix(matrixCopy, rows, cols);										 /* we don't need the matrix copy anymore*/
	
	DeleteInvalidShipsDetailsEntryFromSet(setOfShipsDetails, invalidShips);						 /* after this row, we have only valid ships in setOfShipsDetails, and alse invalidShips																								  updated*/

	return std::make_pair(setOfShipsDetails.size(), invalidShips);								 /* return number of valid ships and set of letters of found invalid ships */
}


void BattleshipGameManager::DeleteInvalidShipsDetailsEntryFromSet(std::set<std::pair<char, std::set<std::pair<int, int>>>>& setOfShipsDetails, std::set<char>& invalidShips)
{
	auto it = setOfShipsDetails.begin();
	while (it != setOfShipsDetails.end())
	{
		if (!Ship::isValidShipDetails(*it))
		{
			invalidShips.insert(it->first);
			it = setOfShipsDetails.erase(it);
		}
		else
		{
			++it;
		}
	}

}

void BattleshipGameManager::PrintWrongSizeOrShapeForShips(std::set<char>& invalidShipsSet, char playerChar)
{
	if (invalidShipsSet.empty()) return;

	for (char shipChar : invalidShipsSet)
	{
		std::cout << "Wrong size or shape for ship " << shipChar << " for player " << playerChar << std::endl;
	}
}

bool BattleshipGameManager::isCorrectNumberOfShipsForPlayer(size_t validShipsCnt, char playerChar)
{

	if (validShipsCnt == NUM_OF_PLAYER_SHIPS) return true;

	else if (validShipsCnt < NUM_OF_PLAYER_SHIPS)
	{
		std::cout << "Too few ships for player " << playerChar << std::endl;
		return false;
	}

	else 		//validShipsCnt > NUM_OF_PLAYER_SHIPS
	{
		std::cout << "Too many ships for player " << playerChar << std::endl;
		return false;
	}
}



bool BattleshipGameManager::checkBoardValidity(const BattleshipBoard& board)
{
	bool hasShipWithWrongSize_A, hasShipWithWrongSize_B, hasTooManyShip_A, hasToManyShip_B;
	bool hasTooFewShips_A, hasTooFewShips_B, hasAdjacentShips;

	size_t validShipsCnt_A, validShipsCnt_B;
	hasShipWithWrongSize_A = hasShipWithWrongSize_B = hasTooManyShip_A = hasToManyShip_B = hasAdjacentShips = false;
	hasTooFewShips_A = hasTooFewShips_B = true;

	const char** boardA = mainBoard.createPlayerBoard(PLAYERID_A);
	const char** boardB = mainBoard.createPlayerBoard(PLAYERID_B);

	//check set of ships of A size
	//todo: we maybe want to delete element (ships) from the ships set while we iterate the this set
	std::pair<size_t, std::set<char>> tmpPair;
	std::set<char> invalidShips_A;
	std::set<char> invalidShips_B;


	tmpPair = FindNumberOfValidShipsInBoard(boardA, mainBoard.getRows(), mainBoard.getCols());
	validShipsCnt_A = tmpPair.first;
	invalidShips_A = tmpPair.second;
	BattleshipBoard::deleteMatrix(const_cast<char**>(boardA), mainBoard.getRows(), mainBoard.getCols());

	tmpPair = FindNumberOfValidShipsInBoard(boardB, mainBoard.getRows(), mainBoard.getCols());
	validShipsCnt_B = tmpPair.first;
	invalidShips_B = tmpPair.second;
	BattleshipBoard::deleteMatrix(const_cast<char**>(boardB), mainBoard.getRows(), mainBoard.getCols());

	PrintWrongSizeOrShapeForShips(invalidShips_A, A);
	PrintWrongSizeOrShapeForShips(invalidShips_B, B);

	bool isCorrectShipsNumA = isCorrectNumberOfShipsForPlayer(validShipsCnt_A, A);
	bool isCorrectShipsNumB = isCorrectNumberOfShipsForPlayer(validShipsCnt_B, B);

	char** copyMainBoardMatrix = GetCopyOfBoard();
	hasAdjacentShips = mainBoard.CheckIfHasAdjacentShips();
	BattleshipBoard::deleteMatrix(copyMainBoardMatrix, mainBoard.getRows(), mainBoard.getCols());

	if (isCorrectShipsNumA && isCorrectShipsNumB && !hasAdjacentShips && invalidShips_A.empty() && invalidShips_B.empty())
		return true;
	else
		return false;

}


void BattleshipGameManager::updateCurrPlayer()
{
	Player*  tmpPlayer;

	//switch the players
	tmpPlayer = currPlayer;
	currPlayer = otherPlayer;
	otherPlayer = tmpPlayer;
}

void BattleshipGameManager::outputGameResult()
{

	int currScore = 0;
	int otherScore = 0;

	// is there a case which both players has 0 ships??? 
	if (currPlayer->getShipsCount() == 0) {
		if (currPlayer->getID() == 0) {
			std::cout << "Player B won" << std::endl;
		}
		else {
			std::cout << "Player A won" << std::endl;
		}
	}
	if (otherPlayer->getShipsCount() == 0) {
		if (otherPlayer->getID() == 0) {
			std::cout << "Player B won" << std::endl;
		}
		else {
			std::cout << "Player A won" << std::endl;
		}
	}

	// space after : ? 
	currScore = currPlayer->getTScore();
	otherScore = otherPlayer->getTScore();
	std::cout << "Points:" << std::endl;

	if (currPlayer->getID() == 0) {
		std::cout << "Player A: " << currScore << std::endl;
		std::cout << "Player B: " << otherScore << std::endl;
	}
	else {
		std::cout << "Player A: " << otherScore << std::endl;
		std::cout << "Player B: " << currScore << std::endl;
	}
}