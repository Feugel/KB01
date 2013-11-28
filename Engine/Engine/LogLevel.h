#ifndef LOGLEVEL_H
#define LOGLEVEL_H

///<summary>
///LogLevel provides a way to log message severity
///</summary>
enum LogLevel
{
	INFO,
	WARNING,
	ERROR,
	FATAL,
	DEBUG,
	SIZE_OF_ENUM
};
///<summary>
///Provides a way to log the string representation to file
///String lengths should be equal
///</summary>
static const char* LogLevelNames[SIZE_OF_ENUM] = { "INFO   ", "WARNING", "ERROR  ", "FATAL  ", "DEBUG  " };
#endif