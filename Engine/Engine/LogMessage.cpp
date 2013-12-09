#include "LogMessage.h"

LogMessage::LogMessage(std::string message)
{
	SYSTEMTIME sysTime;
	GetSystemTime(&sysTime);
	char buffer[40];
	sprintf(buffer, "%02d/%02d/%04d %02d:%02d:%02d.%04d", sysTime.wDay,sysTime.wMonth, sysTime.wYear, sysTime.wHour, sysTime.wMinute, sysTime.wSecond, sysTime.wMilliseconds);
	this->moment = buffer;
	this->level = LogLevel::INFO;
	this->message = message;
}

LogMessage::LogMessage(unsigned int message)
{
	SYSTEMTIME sysTime;
	GetSystemTime(&sysTime);
	char buffer[40];
	sprintf(buffer, "%02d/%02d/%04d %02d:%02d:%02d.%04d", sysTime.wDay,sysTime.wMonth, sysTime.wYear, sysTime.wHour, sysTime.wMinute, sysTime.wSecond, sysTime.wMilliseconds);
	this->moment = buffer;
	this->level = LogLevel::INFO;
	this->message = std::to_string(message);
}


LogMessage::LogMessage(std::string message, LogLevel level)
{
	SYSTEMTIME sysTime;
	GetSystemTime(&sysTime);
	char buffer[40];
	sprintf(buffer, "%02d/%02d/%04d %02d:%02d:%02d.%04d", sysTime.wDay,sysTime.wMonth, sysTime.wYear, sysTime.wHour, sysTime.wMinute, sysTime.wSecond, sysTime.wMilliseconds);
	this->moment = buffer;
	this->level = level;
	this->message = message;
}

LogMessage::LogMessage(unsigned int message, LogLevel level)
{
	SYSTEMTIME sysTime;
	GetSystemTime(&sysTime);
	char buffer[40];
	sprintf(buffer, "%02d/%02d/%04d %02d:%02d:%02d.%04d", sysTime.wDay,sysTime.wMonth, sysTime.wYear, sysTime.wHour, sysTime.wMinute, sysTime.wSecond, sysTime.wMilliseconds);
	this->moment = buffer;
	this->level = level;
	this->message = std::to_string(message);
}