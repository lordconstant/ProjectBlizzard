#include "Timer.h"


Timer::Timer(){
	m_timeElapsed = 0;
}


Timer::~Timer(){
}

float Timer::getElapsedTime(){
	return m_timeElapsed;
}

void Timer::update(){
	if (m_playing){
		m_timeElapsed += TimeControl::getInstance().getDeltaTime();
	}
}

void Timer::pause(){
	if (m_playing){
		m_playing = false;
	}
}

void Timer::play(){
	if (!m_playing){
		m_playing = true;
	}
}

void Timer::stop(){
	m_timeElapsed = 0;
	m_playing = false;
}

void Timer::reset(){
	m_timeElapsed = 0;
}