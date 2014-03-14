#include "Camera.h"


Camera::Camera(){
	m_pos.x = m_pos.y = m_pos.z = 0;
	m_move = new Movement(m_pos, m_angle, 2.0f, 2.0f, 2.0f);
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

	gluLookAt(m_pos.x, m_pos.y, m_pos.z+3, m_pos.x-m_rot.x, m_pos.y+m_rot.y, m_pos.z+m_rot.z, 0.0f, 1.0f, 0.0f);

	//m_move->forward(false);
	//m_move->backward(false);
}

void Camera::firstPerson(int rad, float mouseX, float mouseY, float sHeight, float sWidth){
	// Map the mouse position to two angles
	float angNS, angEW;
	angNS = ((mouseY + 1) / sHeight) * (float)M_PI;
	angEW = (mouseX / sWidth) * 2 * (float)M_PI;
	// Calculate the sines and cosines of these angle
	float sinNS = sin(angNS);
	float cosNS = cos(angNS);
	float sinEW = sin(angEW);
	float cosEW = cos(angEW);
	// calculate the camera coordinate
	m_rot.z = rad * sinNS * cosEW;
	m_rot.y = rad * cosNS;
	m_rot.x = rad * sinNS * sinEW;
}