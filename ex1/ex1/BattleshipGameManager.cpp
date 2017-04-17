#include "BattleshipGameManager.h"

#include <set>

#define ROWS 10
#define COLS 10
#define PLAYER_A 0
#define PLAYER_B 1
#define SHIPS_NUMBER 5
#define A 'A'
#define B 'B'
#define PLAYERID_A 0
#define PLAYERID_B 1


BattleshipGameManager::BattleshipGameManager(std::string boardPath, std::string attackFilePath_a, std::string attackFilePath_b, bool& isGameSuccessfullyCreated) :
	boardFilePath(boardPath), attackFilePath_A(attackFilePath_a), attackFilePath_B(attackFilePath_b), mainBoard(BattleshipBoard(boardFilePath, ROWS, COLS)),
	playerA(Player(PLAYERID_A, attackFilePath_A)), playerB(Player(PLAYERID_B, attackFilePath_B)), currPlayer(nullptr), otherPlayer(nullptr)
{

	//boardFilePath = boardPath;
	//attackFilePath_A = attackFilePath_a;
	//attackFilePath_B = attackFilePath_b;
	//std::cout << "file A is:" << attackFilePath_a;
	//mainBoard = BattleshipBoard(boardFilePath, ROWS, COLS);
	//currPlayer = nullptr;
	//otherPlayer = nullptr;
	//get the information about the ships of the players

	if (!checkBoardValidity(mainBoard))
	{
		isGameSuccessfullyCreated = false;
		return;
	}
	//std::cout << "finish";
	//playerA = Player(PLAYERID_A, attackFilePath_A); //add player board and info
	playerA.setBoard(mainBoard.createPlayerBoard(PLAYERID_A), mainBoard.getRows(), mainBoard.getCols());

	//playerB = Player(PLAYERID_B, attackFilePath_B);
	playerB.setBoard(mainBoard.createPlayerBoard(PLAYERID_B), mainBoard.getRows(), mainBoard.getCols());

	if (playerA.getID() == -1 || playerB.getID() == -1) { //empty player or problem in creating player
		isGameSuccessfullyCreated = false;
		return;
	}

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
		if (attackRes.first == AttackResult::Miss) { // the opponent doesnt have a ship in this coordinates
													 // check if attacked myself
			attackRes = currPlayer->realAttack(nextAttack);
			if (attackRes.first != AttackResult::Miss) { // currPlayer attacked himself
				otherPlayer->updateScore(attackRes.second); // the other player gets points
			}
			// notifyOnAttackResult(); - empty implementation
			// pass turn to other player- if missed both or if attacked myself
			updateCurrPlayer();

			//check if someone won
			if ((currPlayer->getShipsCount() == 0) || (otherPlayer->getShipsCount() == 0)) {
				break;
			}
		}
		else { // attacked opponents ship
			currPlayer->updateScore(attackRes.second);
			// notifyOnAttackResult(); - empty implementation
			// keep my turn 

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
	std::set<std::pair<char, std::set<std::pair<int, int>>>> setOfShipsDetails;	//todo: show the example here
	std::set<char> invalidShips; //set of the invalid ships (to avoid duplicated ships in error messages)
	char** matrixCopy = BattleshipBoard::copyMatrix(const_cast<char**>(matrix), rows, cols);
	setOfShipsDetails = BattleshipBoard::ExtractShipsDetails(matrixCopy, rows, cols);	//after this row, we have set of ships, maybe some of them invalid/ this function will be called also when we will create the player
	BattleshipBoard::deleteMatrix(matrixCopy, rows, cols);
	DeleteInvalidShipsDetailsEntryFromSet(setOfShipsDetails, invalidShips);

	return std::make_pair(setOfShipsDetails.size(), invalidShips);		//return number of valid ship in the set
}
void BattleshipGameManager::DeleteInvalidShipsDetailsEntryFromSet(std::set<std::pair<char, std::set<std::pair<int, int>>>>& setOfShipsDetails, std::set<char>& invalidShips)
{
	auto it = setOfShipsDetails.begin();
	while (it != setOfShipsDetails.end())
	{
		if (!Ship::isValidShipDetails(*it))		// todo: check if crashes!!
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


//
//int BattleshipGameManager::FindNumberOfValidShipsInBoard(std::set<Ship>& ships)
//{
//	auto it = ships.begin();
//	while (it != ships.end())
//	{
//		if (!Ship::isLegalShip(it))
//		{E
//			it = ships.erase(it);
//		}
//		else
//		{
//			++it;
//		}
//	}
//	retrun ships.size();
//}

bool BattleshipGameManager::checkBoardValidity(const BattleshipBoard& battleship_board)
{
	bool hasShipWithWrongSize_A, hasShipWithWrongSize_B, hasTooManyShip_A, hasToManyShip_B;
	bool hasTooFewShips_A, hasTooFewShips_B, hasAdjacentShips;

	size_t validShipsCnt_A, validShipsCnt_B;
	hasShipWithWrongSize_A = hasShipWithWrongSize_B = hasTooManyShip_A = hasToManyShip_B = hasAdjacentShips = false;
	hasTooFewShips_A = hasTooFewShips_B = true;
	//std::cout << "what";

	const char** boardA = mainBoard.createPlayerBoard(PLAYER_A);
	const char** boardB = mainBoard.createPlayerBoard(PLAYER_B);

	//check set of ships of A size
	//todo: we maybe want to delete element (ships) from the ships set while we iterate the this set
	std::pair<size_t, std::set<char>> tmpPair;
	std::set<char> invalidShips_A;
	std::set<char> invalidShips_B;


	tmpPair = FindNumberOfValidShipsInBoard(boardA, mainBoard.getRows(), mainBoard.getCols());
	validShipsCnt_A = tmpPair.first;
	invalidShips_A = tmpPair.second;

	tmpPair = FindNumberOfValidShipsInBoard(boardB, mainBoard.getRows(), mainBoard.getCols());
	validShipsCnt_B = tmpPair.first;
	invalidShips_B = tmpPair.second;

	PrintWrongSizeOrShapeForShips(invalidShips_A, A);
	PrintWrongSizeOrShapeForShips(invalidShips_B, B);

	bool isCorrectShipsNumA = isCorrectNumberOfShipsForPlayer(validShipsCnt_A, A);
	bool isCorrectShipsNumB = isCorrectNumberOfShipsForPlayer(validShipsCnt_B, B);

	char** copyMainBoardMatrix = GetCopyOfBoard();
	hasAdjacentShips = mainBoard.CheckIfHasAdjacentShips();

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