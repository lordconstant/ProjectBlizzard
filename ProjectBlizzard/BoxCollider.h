#pragma once
#include "Collider.h"
#include "DebugPrint.h"
#include <gl\GLU.h>;
#include <gl\GL.h>

class BoxCollider :public Collider{
	float m_width, m_height, m_length;
public:
	BoxCollider();
	~BoxCollider();

	float getWidth();
	float getHeight();
	float getLength();

	void setDimension(float width, float height, float length);

	bool checkCollision(Collider* col);
	bool checkCollision(Vector pos);

	bool hitLeft(BoxCollider* col);
	bool hitright(BoxCollider* col);
	bool hitTop(BoxCollider* col);
	bool hitBottom(BoxCollider* col);

	void render();
};

