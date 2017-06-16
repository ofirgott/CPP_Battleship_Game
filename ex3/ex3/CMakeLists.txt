#############################################################
### YOU SHOULD EDIT THE BELOW WITH YOUR DETAILS AND FILES ###
#############################################################

set(user1 dianakolton)
set(user2 Shahrabany1)
set(user3 ofirg1)
set(id1 "204196729")
set(id2 "204537997")
set(id3 "305645806")

# All source files needed to compile your exe
set (EXE_SOURCE_FILES
	BattleshipGameManager.h
	BattleshipPrint.h
	BattleshipTournamentManager.h
	GamePlayerData.h
	Logger.h
	PlayerAlgoDetails.h
	RoundData.h
	Ship.h
	ShipsBoard.h
	SingleGameProperties.h
	PlayerGameResultData.h
	BattleshipGameManager.cpp
	BattleshipPrint.cpp
	BattleshipTournamentManager.cpp
	GamePlayerData.cpp
	Logger.cpp
	main.cpp
	Ship.cpp
	ShipsBoard.cpp
	PlayerGameResultData.cpp
	BattleshipBoard.h
	BattleshipGameUtils.h
	BoardDataImpl.h
	IBattleshipGameAlgo.h
	BattleshipBoard.cpp
	BattleshipGameUtils.cpp
)
# All source files needed to compile your smart algorithm's .dll
set (SMART_ALGO_SOURCE_FILES
	PlayerSmart.h
	ShipInProcess.h
	PlayerSmart.cpp
	ShipInProcess.cpp
	IBattleshipGameAlgo.h
	BattleshipGameUtils.cpp
	BattleshipGameUtils.h
	BattleshipBoard.h
	BattleshipBoard.cpp
)

##################################
### DO NOT CHANGE FROM HERE ON ###
##################################

message("user: ${user1}, id: ${id1}")

add_definitions(-DUNICODE -D_UNICODE)

set(EX ex3)

# Set exe build parameters
set(EXE_NAME "${EX}.${user1}")
add_executable( ${EXE_NAME}	${EXE_SOURCE_FILES})
set_property(TARGET ${EXE_NAME} PROPERTY FOLDER "${EX}/${user1}")
set_property(TARGET ${EXE_NAME} PROPERTY OUTPUT_NAME "${user1}")

# Set smart algorithm's .dll build parameters
set(ALG3_NAME "${EX}.${user1}.smart")
add_library(${ALG3_NAME} SHARED ${SMART_ALGO_SOURCE_FILES})
set_property(TARGET ${ALG3_NAME} PROPERTY FOLDER "${EX}/${user1}")
set_property(TARGET ${ALG3_NAME} PROPERTY OUTPUT_NAME "${user1}.smart")
target_compile_definitions(${ALG3_NAME} PRIVATE -DALGO_EXPORTS) # preprocessor flag saying we are the one compiling the header now