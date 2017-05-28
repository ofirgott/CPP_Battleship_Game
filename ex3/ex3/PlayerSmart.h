#pragma once
#include "ShipInProcess.h"
#include <vector>
#include "IBattleshipGameAlgo.h"
#include <set>


/* smart algo- keep track on all the coordintes that have been attacked during the game.
* the player holds a set of all legal coordinates that he is allowed to attack.
* after every attack remove the relevent coordiate from attackOptions.
* if possible remove the coordinates that surround the attacked coordinate (for example for a ship that 2 of her
* coordinates have been attacked, if the ship is horizontal remove the coordinates left & right to the ship from attackOptions)
* each player holdes a vector of ships he already attacked. after HIT/SINK add the coordinate
* to the rellevent ship in the vector of SHIPINPROCess or remove the ship from the vector if sank.
* the next attack is chosen from the vector of attacked ships which os sorted by size.
* when player wants to attck chose the largest ship. is ship of size 1 check all options up/down\left\right
* until found a coordinate which is in attack options. ifship is of siz 2,3,4 chose thenext coordinte that will
* continue a sequence of coordinates that belond to the ship (up/down or left/right) and in attack options.
*
* if the vector of attacked ships is of size 0. return a random coordinate to attack from the set of attackOptions
*
*/
static std::vector<IBattleshipGameAlgo *> _instancesVec; //our player collection

class PlayerSmart : public IBattleshipGameAlgo
{
public:
	PlayerSmart() :id(UNDEFINED_PLAYERID), boardRows(-1), boardCols(-1) {};
	~PlayerSmart() = default;
	PlayerSmart& operator=(const PlayerSmart& otherSmartPlayer) = delete;
	PlayerSmart(const PlayerSmart& otherSmartPlayer) = delete;

	/* given a board update the set attackOptions with all the start options for attack */
	void setBoard(const BoardData& board) override;

	// called every time the player changes his order
	void setPlayer(int player) override;

	/* ask player for his move, the attacked pair returned, if no more attackes the pair (-1,-1) is returned*/
	Coordinate attack() override;

	/* notify on last move result,update player smart by the information given*/
	void notifyOnAttackResult(int player, Coordinate move, AttackResult result) override;

	static const int UNDEFINED_PLAYERID = -1;


	//Player() : id(UNDEFINED_PLAYERID), boardRows(-1), boardCols(-1) {};
	//Player(const Player& otherPlayer) = delete;				/* deletes copy constructor */
	//virtual ~Player() = default;
	//Player& operator=(const Player& otherPlayer) = delete;	/* deletes the assignment operator - we want a player to be a Non Copyable object  */
	/* checking the initialization of the board was successful */
	//	bool init(const std::string& path) override { return (id != -1); }

private:
	int id;					// players id , if id == -1 player is invalid or undefined
	int boardRows;
	int boardCols;
	int boardDepth;
//	static const int PLAYERID_A = 0;
//	static const int PLAYERID_B = 1;
	/*a vector of all current ship being attacked*/
	std::vector<ShipInProcess> attackedShips;

	/*a set of all the coordinates that are optional for attack*/
	std::set<Coordinate> attackOptions;

	/*checking if a current coordinate is in the Limits*/
	bool  PlayerSmart::isInBoard(int row, int col, int depth) const;

	/* given a coordinate search all ships in process and check if it belongs to one of them.
	* if so , add it to the ship's details and return the index of the ship (in the vector) it was added to.
	* if doesnt belong to any of them and the ship didnt sink add a new ship of size 1 to shipsinprocess && return -1
	*/
	int PlayerSmart::addCoorToShipsInProcess(int row, int col, int depth, Coordinate* nextCoorTosearch, AttackResult result);

	/* given a coordinate check all the coordinates (up/down/lwft/rgiht) and attack them if werent attacked yet.*/
	Coordinate PlayerSmart::sizeOneAttack(const Coordinate& candidate) const;

	/*util function for attack
	* given a set of coordinates that belong to 1 ship return the next coordinate to attack	*/
	Coordinate  PlayerSmart::nextAttackFromCoors(ShipInProcess& shipDetails, int numOfCoors) const;

	/* given start index and pair. look for pair in all sets starting from index, if found, add pair
	* to the ship at index and delete the ship that holds the matching pair
	*/
	void PlayerSmart::mergeShipDetails(Coordinate* pair, int indexToupdate);

	/* given pair and start index, check if pair belongs to any of the attacked ships
	* if found return index of ship the pair belongs to, else -1.
	*/
	int PlayerSmart::findCoorInAttackedShips(const Coordinate& coorToSearch, int startIndex);

	/* given origin update its coordinates to <row,col>*/
	static Coordinate updateCoordinates(Coordinate& origin, int row, int col, int depth) { origin.row = row; origin.col = col; origin.depth = depth; }

	/*return true if the input pair is in attackoptions, false- otherwise
	* util function for attack
	*/
	bool PlayerSmart::isInAttackOptions(const Coordinate& coors) const;

	/* given a coordinate removefrom attackOptions is exists*/
	void PlayerSmart::removeOneCoordinate(Coordinate& coorToDelete);

	/*remove the adjecent coordinates to pair. i.e if ship isvertical remove left,right coordinates to pair etc..  */
	void  PlayerSmart::removeAllIrreleventCoordinates(const Coordinate& pacoorir, bool isVertical, bool isHorizontal , bool isDimentional);

	/* assume the ships handked here are of size at least 2*/
	void PlayerSmart::removeSankFromReleventCoors(int indexOfCoor);
};
