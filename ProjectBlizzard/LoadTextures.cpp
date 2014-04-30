#include "LoadTextures.h"

int LoadTextures::num = 0;  //set static counter

LoadTextures::LoadTextures(char *fn){
	initialise();
	num++;
	LoadGLTextures(fn);
}

LoadTextures::LoadTextures(bool noGenTexture){
	initialise();
}

void LoadTextures::initialise(){
	textureImageData = NULL;
	texture = new unsigned int;
	status = false;
}

LoadTextures::~LoadTextures(){
	if(texture) delete texture;
	if(textureImageData) delete textureImageData;
}

BITMAP LoadTextures::LoadBMP(char *Filename){	//Loads a Bitmap & returns bitmap object
	FILE *File=NULL;  // File Handle
	HBITMAP hBmp;
	BITMAP bm;

	if (Filename){
		File=fopen(Filename,"r");			// Check To See If The File Exists
		if (File){							// Does The File Exist?
			fclose(File);					// Close The Handle

			HBITMAP hBmp = (HBITMAP) LoadImage (NULL, (LPCTSTR) Filename, IMAGE_BITMAP, 
				0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			GetObject (hBmp, sizeof (bm),  &bm);  //load bitmap structure

			unsigned int bSize = bm.bmHeight * bm.bmWidthBytes;  //ensure padding included in width
			textureImageData = new BYTE[bSize];
			BYTE* tmpBuf = new BYTE[bSize];
			int s = sizeof(bm.bmBits);
			memcpy(tmpBuf, bm.bmBits, bSize);  //copy bmp data to tmp data ptr

			long bufpos = 0;   
			long newpos = 0;
			for(int y = 0; y < bm.bmHeight; y++){  //swap back-to-front BGR img to texture RGB img
				for(int x = 0; x < 3 * bm.bmWidth; x += 3){
					newpos = y * 3 * bm.bmWidth + x;     
					bufpos = (bm.bmHeight - y - 1) * bm.bmWidthBytes + x;

					textureImageData[newpos] = tmpBuf[bufpos + 2];       
					textureImageData[newpos + 1] = tmpBuf[bufpos+1]; 
					textureImageData[newpos + 2] = tmpBuf[bufpos];     
				}
			}
			delete[] tmpBuf;
		}
	}
	return bm;
}

bool LoadTextures::LoadGLTextures(char *s){		// Load Bitmaps And Convert To Textures
	status = false;

// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
	glGenTextures(1, texture);		// Create The Textures

	textureImage = LoadBMP(s);
	if (textureImage.bmHeight > 0){
		status = true;							// Set The Status To TRUE
		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, *texture);
   
// (GL_TEXTURE_MAG_FILTER) for stretched on the screen than the original texture, or when it's smaller 
// (GL_TEXTURE_MIN_FILTER) on the screen than the actual texture. GL_LINEAR also used. 
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);	
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);	

// Generate The Texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureImage.bmWidth, textureImage.bmHeight, 
			0, GL_RGB, GL_UNSIGNED_BYTE, textureImageData);
	}

//	If everything went OK, the variable Status will be TRUE. 
	return status;								
}
