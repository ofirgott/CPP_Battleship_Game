#include "BattleshipGameUtils.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <windows.h>
#include <algorithm>


bool BattleshipGameUtils::isValidDir(const std::string& path)
{
	std::stringstream cdCommandString;
	cdCommandString << "cd " << path << " 1> nul 2> nul" << std::endl;	/* trying to cd to the input directory */
	auto commandRes = system(cdCommandString.str().c_str());
	if (commandRes == 0)
		return true;
	else
		return false;
}

/* return true if str end with given suffix, else return false */
bool BattleshipGameUtils::isStringEndsWith(const std::string& str, const std::string& suffix) {
	if (suffix.size() > str.size()) return false;
	return std::equal(str.begin() + str.size() - suffix.size(), str.end(), suffix.begin());
}

std::vector<std::string> BattleshipGameUtils::SortedDirlistSpecificExtension(std::string const& dirPath, std::string const& ext)
{
	std::vector<std::string> outputFilenames;
	HANDLE dir;
	WIN32_FIND_DATAA fileData; //data struct for file
	std::string currFileName;
	std::string s = dirPath + "\\*" + ext; // only ext endings
	dir = FindFirstFileA(s.c_str(), &fileData); // Notice: Unicode compatible version of FindFirstFile
	if (dir != INVALID_HANDLE_VALUE) //check if the dir opened successfully
	{
		// test each file suffix and set variables as needed
		do
		{
			currFileName = fileData.cFileName;
			outputFilenames.push_back(currFileName);

		} while (FindNextFileA(dir, &fileData)); // Notice: Unicode compatible version of FindNextFile

		/* The order in which FindFirstFileA function returns the file names is dependent on the file system type, so we have ti sort the vector by  file names */

		std::sort(outputFilenames.begin(), outputFilenames.end());

		FindClose(dir); /* Closes a file search handle opened by the FindFirstFile function */
	}

	return outputFilenames;
}

