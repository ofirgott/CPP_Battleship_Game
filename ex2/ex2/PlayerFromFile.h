#pragma once
#include "Player.h"
#include "Ship.h"

class PlayerFromFile : public Player
{
public:
	PlayerFromFile() : Player(), cAttack(0), isDone(false) {};
	~PlayerFromFile() { Ship::deleteShipMatrix(pBoard);  }

	std::pair<int, int> attack() override;

	void notifyOnAttackResult(int player, int row, int col, AttackResult result)override ;	// notify on last move result

																						/* given coordinates  player updates number of ships he has got left&& updates the attack in his ships details.
																						/* @ return the attack result and the number of pointes the other player scored
																						/* if player attacked the same coordinate in the second time return <Hit, -1> to indicate that the player shoudnt keep his turn
																						*/
	std::pair<AttackResult, int> realAttack(std::pair<int, int> coor);
	//todo: we need to changa and adjudst it

private:
	int cAttack; // index of the next attack in pMoves
	std::vector<std::pair<int, int>> pMoves; // vector of moves
	bool isDone; // if false player has more moves; true - no more moves

	/* @return vector of coordinates the player wants to attack during the game
	* if couldnt open attack file / proccess it - return vector of size 1 containing <inf,inf> + print error
	* if attackFile contains a line with more then 2 int's || line with out of bound
	* coordintes || invalid represntation of integrs - ignore line
	*/
	static std::vector<std::pair<int, int>> parseAttackFile(const char* attackFilePath);

	/* split string to tokens according to the given delimiter
	* in case of error  set succsessfulSplit to false
	*/
	static std::vector<std::string> split(const std::string &s, char delim, bool* succsessfulSplit);

	/* check if there is a gap(any character e.g whitespace, letters etc ) between the
	first digit in the string  (if there is such) to the second digit in the strring if there is such*/
	static bool isSeperated(const std::string& token);
};
