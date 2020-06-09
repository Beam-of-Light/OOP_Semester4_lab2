///	\file
///	\brief This file contains definition and implementation of class Timer
#ifndef TIMER
#define TIMER

#include <chrono>

///	\brief Simple timer class
class Timer
{
private:
	std::chrono::time_point<std::chrono::steady_clock> start;	///< Start time 
	std::chrono::time_point<std::chrono::steady_clock> finish;	///< Finish time

public:
	/// \brief Default constructor
	/// \details Start timer
	Timer()
	{
		start = std::chrono::high_resolution_clock::now();
	}
	
	/// \details Start timer
	void start()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	/// \details Calculate duration from start to current time
	/// \return Duration from start to current time
	double get_duration()
	{
		finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = finish - start;
		return duration.count();
	}
};

#endif /* TIMER */