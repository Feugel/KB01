#include "LogManager.h"

LogManager* LogManager::logManager = NULL;


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
	Cleanup();
}

void LogManager::Cleanup()
{
	if(NULL != logMessage)
		delete logMessage;
	if(NULL != logManager)
		delete logManager;
}

template<typename T>
void LogManager::Log(T message)
{
	messageStream << message;
	//std::cout << messageStream.str() << std::endl;
	logMessage = new LogMessage(messageStream.str());
	AppendToLog(logMessage);
	delete logMessage;
	messageStream.str(std::string());
	messageStream.clear();
	
}

template void LogManager::Log(std::string message);
template void LogManager::Log(const char* message);
template void LogManager::Log(LPCWSTR message);
template void LogManager::Log(int message);
template void LogManager::Log(unsigned int message);

template<typename LogLevel, typename T>
void LogManager::Log(LogLevel level, T message)
{
	messageStream << message;
	//std::cout << messageStream.str() << std::endl;
	logMessage = new LogMessage(messageStream.str());
	AppendToLog(logMessage);
	delete logMessage;
	messageStream.str(std::string());
	messageStream.clear();
}

template void LogManager::Log(LogLevel level, std::string message);
template void LogManager::Log(LogLevel level, const char* message);
template void LogManager::Log(LogLevel level, int message);
template void LogManager::Log(LogLevel level, unsigned int message);

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

void LogManager::AppendToLog(LogMessage* message)
{
	logFile << message->moment << " " << LogLevelNames[message->level] << " " << message->message << std::endl;
}