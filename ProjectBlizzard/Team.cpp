#include "Team.h"


Team::Team(void){
}


Team::~Team(void){
}

int Team::getMaxHealth(){
	return m_maxHealth;
}

int Team::getCurHealth(){
	return m_curHealth;
}

int Team::getID(){
	return m_ID;
}

int Team::getSize(){
	return m_size;
}

string Team::getName(){
	return m_name;
}

Unit* Team::getUnit(int unitNum){
	if (unitNum < 0 || unitNum > m_size){
		return NULL;
	}

	return m_units[unitNum];
}

//Weapon* Team::getWeapon(int wepNum){
//	if (wepNum < 0 || wepNum > m_size){
//		return NULL;
//	}
//
//	return m_weapons[wepNum];
//}

void Team::updateMaxHealth(){
	m_maxHealth = 0;

	for (int i = 0; i < m_units.size(); i++){
		m_maxHealth += m_units[i]->getMaxHealth();
	}
}

void Team::updateCurHealth(){
	m_curHealth = 0;
	for (int i = 0; i < m_units.size(); i++){
		m_curHealth += m_units[i]->getCurHealth();
	}
}

void Team::setID(int ID){
	if (ID < 0){
		return;
	}

	m_ID = ID;
}

void Team::setSize(int size){
	if (size == m_units.size() || size <= 0){
		return;
	}

	while (size > m_units.size()){
		if (m_units.size() == 0){
			addUnit(new Unit());
		}else{
			addUnit(*m_units.end());
		}
	}

	while (size < m_units.size()){
		m_units.pop_back();
	}
}

void Team::setName(string name){
	m_name = name;
}

void Team::addUnit(Unit* unit){
	if (!unit){
		return;
	}

	Unit* temp;
	temp = new Unit();
	*temp = *unit;

	m_units.push_back(temp);
}