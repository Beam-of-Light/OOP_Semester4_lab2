#ifndef UTILS_H
#define UTILS_H

#include <chrono>
#include <random>
#include <ctime>

/// Useful functions and classes
namespace utils
{
	int generate_int(int low, int high);

	///	\brief Simple timer class
	class Timer
	{
	private:
		std::chrono::time_point<std::chrono::steady_clock> start;	///< Start time 
		std::chrono::time_point<std::chrono::steady_clock> finish;	///< Finish time

	public:
		Timer();

		void startTimer();
		double getDuration();
	};

}
#endif // !UTILS_H