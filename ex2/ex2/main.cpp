#include "BattleshipBoard.h"
#include "BattleshipGameManager.h"

int main(int argc, char* argv[])
{
	bool gameSuccessfullyCreated = false;							/* boolean for the game constructor */

	try
	{
		BattleshipGameManager Game(argc, argv, gameSuccessfullyCreated);
		if (gameSuccessfullyCreated)
			Game.Run();
		else
			return -1;
	}
	catch (std::exception ex)
	{
		return -1;
	}

	return 0;

}
