#include "BattleshipBoard.h"

BattleshipBoard::BattleshipBoard(const char *** inputMatix, int inputRows, int inputCols, int inputDepth) : matrix(copyMatrix(inputMatix, inputRows, inputCols, inputDepth)), rows(inputRows), cols(inputCols), depth(inputDepth), isSuccCreated(true) {}

BattleshipBoard::BattleshipBoard(const std::string & boardPath)
{
}

BattleshipBoard & BattleshipBoard::operator=(const BattleshipBoard & otherBoard)
{
	// TODO: insert return statement here
}

const char *** BattleshipBoard::createPlayerBoard(int playerID) const
{
	return nullptr;
}

bool BattleshipBoard::CheckIfHasAdjacentShips() const
{
	return false;
}

bool BattleshipBoard::IsShipCharInBoard(char ch)
{
	ch = toupper(ch);
	return (ch == RUBBER_BOAT || ch == ROCKET_SHIP || ch == SUBMARINE || ch == DESTROYER);
}

std::set<std::pair<char, std::set<Coordinate>>> BattleshipBoard::ExtractShipsDetails() const
{
	return std::set<std::pair<char, std::set<Coordinate>>>();
}

void BattleshipBoard::getAllCurrShipCoords(char *** matrix, int x, int y, int z, char currShipChar, std::set<Coordinate>& coordOfCurrentShip, int matRows, int matCols, int matDepth)
{
}

char *** BattleshipBoard::copyMatrix(const char *** matrix, int rows, int cols, int depths)
{
	return nullptr;
}

void BattleshipBoard::deleteMatrix(const char *** matrix, int rows, int cols, int depths)
{
}

std::set<Coordinate> BattleshipBoard::getNearbyCoordinates(int x, int y, int z) const
{
	return std::set<Coordinate>();
}

bool BattleshipBoard::isPlayerShip(const int playerId, const char shipChar)
{
	return false;
}

char *** BattleshipBoard::AllocateNewMatrix(int rows, int cols, int depths)
{
	return nullptr;
}

void BattleshipBoard::InitEmptyBoardVector(std::vector<char> board, int rows, int cols, int depths)
{
}


void BattleshipBoard::CopyInputLineToBoard(char *** matrix, const std::string & line, int currRow, int cols, int depths)
{
}
