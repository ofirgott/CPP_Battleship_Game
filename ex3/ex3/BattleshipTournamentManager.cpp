#include "BattleshipTournamentManager.h"
#include "BattleshipGameUtils.h"
#include <iostream>
#include <condition_variable>
#include <atomic>
//#include "Ship.h"



void BattleshipTournamentManager::RunTurnament()
{
	int numberOfRounds = allRounds.size();
	int numberOfGames = allGamesResults.size();
	int numOfPlayers = algosDetailsVec.size();
	int cnt = 0;

	//in case there are more threads then games
	if (maxGamesThreads > numberOfGames) {
		maxGamesThreads = numberOfGames;
	}
	//creating a pool of threads
	for (int i = 0; i< maxGamesThreads; i++)
	{
		threadsPool.push_back(std::thread(&singleThreadJob));
	}


	//while there are more rounds to print keep waiting for next round
	while (cnt < numberOfRounds ){

		std::unique_lock<std::mutex> lk(isRoundDoneMutex);
		//waiting for current round to end by order (first till last)
		isRoundDoneCondition.wait(lk, [](std::vector<Round>& const allRounds,int cnt) {return allRounds[cnt].status; });
		lk.unlock();

		if (allRounds[cnt].status) {//update sum fileds for current round 
			for (int i = 0; i < numOfPlayers; i++) {
				RoundDataToPrint[i].WinsNumber += allGamesResults[i][cnt].WinsNumber;
				RoundDataToPrint[i].LossesNumber += allGamesResults[i][cnt].LossesNumber;
				RoundDataToPrint[i].PointsFor += allGamesResults[i][cnt].PointsFor;
				RoundDataToPrint[i].PointsAgainst += allGamesResults[i][cnt].PointsAgainst;
			}
			BattleshipPrint::printStandingsTable(RoundDataToPrint, cnt, allRounds.size());//printing the round
			cnt++;//next round to wait for
		}

	}

	for (auto & t:threadsPool) {
		t.join();
	}

}

void BattleshipTournamentManager::singleThreadJob()
{
	StandingsTableEntryData gameResult;	

	while (true)
	{
		
		std::unique_lock<std::mutex> lock(gamesQueueMutex);
		//waiting for current thread to end his game
		queueEmptyCondition.wait(lock, [](std::queue<SingleGameProperties> & const gamesQueue) {return !gamesQueue.empty(); });
		auto currGameProperty =  gamesPropertiesQueue.front();
		gamesPropertiesQueue.pop();
		lock.unlock();
		
		BattleshipGameManager game(boardsVec[currGameProperty.getBoardIndex()], algosDetailsVec[currGameProperty.getPlayerAIndex()].getAlgoFunc(), algosDetailsVec[currGameProperty.getPlayerBIndex()].getAlgoFunc());
		gameResult = game.Run();// function<void()> type

		// the game result returned is from the perspective of playerA
		gameResult.PlayerName = algosDetailsVec[currGameProperty.getPlayerAIndex()].playerName;
		updateAllGamesResults(gameResult , currGameProperty);
		
		
	}
}


void BattleshipTournamentManager::updateAllGamesResults(StandingsTableEntryData currGameRes, SingleGameProperties gamsProperty)
{

	// players indexes 
	int playerAIndex = algosDetailsVec[gamsProperty.getPlayerAIndex()].algosIndexInVec;
	int playerBIndex = algosDetailsVec[gamsProperty.getPlayerBIndex()].algosIndexInVec;

	//create gameResults for the second player 
	StandingsTableEntryData otherPlayerData = StandingsTableEntryData::createOpponentData(currGameRes, algosDetailsVec[gamsProperty.getPlayerBIndex()].playerName);

	// indexes of the properties in the specific player's vector 
	int propertyIndexA = ++playersProgress.at(playerAIndex);
	int propertyIndexB = ++playersProgress.at(playerBIndex);

	// update allGamesResults in the relevent indexes
	allGamesResults[playerAIndex][propertyIndexA].updateFields(currGameRes);
	allGamesResults[playerBIndex][propertyIndexB].updateFields(otherPlayerData);


	--allRounds[propertyIndexA].numOfGamesLeft;
	if (allRounds[propertyIndexA].numOfGamesLeft==0) {
		//need to take care of locks and mutexes and condition variables here, need to set cv in .h	
		std::unique_lock<std::mutex> lock(isRoundDoneMutex);
		allRounds[propertyIndexA].status = true;
		lock.unlock();
		isRoundDoneCondition.notify_one();

	}
	--allRounds[propertyIndexB].numOfGamesLeft;
	if (allRounds[propertyIndexB].numOfGamesLeft == 0) {
		std::unique_lock<std::mutex> lock(isRoundDoneMutex);
		allRounds[propertyIndexB].status = true;
		lock.unlock();
		isRoundDoneCondition.notify_one();
	}

}


