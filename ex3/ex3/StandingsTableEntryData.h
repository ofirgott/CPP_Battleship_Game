#pragma once
#include <string>
#include <algorithm>
#include <vector>

/* we use class and not struct because we want to hide this information*/
class StandingsTableEntryData
{
public:

	StandingsTableEntryData() : playerName(""), winsCnt(0), lossesCnt(0), pointsFor(0), pointsAgainst(0) {}
	StandingsTableEntryData(std::string name, int wins, int losses, int pFor, int pAgainst) : playerName(name), winsCnt(wins), lossesCnt(losses), pointsFor(pFor), pointsAgainst(pAgainst) {}

	~StandingsTableEntryData() = default;
	StandingsTableEntryData(const StandingsTableEntryData& other) = delete;					/* deletes copy constructor */

	/* getters */
	std::string PlayerName()const { return playerName; }
	int WinsNumber()const { return winsCnt; }
	int LossesNumber()const { return lossesCnt; }
	int PointsFor()const { return pointsFor; }
	int PointsAgainst()const { return pointsAgainst; }
	
	static size_t getMaxPlayerNameWidth(const std::vector<StandingsTableEntryData>& standingsVec);
	

	/* setters*/
	void setWinsNumber(int newWinsNum) {  winsCnt = newWinsNum; }
	void setLossesNumber(int newLossesNum) {  lossesCnt = newLossesNum; }
	void setPointsFor(int newPointsForNum) {  pointsFor = newPointsForNum; }
	void setPointsAgainst(int newPointsAgainstNum) {  pointsAgainst = newPointsAgainstNum; }


	/* assume that we compare players with the same number of games */
	bool operator > (const StandingsTableEntryData& other)const;
	
	static void sortPlayersStandingsVector(std::vector<StandingsTableEntryData> standingsVector) { std::sort(standingsVector.begin(), standingsVector.end()); }

private:

	std::string playerName;
	int winsCnt;
	int lossesCnt;
	int pointsFor;
	int pointsAgainst;
};
