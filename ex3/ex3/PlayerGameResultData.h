//#pragma once
//#include <string>
//#include <algorithm>
//#include <vector>
//
///* we use class and not struct because we want to hide this information*/
//class PlayerGameResultData
//{
//public:
//
//	PlayerGameResultData() : numberOfPlayers(0), numberOfRounds(0), currentRound(0) {}
//	PlayerGameResultData(int newNumberOfPlayers, int newNumberOfRounds, int newCurrentRound) : numberOfPlayers(newNumberOfPlayers), numberOfRounds(newNumberOfRounds), currentRound(newCurrentRound) {}
//
//	~PlayerGameResultData() = default;
//
//	/* getters */
//	int getPlayersCnt()const { return numberOfPlayers; }
//	int getRoundsCnt()const { return numberOfRounds; }
//	int getRound()const { return currentRound; }
//
//	/* setters*/
//	void setNumberOfPlayers(int newNumberOfPlayers) { numberOfPlayers = newNumberOfPlayers; }
//	void setNumberOfRounds(int newNumberOfRounds) { numberOfRounds = newNumberOfRounds; }
//	void setCurrentRound(int newCurrentRound) { currentRound = newCurrentRound; }
//
//private:
//	std::vector<std::vector<StandingsTableEntryData>> gameResults;
//	int numberOfPlayers;
//	int numberOfRounds;
//	int currentRound;
//
//};