void BattleshipTournamentManager::createGamesPropertiesQueue()
{

	for (int i = 0; i < algosDetailsVec.size(); i++) {
		for (int j = 0; j < algosDetailsVec.size(); j++) {
			for (int k = 0; k < boardsVec.size(); k++) {
				if (i != j) {
					SingleGameProperties gameDetails(k,i,j);
					gamesPropertiesQueue.push(gameDetails);
				}
			}
		}
	}

}


BattleshipTournamentManager::BattleshipTournamentManager(int argc, char * argv[]) : maxGamesThreads(DEFAULT_THREADS_NUM), successfullyCreated(true)
{

	if (!checkTournamentArguments(argc, argv)) {
		successfullyCreated = false;
		return;
	}

	if (!checkTournamentBoards())
		successfullyCreated = false;

	if (!loadTournamentAlgos())
		successfullyCreated = false;
	
	if (!successfullyCreated) return;
	
	std::cout << "Number of legal players: " << algosDetailsVec.size() << std::endl;
	std::cout << "Number of legal boards: " << boardsVec.size() << std::endl;

	//Ofir -we need to put next rows in seperate function - init tournament data structures or something..

	algosIndex = 0;
	createGamesPropertiesQueue();

	int numOfplayers = algosDetailsVec.size();
	int numOfBoards = boardsVec.size();
	int numOfRounds = gamesPropertiesQueue.size() / numOfplayers;
	
	/*todo: init vector of vectors*/
	allGamesResults.resize(numOfplayers); //vector of size number of players
	for (int i = 0; i < numOfplayers; i++) { // for each player vector of size num of rounds
		allGamesResults[i].resize(numOfRounds);
	}

	allRounds.resize(numOfRounds); // 
	for (int i = 0; i < numOfRounds; i++) {
		allRounds[i].numOfGamesLeft = numOfplayers; //Ofir - ?
		allRounds[i].roundNumber = i;
		allRounds[i].status = false;
	}

	for (int i = 0; i < numOfplayers; i++) {
		playersProgress.push_back(0);
	}
	for (int i = 0; i < numOfplayers; i++) {	//Ofir - dup	
		RoundDataToPrint.push_back(StandingsTableEntryData(algosDetailsVec[i].playerName, 0, 0, 0, 0));
	}
}

BattleshipTournamentManager::~BattleshipTournamentManager()
{
	std::vector<PlayerAlgoDetails>::iterator vitr;

	// close all the dynamic libs we opened 

	for (vitr = algosDetailsVec.begin(); vitr != algosDetailsVec.end(); ++vitr)
	{
		if (vitr->dllFileHandle)
			FreeLibrary(vitr->dllFileHandle);
	}
}


bool BattleshipTournamentManager::checkTournamentArguments(int argc, char * argv[])
{
	std::string path = ".";

	if (argc > 4)
	{
		std::cout << "Error: Too many arguments!" << std::endl;
		return false;
	}

	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-threads") == 0)
		{
			if (i == argc - 1) {	/* we got threads flag but this is the last argument - this is an error because we need the int*/
				std::cout << "Error: got -threads flag, but threads value is missing." << std::endl;
				return false;
			}
			else
			{
				char* stringEnd = nullptr;
				maxGamesThreads = static_cast<int>(strtol(argv[++i], &stringEnd, 10));
				if (*stringEnd || maxGamesThreads < 1)
				{
					std::cout << "Error: -threads flag value is not a valid positive integer." << std::endl;
					return false;
				}
			}
		}
		else  /* this is the dir path */
		{
			path = argv[i];
		}
	}

	if (!BattleshipGameUtils::getFullPath(path)) return false;

	inputDirPath = path;

	if (!BattleshipGameUtils::isValidDir(inputDirPath)) {									/* checks if directory in dir_path exists */
		std::cout << "Wrong path: " << inputDirPath << std::endl;
		return false;
	}

	return true;
}

