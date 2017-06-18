#include "BattleshipTournamentManager.h"
#include "BattleshipGameUtils.h"
#include <iostream>
#include <condition_variable>
#include <atomic>
#include "BattleshipPrint.h"
#include <thread>
#include <fstream>
#include <string>

 const std::string BattleshipTournamentManager::LOG_FILENAME("game.log");


BattleshipTournamentManager::BattleshipTournamentManager(int argc, char * argv[]) : maxGamesThreads(UNINITIALIZED_ARG), successfullyCreated(true), TOURNAMENT_MIN_PLAYERS(UNINITIALIZED_ARG)
{

	if (!checkTournamentArguments(argc, argv)) {					/* checks arguments validity, and parse all arguments from program input and config file */
		successfullyCreated = false;
		return;
	}
	
	Logger::Init(inputDirPath + "/" + LOG_FILENAME, logLevelVal);
	printProgramValuesToLog();

	if (!checkTournamentBoards())									/* checks all board in the input data, and update the board vectors with all valid boards */
		successfullyCreated = false;

	if (!loadTournamentAlgos())										/* checks all players algorithms in the input data, and update the algos vectors with all valid algos */
		successfullyCreated = false;

	if (!successfullyCreated) {
		Logger::append("Failed creating tournament. Extiting...", Error);	/* if we don't have enough algos or boards, we can not create new tournament */
		return;
	}								
	Logger::append("Tournament successfully created !", Info);
	std::cout << "Number of legal players: " << algosDetailsVec.size() << std::endl;
	std::cout << "Number of legal boards: " << boardsVec.size() << std::endl << std::endl;

	createGamesPropertiesQueue();								/* creates all games propertioes for all possible games - each 2 players will play twice on each board - home and away*/

	auto numOfplayers = algosDetailsVec.size();
	auto numOfRounds = static_cast<int> (gamesPropertiesQueue.size() * 2 / numOfplayers);

	Logger::append("Number of Games in the tournament:\t" + std::to_string(gamesPropertiesQueue.size()), Info);
	Logger::append("Number of Rounds in the tournament:\t" + std::to_string(numOfRounds), Info);

	allGamesResults.resize(numOfplayers);															/* allGamesResults dimensions are numOfPlayer X numOfRounds */
	for (auto i = 0; i < numOfplayers; i++) { 
		allGamesResults[i].resize(numOfRounds);														/* use resize to init with initial values for every game */
		allRoundsCumulativeData.emplace_back(PlayerGameResultData(algosDetailsVec[i].playerName));
	}

	allRoundsData.reserve(numOfRounds);								/* use reserve beacuse of the atomic member of RoundData, we will init every value in the next loop */
	for (auto i = 0; i < numOfRounds; i++) {
		allRoundsData.emplace_back(numOfplayers, false);
	}
	playersProgress = std::vector<std::atomic<int>>(numOfplayers);
}

BattleshipTournamentManager::~BattleshipTournamentManager()
{
	std::vector<PlayerAlgoDetails>::iterator vitr;

	for (vitr = algosDetailsVec.begin(); vitr != algosDetailsVec.end(); ++vitr)
	{
		if (vitr->dllFileHandle)
			FreeLibrary(vitr->dllFileHandle);										 /* close all the dynamic libs we opened */
	}
	Logger::Close();																/* close the logger */
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
	logLevelVal = Logger::DEFAULT_LEVEL;
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
		Logger::append("No board files in dir, we will exit from the tournament after checking algos...", Error);
		return false;
	}

	for (auto currBoardFilename : tmpFilenamesVector)
	{
		currBoardFullPath = inputDirPath + "/" + currBoardFilename;
		BattleshipBoard currBoard(currBoardFullPath);

		Logger::append("Checking validity of board in: " + currBoardFullPath, Info);	

		if (checkBoardValidity(currBoard))
		{
			boardsVec.push_back(std::move(currBoard));			/* take the board without create new board */
			Logger::append("Board in: " + currBoardFullPath + " loaded succssefully", Info); 
		}
		else
		{
			Logger::append("Board in: " + currBoardFullPath + " skipped, because of the errors above", Warning);
		}
	}
	Logger::append("Number of valid bords: " + std::to_string(boardsVec.size()), Info);

	if (boardsVec.empty())
	{
		std::cout << "Error: No valid board files (*.sboard) looking in path: " << inputDirPath.c_str() << std::endl;
		Logger::append("No valid boards in directory at all. We will exit from the tournament after checking algos", Error);
		return false;
	}
	else return true;

}

