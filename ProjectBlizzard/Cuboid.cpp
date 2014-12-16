#include "Cuboid.h"


Cuboid::Cuboid(void){
}

Cuboid::Cuboid(float scale, float width, float height, float length) : Model(scale){
	setDimensions(width, height, length);

	setSize(scale);

	for (int i = 0; i < 6; i++){
		m_texture[i] = 0;
	}

	m_textured = false;
}

Cuboid::~Cuboid(void){
	glDeleteTextures(6, m_texture);
}

void Cuboid::Render(){
	if (m_scale != getScale() || m_width != getWidth() || m_height != getHeight() || m_length != getLength()){
		setSize(getScale());
	}

	glEnable(GL_CULL_FACE);
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
	glDisable(GL_CULL_FACE);
}

void Cuboid::drawFace(int v0, int v1, int v2, int v3, float r, float g, float b, int textNum){
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

	glCullFace(GL_BACK);
}

void Cuboid::setSize(float scale){
	m_scale = scale;

	m_width = getWidth();
	m_height = getHeight();
	m_length = getLength();

	float w = (getWidth() / 2) * scale;
	float h = (getHeight() / 2) * scale;
	float l = (getLength() / 2) * scale;

	m_verts[0].set(-w, h, l);
	m_verts[1].set(w, h, l);
	m_verts[2].set(w, h, -l);
	m_verts[3].set(-w, h, -l);
	m_verts[4].set(-w, -h, l);
	m_verts[5].set(w, -h, l);
	m_verts[6].set(w, -h, -l);
	m_verts[7].set(-w, -h, -l);
}

bool Cuboid::setTexture(char* img){
	return setFaceTexture(img, -1);
}

bool Cuboid::setFaceTexture(char* img, int face){
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