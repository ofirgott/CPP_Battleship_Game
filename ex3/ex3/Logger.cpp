#include "Logger.h"
#include <ctime>
#include <chrono>
#include <iostream>

LogLevel Logger::logLevel = DEFAULT_LEVEL;
std::ofstream Logger::outFile;



/* trunc -  any current content is discarded, assuming a length of zero on opening.*/
/* ios::out allows output (write operations) to a stream.*/
void Logger::Init(const std::string & loggerFilePath, LogLevel inputLevel)
{
	logLevel = inputLevel;
	outFile =  std::ofstream(loggerFilePath, std::ios::trunc | std::ios::out);
	printLogEntry("########### Progaram successfully Started ########### \n", "----");
	printLogEntry(" Log Level is : " + levelEnumToString(logLevel), "----");
}

void Logger::Close()
{
	outFile << std::endl;
	printLogEntry("########### Tournament finished. Log closed. ########### \n", "----");
	outFile.close();
}

void Logger::append(const std::string & msg, LogLevel level)
{
	if (level > logLevel) return;
	printLogEntry(msg, levelEnumToString(level));
}

/* format is YYYY-MM-DD HH:mm:ss */
std::string Logger::getTimeInfo() 
{
		time_t     now = time(nullptr);
		struct tm  tstruct;
		char       buf[TIME_BUF_SIZE];
		localtime_s(&tstruct, &now);
		strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
		return buf;
}

std::string Logger::levelEnumToString(LogLevel l)
{
	if (l == LogLevel::Error) return "ERROR";
	else if (l == LogLevel::Warning) return "WARNING";
	else if (l == LogLevel::Debug) return "DEBUG";
	else return "INFO";
}

void Logger::printLogEntry(const std::string & msg, const std::string& level)
{
	if (outFile.is_open())
	{
		outFile << getTimeInfo() << " \t[" << level << "] " << msg << std::endl;
	}
}
