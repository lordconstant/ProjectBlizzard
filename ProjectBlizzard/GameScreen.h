#pragma once
#include "Scene.h"
#include "Camera.h"
#include "Timer.h"
#include "Cube.h"
#include <vector>
#include "TerrainGenerator.h"

class GameScreen :public Scene{
	Camera* m_cam;
	Timer* m_timer;
	vector<Cube>* m_land;
	TerrainGenerator m_tGen;
public:
	GameScreen();
	~GameScreen();

	void initialise();
	void update(float mouseX, float mouseY);
	void render();

	void processKeyUp(int key);
	void processKeyDown(int key);
	void processMouse(int key, int state);

	void genTerrain(int type);
};

