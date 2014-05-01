#pragma once
#include "Model.h"
#include "LoadTextures.h"

enum{BLOCKY = 20, SMOOTH = 30, VERYSMOOTH = 40};

class Sphere :public Model{
	GLUquadricObj* m_sphere;
	unsigned int m_texture;
public:
	Sphere();
	Sphere(float radius);
	~Sphere();

	void Render();
	void setTexture(char* image);
};

