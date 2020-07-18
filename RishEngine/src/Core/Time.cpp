#include "Rish/Core/Time.h"

namespace rl {

std::chrono::steady_clock::time_point Time::m_clock_start = std::chrono::steady_clock::now();

Time Time::Now()
{
	auto clock_end = std::chrono::steady_clock::now();
	std::chrono::duration<float> time_span = std::chrono::duration_cast<std::chrono::duration<float>>(clock_end - m_clock_start);
	return Time(time_span.count());
}

Time Clock::getElapsedTime()
{
	return Time::Now() - m_startTime;
}

Time Clock::restart()
{
	Time now = Time::Now();
	Time elapsed = now - m_startTime;
	m_startTime = now;
	return elapsed;
}

Timer::Timer(Time t, TimerCallback callback)
{
	m_t = t;
	m_timerCallback = callback;
	m_loopTimes = PERMANENT;
}

std::list<Timer> Timer::m_timerList;
std::list<Timer> Timer::m_loopTimerList;

void Timer::restart()
{
	m_start = Time::Now();
}

void Timer::AddTimer(Timer t)
{
	t.restart();
	m_timerList.push_back(t);
}

void Timer::AddLoopTimer(Timer t, int times)
{
	t.restart();
	t.m_loopTimes = times;
	m_loopTimerList.push_back(t);
}

void Timer::Update()
{
	auto timer = m_timerList.begin();

	while (timer != m_timerList.end())
	{
		if(Time::Now() - timer->m_start >= timer->m_t)
		{
			timer->m_timerCallback();
			m_timerList.erase(timer++);
		}
		else
		{
			++timer;
		}
	}

	auto loopTimer = m_loopTimerList.begin();

	while (loopTimer != m_loopTimerList.end())
	{
		if(loopTimer->m_loopTimes)
		{
			if(Time::Now() - loopTimer->m_start >= loopTimer->m_t)
			{
				loopTimer->m_timerCallback();
				loopTimer->restart();
				// if loopTims < 0 indicates it is PERMANENT so that it should be -1, else should decrement by 1
				loopTimer->m_loopTimes = ( loopTimer->m_loopTimes < 0 ? loopTimer->m_loopTimes : --loopTimer->m_loopTimes);
			}
		}

		if(!loopTimer->m_loopTimes)
		{
			m_timerList.erase(loopTimer);
		}

		++loopTimer;
	}
}

void Timer::Clear()
{
	m_timerList.clear();
	m_loopTimerList.clear();
}

}