#include "Main.h"
#include "Logger.h"
#include <iostream>

int main() 
{ 
    
	Logger* logger = new Logger();
	logger->writetolog(Log, "Starting Application");
	
	for (int i = 0; i < 1000000; i++)
	{
		logger->writetolog(Debug, "Test");
	}

	logger->writetolog(Log, "Stopping Application");
	delete logger;

    return 0; 
}

Main::Main(void)
{
	
}


Main::~Main(void)
{
}
