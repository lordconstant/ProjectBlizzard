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
	if (m_deltaTime == 0){
		m_deltaTime++;
	}

	m_deltaTime /= 100;
	m_lastCall = m_curTime;
}