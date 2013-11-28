#include "LogMessage.h"

LogMessage::LogMessage(std::string message)
{
	char buffer[80];
	time_t now = time(0);
	strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", localtime(&now));
	this->moment = buffer;
	this->level = LogLevel::INFO;
	this->message = message;
}

LogMessage::LogMessage(std::string message, LogLevel level)
{
	char buffer[80];
	time_t now = time(0);
	strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", localtime(&now));
	this->moment = buffer;
	this->level = level;
	this->message = message;
}