/*
File: timer.h
Author: Peter Lager
Version: 2.10
Date Last Modified: 27-12-2006


Include file that provides a timer device to either
provide a delay or to measure elapsed time. The same
timer should not be used to perform both actions
simultaneously.

To use the features in this facility you need to #include
this file and add the following line
using namespace timer;

Create an instance of a timer use
Timer mytimer;

To create a half second delay in your program use
mytimer.delay(0.5f);

To measure elapsed time start or reset the timer using

mytimer.startTimer();
or
mytimer.resetTimer();


later in your program you can measure the elapsed
time since the timer was started or reset using

elapsedTime = mytimer.getElapsedTime();

where elapsedTime is of type 'float'

You can also use 
lapTime = mytimer.getLapTime();

which returns the number of seconds passed since
the method was last called.

*/

#pragma once

#include <windows.h>

namespace timer
{

/**
This class provides a high resolution timer object.

To use the features in this facility you need to #include this
file and add the following line
\code using namespace timer; \endcode

You can then create and use your own timer objects e.g.
\code Timer t1, t2; \endcode

Full supporting comments are in the timer.h file
*/

class Timer
{
public:
	Timer(void)
	{
		m_TicksPerSecond.QuadPart = 1;
		m_StartTime.QuadPart = 0;
		startTimer();
	}

	virtual ~Timer(void){};

	// Start clock and initialise start time to now
	bool startTimer()
	{
		if(!QueryPerformanceFrequency(&m_TicksPerSecond))
			return false;
		else
		{
			QueryPerformanceCounter(&m_StartTime);
			return true;
		}
	}

	// Reset clock to now (Does same as startTimer()
	bool resetTimer()
	{
		if(!QueryPerformanceFrequency(&m_TicksPerSecond))
			return false;
		else
		{
			QueryPerformanceCounter(&m_StartTime);
			return true;
		}
	}

	// Get time since the last time this method was called
	float getLapTime()
	{
		static LARGE_INTEGER lastTime = m_StartTime;
		LARGE_INTEGER currentTime;
		float seconds;

		QueryPerformanceCounter(&currentTime);

		seconds = ((float)currentTime.QuadPart - (float)lastTime.QuadPart) /
			(float)m_TicksPerSecond.QuadPart;
		lastTime = currentTime;

		return seconds;
	}

	// Get total time since timer was 'started' or 'reset'
	float getElapsedTime()
	{
		LARGE_INTEGER currentTime;
		float seconds;

		QueryPerformanceCounter(&currentTime);

		seconds = ((float)currentTime.QuadPart - (float)m_StartTime.QuadPart) /
			(float)m_TicksPerSecond.QuadPart;

		return seconds;
	}

	// Pause for a peroid of time measured in seconds 
	void delay(float pauseTime)
	{
		LARGE_INTEGER startTime, currentTime;
		float seconds;

		QueryPerformanceCounter(&startTime);
		do
		{
			QueryPerformanceCounter(&currentTime);
			seconds = ((float)currentTime.QuadPart - (float)startTime.QuadPart) /
				(float)m_TicksPerSecond.QuadPart;

		} while (seconds <= pauseTime);
	}

protected:
	LARGE_INTEGER m_TicksPerSecond;
	LARGE_INTEGER m_StartTime;
};

} // End of namespace timer
