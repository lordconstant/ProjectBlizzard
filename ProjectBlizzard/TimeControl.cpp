#include "TimeControl.h"

TimeControl& TimeControl::getInstance(){
	static TimeControl instance;
	return instance;
}

TimeControl::TimeControl()
{
	m_curTime = m_lastCall = timeGetTime();
}


TimeControl::~TimeControl()
{
}

double TimeControl::getDeltaTime(){
	return m_deltaTime;
}

float TimeControl::getCurTime(){
	return m_curTime;
}

void TimeControl::updateTime(){
	m_curTime = timeGetTime();

	m_deltaTime = m_curTime - m_lastCall;

	m_deltaTime /= 1000;
	m_lastCall = m_curTime;
}