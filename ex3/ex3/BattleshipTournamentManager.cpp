#include "BattleshipTournamentManager.h"
#include "BattleshipGameUtils.h"
#include <iostream>
#include <condition_variable>
#include <atomic>
#include "BattleshipPrint.h"
#include <thread>
#include <fstream>
#include <string>

BattleshipTournamentManager::BattleshipTournamentManager(int argc, char * argv[]) : maxGamesThreads(UNINITIALIZED_ARG), successfullyCreated(true), TOURNAMENT_MIN_PLAYERS(UNINITIALIZED_ARG)
{

	if (!checkTournamentArguments(argc, argv)) {					/* checks arguments validity, and parse all arguments from program input and config file */
		successfullyCreated = false;
		return;
	}

	if (!checkTournamentBoards())									/* checks all board in the input data, and update the board vectors with all valid boards */
		successfullyCreated = false;

	if (!loadTournamentAlgos())										/* checks all players algorithms in the input data, and update the algos vectors with all valid algos */
		successfullyCreated = false;

	if (!successfullyCreated) return;								/* if we don't have enough algos or boards, we can not create new tournament */

	std::cout << "Number of legal players: " << algosDetailsVec.size() << std::endl;
	std::cout << "Number of legal boards: " << boardsVec.size() << std::endl;

	//Ofir -we need to put next rows in seperate function - init tournament data structures or something..

	//algosIndex = 0;
	createGamesPropertiesQueue();								/* create all games propertioes for all possible games - each 2 players will play twice on each board - home and away*/

	auto numOfplayers = algosDetailsVec.size();
	int numOfRounds = static_cast<int> (gamesPropertiesQueue.size() * 2 / numOfplayers);

	std::cout <<"num of round: "<< numOfRounds << " num of games: "<< gamesPropertiesQueue.size()  << std::endl; //todo: print to the log
	std::cout << "num of threads: " << maxGamesThreads << std::endl;
	allGamesResults.resize(numOfplayers);															/* allGamesResults dimensions are numOfPlayer X numOfRounds */
	for (auto i = 0; i < numOfplayers; i++) { 
		allGamesResults[i].resize(numOfRounds);														/* use resize to init with initial values for every game */
		allRoundsCumulativeData.emplace_back(PlayerGameResultData(algosDetailsVec[i].playerName));
	}

	allRoundsData.reserve(numOfRounds);								/* use reserve beacuse of the atomic member of RoundData, we will init every value in the next loop */
	for (auto i = 0; i < numOfRounds; i++) {
		allRoundsData.emplace_back(numOfplayers, false);		//change it to num of players
	}

	playersProgress = std::vector<std::atomic<int>>(numOfplayers);

}

BattleshipTournamentManager::~BattleshipTournamentManager()
{
	std::vector<PlayerAlgoDetails>::iterator vitr;

	for (vitr = algosDetailsVec.begin(); vitr != algosDetailsVec.end(); ++vitr)
	{
		if (vitr->dllFileHandle)
			FreeLibrary(vitr->dllFileHandle);										 /*  close all the dynamic libs we opened  */
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
	

	for (auto i = 1; i < argc; i++)
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
				maxGamesThreads = static_cast<size_t>(strtol(argv[++i], &stringEnd, 10));
				if (*stringEnd || maxGamesThreads < 1)
				{
					std::cout << "Error: -threads flag value is not a valid positive integer." << std::endl;
					return false;
				}
			}
		}
		else path = argv[i]; /* this is the dir path */
	}

	if (!BattleshipGameUtils::getFullPath(path)) return false;

	if (!BattleshipGameUtils::isValidDir(path)) {									/* checks if directory in dir_path exists */
		std::cout << "Wrong path: " << path << std::endl;
		return false;
	}
	inputDirPath = path;

	parseDefaultsFromConfigFile();
	maxGamesThreads = (maxGamesThreads == UNINITIALIZED_ARG ? DEFAULT_THREADS_NUM : maxGamesThreads);

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

