#ifndef LOGMESSAGE_H
#define LOGMESSAGE_H
#include <string>
#include "time.h"
#include <iostream>
#include "Loglevel.h"

struct LogMessage
{
	///<summary>
	///Constructor providing a message, uses the INFO LogLevel as message severity
	///</summary>
	LogMessage(std::string message);
	///<summary>
	///Constructor for logging a message with a given severity
	///</summary>
	LogMessage(std::string message, LogLevel level);
	///<summary>
	///Message Severity
	///</summary>
	LogLevel level;
	///<summary>
	///Message
	///</summary>
	std::string message;
	///<summary>
	///Moment when the message was logged using second precision
	///</summary>
	std::string moment;
};

#endif