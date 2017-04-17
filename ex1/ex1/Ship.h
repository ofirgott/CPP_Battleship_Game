#pragma once
/* the = , copy constructor, needed????
*/

#include <map> // std:: map
#include <utility> //  std::pair
#include <set> // std::set
#include <vector> // std::vector
#include <algorithm>    // std::sort 
#define NROWS 10
#define NCOLS 10

// empty constructor / copy construtor / operator=  do we need ??? !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
class Ship {

public:

	//	Battleship& operator=(const Battleship& ship); // operator =  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//	Battleship(const Battleship& ship); // copy constructor!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	/*
	* input.first - ship's letter, input.second - coordinates for the ship
	* @ assume letter is one of b/p/m/d/B/P/M/D
	* @ return -new object of type Ship with letter and coordinates  + details as in the pdf
	*/
	Ship(const std::pair<char, std::set<std::pair<int, int>>>& input);

	/* distructor*/
	~Ship(); // make sure memory is deallocated properly !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

			 /* returns how much score is gained by hitting this ship*/
	int getPoints();

	/* returns how many parts of the body not hit yet*/
	int getNotHit();

	/*return true- if ship has live parts
	*false- otherwise*/
	bool isAlive();

	char getSymbol() {/////////////////////////////////////////////////////////////////// for tester
		return symbol;
	}
	///////////////////////////////////////////////////////////////// for tester
	int getLength() {
		return len;
	}
	//////////////////////////////////////////////////////////////// for tester
	void printBody() {
		for (auto& part : body) {
			printf("row = %d, col = %d, hit = %d\n", part.first.first, part.first.second, part.second);
		}
	}

	/*@ret: 0 - in case of succesful attack
	1 - attacked the same part as in the past
	-1 - the coordinated given are not of this ship
	*/
	int updateAttack(int row, int col); // should be private! / own game id?!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

										/* given <symbol, set of coordinates>
										@return true - if input represents a valid ship as defined in the pdf
										* false - otherwise
										*/
	static bool Ship::isValidShipDetails(std::pair<char, std::set<std::pair<int, int>>> input);

	/* @return a set of dinamically allocated Battleships
	* @assume- each entry in allpairs cooresponeds to a valid ship
	*/
	static std::set <Ship*> createShipSet(const std::set<std::pair<char, std::set<std::pair<int, int>>>>& allPairs);
	//static std::set <Ship> createShipSet(const std::set<std::pair<char, std::set<std::pair<int, int>>>>& allPairs);
	/* @return Matrix of pointers to Battleships
	*@assume - the set consists valid point4ers to ships
	*/
	static Ship*** createShipMatrix(std::set <Ship*>);
	//static Ship*** createShipMatrix(std::set <Ship>);

private:

	char symbol; // ship's representing letter
	int len; // ship length
	int points; // how much earned by sinking the ship
	int notHit; //how much not hit   
	std::map<std::pair<int, int>, int> body; // <<row,col>,0/1> 0- not hit; 1- hit

											 /* updates ship's fields according to the input values
											 */
	void setFields(int length, int sPoints, std::set< std::pair<int, int> >  coordinates);

	/*@return - true if ship with symbol= id can have setSize coordinates
	* validity as defined in the pdf
	*/
	static bool Ship::isValidShipLen(char id, int setSize);

	/*
	@return -true if ship is horizontal/vertical otherwise false
	*/
	static bool isValidShipCoordinates(const std::set<std::pair<int, int>>& coordinates);

	/*@ return true if all coordinates are equal
	@assume- coors vector is sorted
	*/
	static bool isConstantCoors(const std::vector<int>& coors, int size);

	/*@ return true if coordinates are incremenal (&& with no gaps)
	@assume- coors vector is sorted
	*/
	static bool isIncrementalCoors(const std::vector<int>& coors, int size);

};