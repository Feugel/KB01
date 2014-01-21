#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <string>
#include <fstream>
#include "LogLevel.h"
#include "time.h"
#include <windows.h>

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
	//the ... allows us to capture any amount of any type of parameters. The format parameter defines which types it should capture.
	void Log(std::string format, ...);
	//Log a message with a log level
	void Log(LogLevel level, std::string format, ...);
	////Clean up all resources
	void Cleanup();
private:
	//Constructor using log.txt as the log file.
	LogManager();
	//Constructor using the specified file name as log file.
	LogManager(std::string fileName);
	//Get the current time with ~16ms precision. High performance timers are not yet available.
	std::string GetTime();
	static LogManager* logManager;
	FILE* logFile;
};

#endif