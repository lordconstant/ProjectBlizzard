#pragma once
#include "Scene.h"
#include "Camera.h"
#include "Timer.h"
#include "Cube.h"
#include <vector>
#include "TerrainGenerator.h"
#include "Explosion.h"
#include "Unit.h"

const int NBR_UNITS = 8;

class GameScreen :public Scene{
	Camera* m_cam;
	Timer* m_timer;
	vector<Vector>* m_land;
	TerrainGenerator m_tGen;
	Explosion* m_explo;
	vector<Unit*> m_unit;
	Unit* m_curUnit;
	Cube* m_landCube;
	float m_width, m_height;

	bool renderCubes;
public:
	GameScreen();
	~GameScreen();

	void initialise();
	void update(float mouseX, float mouseY);
	void render();

	void processKeyUp(int key);
	void processKeyDown(int key);
	void processMouse(int key, int state);

	void createGame(int type);
	void genTerrain(int type);
	void placeUnit(Unit* unit);
};

