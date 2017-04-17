
#include <windows.h>
#include <string>
#include "BattleshipGameManager.h"
#include <fstream>


#define DIRLIST_TMP_FILE_PATH "~tmp_dir.txt"


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


bool isStringEndsWith(const std::string& str, const std::string& suffix) {
	if (suffix.size() > str.size()) return false;
	return std::equal(str.begin() + str.size() - suffix.size(), str.end(), suffix.begin());
}

//check the dir list in ~tmp_dir.txt, check if the 3 files exists, prints relevant erros if needed, and then delete the die list file
bool isAllGameFilesExists(const std::string& dir_path, std::string& boardPath, std::string& attackFilePath_a, std::string& attackFilePath_b)
{
	bool isAttackFileExistsA = false, isAttackFileExistsB = false, isBoardExists = false;
	std::string currentFilename;
	std::ifstream dirListFile(dir_path.c_str());

	if (dirListFile.is_open())
	{
		while ((getline(dirListFile, currentFilename)) && !(isAttackFileExistsA && isAttackFileExistsB && isBoardExists)) //we take the first file for every extension. todo: check the getline if necesseray
		{
			if (!isBoardExists && isStringEndsWith(currentFilename, ".sboard"))
			{
				boardPath = dir_path + "\\" + currentFilename;
				isBoardExists = true;
			}
			else if (isAttackFileExistsA && isStringEndsWith(currentFilename, ".attack-a"))
			{
				attackFilePath_a = dir_path + "\\" + currentFilename;
				isAttackFileExistsA = true;
			}
			else if (isAttackFileExistsB && isStringEndsWith(currentFilename, ".attack-b"))
			{
				attackFilePath_b = dir_path + "\\" + currentFilename;
				isAttackFileExistsB = true;
			}
		}
		dirListFile.close();
	}

	else {
		std::cout << "Unable to open file, Exit from Game.\n";
		return false;
	}

	//print relevant error messages

	if (isBoardExists && isAttackFileExistsA && isAttackFileExistsB) {
		return true;
	}
	else {
		if (!isBoardExists)
		{
			std::cout << "Missing board file (*.sboard) looking in path: " << dir_path << std::endl;
		}
		if (!isAttackFileExistsA)
		{
			std::cout << "Missing attack file for player A (*.attack-a) looking in path: " << dir_path << std::endl;
		}
		if (!isAttackFileExistsB)
		{
			std::cout << "Missing attack file for player B (*.attack-b) looking in path: " << dir_path << std::endl;
		}
		return false;
	}

}

bool checkGamefiles(const std::string& dir_path, std::string& boardPath, std::string& attackFilePath_a, std::string& attackFilePath_b) { //todo: check if we want to put this in gameManage class

	if (!isValidDir(dir_path)) {
		std::cout << "Wrong path: " << dir_path << std::endl;
		return false;
	}

	//writes only filenames (without directory names) in dir_path directory 
	//to ~tmp_dir.txt new file in working directory

	std::string dir_cmd("dir ");
	dir_cmd += dir_path;
	dir_cmd += " /b /a-d * > ";		//todo: delete ~tmp_dir.txt after using
	dir_cmd += DIRLIST_TMP_FILE_PATH;
	system(dir_cmd.c_str());					//todo: check if we need the return value of this system call


	if (!isAllGameFilesExists(dir_path, boardPath, attackFilePath_a, attackFilePath_b))
	{
		remove(dir_path.c_str());
		return false;
	}

	remove(dir_path.c_str());
	return true;
}

std::string ExePath() {
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	return std::string(buffer).substr(0, pos);
}

int main(int argc, char* argv[])
{

	std::string dir_path(""), boardPath("good_board_0.sboard"), attackFilePath_a("clean_movesA.attack-a"), attackFilePath_b("clean_movesA.attack-a");
	//char* dir_path = "";
	//char* boardPath = "good_board_1.sboard";
	//char* attackFilePath_a = "file_attack_a.txt";
	//char* attackFilePath_b = "file_attack_b.txt";
	bool isGameSuccessfullyCreated = false;

	//if (argc > 1) {
	//	dir_path = argv[1];
	//}
	//else
	//{
	//	dir_path = ExePath();	//working directory path
	//}



	//if(!checkGamefiles(dir_path, boardPath, attackFilePath_a, attackFilePath_b)){
	//	//todo: problem with game files, exiting..
	//	return -1;
	//}
	//boardPath = "good_board_1.sboard";
	//boardPath = "game.sboard";
	//attackFilePath_a = "þþfile1A.attack-a";
	//attackFilePath_b = "þþþþfile1A.attack-a";


	//std::cout << boardPath;
	BattleshipGameManager Game(boardPath, attackFilePath_a, attackFilePath_b, isGameSuccessfullyCreated);

	//std::cout << dir_path;		//todo: delete this!
	//std::cin.get();
	//exit(0);
	if (!isGameSuccessfullyCreated) {
		std::cout << "we here";
			std::cin.get();
		return -1;
	}

	Game.Run();

	std::cin.get();
	return 0;
}