bool BattleshipTournamentManager::checkBoardValidity(const BattleshipBoard& board)
{
	if (!board.isSuccessfullyCreated()) {
		Logger::append("failed Creating board", Warning);
		return false;
	}

	std::set<std::pair<char, std::set<Coordinate>>> validShips_A, validShips_B;								/* for FindValidAndInvalidShipsInBoard output */
	std::set<char> invalidShips_A, invalidShips_B;


	FindValidAndInvalidShipsInBoard(board, validShips_A, invalidShips_A, validShips_B, invalidShips_B);

	if (validShips_A.empty() || validShips_B.empty())
	{
		Logger::append("One of the players (or both) has no ships at all - invalid board.", Warning);
		return false;
	}
	else {
		PrintWrongSizeOrShapeForShips(invalidShips_A, A);
		PrintWrongSizeOrShapeForShips(invalidShips_B, B);

		comparePlayersShips(validShips_A, validShips_B);

		bool hasAdjacentShips = board.CheckIfHasAdjacentShips();								/* if has adjacent ships, this funcion also prints relevant message */
		if (hasAdjacentShips) Logger::append("Adjacent Ships on Board", Warning);
		return (!hasAdjacentShips && invalidShips_A.empty() && invalidShips_B.empty());
	}
}


void BattleshipTournamentManager::FindValidAndInvalidShipsInBoard(const BattleshipBoard& board, std::set<std::pair<char, std::set<Coordinate>>>& validShips_A, std::set<char>& invalidShips_A, std::set<std::pair<char, std::set<Coordinate>>>& validShips_B, std::set<char>& invalidShips_B)
{
	std::set<std::pair<char, std::set<Coordinate>>> setOfShipsDetails;					/* set of ships details - for example:
																						{<'m', {<1,2,7>,<1,3,7>}> , <'P', {<8,5,1>, <8,6,1> , <8,7,1>}> } */
	std::set<char> invalidShips;													 /* set of the invalid ships (to avoid duplicated ships in error messages) */


	setOfShipsDetails = board.ExtractShipsDetails();	         /* after this row, we have set of ships, maybe some of them invalid */

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
		std::string tmpStr("");
		tmpStr += shipChar;
		Logger::append("Wrong size or shape for ship " + tmpStr + " for player " + playerChar, Warning); 
	}
}

