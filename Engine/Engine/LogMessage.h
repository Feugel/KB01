#ifndef LOGMESSAGE_H
#define LOGMESSAGE_H
#include "time.h"
#include <windows.h>
#include <iostream>
#include <sstream>
#include "Loglevel.h"

struct LogMessage
{
	//Constructor providing a message, uses the INFO LogLevel as message severity
	LogMessage(std::string message);
	//Constructor for logging a message with a given severity
	LogMessage(LogLevel level, std::string message);
	//Message Severity
	LogLevel level;
	//Message
	std::string message;
	//Moment when the message was logged using second precision
	std::string moment;
};

#endif