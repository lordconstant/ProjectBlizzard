#include "Cube.h"

Cube::Cube(void) :Model(0.2f){
	setColor(1.0f, 1.0f, 1.0f);
	setSize(0.2f);
	createVAO();
	setDimensions(0.2f, 0.2f, 0.2f);
}

Cube::Cube(float scale) :Model(scale){
	setColor(1.0f, 1.0f, 1.0f);
	setSize(scale);
	createVAO();
	setDimensions(scale, scale, scale);
}

Cube::Cube(float scale, float r, float g, float b) :Model(scale){
	setColor(r, g, b);
	setSize(scale);
	createVAO();
	setDimensions(scale, scale, scale);
}

Cube::~Cube(void){
}

void Cube::Render(){
	if (m_scale != getScale()){
		setSize(getScale());
	}
		glBindVertexArray(getVAO());
		glEnable(GL_CULL_FACE);

		glPushMatrix();

			glColor3f(getColor().x, getColor().y, getColor().z);
			glTranslatef(getPos().x, getPos().y, getPos().z);

			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, m_indices);

		glPopMatrix();

	glDisable(GL_CULL_FACE);
	glBindVertexArray(0);
}

void Cube::setSize(float scale){
	m_scale = scale;

	setDimensions(1, 1, 1);

	float w = (getWidth() / 2) * scale;
	float h = (getHeight() / 2) * scale;
	float l = (getLength() / 2) * scale;

	m_VBVerts[0] = -w; m_VBVerts[1] = h; m_VBVerts[2] = l;
	m_VBVerts[3] = w; m_VBVerts[4] = h; m_VBVerts[5] = l;
	m_VBVerts[6] = w; m_VBVerts[7] = h; m_VBVerts[8] = -l;
	m_VBVerts[9] = -w; m_VBVerts[10] = h; m_VBVerts[11] = -l;
	m_VBVerts[12] = -w; m_VBVerts[13] = -h; m_VBVerts[14] = l;
	m_VBVerts[15] = w; m_VBVerts[16] = -h; m_VBVerts[17] = l;
	m_VBVerts[18] = w; m_VBVerts[19] = -h; m_VBVerts[20] = -l;
	m_VBVerts[21] = -w; m_VBVerts[22] = -h; m_VBVerts[23] = -l;

	unsigned int temp[] = { 0, 4, 5, 1, 3, 7, 4, 0,
					   2, 6, 7, 3, 1, 5, 6, 2,
					   3, 0, 1, 2, 4, 7, 6, 5};


	memcpy(m_indices, temp, sizeof(int) * 24);
}

float* Cube::getVertArr(){
	return m_VBVerts;
}

unsigned int* Cube::getIndicesArr(){
	return m_indices;
}


void Cube::createVAO(){
	GLuint vao, buffers[2];

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(2, buffers);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_VBVerts[0]) * 24, m_VBVerts, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_indices[0]) * 24, m_indices, GL_STATIC_DRAW);

	glBindVertexArray(0);

	setVAO(vao);
	setBuffer(buffers);
}