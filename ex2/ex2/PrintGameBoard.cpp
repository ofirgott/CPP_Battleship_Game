#include "PrintGameBoard.h"

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

			if (BattleshipBoard::isPlayerShip(PLAYERID_A, currChar)) setColor(PLAYER_A_COLOR);

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
	gotoxy(0, board.getRows() + 5);
}

void PrintGameBoard::printCurrentAttack(int playerId, std::pair<int, int> coord, char currChar, AttackResult res)
{
	if(isQuiet) return;
	int currPlayerColor = (playerId == PLAYERID_A ? PLAYER_A_COLOR: PLAYER_B_COLOR);
	gotoxy(coord.first, coord.second);
	setColor(WHITE_COLOR);



}
