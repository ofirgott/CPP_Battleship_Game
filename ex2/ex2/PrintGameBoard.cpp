#include "PrintGameBoard.h"
#include "BattleshipGameManager.h"

bool PrintGameBoard::isQuiet = printDeafultIsQuiet;
int PrintGameBoard::delay = printDefatultDealy;

void PrintGameBoard::gotoxy(const int x, const int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void PrintGameBoard::hideCursor()
{
	if (isQuiet) return;

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	
	GetConsoleCursorInfo(h, &info);
	info.bVisible = false;
	SetConsoleCursorInfo(h, &info);
}

void PrintGameBoard::setColor(WORD color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void PrintGameBoard::printStartBoard(const BattleshipBoard & board)
{
	if(isQuiet) return;
	
	system("cls");			/* clear the screen */
	hideCursor();

	char currChar;

	for (int i = 0; i < board.getRows(); i++)
	{
		for (int j = 0; j < board.getCols(); j++)
		{
			currChar = board.getCoordValue(i, j);
			
			if (!BattleshipBoard::IsShipCharInBoard(currChar))
			{
				putchar(' ');
				continue;
			}
			
			gotoxy(j, i);

			if (BattleshipBoard::isPlayerShip(BattleshipGameManager::PLAYERID_A, currChar)) setColor(PLAYER_A_COLOR);

			else setColor(PLAYER_B_COLOR);

			putchar(currChar);

		}
	}

	/* print players coloros*/
	setColor(PLAYER_A_COLOR);
	gotoxy(0, board.getRows() + 1);
	std::cout << "Player A" << std::endl;
	setColor(PLAYER_B_COLOR);
	std::cout << "Player B" << std::endl;

	setColor(WHITE_COLOR);
	std::cout << "________________________________";
	
}

void PrintGameBoard::printCurrentAttack(int playerAttackedId, std::pair<int, int> coord, char currChar, AttackResult res)
{
	if(isQuiet) return;

	setColor(ATTACK_COLOR);
	int currPlayerColor = (playerAttackedId == BattleshipGameManager::PLAYERID_A ? PLAYER_A_COLOR: PLAYER_B_COLOR);
	gotoxy(coord.second, coord.first);

	putchar(ATTACK_CHAR);
	Sleep(delay);

	/* check the attack results*/


	gotoxy(coord.second, coord.first);
	/* hit or already hitted coord */
	
	if(res == AttackResult::Hit || res == AttackResult::Sink)
	{
		setColor(currPlayerColor);
		putchar(HIT_CHAR);
	}
	
	else
	{
		putchar(BLANK_CHAR);
	}
	
	setColor(WHITE_COLOR);





	



}
