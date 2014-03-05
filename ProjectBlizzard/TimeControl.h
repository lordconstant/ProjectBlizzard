#pragma once
#include <windows.h>
#include <iostream>

using namespace std;

//namespace timeC{
	class TimeControl{
		double m_curTime, m_deltaTime, m_lastCall;
	public:
		static TimeControl& getInstance();
		~TimeControl();

		double getDeltaTime();
		float getCurTime();

		void updateTime();
	private:
		TimeControl();
	};
//}

