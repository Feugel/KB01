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
	///<summary>
	///Destructor
	///</summary>
	virtual ~LogManager();
	///<summary>
	///Get the current LogManager instance. 
	///If no instance exists, create a new one with log.txt as filename.
	///</summary>
	static LogManager* Instance();
	///<summary>
	///Get the current LogManager instance. 
	///If no instance exists, create a new one with the given filename as log file.
	///</summary>
	static LogManager* Instance(std::string fileName);
	///<summary>
	///Log a message to file with the default INFO LogLevel
	///</summary>
	void Log(std::string message);
	///<summary>
	///Log a message to file with the given LogLevel
	///</summary>
	void Log(LogLevel level, std::string message);
	///<summary>
	///Clean up all resources
	///</summary>
	void Cleanup();
private:
	///<summary>
	///Constructor using log.txt as the log file.
	///</summary>
	LogManager();
	///<summary>
	///Constructor using the specified file name as log file.
	///</summary>
	LogManager(std::string fileName);
	///<summary>
	///Write a string directly to the log file.
	///</summary>
	void AppendToLog(LogMessage* message);
	static LogManager* logManager;
	LogMessage* logMessage;
	std::ofstream logFile;
};

#endif