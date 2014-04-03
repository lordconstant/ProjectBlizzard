#pragma once
#include "Model.h"
#include "Cube.h"
#include "Physics.h"

class Projectile{
	Model* m_model;
	Physics* m_phys;
	Vector m_pos;
public:
	Projectile();
	Projectile(Model* model);
	~Projectile();

	void setPos(Vector pos);
	void setModel(Model* model);
	void setVel(float velX, float velY);
	void setVelX(float velX);
	void setVelY(float velY);
	void setAccel(float accX, float accY);
	void setAccelX(float acc);
	void setAccelY(float acc);

	Model* getModel();
	float getVelX();
	float getVelY();

	void update(float wind);

	Vector nextPos();
};

