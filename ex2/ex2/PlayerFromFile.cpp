#include "PlayerFromFile.h"

std::pair<int, int> PlayerFromFile::attack()
{
	return std::pair<int, int>();
}

void PlayerFromFile::notifyOnAttackResult(int player, int row, int col, AttackResult result)
{
}

std::pair<AttackResult, int> PlayerFromFile::realAttack(std::pair<int, int> coor)
{
	return std::pair<AttackResult, int>();
}

std::vector<std::pair<int, int>> PlayerFromFile::parseAttackFile(const char * attackFilePath)
{
	return std::vector<std::pair<int, int>>();
}

std::vector<std::string> PlayerFromFile::split(const std::string & s, char delim, bool * succsessfulSplit)
{
	return std::vector<std::string>();
}

bool PlayerFromFile::isSeperated(const std::string & token)
{
	return false;
}

IBattleshipGameAlgo* GetAlgorithm()
{
	_instancesVec.push_back(new PlayerFromFile());			// Create new instance and keep it in vector
	return _instancesVec[_instancesVec.size() - 1];		// Return last instance
}