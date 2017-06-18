#include "StandingsTableEntryData.h"



StandingsTableEntryData StandingsTableEntryData::createOpponentData(const StandingsTableEntryData & thisData, std::string otherName)
{
	return StandingsTableEntryData(otherName, thisData.LossesNumber(), thisData.WinsNumber(), thisData.PointsAgainst(), thisData.PointsFor());
}

size_t StandingsTableEntryData::getMaxPlayerNameWidth(const std::vector<StandingsTableEntryData>& standingsVec)
{
	size_t maxLen = 0;
	for (auto& playerData : standingsVec)
		if (playerData.PlayerName().length() > maxLen)
			maxLen = playerData.PlayerName().length();
	return maxLen;
}



//void StandingsTableEntryData::updateFields(StandingsTableEntryData& const dataOrigin) {
//
//	playerName = dataOrigin.playerName;
//	winsCnt = dataOrigin.winsCnt;
//	lossesCnt = dataOrigin.lossesCnt;
//	pointsFor = dataOrigin.PointsFor;
//	pointsAgainst = dataOrigin.pointsAgainst;
//}

//StandingsTableEntryData & StandingsTableEntryData::operator=(StandingsTableEntryData && arg)
//{
//	playerName = arg.playerName;
//	winsCnt = arg.winsCnt;
//	lossesCnt = arg.lossesCnt;
//	pointsFor = arg.pointsFor;
//	pointsAgainst = arg.pointsFor;
//	return *this;
//
//}
//
StandingsTableEntryData & StandingsTableEntryData::operator=(const StandingsTableEntryData & arg)
{
	playerName = arg.playerName;
	winsCnt = arg.winsCnt;
	lossesCnt = arg.lossesCnt;
	pointsFor = arg.pointsFor;
	pointsAgainst = arg.pointsAgainst;
	return *this;
}
