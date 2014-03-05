#pragma once
#include "Model.h"

enum{BLOCKY = 10, SMOOTH = 20, VERYSMOOTH = 30};

class Sphere :public Model{
	GLUquadricObj* m_sphere;
public:
	Sphere();
	Sphere(float radius);
	~Sphere();

	void Render();
};

