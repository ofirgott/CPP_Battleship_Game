#include "BattleshipGameManager.h"
#include "BattleshipGameUtils.h"
#include "GamePlayerData.h"


BattleshipGameManager::BattleshipGameManager(int argc, char * argv[]) : playerAlgoA(nullptr), playerAlgoB(nullptr), inputDirPath(""), gameSuccessfullyCreated(false)
{
	std::string dllPathPlayerA = "", dllPathPlayerB = "", boardPath = "";
	bool printFlag = false;
	int printDelay = 0;
	
	if(!checkGameArguments(argc, argv, printFlag, printDelay)) return;	//todo: need to implement
		
	if(!checkGamefiles(boardPath, dllPathPlayerA, dllPathPlayerB)) return;
	
	mainBoard = BattleshipBoard(boardFilePath, ROWS, COLS);		//todo: maybe we want here move?
	
	if (!checkMainBoardValidity() || !initGamePlayers(dllPathPlayerA, dllPathPlayerB)) return;

	gameSuccessfullyCreated = true;

}

BattleshipGameManager::~BattleshipGameManager()
{
	//std::cout << "in MANAGER DEST \n";
	//std::cout << (void*)playerA.playerAlgo << "this is add of playerA algo\n";
	//std::cout << (void*)playerB.playerAlgo << "this is add of playerB algo\n";
	//delete playerA.playerAlgo;
	//delete playerB.playerAlgo;
	
	delete playerAlgoA;
	delete playerAlgoB;

	std::vector<std::pair<int, HINSTANCE>>::iterator vitr;
	
	// close all the dynamic libs we opened
	
	for (vitr = dll_vec.begin(); vitr != dll_vec.end(); ++vitr)
	{
		FreeLibrary(vitr->second);
	}
}

void BattleshipGameManager::Run()
{
	std::pair<int, int> nextAttack;
	std::pair<AttackResult, int> attackRes;

	GamePlayerData* currPlayer = &playerA;
	GamePlayerData* otherPlayer = &playerB;
	int i = 0;
	// as long as one of the players has more moves and no one won
	while (currPlayer->hasMoreMoves || otherPlayer->hasMoreMoves ) { 
		
		i++;
		if (!currPlayer->hasMoreMoves) {
			// if current player doesnt have anymore moves continue to next player
			//switchCurrPlayer(&currPlayer, &otherPlayer);
			std::swap(currPlayer, otherPlayer);
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

			currPlayer->playerAlgo->notifyOnAttackResult(currPlayer->id, nextAttack.first, nextAttack.second, attackRes.first);
			otherPlayer->playerAlgo->notifyOnAttackResult(currPlayer->id, nextAttack.first, nextAttack.second, attackRes.first);
			// pass turn to other player- if missed || if attacked myself
		
			//switchCurrPlayer(&currPlayer, &otherPlayer);
			std::swap(currPlayer, otherPlayer);
			//check if someone won
			if ((currPlayer->currShipsCount== 0) || (otherPlayer->currShipsCount == 0)) {
				break;
			}
		}
		else { // attacked opponents ship  //Ofir - comment here is wrong -> hit can also represent hit ini my ship
			if (attackRes.second == -1) {	// hit opponents ship but not in a new coordinate; switch turns
				//switchCurrPlayer(&currPlayer, &otherPlayer);
				std::swap(currPlayer, otherPlayer);
			}
			else {
				currPlayer->incrementScore(attackRes.second);
				currPlayer->playerAlgo->notifyOnAttackResult(currPlayer->id, nextAttack.first, nextAttack.second, attackRes.first);
				otherPlayer->playerAlgo->notifyOnAttackResult(currPlayer->id, nextAttack.first, nextAttack.second, attackRes.first);
				// keep my turn 
			}

			if ((currPlayer->currShipsCount == 0) || (otherPlayer->currShipsCount == 0)) { //check if someone won
				break;
			}
		}
	}

	// prints game results 
	outputGameResult(currPlayer, otherPlayer);

	return;

}

void BattleshipGameManager::switchCurrPlayer(GamePlayerData **currPlayer , GamePlayerData **otherPlayer )
{
	GamePlayerData** tmp;
	//todo: ofir - maybe we just want to use the std::swap function instead of this function
	// switch players
	tmp = currPlayer;
	currPlayer = otherPlayer;
	otherPlayer = tmp;
}







