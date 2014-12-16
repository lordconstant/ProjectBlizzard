#pragma once
#include <windows.h>
#include <glew.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "vector.h"
#include "LoadTextures.h"
#include "BoxCollider.h"

class Model{
	Vector m_pos, m_color;
	float m_scale, m_width, m_height, m_length;
	BoxCollider m_collider;
	GLuint m_VAO, m_buffers[2];

public:
	Model();
	Model(float scale);

	virtual ~Model();

	Vector getPos();
	Vector getColor();

	float getScale();
	float getWidth();
	float getHeight();
	float getLength();

	GLuint getVAO();
	GLuint* getBuffer();

	BoxCollider getCollider();

	void setScale(float scale);
	void setDimensions(float width, float height, float length);
	void setPos(Vector pos);
	void setPos(float x, float y, float z);
	void setColor(float r, float g, float b);
	void setVAO(GLuint vao);
	void setBuffer(GLuint* buffers);

	virtual void Render();
};

