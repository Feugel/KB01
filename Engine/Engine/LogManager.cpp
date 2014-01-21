#include "LogManager.h"

LogManager* LogManager::logManager = NULL;


LogManager::LogManager()
{
	this->logFile = fopen("log.txt", "a+");
}

LogManager::LogManager(std::string fileName)
{
	this->logFile = fopen(fileName.c_str(), "a+");
}

LogManager::~LogManager()
{
	Cleanup();
}

void LogManager::Cleanup()
{
	if(NULL != logManager)
		delete logManager;
}

void LogManager::Log(std::string format, ...)
{
	va_list arguments;
	va_start(arguments, format);
	fprintf(logFile, "%s %s ", GetTime().c_str(), LogLevelNames[LogLevel::INFO]);
	vfprintf(logFile, format.c_str(), arguments);
	fprintf(logFile, "%s", "\n");
	va_end(arguments);
}

void LogManager::Log(LogLevel level, std::string format, ...)
{
	va_list arguments;
	va_start(arguments, format);
	fprintf(logFile, "%s %s ", GetTime().c_str(), LogLevelNames[level]);
	vfprintf(logFile, format.c_str(), arguments);
	fprintf(logFile, "%s", "\n");
	va_end(arguments);
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

std::string LogManager::GetTime()
{
	SYSTEMTIME sysTime;
	GetSystemTime(&sysTime);
	char buffer[40];
	sprintf(buffer, "%02d/%02d/%04d %02d:%02d:%02d.%04d", sysTime.wDay,sysTime.wMonth, sysTime.wYear, sysTime.wHour, sysTime.wMinute, sysTime.wSecond, sysTime.wMilliseconds);
	std::string time = buffer;
	return time;
}