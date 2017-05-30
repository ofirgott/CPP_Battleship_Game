#include "BattleshipBoard.h"
#include <iostream>
#include <fstream>

BattleshipBoard::BattleshipBoard(std::vector<char> board, int inputRows, int inputCols, int inputDepth) : boardVec(board), rows(inputRows), cols(inputCols), depth(inputDepth), isSuccCreated(true) {}

BattleshipBoard::BattleshipBoard(const std::string & boardPath) : isSuccCreated(false)
{
	if (boardPath.empty()) return;

	std::string line;

	std::ifstream boardFile(boardPath.c_str());
	if (boardFile.is_open())
	{
		/* parsing the first line to get the board dimensions */
		std::getline(boardFile, line);

		if (!parseBoardDimensions(line)) return;





		int rowCnt = 0;											/* we need to read only (10) rows from the board input file */

		while (rowCnt < rows && std::getline(boardFile, line))  /* while we read < rows lines or we don't reach to eof in board file */
		{
			CopyInputLineToBoard(matrix, line, rowCnt, cols);
			rowCnt++;
		}
		boardFile.close();
	}
	else {														/* we can't open the board file */
		//TODO: print to the logger - std::cout << "Error opening board file in " << boardPath << std::endl;
		return;
	}

	isSuccCreated = true;





}

BattleshipBoard & BattleshipBoard::operator=(const BattleshipBoard & otherBoard)
{
	// TODO: insert return statement here
}

std::vector<char> BattleshipBoard::createPlayerBoard(int playerID)const
{
	auto playerBoard = std::move(InitNewEmptyBoardVector(rows, cols, depth));

	
	for (auto i = 0; i < playerBoard.size(); i++)
	{
		if (IsShipCharInBoard(boardVec[i]) && playerID == PLAYERID_A && isPlayerShip(playerID, boardVec[i])) {		/* returns clean matrix of player A*/
			playerBoard[i] = boardVec[i];
		}
		else if (IsShipCharInBoard(boardVec[i]) && playerID == PLAYERID_B && isPlayerShip(playerID, boardVec[i])) {	/* returns clean matrix of player B */
			playerBoard[i] = boardVec[i];
		}
	}

	return playerBoard;
}

