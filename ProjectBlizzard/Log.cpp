#include "Log.h"


Log::Log(){
	m_logNum = 0;
	m_fileSize = 0;
	m_fileName = "Log.txt";
	m_file.open(m_fileName, ios::trunc);
	m_file.close();
}

Log::~Log(){
}

Log& Log::getInstance(){
	static Log log;

	return log;
}

void Log::addLine(string txt){
	m_file.open(m_fileName, ios::out | ios::app);
	m_lastLine = txt;
	char timeStr[255], hours[3], mins[3], secs[3];

	time_t timeObj;
	time(&timeObj);
	tm *pTime = gmtime(&timeObj);

	if (pTime->tm_hour < 10){
		sprintf_s(hours, "0%i", pTime->tm_hour + 1);
	}
	else{
		sprintf_s(hours, "%i", pTime->tm_hour + 1);
	}

	if (pTime->tm_min < 10){
		sprintf_s(mins, "0%i", pTime->tm_min);
	}
	else{
		sprintf_s(mins, "%i", pTime->tm_min);
	}

	if (pTime->tm_sec < 10){
		sprintf_s(secs, "0%i", pTime->tm_sec);
	}
	else{
		sprintf_s(secs, "%i", pTime->tm_sec);
	}

	sprintf(timeStr, "[%i/%i/%i](%s:%s:%s) - ", pTime->tm_mday, pTime->tm_mon + 1, pTime->tm_year + 1900, hours, mins, secs);
	txt = timeStr + txt + "\n";
	m_file << txt.c_str();
	m_file.close();
}

void Log::clearLog(){
	m_file.open(m_fileName, ios::trunc);
	m_file.close();
}

void Log::removeLastLine(){
	ifstream file(m_fileName, ios::in | ios::ate);
	char* temp = new char[file.tellg()];
	string txt;
	file.read(temp, file.tellg());
	txt = temp;
	delete[] temp;

	txt.resize(txt.length() - m_lastLine.length());
	file.close();

	m_file.open(m_fileName, ios::out | ios::trunc);
	m_file.write(txt.c_str(), txt.length());
	m_file.close();
}

void Log::newErrorLogFile(){
	m_logNum++;
	m_fileName = "Log_" + to_string(m_logNum);
	m_fileName += ".txt";
	clearLog();
}