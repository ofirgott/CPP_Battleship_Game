#pragma once
#include "Ship.h"
#include "IBattleshipGameAlgo.h"
#include <vector>
#include <iostream>
#include "BattleshipBoard.h"
#include <sstream>

class Player : public IBattleshipGameAlgo
{
public:

	/* in case parsing attackFile failed player.getID == -1 ;
	* @assume user_id != -1
	*/
	Player(int user_id = -1, const std::string attackFilePath = "");
	~Player(); // check that thats the way to deallocate the memory !!!!!!!!!!!!!!!!!!!!!!! 


			   /* @return total score gained by player
			   */
	int getTScore();

	/* @ return how much ships player has
	*/
	int getShipsCount();

	/* @ return true if playes has more moves to perform
	* false- otherwise
	*/
	bool getHasMoreMoves();

	/*@ return - players id
	*/
	int getID();

	/* update players score to the prev core + num
	* @assume- num >= 0
	*/
	void updateScore(int num);// need to be private!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

							  /* given coordinates  player updates number of ships he has got left&& updates the attack in his ships details.
							  /* @ return the attack result and the number of pointes the other player scored
							  */
	std::pair<AttackResult, int> realAttack(std::pair<int, int> coor);

	/* @ assume- this function is called once during a game
	*/
	void setBoard(const char** board, int numRows, int numCols) override; // called once to notify player on his board

																		  /* @ return's players next move
																		  * @ assume there are more moves for player
																		  */

	std::pair<int, int> attack() override;
	void notifyOnAttackResult(int player, int row, int col, AttackResult result) override; // notify on last move result

																						   // for tester!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	void printPlayer() {
		printf("players Details\n");
		printf("ID = %d\n", id);
		printf("cShips= %d\n", cShips);
		if (isDone) {
			printf("isDone = true\n");
		}
		else
		{
			printf("isDone = false\n");
		}

		printf("tScore = %d\n", tScore);
		printf("cAttack = %d\n", cAttack);
		printf("print Attack's:\n");
		for (auto& coor : pMoves) {
			printf("(%d,%d) ", coor.first, coor.second);
		}


	}
	/*
	// for tester
	char *** getPlayersBoard() {
	char** board = new (char*[10]);
	for (int i = 0; i < 10; i++)
	{
	board[i] = new (char[10]);
	for (int j = 0; j < 10; j++) {
	board[i][j] = pBoard[i][j]->getSymbol();
	}
	}
	return &board;
	}*/

	// for tester
	void printPlayersBoard() {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (pBoard[i][j] != nullptr) {
					printf("%c ", pBoard[i][j]->getSymbol());
				}
				else {
					printf("%d ", 0);
				}
			}
			printf("\n");
		}
	}

private:
	int id; // players id , if id == -1 player is invalid 
	int tScore; // how much score the player gained this far
	Ship***  pBoard; // matrix of pointers to ships  
	int cShips; // number of ships player has
	int cAttack; // index of the next attack in pMoves
	std::vector<std::pair<int, int>> pMoves; // vector of moves
	bool isDone; // if false player has more moves; true - no more moves

				 /*@ assume the attack file given is in valid format
				 * @return vector of coordinates the player wants to attack during the game
				 * (taken from the example in class)
				 * if couldnt open attackFilePath return vector with size 0 ////////////////////////////////////////// maybe print error ??????????????????????????????????????????????
				 * if attackFile contains a line with more then 2 int's - ignore line
				 * if attackFile contains a line with out of bounds coordintes - ignore line
				 */
	static std::vector<std::pair<int, int>> parseAttackFile(const char* attackFilePath); // check is stoi faild ?!?!!? make sure /r/n && /n formats works !!!!!!!

																								/* split string to tokens according to the givem delimiter
																								*  (taken from the example in class)
																								*/
	static std::vector<std::string> split(const std::string &s, char delim);
};