void BattleshipTournamentManager::comparePlayersShips(std::set<std::pair<char, std::set<Coordinate>>>& validShips_A, std::set<std::pair<char, std::set<Coordinate>>>& validShips_B)
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
		std::cout << "WARNING - the board is not balanced, players have same number of ships but not for each ship type." << std::endl; //TODO: PRINT TO THE LOG - 
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
		std::cout << "Error: Missing minimum number of required Valid algorithm (dll) files looking in path: " << inputDirPath << " (needs at least " << TOURNAMENT_MIN_PLAYERS << ")" << std::endl;
		return false;
	}

	return true;

}

bool BattleshipTournamentManager::loadPlayerDll(const std::string& currDllFilename)
{
	PlayerAlgoDetails currAlgo;
	currAlgo.dllPath = inputDirPath + "/" + currDllFilename;
	currAlgo.playerName = currDllFilename.substr(0, currDllFilename.find(".dll"));


	std::cout << "Trying to load dll player algo in: " << currAlgo.dllPath << std::endl;  //TODO: print to the log - 
	currAlgo.dllFileHandle = LoadLibraryA(currAlgo.dllPath.c_str()); // Notice: Unicode compatible version of LoadLibrary

	if (!currAlgo.dllFileHandle)
	{
		std::cout << "Cannot load dll in: " << currAlgo.dllPath << std::endl; //TODO: print to the log  - 
		return false;
	}
	else
	{
		std::cout << "Trying to get the GetAlgorithm function from the dll file" << std::endl;  //TODO: print to the log - 
		currAlgo.getAlgoFunc = reinterpret_cast<GetAlgoFuncType>(GetProcAddress(currAlgo.dllFileHandle, "GetAlgorithm"));
		if (!currAlgo.getAlgoFunc)
		{
			std::cout << "Error getting GetAlgorithm function from the dll file in: " << currAlgo.dllPath; //todo: print to the log
			FreeLibrary(currAlgo.dllFileHandle);
			return false;
		}
		std::cout << "Success loading player algorithm from dll in: " << currAlgo.dllPath << std::endl; //TODO: print to the log  - 
	}

	//currAlgo.algosIndexInVec = algosIndex++;
	algosDetailsVec.push_back(std::move(currAlgo));
	return true;
}

void BattleshipTournamentManager::parseDefaultsFromConfigFile() 
{

	auto tmpFilenamesVector = BattleshipGameUtils::SortedDirlistSpecificExtension(inputDirPath, ".config");

	BattleshipPrint::setPrintOneTable(PRINT_SINGLE_TABLE);
	BattleshipPrint::setDelay(BattleshipPrint::printDefaultDealy);
	TOURNAMENT_MIN_PLAYERS = TOURNAMENT_MIN_PLAYERS_DEFAULT;

	if (tmpFilenamesVector.empty())
	{
		std::cout << "No Config files (*.config) looking in path: " << inputDirPath.c_str() << std::endl;		//todo: print to the log
		return;
	}

	auto configFileFullPath = inputDirPath + "/" + tmpFilenamesVector[0];		//takes the first config file
	std::cout << "Config file found in path: " << configFileFullPath << std::endl;

	std::string line;

	std::ifstream configFile(configFileFullPath.c_str());
	if(configFile.is_open())
	{
		while(std::getline(configFile, line)){							/* we assume that the design and values in config file are valid */
			std::istringstream configLine(line);
			std::string key;
			if (std::getline(configLine, key, '='))
			{
				std::string value;
				if (std::getline(configLine, value))
					storeConfigline(key, value);
			}
		}
		
		configFile.close();
	}

	else {														/* we can't open the board file */
		std::cout << "Error opening Config file in " << configFileFullPath << "we will take our defaults" << std::endl; //TODO: print to the logger - 	
	}

}

