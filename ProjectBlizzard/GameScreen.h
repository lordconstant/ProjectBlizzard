#pragma once
#include "Scene.h"
#include "Camera.h"
#include "Cube.h"
#include "Sphere.h"
#include <vector>
#include "TerrainGenerator.h"
#include "Explosion.h"
#include "Unit.h"
#include "Team.h"
#include "SceneSelect.h"
#include "random.h"
#include "QuadTree.h"
#include "Timer.h"
#include "Water.h"
#include "Log.h"

using namespace timer;

const int NBR_UNITS = 4;
const int NBR_TEAMS = 2;
const int NBR_LEVELS = 4;
const int TURN_TIME = 60; //One minute
const int HIT_TURN_TIME = 2;
const int FIRED_TURN_TIME = 5;
const int GAME_TIME = 600; //Ten minutes
const float WATER_LEVEL = -0.1f;

class GameScreen :public Scene{
	int m_curTeam;
	Camera* m_cam;
	vector<Vector>* m_land;
	TerrainGenerator m_tGen;
	Explosion* m_explo;
	vector<Team*> m_teams;
	Unit* m_curUnit;
	Cube* m_landCube;
	float m_width, m_height;
	BFont* m_largeFont;
	bool m_fired, m_hitTerrain, m_delayTest;
	Sphere* m_skySphere;
	QuadTree* m_quadTree;
	Water* m_water;
	Timer* m_turnTimer, *m_gameTimer, *m_endTurnTimer;
public:
	GameScreen(HDC& hdc);
	~GameScreen();

	void initialise();
	void update(float mouseX, float mouseY);
	void render();
	void render2D();

	void processKeyUp(int key);
	void processKeyDown(int key);
	void processMouse(int key, int state);

	void createGame(int type);
	void genTerrain(int type);
	void placeUnit(Unit* unit);

	void changeUnit();

	//void boxCollision(Vector pos1, Vector pos2, float w1, float w2, float h1, float h2);

	void BuildQuadTree();
};