void BattleshipTournamentManager::comparePlayersShips(std::set<std::pair<char, std::set<Coordinate>>>& validShips_A, std::set<std::pair<char, std::set<Coordinate>>>& validShips_B)
{
	if (validShips_A.size() != validShips_B.size())
	{
		Logger::append("the board is not balanced, players have different number of ships", Warning);
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
		Logger::append("the board is not balanced, players have same number of ships but not for each ship type", Warning);
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

	Logger::append("Number of valid algos: " + std::to_string(algosDetailsVec.size()), Info);
	if (algosDetailsVec.size() < TOURNAMENT_MIN_PLAYERS)
	{
		std::cout << "Error: Missing minimum number of required Valid algorithm (dll) files looking in path: " << inputDirPath << " (needs at least " << TOURNAMENT_MIN_PLAYERS << ")" << std::endl;
		Logger::append("Directory does not have enough valid algos. Exiting...", Error);
		return false;
	}

	return true;

}

bool BattleshipTournamentManager::loadPlayerDll(const std::string& currDllFilename)
{
	PlayerAlgoDetails currAlgo;
	currAlgo.dllPath = inputDirPath + "/" + currDllFilename;
	currAlgo.playerName = currDllFilename.substr(0, currDllFilename.find(".dll"));


	Logger::append("Trying to load dll player algo in: " + currAlgo.dllPath, Info); 
	currAlgo.dllFileHandle = LoadLibraryA(currAlgo.dllPath.c_str()); // Notice: Unicode compatible version of LoadLibrary

	if (!currAlgo.dllFileHandle)
	{
		Logger::append("Cannot load dll in: " + currAlgo.dllPath, Warning); 
		return false;
	}
	else
	{
		Logger::append("Trying to get the GetAlgorithm function from the dll file", Debug); 
		currAlgo.getAlgoFunc = reinterpret_cast<GetAlgoFuncType>(GetProcAddress(currAlgo.dllFileHandle, "GetAlgorithm"));
		if (!currAlgo.getAlgoFunc)
		{
			Logger::append("Error getting GetAlgorithm function from the dll file in: " + currAlgo.dllPath,Warning);
			FreeLibrary(currAlgo.dllFileHandle);
			return false;
		}
		Logger::append("Success loading player algorithm from dll in: " + currAlgo.dllPath, Info);  
	}

	algosDetailsVec.push_back(std::move(currAlgo));
	return true;
}

/* we assume that the config file has values from the form: <ARG>=<VALUE> (with no spaces) */
void BattleshipTournamentManager::parseDefaultsFromConfigFile() 
{
	auto tmpFilenamesVector = BattleshipGameUtils::SortedDirlistSpecificExtension(inputDirPath, ".config");
	BattleshipPrint::setPrintOneTable(PRINT_SINGLE_TABLE);
	BattleshipPrint::setDelay(BattleshipPrint::printDefaultDealy);
	TOURNAMENT_MIN_PLAYERS = TOURNAMENT_MIN_PLAYERS_DEFAULT;

	if (tmpFilenamesVector.empty())
	{
		Logger::append("No Config files (*.config) looking in path: " + inputDirPath, Info);
		return;
	}

	auto configFileFullPath = inputDirPath + "/" + tmpFilenamesVector[0];		//takes the first config file
	Logger::append("Config file found in path: " + configFileFullPath, Info);
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
					storeConfigLine(key, value);
			}
		}
		
		configFile.close();
	}
	else {														/* we can't open the config file */
		Logger::append("Error opening Config file in " + configFileFullPath + ". we will take our defaults", Warning); 	
	}
}

void BattleshipTournamentManager::storeConfigLine(const std::string& key, const std::string& value)
{
	char* stringEnd = nullptr;
	int intValue = static_cast<size_t>(strtol(value.c_str(), &stringEnd, 10));
	if (*stringEnd || intValue < 0)
	{
		Logger::append("Config file entry value " +  value + " for " + key + "key is not valid. we will not take this value.", Warning);
		return;
	}
	bool validConfigAssign = false;

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
		Logger::append("SINGLE_TABLE_DELAY set to:\t" + std::to_string(intValue), Info);
		BattleshipPrint::setDelay(intValue);
	}
	else if (strcmp(key.c_str(), "TOURNAMENT_MIN_PLAYERS") == 0)
	{
		validConfigAssign = true;
		TOURNAMENT_MIN_PLAYERS = intValue;
	}
	else if (strcmp(key.c_str(), "LOG_LEVEL") == 0)
	{
		validConfigAssign = true;
		logLevelVal = static_cast<LogLevel>(intValue);
	}
	if(validConfigAssign) Logger::append("set default value from config file, KEY = " + key + "\t VALUE = " + std::to_string(intValue), Debug);
}

