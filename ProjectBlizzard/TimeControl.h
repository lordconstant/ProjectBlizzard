#pragma once
#include <windows.h>
#include <iostream>
#include "Timer.h"

using namespace std;
using namespace timer;

class TimeControl{
	double m_curTime, m_deltaTime, m_lastCall;
	Timer* m_timer;
public:
	static TimeControl& getInstance();
	~TimeControl();

	double getDeltaTime();
	float getCurTime();

	void updateTime();
private:
	TimeControl();
};

