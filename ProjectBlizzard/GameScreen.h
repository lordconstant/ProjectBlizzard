#pragma once
#include "Scene.h"
#include "Rectangle.h"
#include "Camera.h"
#include "Timer.h"

class GameScreen :public Scene{
	Rect* m_land;
	Camera* m_cam;
	Timer* m_timer;
public:
	GameScreen();
	~GameScreen();

	void initialise();
	void update(float mouseX, float mouseY);
	void render();

	void processKeyUp(int key);
	void processKeyDown(int key);
	void processMouse(int key, int state);
};

