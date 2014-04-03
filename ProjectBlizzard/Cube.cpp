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
	//m_inc = 0;
		glEnable(GL_CULL_FACE);
		glPushMatrix();
			// Perform transformations here in TRS order
			glTranslatef(getPos().x, getPos().y, getPos().z);
			// Draw each face with a different colour
			drawFace(0, 4, 5, 1, 0.5f, 0.5f, 1.0f);
			drawFace(3, 7, 4, 0, 0.5f, 1.0f, 0.5f);
			drawFace(2, 6, 7, 3, 0.0f, 0.0f, 0.0f);
			drawFace(1, 5, 6, 2, 1.0f, 0.5f, 0.5f);
			drawFace(3, 0, 1, 2, 1.0f, 0.5f, 1.0f);
			drawFace(4, 7, 6, 5, 1.0f, 1.0f, 0.5f);
		glPopMatrix();
		glDisable(GL_CULL_FACE);
}

void Cube::drawFace(int v0, int v1, int v2, int v3, float r, float g, float b){
	glColor3f(r, g, b);
	glBegin(GL_QUADS);
		glVertex3f(m_verts[v0].x, m_verts[v0].y, m_verts[v0].z);
		glVertex3f(m_verts[v1].x, m_verts[v1].y, m_verts[v1].z);
		glVertex3f(m_verts[v2].x, m_verts[v2].y, m_verts[v2].z);
		glVertex3f(m_verts[v3].x, m_verts[v3].y, m_verts[v3].z);
	glEnd();

	/*m_VBVerts[m_inc] = m_verts[v0].x;
	m_VBVerts[m_inc + 1] = m_verts[v0].y;
	m_VBVerts[m_inc + 2] = m_verts[v0].z;

	m_VBVerts[m_inc + 3] = m_verts[v1].x;
	m_VBVerts[m_inc + 4] = m_verts[v1].y;
	m_VBVerts[m_inc + 5] = m_verts[v1].z;

	m_VBVerts[m_inc + 6] = m_verts[v2].x;
	m_VBVerts[m_inc + 7] = m_verts[v2].y;
	m_VBVerts[m_inc + 8] = m_verts[v2].z;

	m_VBVerts[m_inc + 9] = m_verts[v3].x;
	m_VBVerts[m_inc + 10] = m_verts[v3].y;
	m_VBVerts[m_inc + 11] = m_verts[v3].z;

	m_inc += 12;*/

	glCullFace(GL_BACK);
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

	int vertCount = 0;
	for (int i = 0; i < 8; i++){
		m_VBVerts[vertCount] = m_verts[i].x;
		m_VBVerts[vertCount+1] = m_verts[i].y;
		m_VBVerts[vertCount+2] = m_verts[i].z;

		vertCount += 3;
	}

	GLubyte temp[] = { 0, 4, 5, 1, 3, 7, 4, 0,
					   2, 6, 7, 3, 1, 5, 6, 2,
					   3, 0, 1, 2, 4, 7, 6, 5};

	float tempCol[] = { 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f };

	for (int i = 0; i < 24; i++){
		m_bytes[i] = temp[i];
		m_Colours[i] = tempCol[i];
	}
}