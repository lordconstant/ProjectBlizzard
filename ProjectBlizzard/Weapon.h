#pragma once
#include <iostream>
#include <string.h>
#include "vector.h"
#include "Model.h"
#include "Cube.h"
#include "TimeControl.h"
#include "Projectile.h"

#define M_PI 3.1415926f

using namespace std;

class Weapon{
	Model *m_model, *m_ammo;
	Projectile* m_curShot;
	int m_damage, m_amount;
	float m_power;
	string m_name;
	bool m_infinite, m_hit;
	Vector m_pos, m_direction, m_shotDir;
public:
	Weapon();
	Weapon(string name, Model* model, Model* ammo, int damage, int amount);
	~Weapon();

	int getDamage();
	int getAmountWeps();

	float getPower();

	string getName();

	bool isInfinite();
	bool hasModel();

	Vector getPos();

	Projectile* getCurShot();

	void setDamage(int dmg);
	void setAmountWeps(int amount);

	void setPower(float power);
	
	void setName(string name);

	void isInfinite(bool infinite);

	void setModel(Model* model);

	void setPos(Vector pos);
	void setPos(float x, float y, float z);
	void setColor(float r, float g, float b);

	bool useWeapon();

	bool hitObject(Vector pos, float width, float height);
	bool checkAhead(Vector pos, float width, float height);

	void render();
	void update(Vector mouse);
	void updatePower();
private:

	void reduceAmount();
};