bool BattleshipTournamentManager::checkTournamentBoards()
{
	std::string currBoardFullPath;
	auto tmpFilenamesVector = BattleshipGameUtils::SortedDirlistSpecificExtension(inputDirPath, ".sboard");

	if(tmpFilenamesVector.empty())
	{
		std::cout << "No board files (*.sboard) looking in path: " << inputDirPath.c_str() << std::endl;
		return false;
	}

	for (auto currBoardFilename : tmpFilenamesVector)
	{
		currBoardFullPath = inputDirPath + "/" + currBoardFilename;
		BattleshipBoard currBoard(currBoardFullPath);

		//todo: print to the log; - std::cout << "try to parse board file in: " << currBoardFullPath << std::endl;	

		if (checkBoardValidity(currBoard))
		{
			boardsVec.push_back(std::move(currBoard));			/* take the board without create new board */
																// TODO: print to the log : std::cout << "*** Board in: " << currBoardFullPath << "loaded succssefully!!! *****" << std::endl; 
		}
		else
		{
			// TODO: print to the log : std::cout << "Board in: " << currBoardFullPath << "skipped, because of the errors above." << std::endl; 
		}
	}
	std::cout << "Number of valid bords: " << boardsVec.size() << std::endl; //todo: print to the log

	if (boardsVec.empty())
	{
		std::cout << "Error: No valid board files (*.sboard) looking in path: " << inputDirPath.c_str() << std::endl;
		return false;
	}
	else return true;

}

bool BattleshipTournamentManager::checkBoardValidity(const BattleshipBoard& board)
{
	if (!board.isSuccessfullyCreated()) return false;


	std::set<std::pair<char, std::set<Coordinate>>> validShips_A, validShips_B;											/* for FindValidAndInvalidShipsInBoard output */
	std::set<char> invalidShips_A, invalidShips_B;


	FindValidAndInvalidShipsInBoard(board, validShips_A, invalidShips_A, validShips_B, invalidShips_B);

	if (validShips_A.empty())
	{
		// todo: print to the log -  std::cout << "player A has no valid ships at all - invalid board." << std::endl; 
		return false;
	}
	else if (validShips_B.empty())
	{
		//todo: print to the log - std::cout << "player B has no valid ships at all - invalid board." << std::endl; 
		return false;
	}
	else {
		PrintWrongSizeOrShapeForShips(invalidShips_A, A);
		PrintWrongSizeOrShapeForShips(invalidShips_B, B);

		comparePlayersShips(validShips_A, validShips_B);

		bool hasAdjacentShips = board.CheckIfHasAdjacentShips();								/* if has adjacent ships, this funcion also prints relevant message */

		return (!hasAdjacentShips && invalidShips_A.empty() && invalidShips_B.empty());
	}
}


void BattleshipTournamentManager::FindValidAndInvalidShipsInBoard(const BattleshipBoard& board, std::set<std::pair<char, std::set<Coordinate>>>& validShips_A, std::set<char>& invalidShips_A, std::set<std::pair<char, std::set<Coordinate>>>& validShips_B, std::set<char>& invalidShips_B)
{
	std::set<std::pair<char, std::set<Coordinate>>> setOfShipsDetails;					/* set of ships details - for example:
																						{<'m', {<1,2,7>,<1,3,7>}> , <'P', {<8,5,1>, <8,6,1> , <8,7,1>}> } */
	std::set<char> invalidShips;																 /* set of the invalid ships (to avoid duplicated ships in error messages) */


	setOfShipsDetails = board.ExtractShipsDetails();	         /* after this row, we have set of ships, maybe some of them invalid */



/* todo: delete this print */
//int i = 0;
//for(auto& shipDetail : setOfShipsDetails)
//{
//	std::cout << "ship: " << i++ <<"     " << shipDetail.first << "\t { ";
//	for (auto shipCor : shipDetail.second)
//	{
//		std::cout << shipCor << ", ";
//	}
//	std::cout << "} " << std::endl;
//}
	DeleteInvalidShipsDetailsEntryFromSet(setOfShipsDetails, invalidShips);				 /* after this row, we have only valid ships in setOfShipsDetails, and alse invalidShips  updated*/

	for (auto validShipDeatils : setOfShipsDetails)
	{
		if (BattleshipBoard::isPlayerShip(PLAYERID_A, validShipDeatils.first))
			validShips_A.insert(validShipDeatils);

		else validShips_B.insert(validShipDeatils);
	}

	for (auto invalidShipChar : invalidShips)
	{
		if (BattleshipBoard::isPlayerShip(PLAYERID_A, invalidShipChar))
			invalidShips_A.insert(invalidShipChar);

		else invalidShips_B.insert(invalidShipChar);
	}

}

