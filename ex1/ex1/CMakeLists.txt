set(user1 ofirg1)
set(user2 Shahrabany1)
set(user3 dianakolton)
set(id1 "305645806")
set(id2 "204537997")
set(id3 "204196729")
set (SOURCE_FILES
	BattleshipBoard.h
	BattleshipGameManager.h
	IBattleshipGameAlgo.h
	Player.h
	Ship.h
	BattleshipBoard.cpp
	BattleshipGameManager.cpp
	main.cpp
	Player.cpp
	Ship.cpp
)

### DO NOT CHANGE FROM HERE ON ###

message("user: ${user1}, id: ${id1}")
message("user: ${user2}, id: ${id2}")
message("user: ${user3}, id: ${id3}")

set(EXE_NAME "ex1.${user1}")
add_executable( ${EXE_NAME}
	${SOURCE_FILES}
)
#BUILD_BINARY_OUTPUT_DIRECTORY
set_property(TARGET ${EXE_NAME} PROPERTY FOLDER "ex1/${user1}")
set_property(TARGET ${EXE_NAME} PROPERTY OUTPUT_NAME "${user1}")