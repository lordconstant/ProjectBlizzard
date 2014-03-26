#pragma once
#include <string>
#include "Weapon.h"
#include "Movement.h"
#include "vector.h"

using namespace std;

class Unit{
	int m_maxHealth, m_curHealth, m_mass;
	float m_speed;
	string m_name;
	//Model* m_model;
	Weapon* m_wep;
	Vector m_pos, m_angle, m_wepPos, m_modelPos;
	Movement* m_move;
public:
	Unit(void);
	//Unit(string name, Model* model, int health, float speed, int mass);
	~Unit(void);

	int getMaxHealth();
	int getCurHealth();
	int getMass();

	float getSpeed();

	string getName();

	Weapon* getWeapon();

	Movement* move();

	Vector getPosition();

	void setMaxHealth(int hp);
	void setCurHealth(int hp);
	void resetHealth();

	void setMass(int mass);

	void setSpeed(float speed);

	void setName(string name);

	//void setModel(Model* model);

	void setWeapon(Weapon* wep);

	void setPosition(Vector pos);
	void setModelPos(Vector pos);
	void setWepPos(Vector pos);

	void setPosition(float x, float y, float z);
	void setModelPos(float x, float y, float z);
	void setWepPos(float x, float y, float z);

	bool hasModel();
	bool fireWeapon();

	void update();
};

