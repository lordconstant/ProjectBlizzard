#include "BFont.h"

BFont::BFont(HDC hDC, char *fName, int fSize){
	HFONT hFont, oldF;         // windows font
	unsigned int base;
	listBase = 0;
	R = G = B = 1.0f;

	base = glGenLists(96);      // create storage for 96 characters

	if (_stricmp(fName, "symbol") == 0)	{
	     hFont = CreateFont(fSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, SYMBOL_CHARSET, 
							OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
							FF_DONTCARE | FIXED_PITCH, fName);
	}else{
		 hFont = CreateFont(fSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, 
							OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
							FF_DONTCARE | FIXED_PITCH, fName);
	}

	if (!hFont)
		return;

	oldF = (HFONT)SelectObject(hDC, hFont);
	boolean b = wglUseFontBitmaps(hDC, 32, 96, base);
	SelectObject(hDC, oldF);
	listBase = base;
}

void BFont::setColor(float r, float g, float b){
	R = r; G = g; B = b;
}

void BFont::printString(float x, float y, char *s){
	if ((listBase == 0) || (s == NULL))
		return;
	glDisable(GL_TEXTURE_2D);  //req'd for bitmap fonts
	glTranslatef(0.0f, 0.0f, -1.0f);
	glColor3f(R, G, B);
	glRasterPos2f(x, y);

	glPushAttrib(GL_LIST_BIT);
		glListBase(listBase - 32);
		glCallLists(strlen(s), GL_UNSIGNED_BYTE, s);
	glPopAttrib();
	glEnable(GL_TEXTURE_2D);  //reset texture mapping on
	glTranslatef(0.0f, 0.0f, 1.0f);
}

void BFont::ClearFont(unsigned int base){
	if (base != 0)
		glDeleteLists(base, 96);
}


void BFont::CleanUp(){
	ClearFont(listBase);
}
