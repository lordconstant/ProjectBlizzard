#include "BaseGame.h"

extern void DebugOut(const char *);

BaseGame::BaseGame(void){
	hWnd = NULL;
	hDC = NULL;
	hRC = NULL;

	bFullscreen = false;
	m_width = m_height = 1;
	display3D = true;
}

BaseGame::~BaseGame(void){
}


bool BaseGame::CreateScreen(char *wndTitle, int width, int height,int bpp, bool fullscreen){
	WNDCLASS				wc;
	PIXELFORMATDESCRIPTOR	pfd;
	RECT					WindowRect;
	unsigned int			PixelFormat;
	DWORD					dwStyle = WS_OVERLAPPEDWINDOW;

	bFullscreen = fullscreen;

	ZeroMemory(&wc, sizeof(wc));
	wc.style = CS_VREDRAW|CS_HREDRAW|CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	WindowRect.left=0;
	WindowRect.right=width;
	WindowRect.top=0;
	WindowRect.bottom=height;

	AdjustWindowRect(&WindowRect, WS_OVERLAPPEDWINDOW, FALSE);

	if(bFullscreen){
		DEVMODE dm;
		EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm);
		dm.dmSize	= sizeof(DEVMODE);
		dm.dmPelsWidth	= width;
		dm.dmPelsHeight = height;
		dm.dmBitsPerPel = bpp;
		ChangeDisplaySettings(&dm, CDS_FULLSCREEN);
		dwStyle = WS_POPUP;
	}

	hWnd = CreateWindow(CLASS_NAME, wndTitle, 
		dwStyle|WS_CLIPSIBLINGS|WS_CLIPCHILDREN, 
		CW_USEDEFAULT, CW_USEDEFAULT, 
		WindowRect.right-WindowRect.left, 
		WindowRect.bottom-WindowRect.top, 
		NULL, NULL, wc.hInstance, NULL);

	ZeroMemory(&pfd, sizeof(pfd));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = bpp;
	pfd.cDepthBits = 24;		// 24 bit z buffer resolution

	hDC = GetDC(hWnd);

	if(!(PixelFormat = ChoosePixelFormat(hDC, &pfd))){
		MessageBox(hWnd, "Failed to choose pixel format.", "ERROR", MB_OK);
		return false;
	}

	if(!SetPixelFormat(hDC, PixelFormat, &pfd)){
		MessageBox(hWnd, "Failed to set pixel format.", "ERROR", MB_OK);
		return false;
	}

	if(!(hRC = wglCreateContext(hDC))){
		MessageBox(hWnd, "Failed to create the OpenGL rendering context.", "ERROR", MB_OK);
		return false;
	}

	if(!wglMakeCurrent(hDC, hRC)){
		MessageBox(hWnd, "Failed to make current the OpenGL rendering context.", "ERROR", MB_OK);
		return false;
	}
	
	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	Resize(width, height);

	return true;
}


void BaseGame::ReleaseScreen(){
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRC);
	ReleaseDC(hWnd, hDC);
	if(bFullscreen){
		ChangeDisplaySettings(NULL, 0);
	}
	DestroyWindow(hWnd);
}

void BaseGame::Resize(int width, int height){
	if(height==0)
		height=1;
	glViewport(0, 0, width, height);
	m_width = (float)width; 
	m_height = (float)height;
	if(display3D)
		Set3D();
	else
		Set2D();
}

void BaseGame::Set3D(float fov, float nearZ, float farZ){
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	// Calculate The Aspect Ratio Of The Window
	gluPerspective(fov,(GLfloat)m_width/(GLfloat)m_height, nearZ, farZ);
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
	glEnable(GL_DEPTH_TEST);							// Assume we want this for 3D
	display3D = true;
}

void BaseGame::Set2D(float left, float right, float bottom, float top){
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	gluOrtho2D(left, right, bottom, top);
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
	glDisable(GL_DEPTH_TEST);							// Objects are layered in order drawn
	display3D = false;
}