#pragma once
#include "model.h"

enum { LEFT_FACE = 0, RIGHT_FACE, TOP_FACE, BOTTOM_FACE, FRONT_FACE, BACK_FACE };

class Rect :public Model{
	float m_size, m_width, m_height, m_length;
	Vector m_verts[8];
	unsigned int m_texture[6];

public:
	Rect();
	Rect(float size, float width, float height, float length);
	~Rect(void);

	void Render();

	bool setTexture(char* img);
	bool setFaceTexture(char* img, int face);

	float getWidth();
	float getHeight();
	float getLength();
private:
	//Renders a face
	void drawFace(int v0, int v1, int v2, int v3, float r, float g, float b, int textNum);

	//Modifies the size
	void setSize(float size);
};

