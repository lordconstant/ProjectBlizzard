#pragma once

#include <windows.h>
#include <glew.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <stdio.h>
#include "key_codes.h"

#define CLASS_NAME "OpenGL"

/**
This is the parent class for any Game class and performs the actions 
associated with OpenGL and is used to create the game window.  <br>

Your Game class should inherit from this class and provide all the game
specific actions eg creating the game objects and perform the game logic <br>

Although we are using inheritance we are not supporting polymorphism. <br>

This class supports both 2D and 3D games, by default it is set to 3D but for
a 2D game you should call Set2D() before entering the main game loop. <br>

You can also use the Set3D and Set2D methods to create a 2D HUD or status
display.

DO NOT MODIFY THIS CLASS - INHERIT FROM IT AND OVERRIDE 
THESE METHODS IF NECCESSARY FOR YOUR PROGRAM
*/
class BaseGame{
	// Allow event handler direct access to these attributes
	friend LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	HWND	hWnd;
	HDC		hDC;
	HGLRC	hRC;
	/// Whether to display in fullscreen
	bool	bFullscreen;

	/// The width and height of the display area or window
	float m_width, m_height;
	
	/// Whether this is a 3D or 2D game
	bool display3D;

public:
	BaseGame(void);
	virtual ~BaseGame(void);

	// Opengl render methods.
	/**
	Cfreate a display area of the given size and indicate if it should be
	fullscreen.
	@param width display width in pixels
	@param height display height in pixels
	@param bpp the colour depth in bits (usually 32)
	@param fullscreen fullscreen (true) or windowed (false)
	@return true if the display was successfully created else false
	*/
	bool CreateScreen(char *wndTitle, int width, int height,int bpp, bool fullscreen);

	/**
	Release resources resrved during the CreateScreen method
	*/
	void ReleaseScreen();

	/**
	The display has been resized do reset the display perspective 
	depending on whether it is 2D or 3D display.
	*/
	void Resize(int width, int height);

	/**
	Swap the buffers since we are using double buffering
	*/
	void Swap(){ SwapBuffers(hDC); }

	/**
	Sets the display to 3D perspective mode
	@param fov the vertical field of view in degrees
	@param nearZ the nera clipping distance
	@param farZ the distant clipping zone
	*/
	void Set3D(float fov = 60.0f, float nearZ = 0.1f, float farZ = 1000.0f);

	/**
	Sets the display to 2D  <br>
	NOTE: this does not disable depth testing
	@param left value to use for left edge of the display
	@param right value to use for right edge of the display
	@param bottom value to use for bottom edge of the display
	@param top value to use for top edge of the display
	*/
	void Set2D(float left = -1, float right = 1, float bottom = -1, float top = 1);

};
