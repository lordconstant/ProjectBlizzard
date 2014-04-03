#pragma once
#include "scene.h"
#include "Camera.h"
#include "Button3D.h"
#include "SceneSelect.h"

class OptionsScreen :public Scene{
	Button3D* m_btn;
	Camera* m_cam;
public:
	OptionsScreen(void);
	~OptionsScreen(void);

	void initialise();
	void update(float mouseX, float mouseY);
	void render();

	void processKeyUp(int key);
	void processKeyDown(int key);
	void processMouse(int key, int state);
};

