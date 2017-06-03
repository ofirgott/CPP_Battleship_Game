#include "BattleshipTournamentManager.h"
#include "BattleshipGameUtils.h"
#include <iostream>

BattleshipTournamentManager::BattleshipTournamentManager(int argc, char * argv[]) : maxGamesThreads(DEFAULT_THREADS_NUM), successfullyCreated(false)
{
}

BattleshipTournamentManager::~BattleshipTournamentManager()
{
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

	}
	

	if(boardsVec.empty())
	{
		std::cout << "No board files (*.sboard) looking in path: " << inputDirPath.c_str() << std::endl;
		return false;
	}
	else return true;
	
}

bool BattleshipTournamentManager::checkBoardValidity(const BattleshipBoard& board)const
{
	if (!board .isSuccessfullyCreated()) return false;

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

bool BattleshipTournamentManager::loadTournamentAlgos()
{
	return false;
}
