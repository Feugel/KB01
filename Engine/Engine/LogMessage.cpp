#include "LogMessage.h"

std::string moment;
std::string message;
LogLevel level;

LogMessage::LogMessage(std::string message)
{
	char buffer[80];
	std::time_t now = std::time(0);
	std::strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", std::localtime(&now));
	this->moment = buffer;
	this->level = LogLevel::INFO;
	this->message = message;
}

LogMessage::LogMessage(std::string message, LogLevel level)
{
	char buffer[80];
	std::time_t now = std::time(0);
	std::strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", std::localtime(&now));
	this->moment = buffer;
	this->level = level;
	this->message = message;
}