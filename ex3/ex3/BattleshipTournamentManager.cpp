#include "BattleshipTournamentManager.h"
#include "BattleshipGameUtils.h"
#include <iostream>
#include <condition_variable>
//#include "Ship.h"

void BattleshipTournamentManager::RunTurnament()
{
	createGamesQueue();
	for (int i = 0; i< maxGamesThreads; i++)
	{

		threadsPool.push_back(std::thread(&singleThreadJob));
	}

	for (auto & t:threadsPool) {
		t.join();
	}

}

void BattleshipTournamentManager::singleThreadJob()
{
	BattleshipGameManager game;
	StandingsTableEntryData gameResult;

	while (true)
	{
		
		{
			std::unique_lock<std::mutex> lock(gamesQueueMutex);

			queueEmptyCondition.wait(lock, [](std::queue<BattleshipGameManager> & const gamesQueue) {return !gamesQueue.empty(); });
			game = gamesQueue.front();
			gamesQueue.pop();
		}
	
			gameResult = game.Run();// function<void()> type
			updateAllGamesResults(gameResult ,sendotherPlayersName);
		
	}
}


void BattleshipTournamentManager::updateAllGamesResults(StandingsTableEntryData currGameRes,std::string otherName)
{
	StandingsTableEntryData otherPlayerData = StandingsTableEntryData::createOpponentData(currGameRes, otherName);
	std::vector<int>::iterator it;
	/*todo: check if the ++ of the atomic int works !!!!!!!!!!!!!!!!!!!!!!!! :(:(:(:(:(:(:(:(:(:(:(:(:(:(:(*/
	int cnt1 = ++playersProgress.at(currGameRes.PlayerName);
	int cnt2 = ++playersProgress.at(otherPlayerData.PlayerName); 

	//split result for 2 players
	// for player i and j allGamesResults[playersprogress[j]++] (atomic)
	//if(min has canged)- update and send to print
}


void BattleshipTournamentManager::createGamesQueue()
{
	for (auto& player1 : algosDetailsVec) {
		for (auto& player2 : algosDetailsVec) {
			for (auto& borad : boardsVec) {
				if (!(player1 == player2)) {

					todo: check if game was created successfuly
					gamesQueue.push(BattleshipGameManager(borad,player1, player2));

				}
			}
		}
	}
}


BattleshipTournamentManager::BattleshipTournamentManager(int argc, char * argv[]) : maxGamesThreads(DEFAULT_THREADS_NUM), successfullyCreated(false)
{
	if (!checkTournamentArguments(argc, argv)) return;

	if (!checkTournamentBoards()) return;

	if (!loadTournamentAlgos()) return;

	successfullyCreated = true;
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
		std::cout << "Error, Too many arguments!" << std::endl;
		return false;
	}

	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-threads") == 0)
		{
			if (i == argc - 1) {	/* we got threads flag but this is the last argument - this is an error because we need the int*/
				std::cout << "Error, got -threads flag, but threads value is missing." << std::endl;
				return false;
			}
			else
			{
				char* stringEnd = nullptr;
				maxGamesThreads = static_cast<int>(strtol(argv[++i], &stringEnd, 10));
				if (*stringEnd || maxGamesThreads < 1)
				{
					std::cout << "Error, -threads flag value is not a valid positive integer." << std::endl;
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

	if (boardsVec.empty())
	{
		std::cout << "No board files (*.sboard) looking in path: " << inputDirPath.c_str() << std::endl;
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
		//if (!Ship::isValidShipDetails(*it))
		//{
		//invalidShips.insert(it->first);
		//it = setOfShipsDetails.erase(it);
		//}
		//else
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


	for (auto currDllFilename : tmpFilenamesVector)
	{
		loadPlayerDll(currDllFilename);
	}

	if (algosDetailsVec.size() < TOURNAMENT_MIN_PLAYERS)
	{
		std::cout << "Missing algorithm (dll) files looking in path: " << inputDirPath << " (needs at least two)" << std::endl;
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

	algosDetailsVec.push_back(currAlgo);
}
