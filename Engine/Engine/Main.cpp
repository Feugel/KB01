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
	LogManager* logger = new LogManager();
	logger->Log("Test: 1 Million Logs");
	/*for(int i = 0; i < 1000000; i++)
	{
		logger->Log(LogLevel::INFO, "TEST LOG HAHA");
	}*/

	return 0;
}