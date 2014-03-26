#pragma once
#include "DebugPrint.h"
#include "TimeControl.h"
#include "vector.h"

enum{XAXIS, YAXIS, ZAXIS};

class Movement{
	Vector* m_pos, *m_angle;
	float m_xVel, m_yVel, m_zVel;
	bool m_left, m_right, m_up, m_down, m_forwards, m_backwards;
public:
	Movement(Vector& pos, Vector& angle, float xVel, float yVel, float zVel);
	~Movement();

	Vector getPos();

	Vector getAngle();

	void definePos(Vector& pos);
	void defineAngle(Vector& angle);

	void setPos(Vector pos);
	void setPos(float x, float y, float z);

	void setXvel(float speed);
	void setYvel(float speed);
	void setZvel(float speed);
	void setAllVel(float speed);
	void setAllVel(float xSpeed, float ySpeed, float zSpeed);

	void moveXPos(float speed);
	void moveYPos(float speed);
	void moveZPos(float speed);

	void moveX();
	void moveY();
	void moveZ();

	void move(float xSpeed, float ySpeed, float zSpeed);

	void rotateBy(float angle, int axis);
	void rotateTo(float angle, int axis);

	void smoothRotateBy(float angle, float speed, int axis);
	void smoothRotateTo(float angle, float speed, int axis);

	void right(bool dir);
	void left(bool dir);
	void up(bool dir);
	void down(bool dir);
	void forward(bool dir);
	void backward(bool dir);

	void stopMoving();
};

