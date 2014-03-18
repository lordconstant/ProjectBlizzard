#include "GUI.h"


GUI::GUI(void){
	m_texture = 0;
	m_width = 1.0f;
	m_height = 0.25f;
	m_pos = m_rot = Vector(0, 0, 0);
}

GUI::GUI(float width, float height){
	m_texture = 0;
	m_width = width;
	m_height = height;
	m_pos = m_rot = Vector(0, 0, 0);
}

GUI::GUI(float width, float height, char* texName){
	LoadTextures* m_loader = new LoadTextures(texName);

	m_texture = m_loader->getTexture();

	m_width = width;
	m_height = height;
	m_pos = m_rot = Vector(0, 0, 0);

	delete m_loader;
}

GUI::~GUI(void){
}

void GUI::loadTexture(char* texName){
	LoadTextures* m_loader = new LoadTextures(texName);
	
	if(!m_loader->getStatus()){
		delete m_loader;

		return;
	}

	if(m_texture != 0){
		glDeleteTextures(1, &m_texture);
		m_texture = 0;
	}

	m_texture = m_loader->getTexture();
}

void GUI::drawFace(){
	if(m_texture > 0){
		glBindTexture(GL_TEXTURE_2D, m_texture);
	}

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(m_verts[0].x, m_verts[0].y, m_verts[0].z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(m_verts[1].x, m_verts[1].y, m_verts[1].z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(m_verts[2].x, m_verts[2].y, m_verts[2].z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(m_verts[3].x, m_verts[3].y, m_verts[3].z);
	glEnd();
}

void GUI::setSize(){
	m_verts[0] = Vector(0, 0, 0);
	m_verts[1] = Vector(m_width, 0, 0);
	m_verts[2] = Vector(m_width, m_height, 0);
	m_verts[3] = Vector(0, m_height, 0);
}