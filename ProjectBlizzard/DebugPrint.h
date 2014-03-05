#pragma once
#include <Windows.h>
#include <fstream>
using namespace std;

static void DebugOut(const char *szOut){
#ifdef _CONSOLEONLY_
	printf(szOut);
	printf("\n");
#else 
	OutputDebugString(szOut);
	OutputDebugString("\n");
#endif 
}

template <class T>
static void save1DarrayToCSV(char *fileName, T *arry, int n){
	char fn[256];
	sprintf(fn, "%s.csv", fileName);
	ofstream outFile(fn, ios::out);	//Create a CSV file

	outFile << "Num, Value\n";
	for (int i = 0; i < n; i++)
		outFile << i << "," << arry[i] << "\n";

	outFile << "\nMin,=MIN(B2:B" << n+1 << ")\n";	//For Excel, output Summary stats
	outFile << "Max,=MAX(B2:B" << n+1 << ")\n";
	outFile << "Avg,=Average(B2:B" << n+1 << ")\n";

	outFile.close();
}