#pragma once

#include <map> // std:: map
#include <utility> //  std::pair
#include <set> // std::set
#include <vector> // std::vector

#include "IBattleshipGameAlgo.h"



class Ship {
	friend class ShipsBoard;
public:

	/*
	* input.first - ship's letter, input.second - coordinates for the ship
	* @ assume letter is one of b/p/m/d/B/P/M/D
	*/
	explicit Ship(const std::pair<char, std::set<Coordinate>>& input);

	/* distructor*/
	~Ship();

	/* returns how much score is gained by hitting this ship*/
	int getPoints()const;

	/* returns how many parts of the body not hit yet*/
	int getNotHit()const;

	/*return true- if ship not sank yet
	* false- otherwise
	*/
	bool isAlive()const;

	const std::vector<Coordinate> Ship::getCoordinates();

	/*@ret: 0 - in case of hitting this coordinate for the first time
	1 - this coordinates were already attacked in the past
	-1 - the coordinates given are not of this ship
	*/
	int updateAttack(int row, int col, int depth);

	/* given <symbol, set of coordinates>
	@ return true - if data in input.second corresponds to a ship of type input.first
	* false - otherwise
	*/
	static bool Ship::isValidShipDetails(std::pair<char, std::set<Coordinate>> input);

	/* @return a set of dinamically allocated Battleships
	* @assume- each entry in allpairs cooresponeds to a valid ship
	*/
	static std::set <Ship*> createShipSet(const std::set<std::pair<char, std::set<Coordinate>>>& allPairs);

private:

	static const char RUBBER_BOAT = 'B';
	static const char ROCKET_SHIP = 'P';
	static const char SUBMARINE = 'M';
	static const char DESTROYER = 'D';

	char symbol; // ship's representing letter
	int len; // ship length
	int points; // how much earned by sinking the ship
	int notHit; //how much not hit   
	std::map<Coordinate, int> body; // <<row,col>,0/1> 0- not hit; 1- hit

											 /* updates ship's fields according to the input values
											 */
	void setFields(int length, int sPoints, std::set<Coordinate>  coordinates);

	/*@return - true if ship with symbol= id can have 'setSize' number of coordinates
	*/
	static bool Ship::isValidShipLen(char id, int setSize);

	/*
	@return -true if ship is horizontal/vertical otherwise false
	*/
	static bool isValidShipCoordinates(const std::set<Coordinate>& coordinates);

	/*@ return true if all coordinates are equal
	@assume- coors vector is sorted
	*/
	static bool isConstantCoors(const std::vector<int>& coors, int size);

	/*@ return true if coordinates are incremenal (&& with no gaps)
	@assume- coors vector is sorted
	*/
	static bool isIncrementalCoors(const std::vector<int>& coors, int size);

}; 
