#pragma once
#include "key_codes.h"

class Scene{
protected:
	float m_mouseX, m_mouseY;
public:
	Scene();
	~Scene();

	virtual void initialise() = 0;
	virtual void update(float mouseX, float mouseY) = 0;
	virtual void render() = 0;

	virtual void processKeyUp(int key) = 0;
	virtual void processKeyDown(int key) = 0;
	virtual void processMouse(int key, int state) = 0;
};

