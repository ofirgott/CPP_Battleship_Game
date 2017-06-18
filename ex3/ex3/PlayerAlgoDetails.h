#pragma once

#include <windows.h>
#include "IBattleshipGameAlgo.h"

typedef IBattleshipGameAlgo *(*GetAlgoFuncType)();

/**
 * \brief Players data and resources - for the tournament algos vector
 */
struct PlayerAlgoDetails
{
	HINSTANCE dllFileHandle;										/* dll handle. will be freed in the TournamentMangaer destructor! */
	std::string dllPath;											/* full path of the dll file */
	std::string playerName;											/* short file name, without extentsion (for table) */
	GetAlgoFuncType getAlgoFunc = nullptr;							/* pointer to the getAlgo function pointer */
	//int algosIndexInVec;
	
	PlayerAlgoDetails() = default;									
	
	PlayerAlgoDetails(const PlayerAlgoDetails& other) = delete;		/* deletes copy ctor */
	
	PlayerAlgoDetails(PlayerAlgoDetails&& otherPlayer) noexcept : dllFileHandle(std::move(otherPlayer.dllFileHandle)), dllPath(otherPlayer.dllPath), playerName(otherPlayer.playerName){ std::swap(getAlgoFunc, otherPlayer.getAlgoFunc); }		/* move constructor */

};


