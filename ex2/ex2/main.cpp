#include "BattleshipBoard.h"
#include "BattleshipGameManager.h"

int main(int argc, char* argv[])
{
	try
	{
		BattleshipGameManager Game(argc, argv);
		if (Game.isGameSuccessfullyCreated())
			Game.Run();
		else {
			system("pause");
			return -1;
		}
		system("pause");
		return 0;
		
	}
	catch (std::exception ex)
	{
		system("pause");
		return -1;
	}
	

}
