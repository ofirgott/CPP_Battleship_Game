#pragma once
#include "BattleshipBoard.h"

/* implementing BoardData function  */

class BoardDataImpl : public BoardData
{
public:

	BoardDataImpl(int player, const BattleshipBoard& board) : playerID(player), gameMainBoard(board) 
	{
		_rows = gameMainBoard.getRows();				
		_cols = gameMainBoard.getCols();
		_depth = gameMainBoard.getDepth();
	}

	BoardDataImpl(const BoardDataImpl& otherBoard) = delete;									/* deletes copy constructor */
	BoardDataImpl& operator=(const BoardDataImpl& otherBoard) = delete;							/* delete copy assignment */

	
	char charAt(Coordinate c)const override {
		if (gameMainBoard.isCoordianteInBoard(c.row - 1, c.col - 1, c.depth - 1) && BattleshipBoard::isPlayerShip(playerID, gameMainBoard(c.row - 1, c.col - 1, c.depth - 1)))
			return  gameMainBoard(c.row - 1, c.col - 1, c.depth - 1);
		else return BattleshipBoard::BLANK_CHAR;
	}


private:

	int playerID;															/* player id in current game. to show appropriate view of the main board*/
	const BattleshipBoard& gameMainBoard;									/* the refernce to the board will not die while we have BoardDataImpl object */
};