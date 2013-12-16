#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <string>
#include <fstream>
#include "LogMessage.h"

//LogManager class provides basic logging capabilities.
//It does not keep the log in memory, it writes it directly to file.
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
	//Template allows multiple types for the parameter (char, int) to automatically fill in.
	//Using stringstream ensures we get the actual value and not the character defined by that ASCII or UNICODE value.
	//Might be nice to overhaul for variadic templates (VC12(VS2013) functionality), which allows 'unlimited' parameters
	template<typename T>
	void Log(T message);
	//Log a message with a log level
	//Template allows multiple types for the parameter (char, int, etc.) to automatically fill in.
	//Using stringstream ensures we get the actual value and not the character defined by that ASCII or UNICODE value.
	//Might be nice to overhaul for variadic templates (VC12(VS2013) functionality), which allows 'unlimited' parameters
	template<typename LogLevel, typename T>
	void Log(LogLevel level, T message);
	////Clean up all resources
	void Cleanup();
private:
	//Constructor using log.txt as the log file.
	LogManager();
	//Constructor using the specified file name as log file.
	LogManager(std::string fileName);
	//Write a string directly to the log file.
	void AppendToLog(LogMessage* message);
	std::stringstream messageStream;
	static LogManager* logManager;
	LogMessage* logMessage;
	std::ofstream logFile;
};



#endif