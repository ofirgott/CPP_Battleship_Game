#pragma once
#include "ShipInProcess.h"
#include <vector>
#include "IBattleshipGameAlgo.h"
#include <set>
#include"testPlayerSmart.h"


/* smart algo- keep track on all the coordintes that have been attacked during the game.
* the player holds a set of all legal coordinates that he is allowed to attack.
* after every attack remove the relevent coordiate from attackOptions.
* if possible remove the coordinates that surround the attacked coordinate (for example for a ship that 2 of her
* coordinates have been attacked, if the ship is horizontal remove the coordinates left & right to the ship from attackOptions)
* because of the new assumptions that player A and player B have the same kind of ships, the smart player holds an ordered vector
* that simulates the ship of the enemy and he is following what kind of ships the enemy holds all the time. 
* if the minimal size of ship the enemy has is for exemple 3 we can remove all attackOptions that are only in size 2
* those cordinates are being moved to another pulll and are saved of a case of inbalance between the two ship.
* if in any part of the game we find out that the two players are inbalance' all the coordinates from the new pool are going back to attackOptions pool
* if attackOptions is done and the game is not its another sign for  inbalance between the two ship, and in that case also 
* all the coordinates from the new pool are going back to attackOptions pool.
* each player holdes a vector of ships he already attacked. after HIT/SINK add the coordinate
* to the rellevent ship in the vector of shipInProcess or remove the ship from the vector if sank.
* the next attack is chosen from the vector of attacked ships which os sorted by size.
* when player wants to attck chose the largest ship. is ship of size 1 check all options up/down\left\right
* until found a coordinate which is in attack options. ifship is of siz 2,3,4 chose thenext coordinte that will
* continue a sequence of coordinates that belond to the ship (up/down or left/right) and in attack options.
*
* if the vector of attacked ships is of size 0. return a random coordinate to attack from the set of attackOptions

*/

struct compareCoordinates {
	friend bool operator<(const Coordinate& c1, const Coordinate& c2) {
		if (c1.col == c2.col) {
			if (c1.row == c2.row) {
				return c1.depth < c2.depth;
			}
			return c1.row < c2.row;
		}
		return c1.col < c2.col;
	}
};

class PlayerSmart : public IBattleshipGameAlgo
{

public:

	friend class testPlayerSmart; //// delete--------------------------------------------------------------------------------------
	PlayerSmart() :id(UNDEFINED_PLAYERID), boardRows(-1), boardCols(-1) ,boardDepth(-1), currSunkShipSize(-1), isBoardBalanced(true){};
	~PlayerSmart() = default;
	PlayerSmart& operator=(const PlayerSmart& otherSmartPlayer) = delete;
	PlayerSmart(const PlayerSmart& otherSmartPlayer) = delete;

	/* given a board update the set attackOptions with all the start options for attack
	* also initialazing the set of all the enemy ships*/
	void setBoard(const BoardData& board) override;

	// called every time the player changes his order
	void setPlayer(int player) override; 

	/* ask player for his move, the attacked coordinate returned, if no more attackes, the coordinate (-1,-1,-1) is returned*/
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
	int currSunkShipSize;
	bool isBoardBalanced;

//	static const int PLAYERID_A = 0;
//	static const int PLAYERID_B = 1;

	/*a vector of all current ship being attacked*/
	std::vector<ShipInProcess> attackedShips;
	/*a set of all the coordinates that are optional for attack*/
	std::set<Coordinate, compareCoordinates> attackOptions;

	/*improvments according to the new assumptions - balance of ships in board*/
	std::vector<std::pair<int, int>> shipsCount; // vector of enemie's ship's: pair of <shipSize,count> kept in icreasing order (by ship's size)
	std::set<Coordinate, compareCoordinates> imbalancedAttackOptions;// second poll of attack options in the case that the enemie's ship's count doesnt coorespond to my shipCount

	/*pours all content of imbalancedAttackOptions to attackOptions to continue the imbalanced game  */
	void PlayerSmart::pourImbalancedToAttackOptions();

	/*given the size of the ship that sunk,update that there is one less ship in this size
	if after the update the number of ships of size sunkShipSize is -1, the board was imbalanced 
	set isBoardBalanced = false and update the attack options pool	*/
	void PlayerSmart::updateShipsCount(int sunkShipSize);

