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
	///Constructor using log.txt as the log file.
	///</summary>
	LogManager();
	///<summary>
	///Constructor using the specified file name as log file.
	///</summary>
	LogManager(std::string fileName);
	///<summary>
	///Destructor
	///</summary>
	virtual ~LogManager();
	///<summary>
	///Log a message to file with the default INFO LogLevel
	///</summary>
	void Log(std::string message);
	///<summary>
	///Log a message to file with the given LogLevel
	///</summary>
	void Log(LogLevel level, std::string message);
private:
	void AppendToLog(LogMessage* message);
	LogMessage* logMessage;
	std::ofstream logFile;
};

#endif