#pragma once
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "vector.h"
#include "LoadTextures.h"

class Model{
	Vector m_pos;
	float m_scale;
public:
	Model();
	Model(float scale);

	~Model();

	Vector getPos();
	float getScale();

	void setScale(float scale);
	void setPos(Vector pos);
	void setPos(float x, float y, float z);

	virtual void Render();
};

