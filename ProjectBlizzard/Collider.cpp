#include "Collider.h"


Collider::Collider(){
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

int Collider::getID(){
	return m_id;
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

void Collider::setID(int id){
	m_id = id;
}