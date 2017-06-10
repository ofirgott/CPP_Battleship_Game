#pragma once


//#include "Ship.h"
#include "IBattleshipGameAlgo.h"
#include "ShipsBoard.h"
#include <memory>

/*keeps all current algo details*/
class GamePlayerData {
	friend class BattleshipGameManager;

public:

	GamePlayerData& operator=(const GamePlayerData& otherPlayer) = delete;		/* deletes assignment constructor */
	GamePlayerData& GamePlayerData::operator=(GamePlayerData&& other) noexcept;
	GamePlayerData(GamePlayerData&& other)noexcept = delete;					/*  move c'tor */
	GamePlayerData(const GamePlayerData& otherPlayer) = delete;					/* deletes copy constructor */
	GamePlayerData() : id(UNDEFINED_PLAYERID), playerAlgo(nullptr), shipsBoard(), currShipsCount(0), score(0), hasMoreMoves(true){};
	//id(UNDEFINED_PLAYERID), playerAlgo(nullptr), hasMoreMoves(true), score(0), shipsBoard(), currShipsCount(0) {}
	
	GamePlayerData(int playerID, std::unique_ptr<IBattleshipGameAlgo> inputPlayerAlgo, ShipsBoard inputShipsBoard, size_t shipsCount) : id(playerID),playerAlgo(std::move(inputPlayerAlgo)), shipsBoard(std::move(inputShipsBoard)), currShipsCount(shipsCount),score(0), hasMoreMoves(true) {}
	~GamePlayerData();

private:
	int id;
	std::unique_ptr<IBattleshipGameAlgo> playerAlgo;						  /* will be deleted by the BattleshipGameManager class!  */
	ShipsBoard shipsBoard;
	size_t currShipsCount;
	int score;
	bool hasMoreMoves;
	
	static const int UNDEFINED_PLAYERID = -1;

	/*get next valid attack coordinates,if player doesnt have more moves return <-1,-1,-1>*/
	Coordinate getAlgoNextAttack() const;

	/* given coordinates player updates number of ships he has got left&& updates the attack in his ships details.
	return the attack result and the number of points the attack scored
	if player attacked the same coordinate in the second time return <Hit, -1> to indicate that the player shoudnt keep his turn
	*/
	std::pair<AttackResult, int> realAttack(Coordinate coor);

	/* update players score to the prev score + num
	assume- num >= 0
	*/
	void incrementScore(int value) { if (value > 0) score += value; }

	bool isSet()const { return (id >= 0 && playerAlgo && shipsMatrix && currShipsCount > 0 && boardRows > 0 && boardCols > 0); }

};