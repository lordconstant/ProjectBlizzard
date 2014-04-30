#include "TimeControl.h"

TimeControl& TimeControl::getInstance(){
	static TimeControl instance;
	return instance;
}

TimeControl::TimeControl()
{
	m_timer = new Timer;
	m_curTime = m_lastCall = m_timer->getElapsedTime();
}


TimeControl::~TimeControl(){
	if (m_timer){
		delete m_timer;
	}
}

double TimeControl::getDeltaTime(){
	return m_deltaTime;
}

float TimeControl::getCurTime(){
	return m_curTime;
}

void TimeControl::updateTime(){
	m_curTime = m_timer->getElapsedTime();

	m_deltaTime = m_curTime - m_lastCall;

	m_lastCall = m_curTime;
}