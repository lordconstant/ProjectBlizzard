#pragma once
#include "vector.h"

class Collider{
	Vector m_pos, m_rot;
public:
	Collider();
	Collider(float x, float y, float z);
	virtual ~Collider();

	Vector getPos();
	Vector getRotation();

	void setPos(Vector pos);
	void setPos(float x, float y, float z);

	void setRot(Vector rot);
	void setRot(float x, float y, float z);
};

