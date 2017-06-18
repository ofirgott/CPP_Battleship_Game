#pragma once
#include <atomic>

class RoundData
{
public:
	
	friend class BattleshipTournamentManager;					/* for easy accessing */

	RoundData() : isRoundDone(false) { }
	explicit RoundData(size_t numOfPlayers, bool s = false) : isRoundDone(s) { numOfPlayersLeft.store(numOfPlayers); }
	
	RoundData(const RoundData& round) = delete;					/* deletes copy constructor */
	
	RoundData(RoundData&& round) noexcept : isRoundDone(round.isRoundDone) { numOfPlayersLeft.store(round.numOfPlayersLeft.load()); }		/* move ctor */
	/* we make the move only in at the begining of the tournament, so we dont have to worry about thread safety here (the load the store treak) */

	~RoundData() = default;


private:

	std::atomic<size_t> numOfPlayersLeft;			/* (ATOMIC and thread safe!) -  checks how many players have to play in this round */
	bool isRoundDone;								/* indicated if numOfPlayers == 0 and we done with current round */

};
