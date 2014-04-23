#pragma once
#include "vector.h"

class Collider{
	Vector m_pos, m_rot;
	int m_id;
public:
	Collider();
	Collider(float x, float y, float z);
	~Collider();

	Vector getPos();
	Vector getRotation();

	int getID();

	void setPos(Vector pos);
	void setPos(float x, float y, float z);

	void setRot(Vector rot);
	void setRot(float x, float y, float z);
	
	void setID(int id);

	//Returns true if collision occured
	virtual bool checkCollision(Collider* col) = 0;
	virtual bool checkCollision(Vector pos) = 0;
};