void BattleshipTournamentManager::storeConfigline(const std::string& key, const std::string& value)
{
	char* stringEnd = nullptr;
	bool validConfigAssign = false;
	int intValue = static_cast<size_t>(strtol(value.c_str(), &stringEnd, 10));
	if (*stringEnd || intValue < 0)
	{
		std::cout << "WARNING: config entry value is not valid. we will not take this value." << std::endl;
		return;
	}

	if (strcmp(key.c_str(), "MAX_THREADS_NUM") == 0)
	{
		validConfigAssign = true;
		maxGamesThreads = (maxGamesThreads == UNINITIALIZED_ARG ? intValue : maxGamesThreads);
	}
	else if (strcmp(key.c_str(), "PRINT_SINGLE_TABLE") == 0)
	{
		validConfigAssign = true;
		BattleshipPrint::setPrintOneTable(intValue ? true : false);
	}
	else if (strcmp(key.c_str(), "SINGLE_TABLE_DELAY") == 0)
	{
		validConfigAssign = true;
		BattleshipPrint::setDelay(intValue);
	}
	else if (strcmp(key.c_str(), "TOURNAMENT_MIN_PLAYERS") == 0)
	{
		validConfigAssign = true;
		TOURNAMENT_MIN_PLAYERS = intValue;
	}
	if(validConfigAssign) std::cout << "DEBUG, assign default value from config file, KEY = " << key << "\t VALUE = " << intValue << std::endl;	//todo: print to the log
		
}

void BattleshipTournamentManager::RunTournament()	
{
	maxGamesThreads = (maxGamesThreads > gamesPropertiesQueue.size() ? gamesPropertiesQueue.size() : maxGamesThreads); /* in case there are more threads then games */
	//std::cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << BattleshipPrint::getDelay() << std::endl;
	std::vector <std::thread> threadsPool;
	threadsPool.reserve(maxGamesThreads);
	
	for (auto i = 0; i< maxGamesThreads; i++)
	{
		threadsPool.emplace_back(std::thread(&BattleshipTournamentManager::singleThreadJob, this));	 /* creating a pool of threads */
	}

	int currRound = 0;
	
	while (currRound < allRoundsData.size()) {														/* while there are more rounds to print keep waiting for next round */

		std::unique_lock<std::mutex> lk(isRoundDoneMutex);
		
		isRoundDoneCondition.wait(lk, [&]() {return allRoundsData[currRound].isRoundDone; });		/* waiting for current round to end by order (first till last) */
		lk.unlock();

		if (allRoundsData[currRound].isRoundDone) {															/* sanity check in case of spurious wake up */
			for (auto i = 0; i < algosDetailsVec.size(); i++) {												/* update sum fileds for current round  */
				allRoundsCumulativeData[i].winsCnt += allGamesResults[i][currRound].winsCnt;
				allRoundsCumulativeData[i].lossesCnt += allGamesResults[i][currRound].lossesCnt;
				allRoundsCumulativeData[i].pointsFor += allGamesResults[i][currRound].pointsFor;
				allRoundsCumulativeData[i].pointsAgainst += allGamesResults[i][currRound].pointsAgainst;
			}
			
			std::cout << "Players status after round: " << currRound +1  << ": " << std::endl;
			for (size_t i = 0; i < algosDetailsVec.size(); i++)
			{
				size_t r = allRoundsData.size();
				std::cout << ", Player" << i << algosDetailsVec[i].playerName <<  ": ";
				for (size_t j = 0; j < allRoundsData.size(); j++)
				{
					
					if (allGamesResults[i][j].WinsNumber() == 0 && allGamesResults[i][j].LossesNumber() == 0 && allGamesResults[i][j].pointsFor == 0 && allGamesResults[i][j].pointsAgainst == 0) {
						r = j;
						j = allRoundsData.size();
					}
					
				}
				std::cout << r;

			}
			std::cout << std::endl<<std::endl;
			std::cout << gamesPropertiesQueue.size() << " Games remaining..." << std::endl;
			if (gamesPropertiesQueue.size() == 1) {
				std::cout << "ITS " << gamesPropertiesQueue.front().getPlayerIndexA() << " against " << gamesPropertiesQueue.front().getPlayerIndexB() << " on board " << gamesPropertiesQueue.front().getBoardIndex() << std::endl;
			}
			BattleshipPrint::printStandingsTable(allRoundsCumulativeData, currRound + 1, allRoundsData.size());//printing the round
		
			currRound++;//next round to wait for
		}

	}
	//std::cout << "games completed" << std::endl;
	for (auto & t : threadsPool) {
		t.join();
	}

}

