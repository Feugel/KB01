#include "LogManager.h"


LogManager::LogManager()
{
	this->logFile = std::ofstream("log.txt", std::fstream::app);
}

LogManager::LogManager(std::string fileName)
{
	this->logFile = std::ofstream(fileName, std::fstream::app);
}

LogManager::~LogManager()
{
}

void LogManager::Log(std::string message)
{
	logMessage = new LogMessage(message);
	AppendToLog(logMessage);
}

void LogManager::Log(LogLevel level, std::string message)
{
	logMessage = new LogMessage(message, level);;
	AppendToLog(logMessage);
}

void LogManager::AppendToLog(LogMessage* message)
{
	logFile << message->moment << " " << LogLevelNames[message->level] << " " << message->message << std::endl;
}
							 
LogMessage* logMessage;
std::ofstream logFile;