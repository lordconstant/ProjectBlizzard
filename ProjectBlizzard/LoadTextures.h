#ifndef LOADTEXTURES_H
#define LOADTEXTURES_H

#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <stdio.h>			// Header File For File I/O
//
// Class to load a bitmap file to a texture
// Note: Use getTexture to return texture number
//
class LoadTextures{
	bool status;
	BITMAP textureImage;  //data structure for bitmaps
	unsigned int *texture;
	static int num;
public:
	BYTE* textureImageData;  //bitmap data
	LoadTextures(char *Filename);
	LoadTextures(bool noGenTexture);
	void initialise();
	~LoadTextures();
	BITMAP LoadBMP(char *Filename);
	bool LoadGLTextures(char *s);
	bool getStatus(){ return status; }
	static int getNum(){ return num; }
	unsigned int getTexture(){ return *texture; }
	BYTE* getTextureImage(){ return textureImageData; }
};

#endif