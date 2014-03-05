#pragma once
#include <Windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "Movement.h"

class Camera{
	float m_angle;
	Vector m_pos;
	Movement* m_move;
public:
	Camera();
	~Camera();

	Vector getPos();

	float getAngle();

	Movement* move();

	void update();
};

