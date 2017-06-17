#include "PlayerGameResultData.h"



PlayerGameResultData PlayerGameResultData::createOpponentData(const PlayerGameResultData & otherPlayerData)
{
	return PlayerGameResultData(otherPlayerData.LossesNumber(), otherPlayerData.WinsNumber(), otherPlayerData.PointsAgainst(), otherPlayerData.PointsFor());
}

size_t PlayerGameResultData::getMaxPlayerNameWidth(const std::vector<PlayerGameResultData>& standingsVec)
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
PlayerGameResultData & PlayerGameResultData::operator=(const PlayerGameResultData & arg)
{
	playerName = arg.playerName;
	winsCnt = arg.winsCnt;
	lossesCnt = arg.lossesCnt;
	pointsFor = arg.pointsFor;
	pointsAgainst = arg.pointsAgainst;
	return *this;
}
