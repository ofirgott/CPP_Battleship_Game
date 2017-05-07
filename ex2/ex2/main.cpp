#include "BattleshipGameManager.h"

int main(int argc, char* argv[])
{
	try
	{
		BattleshipGameManager Game(argc, argv);
		if (Game.isGameSuccessfullyCreated()){
			Game.Run();
			system("pause");
			return 0;
		}
		else {
			system("pause");
			return -1;
		}
		
		
	}
	catch (std::exception ex)
	{
		system("pause");
		return -1;
	}
	

}
