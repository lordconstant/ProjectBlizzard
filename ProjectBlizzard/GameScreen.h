#pragma once
#include "Scene.h"
#include "Camera.h"
#include "Timer.h"
#include "Cube.h"
#include <vector>
#include "TerrainGenerator.h"
#include "Explosion.h"
#include "Unit.h"
#include "Team.h"
#include "SceneSelect.h"

const int NBR_UNITS = 4;
const int NBR_TEAMS = 2;

class GameScreen :public Scene{
	int m_curTeam;
	Camera* m_cam;
	Timer* m_timer;
	vector<Vector>* m_land;
	TerrainGenerator m_tGen;
	Explosion* m_explo;
	vector<Team*> m_teams;
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

	void changeUnit();
};

