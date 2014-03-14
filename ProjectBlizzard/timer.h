#pragma once
#include "TimeControl.h"

class Timer{
	float m_timeElapsed;
	bool m_playing;
public:
	Timer();
	~Timer();

	float getElapsedTime();

	void update();
	void pause();
	void play();
	void stop();
	void reset();
};

