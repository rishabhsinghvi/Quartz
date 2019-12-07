#ifndef QUARTZ_TIMER_H
#define QUARTZ_TIMER_H

#include<chrono>

namespace Quartz
{
	class Timer
	{
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
	public:

		Timer() = default;

		void reset();

		void stop();

		void getDeltaT();

	};
}

#endif