#include "Weapon.h"


Weapon::Weapon(){

}


Weapon::~Weapon(){
}

int Weapon::getDamage(){
	return m_damage;
}

int Weapon::getAmountWeps(){
	return m_amount;
}

float Weapon::getPower(){
	return m_power;
}

string Weapon::getName(){
	return m_name;
}

bool Weapon::isInfinite(){
	return m_infinite;
}

bool Weapon::hasModel(){
	/*if (m_model){
		return true;
	}*/

	return false;
}

Vector Weapon::getPos(){
	return m_pos;
}

void Weapon::setDamage(int dmg){
	if (dmg < 0){
		return;
	}

	m_damage = dmg;
}

void Weapon::setAmountWeps(int amount){
	if (amount < 0){
		return;
	}

	m_amount = amount;
}

void Weapon::setPower(float power){
	if (power < 0){
		return;
	}

	m_power = power;
}

void Weapon::setName(string name){
	m_name = name;
}

void Weapon::isInfinite(bool infinite){
	m_infinite = infinite;
}

//void Weapon::setModel(Model* model){
	//if (!model){
	//	return;
	//}

	//if (m_model){
	//	delete m_model;
	//	m_model = NULL;
	//}

	//m_model = new Model();

	//*m_model = *model;
//} 

void Weapon::setPos(Vector pos){
	m_pos = pos;
}

void Weapon::setPos(float x, float y, float z){
	Vector temp;
	temp.x = x;
	temp.y = y;
	temp.z = z;
	setPos(temp);
}

bool Weapon::useWeapon(){
	return false;
}

void Weapon::reduceAmount(){
	if (m_infinite || m_amount <= 0){
		return;
	}

	m_amount--;
}