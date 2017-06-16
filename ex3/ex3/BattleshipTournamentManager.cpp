#include "BattleshipTournamentManager.h"
#include "BattleshipGameUtils.h"
#include <iostream>
#include <condition_variable>
#include <atomic>
//	#include <thread>
//#include "Ship.h"


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

	auto numOfplayers = algosDetailsVec.size();
	auto numOfBoards = boardsVec.size();
	int numOfRounds = static_cast<int> (gamesPropertiesQueue.size() * 2 / numOfplayers);
	std::cout <<"num of round: "<< numOfRounds << " num of games: "<< gamesPropertiesQueue.size()  << std::endl;
	/*todo: init vector of vectors*/
	allGamesResults.resize(numOfplayers); //vector of size number of players
	for (auto i = 0; i < numOfplayers; i++) { // for each player vector of size num of rounds
		allGamesResults[i].resize(numOfRounds);
	}

	//allRounds.resize(numOfRounds); // 
	//for (auto i = 0; i < numOfRounds; i++) {
	//	allRounds[i].numOfGamesLeft.store(gamesPropertiesQueue.size() / numOfRounds);		//Ofir - I fixed it from store(numOfRounds);. I think it works now. EDIT: maybe it is not true
	//	//allRounds[i].roundNumber = i; unneccessary..
	//	allRounds[i].status = false;
	//}
	allRounds.reserve(numOfRounds);
	for (auto i = 0; i < numOfRounds; i++) {
		allRounds.emplace_back(numOfplayers, false);		//change it to num of players
		//allRounds[i].numOfGamesLeft.store(gamesPropertiesQueue.size() / numOfRounds);		//Ofir - I fixed it from store(numOfRounds);. I think it works now. EDIT: maybe it is not true
		//allRounds[i].roundNumber = i; unneccessary..
		//allRounds[i].status = false;
	}


	playersProgress = std::vector<std::atomic<int>>(numOfplayers);
	//playersProgress.resize(numOfplayers);
	//for (auto i = 0; i < numOfplayers; i++)
	//{
		//playersProgress[i].store(-1);
		//std::atomic<int>		 a{ 0 };
		//playersProgress.emplace_back(a);
		//std::atomic_init(a, 0);
	//}

	for (auto i = 0; i < numOfplayers; i++) {	//Ofir - dup	
		cumulativeResultsData.emplace_back(PlayerGameResultData(algosDetailsVec[i].playerName));
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
				maxGamesThreads = static_cast<size_t>(strtol(argv[++i], &stringEnd, 10));
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
	currAlgo.dllFileHandle = LoadLibraryA(currAlgo.dllPath.c_str()); // Notice: Unicode compatible version of LoadLibrary

	if (!currAlgo.dllFileHandle)
	{
		std::cout << "Cannot load dll in: " << currAlgo.dllPath << std::endl; //TODO: print to the log  - 
		return;
	}
	else
	{
		std::cout << "Trying to get the GetAlgorithm function from the dll file" << std::endl;  //TODO: print to the log - 
		currAlgo.getAlgoFunc = reinterpret_cast<GetAlgoFuncType>(GetProcAddress(currAlgo.dllFileHandle, "GetAlgorithm"));
		if (!currAlgo.getAlgoFunc)
		{
			std::cout << "Error getting GetAlgorithm function from the dll file in: " << currAlgo.dllPath; //todo: print to the log
			FreeLibrary(currAlgo.dllFileHandle);
			return;
		}
		std::cout << "Success loading player algorithm from dll in: " << currAlgo.dllPath << std::endl; //TODO: print to the log  - 
	}

	currAlgo.algosIndexInVec = algosIndex;
	algosIndex++;
	algosDetailsVec.push_back(std::move(currAlgo));
}


void BattleshipTournamentManager::RunTournament()
{
	auto numberOfRounds = allRounds.size();
	auto numberOfGames = allGamesResults.size();
	auto numOfPlayers = algosDetailsVec.size();
	int currRound = 0;

	//in case there are more threads then games
	if (maxGamesThreads > numberOfGames) {
		maxGamesThreads = numberOfGames;
	}

	std::vector <std::thread> threadsPool;
	threadsPool.reserve(maxGamesThreads);

	//creating a pool of threads
	for (auto i = 0; i< maxGamesThreads; i++)
	{
		threadsPool.emplace_back(std::thread(&BattleshipTournamentManager::singleThreadJob, this));	
	}
	//for the thread issue:
	//https://stackoverflow.com/questions/26516683/reusing-thread-in-loop-c/29742586#29742586
	//https://stackoverflow.com/questions/23717151/why-emplace-back-is-faster-than-push-back


	//while there are more rounds to print keep waiting for next round
	while (currRound < numberOfRounds) {

		std::unique_lock<std::mutex> lk(isRoundDoneMutex);
		//waiting for current round to end by order (first till last)
		isRoundDoneCondition.wait(lk, [&]() {return allRounds[currRound].isRoundDone; }); //Ofir - maybe prefer to do [&] ?
		lk.unlock();

		if (allRounds[currRound].isRoundDone) {//update sum fileds for current round 
			for (auto i = 0; i < numOfPlayers; i++) {
				cumulativeResultsData[i].winsCnt += allGamesResults[i][currRound].winsCnt;
				cumulativeResultsData[i].lossesCnt += allGamesResults[i][currRound].lossesCnt;
				cumulativeResultsData[i].pointsFor += allGamesResults[i][currRound].pointsFor;
				cumulativeResultsData[i].pointsAgainst += allGamesResults[i][currRound].pointsAgainst;
			}
			
			std::cout << "Players status after round: " << currRound +1  << ": " << std::endl;
			for (size_t i = 0; i < numOfPlayers; i++)
			{
				size_t r = numberOfRounds;
				std::cout << "Player: " << i << " - \t";
				for (size_t j = 0; j < numberOfRounds; j++)
				{
					
					if (allGamesResults[i][j].WinsNumber() == 0 && allGamesResults[i][j].LossesNumber() == 0 && allGamesResults[i][j].pointsFor == 0 && allGamesResults[i][j].pointsAgainst == 0) {
						r = j;
						j = numberOfRounds;
					}
					
				}
				std::cout << r;
				std::cout << std::endl;
			}
			BattleshipPrint::printStandingsTable(cumulativeResultsData, currRound + 1, allRounds.size());//printing the round
		
			currRound++;//next round to wait for
		}

	}
	std::cout << "games completed" << std::endl;
	for (auto & t : threadsPool) {
		t.join();
	}

}

