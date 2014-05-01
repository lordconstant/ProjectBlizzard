#pragma once
#include <windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "vector.h"
#include "LoadTextures.h"

class Water{
	float m_width, m_length;
	Vector m_pos;
	unsigned int m_texture;
public:
	Water(char* image, float width, float length);
	~Water();

	float getWidth();
	float getLength();
	Vector getPos();

	void setPos(Vector pos);
	void render();
	void setTexture(char* image);
	void setWidth(float width);
	void setLength(float length);
};

