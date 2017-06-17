#pragma once
#include <fstream>
#include <string>

enum LogLevel
{
	ERROR,
	WARNING,
	INFO,
	DEBUG
};

class Logger
{

public: 
	explicit Logger(const std::string& loggerFilePath, LogLevel inputLevel = LogLevel::INFO);
	~Logger();

	Logger(const Logger& otherlogger) = delete;

	void append(const std::string& msg, LogLevel level);
	

private:
	static const int TIME_BUF_SIZE = 80;
	

	LogLevel logLevel;
	std::ofstream outFile;

	static std::string getTimeInfo();
	static std::string levelEnumToString(LogLevel l);

	//void printLogEntry(std::string, )
};