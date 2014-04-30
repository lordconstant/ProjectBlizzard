#pragma once
#include <string>
#include "Weapon.h"
#include "Movement.h"
#include "vector.h"
#include "Cube.h"
#include "DebugPrint.h"
#include "Physics.h"

using namespace std;

const int JUMP_POWER = 1;

class Unit{
	int m_maxHealth, m_curHealth;
	float m_speed;
	string m_name;
	Model* m_model;
	Weapon* m_wep;
	Vector m_pos, m_angle, m_wepPos, m_modelPos;
	Movement* m_move;
	bool m_dead;
	Physics* m_phys;
public:
	Unit(void);
	Unit(string name, Model* model, int health, float speed);
	~Unit(void);

	int getMaxHealth();
	int getCurHealth();

	float getSpeed();

	string getName();

	Weapon* getWeapon();

	Movement* move();
	Physics* getPhysics();

	Vector getPosition();

	Model* getModel();

	void setMaxHealth(int hp);
	void setCurHealth(int hp);
	void resetHealth();

	void setSpeed(float speed);

	void setName(string name);

	void setModel(Model* model);

	void setWeapon(Weapon* wep);

	void setPosition(Vector pos);
	void setModelPos(Vector pos);
	void setWepPos(Vector pos);
	void setColor(float r, float g, float b);

	void setPosition(float x, float y, float z);
	void setModelPos(float x, float y, float z);
	void setWepPos(float x, float y, float z);

	bool hasModel();
	bool fireWeapon();
	bool isDead();

	void update(Vector mouse);

	void jump();

	void render();

	void renderHealthBar();
};

