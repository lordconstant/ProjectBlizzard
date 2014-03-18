#include "Cube.h"

Cube::Cube(void) :Model(0.2){
	setSize(0.2f);
}

Cube::Cube(float size):Model(size){
	setSize(size);
}

Cube::~Cube(void){
}

void Cube::Render(){
	if (m_size != getScale()){
		setSize(getScale());
	}

	glPushMatrix();
		// Perform transformations here in TRS order
		glTranslatef(getPos().x, getPos().y, getPos().z);
		// Draw each face with a different colour
		drawFace(0, 4, 5, 1, 0.5f, 0.5f, 1.0f);
		drawFace(3, 7, 4, 0, 0.5f, 1.0f, 0.5f);
		drawFace(2, 6, 7, 3, 0.5f, 1.0f, 1.0f);
		drawFace(1, 5, 6, 2, 1.0f, 0.5f, 0.5f);
		drawFace(3, 0, 1, 2, 1.0f, 0.5f, 1.0f);
		drawFace(4, 7, 6, 5, 1.0f, 1.0f, 0.5f);
	glPopMatrix();
}

void Cube::drawFace(int v0, int v1, int v2, int v3, float r, float g, float b){
	glColor3f(r, g, b);
	glBegin(GL_QUADS);
		glVertex3f(m_verts[v0].x, m_verts[v0].y, m_verts[v0].z);
		glVertex3f(m_verts[v1].x, m_verts[v1].y, m_verts[v1].z);
		glVertex3f(m_verts[v2].x, m_verts[v2].y, m_verts[v2].z);
		glVertex3f(m_verts[v3].x, m_verts[v3].y, m_verts[v3].z);
	glEnd();
}

void Cube::setSize(float size){
	m_size = size;
	float hs = size / 2;
	m_verts[0].set(-hs, hs, hs);
	m_verts[1].set(hs, hs, hs);
	m_verts[2].set(hs, hs, -hs);
	m_verts[3].set(-hs, hs, -hs);
	m_verts[4].set(-hs, -hs, hs);
	m_verts[5].set(hs, -hs, hs);
	m_verts[6].set(hs, -hs, -hs);
	m_verts[7].set(-hs, -hs, -hs);
}