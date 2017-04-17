#include "BattleshipBoard.h"
#include "Player.h"
#include <set>
#include <map>

#define NUM_OF_PLAYER_SHIPS 5 //todo: constants file

class BattleshipGameManager
{
public:
	BattleshipGameManager() : boardFilePath(), attackFilePath_A(), attackFilePath_B(), mainBoard(BattleshipBoard()), playerA(), playerB(), currPlayer(), otherPlayer() { std::cout << "we here"; };
	BattleshipGameManager(std::string boardPath, std::string attackFilePath_a, std::string attackFilePath_b, bool& isGameSuccessfullyCreated);
	~BattleshipGameManager() {};
	BattleshipGameManager(const BattleshipGameManager& otherGame) = delete;
	//todo: deal with other operators
	void Run();


private:

	std::string boardFilePath;
	std::string attackFilePath_A;
	std::string attackFilePath_B;
	BattleshipBoard  mainBoard;
	Player playerA;
	Player playerB;
	Player*  currPlayer;
	Player*  otherPlayer;

	char** GetCopyOfBoard()const { return mainBoard.GetCopyOfBoard(); };
	bool checkBoardValidity(const BattleshipBoard& battleship_board);
	static std::pair<size_t, std::set<char>> FindNumberOfValidShipsInBoard(const char** board, int rows, int cols);
	static void DeleteInvalidShipsDetailsEntryFromSet(std::set<std::pair<char, std::set<std::pair<int, int>>>>& setOfShipsDetails, std::set<char>& invalidShips);
	void PrintWrongSizeOrShapeForShips(std::set<char>& invalidShipsSet, char playerChar);
	bool isCorrectNumberOfShipsForPlayer(size_t validShipsCnt, char playerChar);
	void updateCurrPlayer(); /*utility function for Run, switches currentPlayer with otherPlayer */
	void outputGameResult();

};
