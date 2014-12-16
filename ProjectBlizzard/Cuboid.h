#pragma once
#include "model.h"

enum { FRONT_FACE = 0, RIGHT_FACE, TOP_FACE, BOTTOM_FACE, LEFT_FACE, BACK_FACE };

class Cuboid: public Model{
	float m_scale, m_width, m_height, m_length;
	Vector m_verts[8];
	unsigned int m_texture[6];
	bool m_textured;
public:
	Cuboid();
	Cuboid(float scale, float width, float height, float length);
	~Cuboid(void);

	void Render();

	bool setTexture(char* img);
	bool setFaceTexture(char* img, int face);
private:
	//Renders a face
	void drawFace(int v0, int v1, int v2, int v3, float r, float g, float b, int textNum);

	//Modifies the size
	void setSize(float scale);
};

