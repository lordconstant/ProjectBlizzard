#pragma once
#include "key_codes.h"
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "vector.h"

class Scene{
protected:
	float m_mouseX, m_mouseY, m_sWidth, m_sHeight;
	Vector m_mousePos;
public:
	Scene();
	~Scene();

	virtual void initialise() = 0;
	virtual void update(float mouseX, float mouseY) = 0;
	virtual void render() = 0;

	virtual void processKeyUp(int key) = 0;
	virtual void processKeyDown(int key) = 0;
	virtual void processMouse(int key, int state) = 0;

	void mouseToWorldCoord(float x, float y);
	void setScreenSize(float width, float height);
protected:
	void updateMouse(float mouseX, float mouseY);
};

