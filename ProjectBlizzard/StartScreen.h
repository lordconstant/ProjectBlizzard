#pragma once
#include "Scene.h"
#include "Camera.h"
#include "Cube.h"
#include <vector>

using namespace std;

class StartScreen :public Scene{
	vector<Cube*> m_cubes;
	Camera* m_cam;
public:
	StartScreen();
	~StartScreen();

	void initialise();
	void update();
	void render();

	void processKey(int key);
};

