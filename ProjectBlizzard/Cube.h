#pragma once

#include "Model.h"

class Cube: public Model{
	float m_size;

	Vector m_verts[8];
public:
	Cube(void);

	Cube(float size);

	~Cube(void);

	void Render();
private:
	//Renders a face
	void drawFace(int v0, int v1, int v2, int v3, float r, float g, float b);

	//Modifies the size
	void setSize(float size);
};
