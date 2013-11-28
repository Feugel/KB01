#include "LogManager.h"

class Main
{
public:
	int main();
private:
	LogManager* logger;
};


int main()
{
	LogManager* logger = LogManager::Instance();
	logger->Log("Test: 1 Million Logs");
	for(int i = 0; i < 1000000; i++)
	{
		LogManager::Instance()->Log(LogLevel::WARNING, "TEST");
		//logger->Log(LogLevel::INFO, "TEST LOG HAHA");
	}

	return 0;
}