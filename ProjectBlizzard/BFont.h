#pragma once

#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library

class BFont {
private:
	unsigned int listBase;	// display list base
	float R, G, B, height;

public:
	BFont(HDC hDC, char* fName, int fSize);
	~BFont() { CleanUp(); }

	void printString(float x, float y, char* s);
	void ClearFont(unsigned int base);
	void CleanUp();
	void setColor(float r, float g, float b);
	float getHeight();
};