	/*return the size of the other player smallest ship */
	int PlayerSmart::getMinShipSize();

	/* given attacked coordinate check all 4 directions if can delete Coordinates from attackOptions acording to the 
	* new assumption (balanced ships)*/
	void PlayerSmart::clearFourAdjecentCoors(Coordinate attackedCoordinate, AttackResult res,int minIncCoor, int maxInCoor ,bool isVertical , bool isHorizontal);

	/*for the nighbers of the attacked ship check in 6 directions if there are new unrelevent coordinates to attack
	* if the distance to the next "wall" is lass then the minimal ship - this space in nor opptional for atteck anymore and
	* we move it to the second pool */
	void PlayerSmart::checkSixDirections(Coordinate deadCoordinate);

	/* given a Coordinate count the number of available Coordinates to Attack  starting from startCoordinate 
	up to the closest removed Coor("wall"). if the distance between the "walls" is larger then the smallest ship the opponent owns
	return -1, (= cant remove anything in thiscase) else return the number of coordinates that should be removed.	*/
	int PlayerSmart::countDistance(Coordinate startCoordinate, int minShipSize, bool isVertical, bool isHorizontal, int direction);
	
	/*move coordinate to the second pool*/
	void PlayerSmart::transferCoordinatesToSecondPoll(Coordinate startCoordinate, int numOfCoors, bool isVertical, bool isHorizontal, int direction);

	/*checking if a current coordinate is in the Limits*/
	bool  PlayerSmart::isInBoard(int row, int col, int depth) const;

	/* given a coordinate search all ships in process and check if it belongs to one of them.
	* if so , add it to the ship's details and return the index of the ship (in the vector) it was added to.
	* if doesnt belong to any of them and the ship didnt sink add a new ship of size 1 to shipsinprocess && return -1*/
	int PlayerSmart::addCoorToShipsInProcess(int row, int col, int depth, Coordinate* nextCoorTosearch, AttackResult result);

	/* given a coordinate check all the coordinates (up/down/lwft/rgiht/in/out) and attack them if werent attacked yet.*/
	Coordinate PlayerSmart::sizeOneAttack(const Coordinate& candidate) const;

	/*util function for attack
	* given a set of coordinates that belong to 1 ship return the next coordinate to attack	*/
	Coordinate  PlayerSmart::nextAttackFromCoors(ShipInProcess& shipDetails, int numOfCoors) const;

	/* given start index and coordinate. look for pair in all sets starting from index, if found, add coordinate
	* to the ship at index and delete the ship that holds the matching pair	*/
	void PlayerSmart::mergeShipDetails(Coordinate* pair, int indexToupdate);

	/* given coordinate and start index, check if coordinate belongs to any of the attacked ships
	* if found return index of ship the coordinate belongs to, else -1.*/
	int PlayerSmart::findCoorInAttackedShips(const Coordinate& coorToSearch, int startIndex);

	/* given origin update its coordinates to <row,col,depth>*/
	static void updateCoordinates(Coordinate& origin, int row, int col, int depth) { origin.row = row; origin.col = col; origin.depth = depth; }

	/*return true if the input coordinate is in attackoptions, false- otherwise
	* util function for attack	*/
	bool PlayerSmart::isInAttackOptions(const Coordinate& coors) const;

	/* given a coordinate removefrom attackOptions is exists*/
	void PlayerSmart::removeOneCoordinate(Coordinate& coorToDelete);

	/*remove the adjecent coordinates to current coordinate. i.e if ship isvertical remove left,right,in,out coordinates to coordinate etc..  */
	void  PlayerSmart::removeAllIrreleventCoordinates(const Coordinate& pacoorir, bool isVertical, bool isHorizontal , bool isDimentional);

	/* assume the ships handked here are of size at least 2*/
	void PlayerSmart::removeSankFromReleventCoors(int indexOfCoor);

	//for tester +---------------------------------------------------------------------------------- delete 
	bool PlayerSmart::isInImbalancedOptions(const Coordinate& coors) const
	{
		auto it = imbalancedAttackOptions.find(coors);
		if (it != imbalancedAttackOptions.end())//coordinate was found in attackOptions
		{
			return true;
		}

		return false;
	}
};
