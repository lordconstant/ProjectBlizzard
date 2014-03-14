#pragma once
#include <Windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "vector.h"
#include "Movement.h"

#define M_PI 3.14159265358979323846

class Camera{
	float m_angle;
	Vector m_pos, m_rot;
	Movement* m_move;
public:
	Camera();
	~Camera();

	Vector getPos();

	float getAngle();

	Movement* move();

	void update();

	void firstPerson(int rad, float mouseX, float mouseY, float sHeight, float sWidth);
};

