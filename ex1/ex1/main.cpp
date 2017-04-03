#include "BattleshipGameFromFile.h"
#include <windows.h>
#include <string>

//check if directory in path exists (taken from: http://stackoverflow.com/a/8233867)
bool isValidDir(const std::string& path)
{
	DWORD ftyp = GetFileAttributesA(path.c_str());

	if (ftyp == INVALID_FILE_ATTRIBUTES) //invalid path checking
		return false;  

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY) //check if path is a directory
		return true;   

	return false; 
}


bool checkGamefiles(std::string& dir_path){ //todo: check if we want to put this in gameManage class
	
	bool valid_path = false, isAttackFileExistsA = false, isAttackFileExistsB = false, isBoardExists = false;

	if (!isValidDir(dir_path)){
		std::cout << "Wrong path: " << dir_path << std::endl;
		return false;
	}

	//writes only filenames (without directory names) in dir_path directory 
	//to ~tmp_dir.txt new file in working directory

	std::string dir_cmd("dir ");
	dir_cmd += dir_path;
	dir_cmd += " /b /a-d * > ~tmp_dir.txt";		//todo: delete ~tmp_dir.txt after using
	system(dir_cmd.c_str());
	

	


	return true;
}


int main(int argc, char* argv[])
{
	std::string dir_path = "";

	if (argc > 1) {
		dir_path = argv[1];
	}

	if(!checkGamefiles(dir_path)){
		return -1;
	}


}