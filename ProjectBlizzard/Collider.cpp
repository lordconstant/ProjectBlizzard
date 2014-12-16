#include "Collider.h"


Collider::Collider(){
	m_rot = m_pos = Vector(0, 0, 0);
}

Collider::Collider(float x, float y, float z){
	setRot(x, y, z);
}

Collider::~Collider(){
}

Vector Collider::getPos(){
	return m_pos;
}

Vector Collider::getRotation(){
	return m_rot;
}

void Collider::setPos(Vector pos){
	m_pos = pos;
}

void Collider::setPos(float x, float y, float z){
	setPos(Vector(x, y, z));
}

void Collider::setRot(Vector rot){
	m_rot = rot;
}

void Collider::setRot(float x, float y, float z){
	setRot(Vector(x, y, z));
}