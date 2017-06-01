#pragma once
#include "BattleshipBoard.h"

class BoardDataImpl : public BoardData
{
public:

	BoardDataImpl(int player, const BattleshipBoard& board) : playerID(player), gameMainBoard(board) 
	{
		_rows = gameMainBoard.getRows();				/* TODO: make sure that this is the right place for this assignment */
		_cols = gameMainBoard.getCols();
		_depth = gameMainBoard.getDepth();
	}
	
	char charAt(Coordinate c)const override {
		if (BattleshipBoard::isPlayerShip(playerID, gameMainBoard(c.row - 1, c.col - 1, c.depth - 1)))
			return  gameMainBoard(c.row - 1, c.col - 1, c.depth - 1);
		else return BattleshipBoard::BLANK_CHAR;
	}


private:

	int playerID;
	const BattleshipBoard& gameMainBoard;
};