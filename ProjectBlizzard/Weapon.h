#pragma once
#include <iostream>
#include <string.h>
#include "vector.h"

using namespace std;

class Weapon{
	//Model* m_model;
	int m_damage, m_amount;
	float m_power;
	string m_name;
	bool m_infinite;
	Vector m_pos;
public:
	Weapon();
	~Weapon();

	int getDamage();
	int getAmountWeps();

	float getPower();

	string getName();

	bool isInfinite();
	bool hasModel();

	Vector getPos();

	void setDamage(int dmg);
	void setAmountWeps(int amount);

	void setPower(float power);
	
	void setName(string name);

	void isInfinite(bool infinite);

	//void setModel(Model* model);

	void setPos(Vector pos);
	void setPos(float x, float y, float z);
	
	bool useWeapon();

private:

	void reduceAmount();
};

