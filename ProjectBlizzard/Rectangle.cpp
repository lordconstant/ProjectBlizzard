#include "Rectangle.h"


Rect::Rect(void){
}

Rect::Rect(float size, float width, float height, float length){
	m_width = width;
	m_height = height;
	m_length = length;

	setSize(size);

	for (int i = 0; i < 6; i++){
		m_texture[i] = 0;
	}

	m_textured = false;
}

Rect::~Rect(void)
{
}

void Rect::Render(){
	if (m_size != getScale()){
		setSize(getScale());
	}

	glPushMatrix();
		if(m_textured){
			glEnable(GL_TEXTURE_2D);
		}

		// Perform transformations here in TRS order
		glTranslatef(getPos().x, getPos().y, getPos().z);
		//Draw each face with a different colour
		drawFace(0, 4, 5, 1, 1.0f, 1.0f, 1.0f, 0);
		drawFace(3, 7, 4, 0, 1.0f, 1.0f, 1.0f, 1);
		drawFace(2, 6, 7, 3, 1.0f, 1.0f, 1.0f, 2);
		drawFace(1, 5, 6, 2, 1.0f, 1.0f, 1.0f, 3);
		drawFace(3, 0, 1, 2, 0.0f, 1.0f, 1.0f, 4);
		drawFace(4, 7, 6, 5, 1.0f, 1.0f, 1.0f, 5);

		if(m_textured){
			glDisable(GL_TEXTURE_2D);
		}
	glPopMatrix();
}

void Rect::drawFace(int v0, int v1, int v2, int v3, float r, float g, float b, int textNum){
	if (textNum >= 0 && textNum <= 5 && m_textured){
		glBindTexture(GL_TEXTURE_2D, m_texture[textNum]);
	}

	glColor3f(r, g, b);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(m_verts[v0].x, m_verts[v0].y, m_verts[v0].z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(m_verts[v1].x, m_verts[v1].y, m_verts[v1].z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(m_verts[v2].x, m_verts[v2].y, m_verts[v2].z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(m_verts[v3].x, m_verts[v3].y, m_verts[v3].z);
	glEnd();
}

void Rect::setSize(float size){
	m_size = size;
	float hs = size / 2;
	m_verts[0].set(-hs*m_width, hs*m_height, hs*m_length);
	m_verts[1].set(hs*m_width, hs*m_height, hs*m_length);
	m_verts[2].set(hs*m_width, hs*m_height, -hs*m_length);
	m_verts[3].set(-hs*m_width, hs*m_height, -hs*m_length);
	m_verts[4].set(-hs*m_width, -hs*m_height, hs*m_length);
	m_verts[5].set(hs*m_width, -hs*m_height, hs*m_length);
	m_verts[6].set(hs*m_width, -hs*m_height, -hs*m_length);
	m_verts[7].set(-hs*m_width, -hs*m_height, -hs*m_length);
}

bool Rect::setTexture(char* img){
	return setFaceTexture(img, -1);
}

bool Rect::setFaceTexture(char* img, int face){
	if (face >= 6){
		return false;
	}

	LoadTextures* lt = new LoadTextures(img);

	if (!lt){
		return false;
	}

	if (face <= -1){
		for (int i = 0; i < 6; i++){
			if (m_texture[i] > 0){
				glDeleteTextures(1, &m_texture[face]);
				m_texture[i] = 0;
			}

			m_texture[i] = lt->getTexture();
		}

		delete lt;
		lt = NULL;

		m_textured = true;

		return true;
	}

	if (m_texture[face] > 0){
		glDeleteTextures(1, &m_texture[face]);
		m_texture[face] = 0;
	}

	m_texture[face] = lt->getTexture();

	m_textured = true;

	delete lt;
	lt = NULL;

	return true;
}

float Rect::getWidth(){
	return m_width;
}

float Rect::getHeight(){
	return m_height;
}

float Rect::getLength(){
	return m_length;
}