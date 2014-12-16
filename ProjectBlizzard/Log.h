#pragma once
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>

using namespace std;

class Log
{
	int m_logNum, m_fileSize;
	string m_fileName, m_lastLine;
	ofstream m_file;
	Log();
public:
	static Log& getInstance();
	~Log();

	//Adds a new line to the error log
	void addLine(string txt);
	//Clears all text from the current error log
	void clearLog();
	//Removes the last line added to the error log
	void removeLastLine();
	//Creates a new separate error log file (leaving the old one)
	void newErrorLogFile();
};

