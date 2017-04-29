#include "PlayerFromFile.h"
#include "BattleshipGameUtils.h"

std::pair<int, int> PlayerFromFile::attack()
{
	return std::pair<int, int>();		//todo: implement
}

bool PlayerFromFile::init(const std::string & path)
{
	if (id == UNDEFINED_PLAYERID || !BattleshipGameUtils::isValidDir(path))
		return false;

	int attackFileOrder;
	auto attackFilenames = BattleshipGameUtils::SortedDirlistSpecificExtension(path, ".attack");
	
	if(attackFilenames.size() == 0)			/* no relevant attack files in path */
	
		return false;
	
	else if (attackFilenames.size() == 1)
		attackFileOrder = 0;
	
	else
	{
		if (id == PLAYERID_A) attackFileOrder = 0;
		else attackFileOrder = 1;
	}

	auto myAttackFilePath = path + "\\" + attackFilenames[attackFileOrder];
	
	movesVector = parseAttackFile(myAttackFilePath);	//todo : add parseAttackFile to the code 

	movesVectorItr = movesVector.begin();

	return true;
}
