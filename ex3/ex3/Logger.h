#pragma once
#include <fstream>
#include <string>

enum LogLevel
{
	Error, Warning, Info, Debug,
};

class Logger
{

public: 
	
	static void Init(const std::string& loggerFilePath = DEFAULT_FILENAME, LogLevel inputLevel = LogLevel::Info);
	static void Close();
	static void append(const std::string& msg, LogLevel level);
	
	static const LogLevel DEFAULT_LEVEL = Info; 
	static const std::string DEFAULT_FILENAME;
	
private:
	static const int TIME_BUF_SIZE = 80;
	
	Logger() = delete;

	static LogLevel logLevel;
	static std::ofstream outFile;

	static std::string getTimeInfo();
	static std::string levelEnumToString(LogLevel l);
	static void printLogEntry(const std::string & msg, const std::string& level);
};