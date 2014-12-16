#pragma once

#include "Model.h"

class Cube: public Model{
	float m_VBVerts[24], m_scale;
	unsigned int m_indices[24];
public:

	Cube(void);
	Cube(float scale);
	Cube(float scale, float r, float g, float b);
	~Cube(void);

	void Render();

	float* getVertArr();
	unsigned int* getIndicesArr();

private:
	//Modifies the size
	void setSize(float scale);

	void createVAO();
};
