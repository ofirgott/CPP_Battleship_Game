#pragma once
#include "Player.h"


class PlayerFromFile : public Player
{
public:
	PlayerFromFile() : Player(), isDone(false) {};	//todo: i want to use iterator instead

	std::pair<int, int> attack() override;

	bool init(const std::string& path) override;

	void notifyOnAttackResult(int player, int row, int col, AttackResult result) override {} //empty implementaion


private:
	std::vector<std::pair<int, int>> movesVector; // vector of moves
	std::vector<std::pair<int, int>>::const_iterator movesVectorItr;
	bool isDone; // if false player has more moves; true - no more moves	


	std::vector<std::pair<int, int>> parseAttackFile(const std::string& attackFilePath) const;

	/* split string to tokens according to the given delimiter
	* in case of error  set succsessfulSplit to false
	*/
	static std::vector<std::string> split(const std::string &s, char delim, bool* succsessfulSplit);

	/* check if there is a gap(any character e.g whitespace, letters etc ) between the
	first digit in the string  (if there is such) to the second digit in the strring if there is such*/
	static bool isSeperated(const std::string& token);


};