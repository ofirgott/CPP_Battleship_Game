#pragma once
#include <string>
#include <vector>


/**
 * \brief  Maintains data that necessary for single game result. we also use this class to maintain cumulative player data in tournament
 * Note that we represent single tie with 0 in winsCnt and lossesCnt
 * 
 * (we use class and not struct because we want to hide this information)
 */
class PlayerGameResultData
{
public:
	friend class BattleshipTournamentManager;

	explicit PlayerGameResultData(std::string name, int wins = 0, int losses = 0, int pFor = 0, int pAgainst = 0) : playerName(name), winsCnt(wins), lossesCnt(losses), pointsFor(pFor), pointsAgainst(pAgainst) {}

	explicit PlayerGameResultData(int wins = 0, int losses = 0, int pFor = 0, int pAgainst = 0) : playerName(""), winsCnt(wins), lossesCnt(losses), pointsFor(pFor), pointsAgainst(pAgainst) {}														/* ctor without name. we don't need it for single game result */
	~PlayerGameResultData() = default;

	/* given one players data create the opponents data by switching the loss-wins and pointsfor-agqainst fields*/
	static PlayerGameResultData createOpponentData(const PlayerGameResultData& otherPlayerData);

	/* getters */
	std::string PlayerName()const { return playerName; }
	int WinsNumber()const { return winsCnt; }
	int LossesNumber()const { return lossesCnt; }
	int PointsFor()const { return pointsFor; }
	int PointsAgainst()const { return pointsAgainst; }

	static size_t getMaxPlayerNameWidth(const std::vector<PlayerGameResultData>& standingsVec);			/* for nice prints */

	PlayerGameResultData& operator=(const PlayerGameResultData & arg);									/* assignment operator */
private:

	std::string playerName;											/* the name is for the cumulative case, in order to print it in the table */
	int winsCnt;													/* in single game this var will be 0/1*/
	int lossesCnt;													/* in single game this var will be 0/1*/
	long pointsFor;
	long pointsAgainst;
};
