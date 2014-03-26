#pragma once
#include <Windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "vector.h"
#include "Movement.h"

#define M_PI 3.14159265358979323846

class Camera{
	Vector m_pos, m_angle, m_rot;
	Movement* m_move;
public:
	Camera();
	~Camera();

	Vector getPos();

	Vector getAngle();

	Movement* move();

	void update();

	float degToRads(float angle);
};

