#include "Camera.h"


Camera::Camera(){
	m_pos.x = m_pos.y = m_pos.z = 0;
	m_move = new Movement(m_pos, m_angle, 0.2, 0.2, 10);
	m_angle = 0;
}


Camera::~Camera(){
	delete m_move;
}

Vector Camera::getPos(){
	return m_pos;
}

float Camera::getAngle(){
	return m_angle;
}

Movement* Camera::move(){
	return m_move;
}

void Camera::update(){
	m_move->moveX();
	m_move->moveY();
	m_move->moveZ();

	gluLookAt(m_pos.x, m_pos.z + m_pos.y, m_pos.z + 2,m_pos.x,m_pos.z + m_pos.y, m_pos.z, 0.0f, 1.0f, 0.0f);

	m_move->forward(false);
	m_move->backward(false);
}