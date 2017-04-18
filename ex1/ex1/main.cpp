#include <string>
#include <fstream>
#include "BattleshipGameManager.h"
#include "Constants.h"
#include <iostream>

bool isValidDir(const std::string& path)
{
	std::stringstream cdCommandString;
	cdCommandString << "cd " << path << " 1> nul 2> nul" << std::endl;	/* trying to cd to the input directory */
	int commandRes = system(cdCommandString.str().c_str());
	if (commandRes == 0)
		return true;
	else
		return false;
}

/* return true if str end with given suffix, else return false */
bool isStringEndsWith(const std::string& str, const std::string& suffix) {
	if (suffix.size() > str.size()) return false;
	return std::equal(str.begin() + str.size() - suffix.size(), str.end(), suffix.begin());
}

/* check the dir list in ~tmp_dir.txt, check if the 3 game files exists, and prints relevant erros if needed */
bool isAllGameFilesExists(const std::string& dir_path, std::string& boardPath, std::string& attackFilePath_a, std::string& attackFilePath_b)
{
	bool isAttackFileExistsA = false, isAttackFileExistsB = false, isBoardExists = false;
	std::string currentFilename;
	std::ifstream dirListFile(DIRLIST_TMP_FILE_PATH);

	if (dirListFile.is_open())
	{
		/* searching in the dir list file until we reach to the eof, or if we already find our 3 files paths */
		while ((getline(dirListFile, currentFilename)) && !(isAttackFileExistsA && isAttackFileExistsB && isBoardExists)) //we take the first file for every relevant extension we see.
		{
			if (!isBoardExists && isStringEndsWith(currentFilename, ".sboard"))
			{
				boardPath = dir_path.empty() ? currentFilename : dir_path + "\\" + currentFilename;
				isBoardExists = true;
			}
			else if (!isAttackFileExistsA && isStringEndsWith(currentFilename, ".attack-a"))
			{
				attackFilePath_a = dir_path.empty() ? currentFilename : dir_path + "\\" + currentFilename;
				isAttackFileExistsA = true;
			}
			else if (!isAttackFileExistsB && isStringEndsWith(currentFilename, ".attack-b"))
			{
				attackFilePath_b = dir_path.empty() ? currentFilename : dir_path + "\\" + currentFilename;
				isAttackFileExistsB = true;
			}
		}
		if (!dirListFile.eof() && !(isAttackFileExistsA && isAttackFileExistsB && isBoardExists)) {		//some problem with the getline funcion - exit
			std::cout << "Error reading temp dirList file in "<< DIRLIST_TMP_FILE_PATH <<" , Exit from Game."<< std::endl;
			return false;
		}
		dirListFile.close();
	}

	else {				/* we have a problem in opening the dir list file, so we exit */
		std::cout << "Unable to open temp dirList file in " << DIRLIST_TMP_FILE_PATH << " , Exit from Game." << std::endl;
		return false;
	}

	/* prints relevant error messages */

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

/* given the input dir path, returns true if dir_path contains board file and 2 attack files for A and B, else return false */
bool checkGamefiles(const std::string& dir_path, std::string& boardPath, std::string& attackFilePath_a, std::string& attackFilePath_b) {
	
	if (!isValidDir(dir_path)) {									/* checks if directory in dir_path exists */
		std::cout << "Wrong path: " << dir_path << std::endl;
		return false;
	}

	/* writes only filenames (without directory names) in dir_path directory to ~tmp_dir.txt new file in working directory */
		
	std::stringstream dirCmd;
	dirCmd << "dir \"" << dir_path << "\" /b /a-d" << ">\""<<DIRLIST_TMP_FILE_PATH<<"\"" << " 2> nul";
	system(dirCmd.str().c_str());


	if (!isAllGameFilesExists(dir_path, boardPath, attackFilePath_a, attackFilePath_b))
	{
		remove(DIRLIST_TMP_FILE_PATH);				/* remove the dir list temp file */
		return false;
	}

	remove(DIRLIST_TMP_FILE_PATH);
	return true;
}


int main(int argc, char* argv[])
{

	std::string dir_path = "", boardPath="", attackFilePath_a="", attackFilePath_b="";

	bool isGameSuccessfullyCreated = false;							/* boolean for the game constructor */

	if (argc > 1)
		dir_path = argv[1];

	if(!checkGamefiles(dir_path, boardPath, attackFilePath_a, attackFilePath_b)){

		std::cin.get();								// todo: delete this row
		return -1;
	}

	BattleshipGameManager Game(boardPath, attackFilePath_a, attackFilePath_b, isGameSuccessfullyCreated);

	if (!isGameSuccessfullyCreated) {
		std::cin.get();								//todo: delete this row
		return -1;
	}

	Game.Run();

	std::cin.get();									//todo: delete this row
	return 0;
}