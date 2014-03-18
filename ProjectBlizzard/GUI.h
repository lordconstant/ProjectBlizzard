#pragma once
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "vector.h"
#include "LoadTextures.h"

class GUI{
	float m_width, m_height;
	Vector m_verts[4], m_pos, m_rot;
	unsigned int m_texture;
public:
	GUI(void);
	GUI(float width, float height);
	GUI(float width, float height, char* texName);
	~GUI(void);

	virtual void render() = 0;
	void loadTexture(char* texName);
	
protected:
	void setSize();
	void drawFace();
};

