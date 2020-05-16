#ifndef TIMER
#define TIMER

#include <chrono>

class Timer
{
private:
	std::chrono::time_point<std::chrono::steady_clock> start, finish;

public:
	Timer()
	{
		start = std::chrono::high_resolution_clock::now();
	}
	
	void start()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	double get_duration()
	{
		finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = finish - start;
		return duration.count();
	}
};

#endif /* TIMER */