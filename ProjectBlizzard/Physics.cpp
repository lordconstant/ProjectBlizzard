#include "Physics.h"


Physics::Physics(Vector& pos){
	m_pos = &pos;
	m_vel = m_acc = Vector(0, 0, 0);
	m_grounded = false;
	m_wind = 0;
}


Physics::~Physics()
{
}

Vector Physics::getVelocity(){
	return m_vel;
}

void Physics::definePos(Vector &pos){
	m_pos = &pos;
}

void Physics::setAccel(float x, float y){
	m_acc = Vector(x, y, 0);
}

void Physics::setAccelX(float acc){
	m_acc.x = acc;
}

void Physics::setAccelY(float acc){
	m_acc.y = acc;
}

void Physics::setVelocity(float x, float y){
	m_vel = Vector(x, y, 0);
}

void Physics::setVelocityX(float vel){
	m_vel.x = vel;
}

void Physics::setVelocityY(float vel){
	m_vel.y = vel;
}

void Physics::setWind(float power){
	m_wind = power;
}

void Physics::isGrounded(bool grounded){
	m_grounded = grounded;
}

bool Physics::isGrounded(){
	return m_grounded;
}

void Physics::update(){
	if (!m_grounded){
		m_vel.x += m_acc.x;
		m_vel.y += m_acc.y;

		m_acc.y += GRAVITY;
		m_acc.x -= m_wind;

		if (m_vel.y < TERMINAL_VELOCITY){
			m_vel.y = TERMINAL_VELOCITY;
		}

		m_pos->x += m_vel.x * TimeControl::getInstance().getDeltaTime();
		m_pos->y += m_vel.y * TimeControl::getInstance().getDeltaTime();
	}else{
		m_vel.x += m_acc.x;
		m_vel.y = 0;

		m_pos->x += m_vel.x * TimeControl::getInstance().getDeltaTime();
	}
}

Vector Physics::nextPos(){
	Vector tempPos = *m_pos, tempVel = m_vel, tempAcc = m_acc;

	if (!m_grounded){
		tempVel.x += tempAcc.x;
		tempVel.y += tempAcc.y;

		if (tempVel.y < TERMINAL_VELOCITY){
			tempVel.y = TERMINAL_VELOCITY;
		}

		tempPos.x += tempVel.x * TimeControl::getInstance().getDeltaTime();
		tempPos.y += tempVel.y * TimeControl::getInstance().getDeltaTime();
	}
	else{
		tempVel.x += tempAcc.x;
		tempVel.y = 0;

		tempPos.x += tempVel.x * TimeControl::getInstance().getDeltaTime();
	}

	return tempPos;
}