void BattleshipGameManager::outputGameResult(GamePlayerData* currPlayer, GamePlayerData* otherPlayer)
{

	int currScore;
	int otherScore;

	if (currPlayer->currShipsCount == 0) {
		if (currPlayer->id  == PLAYERID_A) {
			std::cout << "Player B won" << std::endl;
		}
		else {
			std::cout << "Player A won" << std::endl;
		}
	}

	if (otherPlayer->currShipsCount == 0) {
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

bool BattleshipGameManager::checkGameArguments(int argc, char *argv[], bool & printFlag, int & printDelay)
{
	std::string path = ".";
	//todo: implement
	if(argc > 1)
	{
		inputDirPath = argv[1];
	}
	
	printFlag = false;
	printDelay = 0;
	return true;
}

bool BattleshipGameManager::checkGamefiles(std::string & boardPath, std::string & dllPathPlayerA, std::string & dllPathPlayerB)
{
	
	
	if (!BattleshipGameUtils::isValidDir(inputDirPath)) {									/* checks if directory in dir_path exists */
		std::cout << "Wrong path: " << inputDirPath << std::endl;
		return false;
	}
	/* finds the board file */
	auto tmpFilenamesVector = BattleshipGameUtils::SortedDirlistSpecificExtension(inputDirPath, ".sboard");
	
	if (tmpFilenamesVector.size() == 0){
		std::cout << "Missing board file (*.sboard) looking in path: " << inputDirPath << std::endl;
		return false;
	}
	else boardFilePath = inputDirPath + "/" + tmpFilenamesVector[0];

	tmpFilenamesVector = BattleshipGameUtils::SortedDirlistSpecificExtension(inputDirPath, ".dll");

	if(tmpFilenamesVector.size() < 2){
		std::cout << "Missing an algorithm (dll) file looking in path: " << inputDirPath << std::endl;
		return false;
	}

	dllPathPlayerA = inputDirPath+ "/" + tmpFilenamesVector[0];
	dllPathPlayerB = inputDirPath + "/" + tmpFilenamesVector[1];



	
	return true;
}



bool BattleshipGameManager::checkMainBoardValidity()const
{
	if (!mainBoard.isSuccessfullyCreated()) return false;
	
	bool hasShipWithWrongSize_A, hasShipWithWrongSize_B, hasTooManyShip_A, hasToManyShip_B;
	bool hasTooFewShips_A, hasTooFewShips_B, hasAdjacentShips;

	size_t validShipsCnt_A, validShipsCnt_B;
	hasShipWithWrongSize_A = hasShipWithWrongSize_B = hasTooManyShip_A = hasToManyShip_B = hasAdjacentShips = false;
	hasTooFewShips_A = hasTooFewShips_B = true;

	const char** matrixA = const_cast<const char**>(mainBoard.createPlayerBoard(PLAYERID_A));						/* allocates new matrix */
	BattleshipBoard boardA(matrixA, mainBoard.getRows(), mainBoard.getCols());
	const char** MatrixB = const_cast<const char**>(mainBoard.createPlayerBoard(PLAYERID_B));
	BattleshipBoard boardB(MatrixB, mainBoard.getRows(), mainBoard.getCols());
	std::pair<size_t, std::set<char>> tmpPair;											/* for FindNumberOfValidShipsInBoard output*/
	std::set<char> invalidShips_A;
	std::set<char> invalidShips_B;


	tmpPair = FindNumberOfValidShipsInBoard(boardA);
	validShipsCnt_A = tmpPair.first;
	invalidShips_A = tmpPair.second;
	BattleshipBoard::deleteMatrix(matrixA, boardA.getRows(), boardA.getCols());

	tmpPair = FindNumberOfValidShipsInBoard(boardB);
	validShipsCnt_B = tmpPair.first;
	invalidShips_B = tmpPair.second;
	BattleshipBoard::deleteMatrix(MatrixB, boardB.getRows(), boardB.getCols());

	PrintWrongSizeOrShapeForShips(invalidShips_A, A);
	PrintWrongSizeOrShapeForShips(invalidShips_B, B);

	bool isCorrectShipsNumA = isCorrectNumberOfShipsForPlayer(validShipsCnt_A, A);
	bool isCorrectShipsNumB = isCorrectNumberOfShipsForPlayer(validShipsCnt_B, B);


	hasAdjacentShips = mainBoard.CheckIfHasAdjacentShips();								/* if has adjacent ships, this funcion also prints relevant message */
	
	if (isCorrectShipsNumA && isCorrectShipsNumB && !hasAdjacentShips && invalidShips_A.empty() && invalidShips_B.empty())
		return true;
	else
		return false;

}

std::pair<size_t, std::set<char>> BattleshipGameManager::FindNumberOfValidShipsInBoard(BattleshipBoard& board)const
{
	std::set<std::pair<char, std::set<std::pair<int, int>>>> setOfShipsDetails;					/* set of ships details - for example:
																								{<'m', {<1,2>,<1,3>}> , <'P', {<8,5>, <8,6> , <8,7>}> } */
	std::set<char> invalidShips;																 /* set of the invalid ships (to avoid duplicated ships in error messages) */


	setOfShipsDetails = board.ExtractShipsDetails();	         /* after this row, we have set of ships, maybe some of them invalid -  this function will 																							  be called also when we will create the player */


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
	// for each ship detail in allShipsDetails allocate a new ship ith this details
	std::set<Ship*> shipsSet = Ship::createShipSet(allShipsDetails);

	// create matrix of pointers to the ships allocated for this player
	shipsMatrix = Ship::createShipMatrix(shipsSet);

	if (!player->init(inputDirPath)) {
		std::cout << "Algorithm initialization failed for dll: " << dllPathPlayer << std::endl;
		return false;
	}
	return true;
}

bool BattleshipGameManager::initGamePlayers(const std::string & dllPathPlayerA, const std::string & dllPathPlayerB)
{
	//IBattleshipGameAlgo* playerAlgoA = nullptr;
	//IBattleshipGameAlgo* playerAlgoB = nullptr;
	Ship*** shipsMatA = nullptr;
	Ship*** shipsMatB = nullptr;
	size_t shipsCntA = 0, shipsCntB = 0;
	
	HINSTANCE hDllA, hDllB;
	//const std::string tmpppppppppA = "C:/Users/Ofir/Documents/GitHub/ex2/x64/Debug/PlayerFromFile.dll";
		
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
