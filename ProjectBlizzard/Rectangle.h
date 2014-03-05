#pragma once
#include "model.h"

class Rect :public Model{
	float m_size, m_width, m_height, m_length;
	Vector m_verts[8];
public:
	Rect();
	Rect(float size, float width, float height, float length);
	~Rect(void);

	void Render();
private:
	//Renders a face
	void drawFace(int v0, int v1, int v2, int v3, float r, float g, float b);

	//Modifies the size
	void setSize(float size);
};

