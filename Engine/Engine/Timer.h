#ifndef TIMER_H
#define TIMER_H

#include <time.h>

class Timer {
	public:
		Timer();
		void           Start();
		void           Stop();
		void           Reset();
		bool           IsRunning();
		unsigned long  GetTime();
		bool           IsOver(unsigned long seconds);
	private:
		bool           resetted;
		bool           running;
		unsigned long  beg;
		unsigned long  end;
};
#endif