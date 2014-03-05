#include "Unit.h"


Unit::Unit(void){
	m_maxHealth = m_curHealth = 100;
	m_speed = 2;
	m_name = "Unit";
	//m_model = NULL;
	m_wep = NULL;
	Vector temp;
	temp.x = temp.y = temp.z = 0;
	m_wepPos = m_modelPos = temp;
	m_move = new Movement(m_pos, m_angle, 5, 5, 5);
}


Unit::~Unit(void){
	/*if (m_model){
		delete m_model;
		m_model = NULL;
	}*/

	if (m_wep){
		delete m_wep;
		m_wep = NULL;
	}
}

int Unit::getMaxHealth(){
	return m_maxHealth;
}

int Unit::getCurHealth(){
	return m_curHealth;
}

int Unit::getMass(){
	return m_mass;
}

float Unit::getSpeed(){
	return m_speed;
}

string Unit::getName(){
	return m_name;
}

Weapon* Unit::getWeapon(){
	return m_wep;
}

Movement* Unit::move(){
	return m_move;
}

Vector Unit::getPosition(){
	return m_move->getPos();
}


void Unit::setMaxHealth(int hp){
	if (hp < 1){
		return;
	}

	m_maxHealth = hp;
}

void Unit::setCurHealth(int hp){
	if (hp < 0 || hp > m_maxHealth){
		return;
	}

	m_curHealth = hp;
}

void Unit::resetHealth(){
	m_curHealth = m_maxHealth;
}

void Unit::setMass(int mass){
	if (mass < 1){
		return;
	}

	m_mass = mass;
}

void Unit::setSpeed(float speed){
	if (speed < 0){
		return;
	}

	m_speed = speed;
}

void Unit::setName(string name){
	m_name = name;
}

//void Unit::setModel(Model* model){
//	if (!model){
//		return;
//	}
//
//	if (m_model){
//		delete m_model;
//		m_model = NULL;
//	}
//
//	m_model = new Model();
//	*m_model = *model;
//}

void Unit::setWeapon(Weapon* wep){
	if (!wep){
		return;
	}

	if (m_wep){
		delete m_wep;
		m_wep = NULL;
	}

	m_wep = new Weapon;
	*m_wep = *wep;
}

void Unit::setPosition(Vector pos){
	m_move->setPos(pos);
	//if (m_model){
//		setModelPos(pos + m_modelPos);
	//}

	if (m_wep){
		setWepPos(pos + m_wepPos);
	}
}

void Unit::setModelPos(Vector pos){
	/*m_model->setPos(m_move->getPos() + pos);
	m_modelPos = pos;*/
}

void Unit::setWepPos(Vector pos){
	m_wep->setPos(m_move->getPos() + pos);
	m_wepPos = pos;
}

void Unit::setPosition(float x, float y, float z){
	Vector temp;
	temp.x = x;
	temp.y = y;
	temp.z = z;

	setPosition(temp);
}

void Unit::setModelPos(float x, float y, float z){
	Vector temp;
	temp.x = x;
	temp.y = y;
	temp.z = z;

	setModelPos(temp);
}

void Unit::setWepPos(float x, float y, float z){
	Vector temp;
	temp.x = x;
	temp.y = y;
	temp.z = z;

	setWepPos(temp);
}

//bool Unit::hasModel(){
//	if (m_model){
//		return true;
//	}
//
//	return false;
//}

bool Unit::fireWeapon(){
	if (!m_wep){
		return false;
	}

	m_wep->useWeapon();

	return true;
}