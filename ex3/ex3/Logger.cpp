#include "Logger.h"
#include <ctime>
#include <chrono>
#include <iostream>

/* trunc -  any current content is discarded, assuming a length of zero on opening.*/
/* ios::out allows output (write operations) to a stream.*/
Logger::Logger(const std::string & loggerFilePath, LogLevel inputLevel) : logLevel(inputLevel), outFile(loggerFilePath, std::ios::trunc | std::ios::out)
{
	//append("")
}

Logger::~Logger()
{
}

void Logger::append(const std::string & msg, LogLevel level)
{
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
	if (l == LogLevel::ERROR) return "ERROR";
	else if (l == LogLevel::WARNING) return "WARNING";
	else if (l == LogLevel::DEBUG) return "DEBUG";
	else return "INFO";
}
