#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <string>
#include <fstream>
#include "LogMessage.h"

///<summary>
///LogManager class provides basic logging capabilities.
///It does not keep the log in memory, it writes it directly to file.
///</summary>
class LogManager
{
public:
	//Destructor
	virtual ~LogManager();
	//Get the current LogManager instance. 
	//If no instance exists, create a new one with log.txt as filename.
	static LogManager* Instance();
	//Get the current LogManager instance. 
	//If no instance exists, create a new one with the given filename as log file.
	static LogManager* Instance(std::string fileName);
	//Log a message to file with the default INFO LogLevel
	void Log(std::string message);
	////Log a message composed from an unsigned int to file with the default INFO LogLevel
	void Log(unsigned int message);
	//Log a message to file with the given LogLevel
	void Log(LogLevel level, std::string message);
	//Log a message to file with the given LogLevel
	void Log(LogLevel level, unsigned int message);
	//Clean up all resources
	void Cleanup();
private:
	//Constructor using log.txt as the log file.
	LogManager();
	//Constructor using the specified file name as log file.
	LogManager(std::string fileName);
	//Write a string directly to the log file.
	void AppendToLog(LogMessage* message);
	static LogManager* logManager;
	LogMessage* logMessage;
	std::ofstream logFile;
};

#endif