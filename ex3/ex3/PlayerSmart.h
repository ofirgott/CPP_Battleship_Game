#pragma once
#include "ShipInProcess.h"
#include <vector>
#include <tuple>
#include "IBattleshipGameAlgo.h"
#include <set>
#include "testPlayerSmart.h"
#include "BattleshipGameUtils.h"

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


class PlayerSmart : public IBattleshipGameAlgo
{
public:

	PlayerSmart() :id(UNDEFINED_PLAYERID), boardRows(-1), boardCols(-1), boardDepth(-1), currSunkShipSize(-1), isBoardBalanced(true) {};
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

private:
	static const int UNDEFINED_PLAYERID = -1; // should be private?? 
	int id;		// players id , if id == -1 player is invalid or undefined
	int boardRows;
	int boardCols;
	int boardDepth;
	int currSunkShipSize;
	bool isBoardBalanced;
	std::vector<ShipInProcess> attackedShips; 	/*a vector of all current ship being attacked*/
	std::set<Coordinate> attackOptions; 	/*a set of all the coordinates that are optional for attack*/
	std::vector<std::pair<int, int>> shipsCount; /*Count of assumed opponents ships count <shipSize,count> increasing order of ship's size */
	std::set<Coordinate> imbalancedAttackOptions;// second pool of attack option if Board is Imbalanced
	std::set<Coordinate> permanentlyDeadCoordinates;// sunk coordinates

	/* for each dead coordinate check all six directions to the next dead coordinate
	if there isnt room for smallest ship transfer the gap to imbalanced options*/
	void PlayerSmart::transferAllWallsToImbalanced();

	/* check all 6 directions of deadCoordinate if it became an affective "wall"
	* if the distance from deadCoordinate to the next "wall" is less then the minimal ship
	-this space in not opptional for atteck anymore and we move it to the second pool */
	void PlayerSmart::checkSixDirectionsForWalls(Coordinate deadCoordinate);

	/* given a coordinate check 4 adjecent coor's that arnt in the incremental direction
	of the ship if they are new walls*/
	void PlayerSmart::checkConstantDirectionsForWalls(Coordinate attackedCoordinate, bool isVertical, bool isHorizontal, bool isDimentional);

	/* given a coordinate check 2 incremental edges of the ship if they are new walls*/
	void PlayerSmart::checkIncrementalDirectionsForWalls(Coordinate attackedCoordinate, ShipInProcess& attackedShip);

	/* given a Coordinate - count the number of permanently dedCoordinates starting from startCoordinate.
	if the distance between the "walls" is larger then the smallest ship the opponent owns
	return -1, (= cant remove anything in this case) else return the number of coordinates that should be removed.	*/
	int PlayerSmart::countDistance(Coordinate deadCoordinate, int minShipSize, int vertical, int horizontal, int direction);

	/*move coordinate to the second pool*/
	void PlayerSmart::transferCoordinatesToSecondPoll(Coordinate startCoordinate, int numOfCoors, int vertical, int horizontal, int direction);


	/* assume the ships handled here are of size at least 2. remove the incremental
	edges of the sunk ship and remove the ship from the attacked ships vector*/
	void PlayerSmart::removePermementlyIncrementalDirection(int shipToDelIndex);

	/*remove the coors 4 adjecent coordinates. that arnt in the incremental direction*/
	void PlayerSmart::removePermanentlyConstDirections(const Coordinate& coor, bool isVertical, bool isHorizontal, bool isDimentional);

	/*for a given coordinate check if its edges are walls*/
	void PlayerSmart::cleanAttackOptions(const Coordinate & targetCoor);

	/*for each coordinate in the surrounding of the ship if not in the incremental direction check if a wall*/
	void PlayerSmart::cleanAttackOptions(ShipInProcess& shipToClean, const Coordinate& attacked);

	/* given a set of coordinates that belong to 1 ship return the next coordinate to attack	*/
	Coordinate  PlayerSmart::nextAttackFromCoors(ShipInProcess& shipDetails, int numOfCoors) const;

	/*pours all content of imbalancedAttackOptions to attackOptions to continue the imbalanced game  */
	void PlayerSmart::pourImbalancedToAttackOptions();

	/* given a coordinate check all the coordinates (up/down/lwft/rgiht/in/out) and attack them if werent attacked yet.*/
	Coordinate PlayerSmart::sizeOneAttack(const Coordinate& candidate) const;

	/*given the size of the ship that sunk,update that there is one less ship in this size
	if after the update the number of ships of size sunkShipSize is -1, the board was imbalanced
	set isBoardBalanced = false and update the attack options pool	*/
	void PlayerSmart::updateShipsCount(int sunkShipSize);

	/*return the size of the other player's curr smallest ship */
	int PlayerSmart::getMinShipSize();

	/* given a coordinate search attackedships and check if it belongs to one of them.
	if found a ship it belongs to -  update this ship details and return the index of the ship it was added to.
	else return -1 [the ship sunk|| was added as new] .
	if the ship sunk(of size 1), update sunkShipSize to -1*/
	int PlayerSmart::addCoorToShipInProcess(const Coordinate& targetCoor, Coordinate* nextCoorTosearch, AttackResult result);

	/* given startIndex(of the ship we want to add coordinates to) and coorToSearch.
	look for the coordinate in all attacked ships starting from index, if found, merge the 2 ships
	and remove the second ship from attacked ships*/
	void PlayerSmart::mergeShipDetails(Coordinate* pair, int indexToupdate);

	/*iterate over attackShips vector starting from startIndex, and for each shipinprocess
	check if coor belongs to the ship if does return its coordinate else return -1*/
	int PlayerSmart::findCoorInAttackedShips(const Coordinate& coorToSearch, int startIndex);

	/*checking if a current coordinate is within board Limits*/
	bool  PlayerSmart::isInBoard(int row, int col, int depth) const;

	/* clear member fields from previous runs*/
	void PlayerSmart::cleanMembers();

	/*remove coordinate from given set*/
	void PlayerSmart::delFromSet(std::set<Coordinate>& data, const Coordinate& coors);

	/*true iff coor in data*/
	bool PlayerSmart::isInSet(const std::set<Coordinate>& data, const Coordinate& coors) const;

	/* given origin update its coordinates to <row,col,depth>*/
	static void updateCoordinates(Coordinate& origin, int row, int col, int depth) { origin.row = row; origin.col = col; origin.depth = depth; }
	/*utility functions****************************************************************************************/
	/*returns (1,0,0), (0,1,0) (0,0,1) ,(1,0,0), (0,1,0) (0,0,1)*/
	static std::vector<Coordinate> setSixOptionsVector();
	/*(0, 1, 0)(0, -1, 0)*/
	static std::vector<Coordinate> setHorizontalOptionsVector();
	/*(1, 0, 0)(-1, 0, 0)*/
	static std::vector<Coordinate> setVerticalOptionsVector();
	/*(0, 0, 1)(0, 0, -1)*/
	static std::vector<Coordinate> setDimentionalOptionsVector();
	/* move all coors in tempOptions to allOptions*/
	static void mergeVector(std::vector<Coordinate>& allOptions, const std::vector<Coordinate>& tempOptions);;
	/*(1, 0, 1)(1, 0, -1)(0, 1, 1) (0, 1, -1) (0, 0, 1) (0, 0, -1)*/
	static std::vector<Coordinate> setVectorForCheckSixDirections();
	
	/*utility functions ****************************************************************************************/

};
