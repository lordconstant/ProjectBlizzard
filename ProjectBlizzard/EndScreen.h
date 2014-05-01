#pragma once
#include "Scene.h"
#include "Button3D.h"
#include "Camera.h"
#include "BFont.h"
#include "SceneSelect.h"

const int NBR_BTNS = 3;

class EndScreen :public Scene{
	Button3D* m_btns[NBR_BTNS];
	BFont* m_largeFont;
	Camera* m_cam;
public:
	EndScreen(HDC hdc);
	~EndScreen();

	void initialise();
	void update(float mouseX, float mouseY);
	void render();
	void render2D();

	void processKeyUp(int key);
	void processKeyDown(int key);
	void processMouse(int key, int state);
};

