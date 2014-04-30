#pragma once
#include "Scene.h"
#include "Camera.h"
#include "Button3D.h"
#include "Explosion.h"
#include "SceneSelect.h"
#include <vector>

using namespace std;

class StartScreen :public Scene{
	vector<Button3D*> m_btns;
	Camera* m_cam;
public:
	StartScreen(HDC hdc);
	~StartScreen();

	void initialise();
	void update(float mouseX, float mouseY);
	void render();
	void render2D();

	void processKeyUp(int key);
	void processKeyDown(int key);
	void processMouse(int key, int state);
};

