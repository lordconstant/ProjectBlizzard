#include "Physics.h"


Physics::Physics(Vector& pos){
	m_pos = &pos;
	m_vel = m_acc = Vector(0, 0, 0);
	m_grounded = false;
	m_wind = 0;
	m_slowed = true;
}


Physics::~Physics(){
}

float Physics::getAccelX(){
	return m_acc.x;
}

float Physics::getAccelY(){
	return m_acc.y;
}

float Physics::getVelX(){
	return m_vel.x;
}

float Physics::getVelY(){
	return m_vel.y;
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

void Physics::slowDown(){
	//if (!m_slowed){
		m_slowed = true;
		setVelocity(m_vel.x, m_vel.y);
		setAccel(m_acc.x, m_acc.y);
	//}
}

void Physics::update(){
	if (!m_grounded){
		m_vel.x += m_acc.x * TimeControl::getInstance().getDeltaTime();;
		m_vel.y += m_acc.y * TimeControl::getInstance().getDeltaTime();;

		m_acc.y += GRAVITY * TimeControl::getInstance().getDeltaTime();
		m_acc.x -= m_wind * TimeControl::getInstance().getDeltaTime();

		if (m_vel.y < TERMINAL_VELOCITY){
			m_vel.y = TERMINAL_VELOCITY;
		}

		m_pos->x += m_vel.x * TimeControl::getInstance().getDeltaTime();
		m_pos->y += m_vel.y * TimeControl::getInstance().getDeltaTime();
	}else{
		m_slowed = false;

		m_vel.x += m_acc.x * TimeControl::getInstance().getDeltaTime();

		if (m_vel.x < 0 && m_acc.x == 0){
			m_vel.x += DRAG * TimeControl::getInstance().getDeltaTime();
			if (m_vel.x > 0){
				m_vel.x = 0;
			}
		}

		if (m_vel.x > 0 && m_acc.x == 0){
			m_vel.x -= DRAG * TimeControl::getInstance().getDeltaTime();

			if (m_vel.x < 0){
				m_vel.x = 0;
			}
		}

		m_vel.y = 0;
		m_acc.y = 0;

		m_pos->x += m_vel.x * TimeControl::getInstance().getDeltaTime();
	}
}

Vector Physics::nextPos(){
	Vector tempPos = *m_pos, tempVel = m_vel, tempAcc = m_acc;
	Vector orgPos = *m_pos;
	if (!m_grounded){
		tempVel.x += tempAcc.x * TimeControl::getInstance().getDeltaTime();
		tempVel.y += tempAcc.y * TimeControl::getInstance().getDeltaTime();

		if (tempVel.y < TERMINAL_VELOCITY){
			tempVel.y = TERMINAL_VELOCITY;
		}

		tempPos.x += tempVel.x * TimeControl::getInstance().getDeltaTime();
		tempPos.y += tempVel.y * TimeControl::getInstance().getDeltaTime();
	}
	else{
		tempVel.x += tempAcc.x * TimeControl::getInstance().getDeltaTime();
		tempVel.y = 0;

		if (tempVel.x < 0 && tempAcc.x == 0){
			tempVel.x += DRAG * TimeControl::getInstance().getDeltaTime();
			if (tempVel.x > 0){
				tempVel.x = 0;
			}
		}

		if (tempVel.x > 0 && tempAcc.x == 0){
			tempVel.x -= DRAG * TimeControl::getInstance().getDeltaTime();

			if (tempVel.x < 0){
				tempVel.x = 0;
			}
		}

		tempPos.x += tempVel.x * TimeControl::getInstance().getDeltaTime();
	}

	*m_pos = orgPos;

	return tempPos;
}