/* for battleship pixel in the board, we will check if the adjacent pixels of this pixel (up, down, left and right)
is a different ship - if so, we have an adjacent error in board.
*/
bool BattleshipBoard::CheckIfHasAdjacentShips() const
{
	char currPos;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			for (int k = 0; k < depth; k++)
			{
				currPos = (*this)(i, j, k);

				if (currPos == ' ') continue;			/* if current position is not a ship - it is a ' ', because we clean the board at the begining */

				auto nearbyCoordSet = getNearbyCoordinates(i, j, k);

				for (auto adjacentCoor : nearbyCoordSet)		/* for each nearby coordinate we check if we have adjacent ship (surronding other char)  */
				{
					char adjacentVal = (*this)(adjacentCoor.row, adjacentCoor.col, adjacentCoor.depth);

					if (IsShipCharInBoard(adjacentVal) && adjacentVal != currPos)
					{
						// TODO: print to the logger std::cout << "Adjacent Ships on Board" << std::endl;
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool BattleshipBoard::IsShipCharInBoard(char ch)
{
	ch = toupper(ch);
	return (ch == RUBBER_BOAT || ch == ROCKET_SHIP || ch == SUBMARINE || ch == DESTROYER);
}

std::set<std::pair<char, std::set<Coordinate>>> BattleshipBoard::ExtractShipsDetails() const
{
	auto boardVecCopy = boardVec;
	std::set<std::pair<char, std::set<Coordinate>>> setOfShipsDetails;
	char currShipChar;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			for (int k = 0; k < depth; k++)
			{
				int currIndex = calcCoordIndex(i, j, k, rows, cols, depth);
				
				if((currShipChar = boardVecCopy.at(currIndex)) == ' ') continue;

				std::set<Coordinate> coordOfCurrentShip;

				getAllCurrShipCoords(boardVecCopy, i, j, k, currShipChar, coordOfCurrentShip, rows, cols, depth);

				setOfShipsDetails.insert(std::make_pair(currShipChar, coordOfCurrentShip));				/* insert to the big set current ship details - <'m', {<1,2>,<1,3>}>*/

				for (auto coord : coordOfCurrentShip)
				{
					currIndex = calcCoordIndex(coord.row, coord.col, coord.depth, rows, cols, depth);
					boardVecCopy.at(currIndex) = ' ';													/* clear the board from this ship (we should have a copy of the board) */
				}
				coordOfCurrentShip.clear();
			}
		}
	}

	return std::set<std::pair<char, std::set<Coordinate>>>(setOfShipsDetails);
}

void BattleshipBoard::getAllCurrShipCoords(std::vector<char> board, int r, int c, int d, char currShipChar, std::set<Coordinate>& coordOfCurrentShip, int boardRows, int boardCols, int boardDepth)
{
	/*  note that in this function we can coordinate with line 0! if we want to use this function outside, we need to pay attention for this. */

	int CoordIndex = calcCoordIndex(r, c, d, boardRows, boardCols, boardDepth);
	if (currShipChar == board.at(CoordIndex))
	{
		board.at(CoordIndex) = ' ';												/* clear the current position and add it to the coordinates set*/
		coordOfCurrentShip.insert({r, c, d});

		if(isCoordianteInBoard(r, c + 1, d, boardRows, boardCols, boardDepth))
			getAllCurrShipCoords(board, r, c + 1, d, currShipChar, coordOfCurrentShip, boardCols, boardRows, boardDepth);
		if (isCoordianteInBoard(r, c - 1, d, boardCols, boardRows, boardDepth))
			getAllCurrShipCoords(board, r, c - 1, d, currShipChar, coordOfCurrentShip, boardCols, boardRows, boardDepth);
		if (isCoordianteInBoard(r + 1, c, d, boardCols, boardRows, boardDepth))
			getAllCurrShipCoords(board, r + 1, c, d, currShipChar, coordOfCurrentShip, boardCols, boardRows, boardDepth);
		if (isCoordianteInBoard(r - 1, c, d, boardCols, boardRows, boardDepth))
			getAllCurrShipCoords(board, r - 1, c, d, currShipChar, coordOfCurrentShip, boardCols, boardRows, boardDepth);
		if (isCoordianteInBoard(r, c, d + 1, boardCols, boardRows, boardDepth))
			getAllCurrShipCoords(board, r, c, d + 1, currShipChar, coordOfCurrentShip, boardCols, boardRows, boardDepth);
		if (isCoordianteInBoard(r, c, d - 1, boardCols, boardRows, boardDepth))
			getAllCurrShipCoords(board, r, c, d - 1, currShipChar, coordOfCurrentShip, boardCols, boardRows, boardDepth);
	}
}



std::set<Coordinate> BattleshipBoard::getNearbyCoordinates(int r, int c, int d) const
/* we check in this function every coordinate seperatly */
{
	std::set<Coordinate> adjCoordSet;
	
	if (isCoordianteInBoard(r - 1, c, d)) adjCoordSet.insert({r - 1, c, d});    //adjCoordSet.insert(std::make_pair(x - 1, y)
	if (isCoordianteInBoard(r + 1, c, d)) adjCoordSet.insert({r + 1, c, d});
	if (isCoordianteInBoard(r, c - 1, d)) adjCoordSet.insert({r, c - 1, d});
	if (isCoordianteInBoard(r, c + 1, d)) adjCoordSet.insert({r, c + 1, d});
	if (isCoordianteInBoard(r, c, d - 1)) adjCoordSet.insert({ r, c, d - 1});
	if (isCoordianteInBoard(r, c, d + 1)) adjCoordSet.insert({ r, c, d + 1});

	return std::set<Coordinate>(adjCoordSet);
}


bool BattleshipBoard::isPlayerShip(const int playerId, const char shipChar)
{
	if (playerId == PLAYERID_A && isupper(shipChar)) {
		return true;
	}
	else if (playerId == PLAYERID_B && islower(shipChar)) {
		return true;
	}
	else {
		return false;
	}
}

char BattleshipBoard::operator()(int r, int c, int d)const
{
	if (isCoordianteInBoard(r, c, d)) {
		return boardVec.at(calcCoordIndex(r, c, d, rows, cols, depth));
	}
	else return BLANK_CHAR;
}

void BattleshipBoard::setCoord(int r, int c, int d, char ch)
{
	if (!isCoordianteInBoard(r, c, d)) return;

	boardVec[calcCoordIndex(r, c, d, rows, cols, depth)] = ch;
}


//char BattleshipBoard::getBoardCoord(std::vector<char> boardVector, int r, int c, int d, int rowsNum, int colsNum, int depthNum)
//{
//	return boardVector.at(calcCoordIndex(r, c, d, rowsNum, colsNum, depthNum));
//}




/* this is strange to return reference to a vector, so we will return by value, and then we will make move to prevent new allocation */
std::vector<char> BattleshipBoard::InitNewEmptyBoardVector(int rows, int cols, int depths)
{
	std::vector<char> vec(rows * cols * depths, BLANK_CHAR);
	return vec;
}
 

void BattleshipBoard::CopyInputLineToBoard(const std::string & line)
{
}

bool BattleshipBoard::parseBoardDimensions(std::string line)
{
	std::vector<int> dimsVec;
	
	size_t pos;
	char* stringEnd = nullptr;

	while((pos = line.find(BOARD_DIM_DELIMITER)) != std::string::npos)
	{
		dimsVec.push_back(strtol(line.substr(0, pos).c_str(), &stringEnd, 10));

		if (*stringEnd) {
			//todo: print to the logger "dimension row contains non-number chars
			return false;
		}
		line.erase(0, pos + 1);
	}

	if(dimsVec.size() < 3){
		//todo: print to the logger: "dimesnions row contains less than 3 dimensions
		return false;
	}

	cols = dimsVec[0];
	rows = dimsVec[1];
	depth = dimsVec[2];

	return true;
	
}
