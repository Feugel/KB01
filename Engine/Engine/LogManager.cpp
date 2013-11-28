#include "LogManager.h"

LogManager* LogManager::logManager = NULL;

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

LogManager* LogManager::Instance()
{
	if(NULL == logManager)
		logManager = new LogManager();
	return logManager;
}

LogManager* LogManager::Instance(std::string fileName)
{
	if(NULL == logManager)
		logManager = new LogManager(fileName);
	return logManager;
}

void LogManager::Cleanup()
{
	// clean up logmanager, logmessage etc
}

LogManager::LogManager()
{
	this->logFile = std::ofstream("log.txt", std::fstream::app);
}

LogManager::LogManager(std::string fileName)
{
	this->logFile = std::ofstream(fileName, std::fstream::app);
}

void LogManager::AppendToLog(LogMessage* message)
{
	logFile << message->moment << " " << LogLevelNames[message->level] << " " << message->message << std::endl;
	delete message;
}