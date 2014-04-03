#pragma once
#include <math.h>
#include "vector.h"
#include "TimeControl.h"
#include "DebugPrint.h"

const float GRAVITY = -0.075f;
const float TERMINAL_VELOCITY = -5.0f;

class Physics{
	Vector m_vel, m_acc, *m_pos;
	float m_wind;
	bool m_grounded;
public:
	Physics(Vector &pos);
	~Physics();

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

	void update();

	Vector nextPos();
};