void BattleshipTournamentManager::printRouondGameResToLog(int currRound) const
{
	std::string currRoundGamesResultsStr = "";
	for (auto i = 0; i < algosDetailsVec.size(); i++)
	{
		std::string res = "";
		if (allGamesResults[i][currRound].WinsNumber()) res = "Won";
		else if (allGamesResults[i][currRound].LossesNumber()) res = "Lost";
		else res = "tied";
	
		currRoundGamesResultsStr += "\t\t\t\t\t\t\t\t\tPlayer: " + std::to_string(i) + "(" + algosDetailsVec[i].playerName + ") " + res + "\t" + std::to_string(allGamesResults[i][currRound].PointsFor()) + " : " + std::to_string(allGamesResults[i][currRound].PointsAgainst()) + "\n";
	}
	Logger::append("Games results in round " + std::to_string(currRound+1) + ":\n" + currRoundGamesResultsStr, Debug);
}

void BattleshipTournamentManager::printProgramValuesToLog() const
{
	Logger::append("Tournament directory set to:\t" + inputDirPath, Info);
	Logger::append("MAX_THREADS_NUM set to:\t" + std::to_string(maxGamesThreads), Info);
	Logger::append("PRINT_SINGLE_TABLE set to:\t" + std::to_string(PRINT_SINGLE_TABLE), Info);
	Logger::append("TOURNAMENT_MIN_PLAYERS set to:\t" + std::to_string(TOURNAMENT_MIN_PLAYERS), Info);
}

void BattleshipTournamentManager::RunTournament()	
{
	maxGamesThreads = (maxGamesThreads > gamesPropertiesQueue.size() ? gamesPropertiesQueue.size() : maxGamesThreads); /* in case there are more threads then games */
	Logger::append("Number of Games threads set to:\t" + std::to_string(maxGamesThreads), Info);
	
	std::vector <std::thread> threadsPool;
	threadsPool.reserve(maxGamesThreads);
	
	Logger::append("START running tournament games...", Info);
	
	for (auto i = 0; i< maxGamesThreads; i++)
	{
		threadsPool.emplace_back(std::thread(&BattleshipTournamentManager::singleThreadJob, this));	 /* creating a pool of threads */
		Logger::append("New thread created", Debug);
	}
	int currRound = 0;
	
	while (currRound < allRoundsData.size()) {														/* while there are more rounds to print keep waiting for next round */

		std::unique_lock<std::mutex> lk(isRoundDoneMutex);
		
		isRoundDoneCondition.wait(lk, [&]() {return allRoundsData[currRound].isRoundDone; });		/* waiting for current round to end by order (first till last) */
		lk.unlock();
		
		printRouondGameResToLog(currRound);

		if (allRoundsData[currRound].isRoundDone) {															/* sanity check in case of spurious wake up */
			for (auto i = 0; i < algosDetailsVec.size(); i++) {												/* update sum fileds for current round  */
				allRoundsCumulativeData[i].winsCnt += allGamesResults[i][currRound].winsCnt;
				allRoundsCumulativeData[i].lossesCnt += allGamesResults[i][currRound].lossesCnt;
				allRoundsCumulativeData[i].pointsFor += allGamesResults[i][currRound].pointsFor;
				allRoundsCumulativeData[i].pointsAgainst += allGamesResults[i][currRound].pointsAgainst;
			}
			Logger::append("before printing round " + std::to_string((currRound + 1)) + ":\t" + std::to_string(gamesPropertiesQueue.size()) + " Games remaining to play" , Debug);	
			BattleshipPrint::printStandingsTable(allRoundsCumulativeData, currRound + 1, allRoundsData.size());		/* printing current round data */
			currRound++;																							/* next round to wait for */
		}
	}
	for (auto & t : threadsPool) {
		t.join();
	}
	Logger::append("FINISH all tournament games and tables prints", Info);
}

void BattleshipTournamentManager::singleThreadJob()
{
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
				if (i != j) {												    /* player can not play against himself*/
					gamesPropertiesQueue.emplace(SingleGameProperties(k, i, j));
				}
			}
		}
	}

}