void BattleshipTournamentManager::DeleteInvalidShipsDetailsEntryFromSet(std::set<std::pair<char, std::set<Coordinate>>>& setOfShipsDetails, std::set<char>& invalidShips)
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

void BattleshipTournamentManager::PrintWrongSizeOrShapeForShips(std::set<char>& invalidShipsSet, char playerChar)
{
	if (invalidShipsSet.empty()) return;

	for (auto shipChar : invalidShipsSet)
	{
		// TODO: print to the log  - std::cout << "Wrong size or shape for ship " << shipChar << " for player " << playerChar << std::endl; 
	}
}

void BattleshipTournamentManager::comparePlayersShips(std::set<std::pair<char, std::set<Coordinate>>> validShips_A, std::set<std::pair<char, std::set<Coordinate>>> validShips_B)
{
	if (validShips_A.size() != validShips_B.size())
	{
		//TODO: PRINT TO THE LOG - std::cout << "WARNING - the board is not balanced, players have different number of ships." << std::endl;
		return;
	}

	std::vector<std::pair<int, int>> shipsCountVec_A, shipsCountVec_B;

	BattleshipBoard::countShipsTypes(validShips_A, shipsCountVec_A);
	BattleshipBoard::countShipsTypes(validShips_B, shipsCountVec_B);
	bool hasDiffTypesBalance = false;

	if (shipsCountVec_A.size() != shipsCountVec_B.size())			/* we can have same number of ships, but different number from each type */
		hasDiffTypesBalance = true;

	else
	{
		for (int i = 0; i < shipsCountVec_A.size(); i++)			/* those vectors sorted by the ship type sizes */
		{
			if (shipsCountVec_A[i].first != shipsCountVec_A[i].first || shipsCountVec_A[i].second != shipsCountVec_A[i].second)
				hasDiffTypesBalance = true;

		}
	}

	if (hasDiffTypesBalance)
		;//TODO: PRINT TO THE LOG -  std::cout << "WARNING - the board is not balanced, players have same number of ships but not for each ship type." << std::endl; 
}

bool BattleshipTournamentManager::loadTournamentAlgos()
{
	std::string currDllFullPath;
	auto tmpFilenamesVector = BattleshipGameUtils::SortedDirlistSpecificExtension(inputDirPath, ".dll");

	if(tmpFilenamesVector.empty())
	{
		std::cout << "Missing algorithm (dll) files looking in path: " << inputDirPath << " (needs at least two)" << std::endl;
		return false;
	}

	for (auto currDllFilename : tmpFilenamesVector)
	{
		loadPlayerDll(currDllFilename);
	}

	std::cout << "Number of valid algos: " << algosDetailsVec.size() << std::endl; //todo: print to the log
	if (algosDetailsVec.size() < TOURNAMENT_MIN_PLAYERS)
	{
		std::cout << "Error: Missing minimum number of required Valid algorithm (dll) files looking in path: " << inputDirPath << " (needs at least two)" << std::endl;
		return false;
	}

	return true;

}

void BattleshipTournamentManager::loadPlayerDll(const std::string & currDllFilename)
{
	PlayerAlgoDetails currAlgo;
	currAlgo.dllPath = inputDirPath + "/" + currDllFilename;
	currAlgo.playerName = currDllFilename.substr(0, currDllFilename.find(".dll"));


	std::cout << "Trying to load dll player algo in: " << currAlgo.dllPath << std::endl;  //TODO: print to the log - 
	currAlgo.dllFileHandle = LoadLibraryA(currDllFilename.c_str()); // Notice: Unicode compatible version of LoadLibrary

	if (!currAlgo.dllFileHandle)
	{
		std::cout << "Cannot load dll in: " << currAlgo.dllPath << std::endl; //TODO: print to the log  - 
		return;
	}
	else
	{
		currAlgo.getAlgoFunc = reinterpret_cast<GetAlgoFuncType>(GetProcAddress(currAlgo.dllFileHandle, "GetAlgorithm"));
		if (!currAlgo.getAlgoFunc)
		{
			std::cout << "Error getting GetAlgorithm function from the dll file in: " << currAlgo.dllPath;
			FreeLibrary(currAlgo.dllFileHandle);
			return;
		}
	}

	currAlgo.algosIndexInVec = algosIndex;
	algosIndex++;
	algosDetailsVec.push_back(currAlgo);
}
