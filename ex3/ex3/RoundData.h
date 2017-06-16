#pragma once
#include <atomic>

class RoundData
{
public:
	
	friend class BattleshipTournamentManager;

	RoundData() : isRoundDone(false) { }
	//Round(int rNum, int atom, bool s) : roundNumber(rNum), status(s){ numOfGamesLeft.store(0); }
	explicit RoundData(size_t numOfPlayers, bool s = false) : isRoundDone(s) { numOfPlayersLeft.store(numOfPlayers); }
	RoundData(const RoundData& round) = delete;
	RoundData(RoundData&& round) noexcept : isRoundDone(round.isRoundDone) { numOfPlayersLeft.store(round.numOfPlayersLeft.load()); }

	~RoundData() = default;

	//bool IsRoundDone()const { return isRoundDone;  }

private:

	std::atomic<size_t> numOfPlayersLeft;
	bool isRoundDone;

	//explicit Round(const Round& round) : roundNumber(round.roundNumber), status(round.status) { numOfGamesLeft.store(round.numOfGamesLeft.load()); }			/* copy constructor */	
	//Round& operator=(Round& round) { roundNumber = round.roundNumber; numOfGamesLeft.store(round.numOfGamesLeft.load());  status = round.status; return *this; }								/* delete copy assignment */
};
