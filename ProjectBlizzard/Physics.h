#pragma once
#include <math.h>
#include "vector.h"
#include "TimeControl.h"
#include "DebugPrint.h"

const float GRAVITY = -5.0f;
const float TERMINAL_VELOCITY = -10.0f;
const float DRAG = 2.0f;

class Physics{
	Vector m_vel, m_acc, *m_pos;
	float m_wind;
	bool m_grounded;
	bool m_slowed;
public:
	Physics(Vector &pos);
	~Physics();

	float getAccelX();
	float getAccelY();
	float getVelX();
	float getVelY();

	Vector getVelocity();

	void definePos(Vector &pos);
	void setAccel(float x, float y);
	void setAccelX(float acc);
	void setAccelY(float acc);
	void setVelocity(float x, float y);
	void setVelocityX(float vel);
	void setVelocityY(float vel);
	void setWind(float power);
	void isGrounded(bool grounded);
	bool isGrounded();

	void slowDown();

	void update();

	Vector nextPos();
};