void BattleshipTournamentManager::singleThreadJob()
{
	PlayerGameResultData currGameResult;

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

		/* we take the relevant 2 pointersfrom the players vetrors, and insert them to unique ptrs -> then we will move the move the responsibility for those ptrs to the (single) game manager */

		BattleshipGameManager currGame(boardsVec[currGameProperties.getBoardIndex()], std::move(playerAlgoA), std::move(playerAlgoB));
		currGameResult = currGame.Run();

								// the game result returned is from the perspective of playerA
		//currGameResult.playerName = algosDetailsVec[currGameProperties.getPlayerIndexA()].playerName;		//Ofir - why we need the name? can we leave it empty?
		//std::cout << "game: " << currGameProperties.getPlayerIndexA() << "VS " << currGameProperties.getPlayerIndexB() << " in Board: " << currGameProperties.getBoardIndex() << std::endl;
		updateAllGamesResults(currGameResult, currGameProperties);
		//std::cout << "Game Done" << std::endl;
	}
}


void BattleshipTournamentManager::updateAllGamesResults(const PlayerGameResultData& currGameRes, const SingleGameProperties& gamsProperty)
{

	// players indexes 
	auto playerAIndex = algosDetailsVec[gamsProperty.getPlayerIndexA()].algosIndexInVec;
	auto playerBIndex = algosDetailsVec[gamsProperty.getPlayerIndexB()].algosIndexInVec;

	//create gameResults for the second player 
	auto otherPlayerData = PlayerGameResultData::createOpponentData(currGameRes, algosDetailsVec[gamsProperty.getPlayerIndexB()].playerName);

	// indexes of the properties in the specific player's vector 
	int propertyIndexA = ++playersProgress[playerAIndex];		//Ofir - maybe we need to use volatile or lock here, as described here: https://stackoverflow.com/a/27768860
	int propertyIndexB = ++playersProgress[playerBIndex];

	// update allGamesResults in the relevent indexes
	allGamesResults[playerAIndex][propertyIndexA-1] = currGameRes;
	allGamesResults[playerBIndex][propertyIndexB-1] = otherPlayerData;


	--allRounds[propertyIndexA-1].numOfPlayersLeft;
	if (allRounds[propertyIndexA-1].numOfPlayersLeft == 0) {
		//need to take care of locks and mutexes and condition variables here, need to set cv in .h	
		std::unique_lock<std::mutex> lock(isRoundDoneMutex);
		allRounds[propertyIndexA-1].isRoundDone = true;
		lock.unlock();
		isRoundDoneCondition.notify_one();

	}
	--allRounds[propertyIndexB-1].numOfPlayersLeft;
	if (allRounds[propertyIndexB-1].numOfPlayersLeft == 0) {
		std::unique_lock<std::mutex> lock(isRoundDoneMutex);
		allRounds[propertyIndexB-1].isRoundDone = true;
		lock.unlock();
		isRoundDoneCondition.notify_one();
	}

}


void BattleshipTournamentManager::createGamesPropertiesQueue()
{
	std::vector<SingleGameProperties> tmpPropertiesVector;
	
	for (auto i = 0; i < algosDetailsVec.size(); i++)
	{
		for (auto j = 0; j < algosDetailsVec.size(); j++)
		{
			for (auto k = 0; k < boardsVec.size(); k++)
			{
				if (i != j) {
					//SingleGameProperties gameDetails(k, i, j);
					tmpPropertiesVector.push_back(SingleGameProperties(k, i, j));
				}
			}
		}
	}
	std::sort(tmpPropertiesVector.begin(), tmpPropertiesVector.end(),
		[](const SingleGameProperties & a, const SingleGameProperties & b) { return a.getBoardIndex() < b.getBoardIndex(); });

	for (auto element : tmpPropertiesVector) {  

		gamesPropertiesQueue.emplace(element);
	}
	
}