void BattleshipTournamentManager::singleThreadJob()
{
	std::cout << "---------------I AM THREAD" << std::endl;
	while (!gamesPropertiesQueue.empty())
	{
		std::unique_lock<std::mutex> lock(gamesQueueMutex);				/* we lock here to deal with the games queue */
		
		if (gamesPropertiesQueue.empty()) {								/* if the queue is empty, we are done -> no new games will be inserted to the queue */
			return;														/* lock is unlocked here */
		}
		auto currGameProperties = gamesPropertiesQueue.front();			/* takes the next game form the queue */
		gamesPropertiesQueue.pop();
		lock.unlock();

		std::unique_ptr<IBattleshipGameAlgo> playerAlgoA(algosDetailsVec[currGameProperties.getPlayerIndexA()].getAlgoFunc());
		std::unique_ptr<IBattleshipGameAlgo> playerAlgoB(algosDetailsVec[currGameProperties.getPlayerIndexB()].getAlgoFunc());

		/* we take the relevant 2 pointers from the players vetrors, and insert them to unique ptrs -> then we will move the move the responsibility for those ptrs to the (single) game manager */

		BattleshipGameManager currGame(boardsVec[currGameProperties.getBoardIndex()], std::move(playerAlgoA), std::move(playerAlgoB));
	
		auto currGameResult = currGame.Run();						/* the game result returned is from the perspective of playerA */
		
		updateGamesResults(currGameResult, currGameProperties.getPlayerIndexA(), currGameProperties.getPlayerIndexB());
		
	}
}


void BattleshipTournamentManager::updateGamesResults(const PlayerGameResultData& currGameResultA, int playerIndexA, int playerIndexB)
{

	auto currGameResultB = PlayerGameResultData::createOpponentData(currGameResultA);					 /* creates gameResults in view of the second player */

	int currRoundA = playersProgress[playerIndexA]++;		/* Performs atomic post-increment, equivalent to fetch_add(1), and returns the value (int) before the modification */
	int currRoundB = playersProgress[playerIndexB]++;

	// update allGamesResults in the relevent indexes
	allGamesResults[playerIndexA][currRoundA] = currGameResultA;
	allGamesResults[playerIndexB][currRoundB] = currGameResultB;


	if (--allRoundsData[currRoundA].numOfPlayersLeft == 0) {
		std::unique_lock<std::mutex> lock(isRoundDoneMutex);
		allRoundsData[currRoundA].isRoundDone = true;
		lock.unlock();
		isRoundDoneCondition.notify_one();
	}

	if (--allRoundsData[currRoundB].numOfPlayersLeft == 0) {
		std::unique_lock<std::mutex> lock(isRoundDoneMutex);
		allRoundsData[currRoundB].isRoundDone = true;
		lock.unlock();
		isRoundDoneCondition.notify_one();
	}

}


void BattleshipTournamentManager::createGamesPropertiesQueue()
{
	for (auto k = 0; k < boardsVec.size(); k++)
	{
		for (auto i = 0; i < algosDetailsVec.size(); i++)
		{
			for (auto j = 0; j < algosDetailsVec.size(); j++)
			{
				if (i != j) {
					gamesPropertiesQueue.emplace(SingleGameProperties(k, i, j));
				}
			}
		}
	}

}
