#############################################################
### YOU SHOULD EDIT THE BELOW WITH YOUR DETAILS AND FILES ###
#############################################################

set(user1 ofirg1)
set(user2 Shahrabany1)
set(user3 dianakolton)
set(id1 "305645806")
set(id2 "204537997")
set(id3 "204196729")

# All source files needed to compile your exe
set (EXE_SOURCE_FILES
	Matrix.h
	Matrix.cpp
	main.cpp
)

##################################
### DO NOT CHANGE FROM HERE ON ###
##################################

message("user: ${user1}, id: ${id1}")

add_definitions(-DUNICODE -D_UNICODE)

set(EX ex4)

# Set exe build parameters
set(EXE_NAME "${EX}.${user1}")
add_executable( ${EXE_NAME}	${EXE_SOURCE_FILES})
set_property(TARGET ${EXE_NAME} PROPERTY FOLDER "${EX}/${user1}")
set_property(TARGET ${EXE_NAME} PROPERTY OUTPUT_NAME "${user1}")