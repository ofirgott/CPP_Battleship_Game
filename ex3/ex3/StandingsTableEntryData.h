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

	/* given one players data create the opponents data by switchin the loss-wins and pointsfor-agqainst fields*/
	static StandingsTableEntryData createOpponentData(const StandingsTableEntryData& thisData, std::string otherName);

	/* getters */
	std::string PlayerName()const { return playerName; }
	int WinsNumber()const { return winsCnt; }
	int LossesNumber()const { return lossesCnt; }
	int PointsFor()const { return pointsFor; }
	int PointsAgainst()const { return pointsAgainst; }

	static size_t getMaxPlayerNameWidth(const std::vector<StandingsTableEntryData>& standingsVec);



	/* setters*/
	void setPlayerName(std::string newName) { playerName = newName; }
	void setWinsNumber(int newWinsNum) { winsCnt = newWinsNum; }
	void setLossesNumber(int newLossesNum) { lossesCnt = newLossesNum; }
	void setPointsFor(int newPointsForNum) { pointsFor = newPointsForNum; }
	void setPointsAgainst(int newPointsAgainstNum) { pointsAgainst = newPointsAgainstNum; }

	//StandingsTableEntryData& operator=(StandingsTableEntryData&& arg)noexcept = default;  			//move assignment
	//StandingsTableEntryData& operator=(const StandingsTableEntryData& arg) = default;
	//StandingsTableEntryData(const StandingsTableEntryData& other) = default;			/* deletes copy constructor */
	//bool operator<(const StandingsTableEntryData &rhs) const { return playerName < rhs.playerName; }

	//void StandingsTableEntryData::updateFields(StandingsTableEntryData& const dataOrigin);
	StandingsTableEntryData& operator=(const StandingsTableEntryData & arg);
private:

	std::string playerName;
	int winsCnt;
	int lossesCnt;
	int pointsFor;
	int pointsAgainst;
};