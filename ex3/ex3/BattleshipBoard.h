#pragma once
#include <set>
#include <iostream>

class BattleshipBoard
{
public:
	BattleshipBoard() : matrix(nullptr), rows(-1), cols(-1), isSuccCreated(false) {}
	BattleshipBoard(const std::string& boardPath);

	BattleshipBoard& operator=(const BattleshipBoard& otherBoard); // copy assignment





private:

	static const int PLAYERID_A = 0;
	static const int PLAYERID_B = 1;
	static const char RUBBER_BOAT = 'B';
	static const char ROCKET_SHIP = 'P';
	static const char SUBMARINE = 'M';
	static const char DESTROYER = 'D';


	char*** matrix;
	int rows;
	int cols;
	int depth;
	bool isSuccCreated;



};