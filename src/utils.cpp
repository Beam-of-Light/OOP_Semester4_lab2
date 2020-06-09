#include "utils.h"

namespace utils
{
	/// \details Generates pseudorandom integer
	/// \param[in] low, high Set interval for generation
	/// \return pseudorandom integer on the interval [low, high]
	int generate_int(int low, int high) {
		static std::random_device rd;
		static std::seed_seq seed{ rd(), (unsigned)time(nullptr) };
		static std::mt19937 gen(seed);
		std::uniform_int_distribution<> dis(low, high);
		return dis(gen);
	}

	/// \brief Default constructor
	/// \details Start timer
	Timer::Timer()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	/// \details Start timer
	void Timer::startTimer()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	/// \details Calculate duration from start to current time
	/// \return Duration from start to current time
	double Timer::getDuration()
	{
		finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = finish - start;
		return duration.count();
	}
}