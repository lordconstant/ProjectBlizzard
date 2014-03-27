#pragma once
#include "Scene.h"
#include "Camera.h"
#include "Timer.h"
#include "Cube.h"
#include <vector>
#include "TerrainGenerator.h"
#include "Explosion.h"

class GameScreen :public Scene{
	Camera* m_cam;
	Timer* m_timer;
	vector<Model*>* m_land;
	TerrainGenerator m_tGen;
	Explosion* m_explo;
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

