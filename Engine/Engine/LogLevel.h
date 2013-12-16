#ifndef LOGLEVEL_H
#define LOGLEVEL_H

//LogLevel provides a way to log message severity
enum LogLevel
{
	INFO,
	WARNING,
	ERR,
	FATAL,
	DEBUG,
	SIZE_OF_ENUM
};
//Provides a way to log the string representation to file
//String lengths should be equal
static const char* LogLevelNames[SIZE_OF_ENUM] = { "INFO   ", "WARNING", "ERROR  ", "FATAL  ", "DEBUG  " };
#endif