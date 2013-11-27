#include <iostream>
#include <fstream>
#include <ctime>

enum levels
	{
		Severe,
		Error,
		Log,
		Debug
	};

class Logger
{
public:
	Logger(void);
	~Logger(void);
	void setLevel(int level);
	void writetolog(levels level, char message[]);
	
	
private:
	void preparelog();
	char* getcharlevels(levels level);
	int loglevel;

	std::ofstream outputFile;
};

