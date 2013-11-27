#include "Logger.h"


Logger::Logger(void)
{
	outputFile.open("Log.txt", std::fstream::app);
}

Logger::~Logger(void)
{
	outputFile.close();
}

void Logger::setLevel(int level)
{
	loglevel = level;
}
void Logger::writetolog(levels level, char message[])
{
	outputFile << std::time(0);
	outputFile << " - ";
	outputFile << getcharlevels(level);
	outputFile << " - ";
	outputFile << message << std::endl;
}

char* Logger::getcharlevels(levels level)
{
	// keep al returns at same length
	switch (level)
	{
	case Severe:
		return "Severe";
	case Error:
		return "Error ";
	case Log:
		return "Log   ";
	case Debug:
		return "Debug ";
	default:
		return "None  ";
	}

}