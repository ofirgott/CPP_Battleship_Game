#include "PlayerFromFile.h"
#include "BattleshipGameUtils.h"

std::pair<int, int> PlayerFromFile::attack()
{
	return std::pair<int, int>();
}

bool PlayerFromFile::init(const std::string & path)
{
	if (id == UNDEFINED_PLAYERID)
		return false;

	if (!BattleshipGameUtils::isValidDir(path))
		return false;

	


	return true;
}
