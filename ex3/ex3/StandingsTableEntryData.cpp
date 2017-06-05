#include "StandingsTableEntryData.h"


size_t StandingsTableEntryData::getMaxPlayerNameWidth(const std::vector<StandingsTableEntryData>& standingsVec)
{
	size_t maxLen = 0;
	for (auto& playerData : standingsVec)
		if (playerData.PlayerName().length() > maxLen)
			maxLen = playerData.PlayerName().length();
	return maxLen;
}

bool StandingsTableEntryData::operator > (const StandingsTableEntryData & other) const
{
	if (winsCnt != other.winsCnt)
		return winsCnt > other.winsCnt;
	else
		return pointsFor > other.pointsFor;
}