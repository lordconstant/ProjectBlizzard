// Initial OpenGL Framework
// DO not modify this project. Use a copy of it.
#pragma once
#include "Game.h"

// tell the compiler to always link into a Winmain, even if we are using a console app
#pragma comment (linker, "/ENTRY:WinMainCRTStartup") 

/*
The following code tells the linker whether to create a console or not. If we are debugging logic,
we can easily switch to console output and print debug messages to the console.
*/

// comment this out for OGL usage.
//#define _CONSOLEONLY_

#ifdef _CONSOLEONLY_
	#pragma comment (linker, "/SUBSYSTEM:CONSOLE") // Show console output in debug mode 
#else 
	#pragma comment (linker, "/SUBSYSTEM:WINDOWS") 
#endif 

Game g_Game;	//Access to Game Object


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	switch(uMsg){
		case WM_KEYDOWN:
			g_Game.sceneSel->getCurScene()->processKeyDown(wParam);
			switch(wParam)	{
				case VK_ESCAPE:
					PostQuitMessage(0);
					break;
				case VK_O:
					g_Game.sceneSel->setScene(OPTIONS);
				default:
					break;
			}
			break;
		case WM_KEYUP:
			g_Game.sceneSel->getCurScene()->processKeyUp(wParam);
			break;
		case WM_DESTROY:
		case WM_CLOSE:
			PostQuitMessage(0);
			break;
		case WM_SIZE:
			g_Game.Resize(LOWORD(lParam), HIWORD(lParam));
			break;
		case WM_MOUSEMOVE:
			// Track the mouse position
			g_Game.mouseX = LOWORD(lParam);
			g_Game.mouseY = HIWORD(lParam);
			break;
		case WM_LBUTTONDOWN:
			g_Game.sceneSel->getCurScene()->processMouse(uMsg, wParam);
			break;
		case WM_RBUTTONDOWN:
			g_Game.sceneSel->getCurScene()->processMouse(uMsg, wParam);
			break;
		case WM_MOUSEWHEEL:
			g_Game.sceneSel->getCurScene()->processMouse(uMsg, wParam);
			break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

/**
This is the starting point for the application
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow){
	MSG msg;
	bool done = false;

	// don't create a screen if we are in "console output" mode
#ifndef _CONSOLEONLY_
	g_Game.CreateScreen("OpenGL Framework", 800, 600, 32, false);
	g_Game.InitOpenGL();
#endif

	DebugOut("Initialising Game");
	g_Game.Initialise();

	// ===========================================================================
	//            THE MAIN GAME LOOP
	// ===========================================================================
	while(!done){
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			if(msg.message == WM_QUIT){
				done = true;
			}else{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}else{
			// the loop that updates the game..
			g_Game.Update();
			// don't perform graphical updates if we are in "console" mode
#ifndef _CONSOLEONLY_
			g_Game.Render();
			g_Game.Swap();
#endif

		}
	}

// don't need to release any screens if we are using a console.
#ifndef _CONSOLEONLY_
	g_Game.ReleaseScreen();
#endif
	
	g_Game.Shutdown();

	return msg.wParam;
}
