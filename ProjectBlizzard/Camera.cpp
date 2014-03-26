#include "Camera.h"


Camera::Camera(){
	m_pos.x = m_pos.y = m_pos.z = 0;
	m_move = new Movement(m_pos, m_angle, 2.0f, 2.0f, 4.0f);
}


Camera::~Camera(){
	delete m_move;
}

Vector Camera::getPos(){
	return m_pos;
}

Vector Camera::getAngle(){
	return m_angle;
}

Movement* Camera::move(){
	return m_move;
}

void Camera::update(){
	m_move->moveX();
	m_move->moveY();
	m_move->moveZ();

	gluLookAt(m_pos.x-degToRads(m_angle.x), m_pos.y+degToRads(m_angle.x), m_pos.z+3+degToRads(m_angle.x), m_pos.x, m_pos.y, m_pos.z, 0.0f, 1.0f, 0.0f);

	m_move->forward(false);
	m_move->backward(false);
}

float Camera::degToRads(float angle){
	return (angle*M_PI)/180;
}