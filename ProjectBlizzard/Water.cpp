#include "Water.h"


Water::Water(char* image, float width, float length){
	m_width = width;
	m_length = length;

	setTexture(image);
}


Water::~Water(){
	glDeleteTextures(1, &m_texture);
}

float Water::getWidth(){
	return m_width;
}

float Water::getLength(){
	return m_length;
}

Vector Water::getPos(){
	return m_pos;
}

void Water::setPos(Vector pos){
	m_pos = pos;
}

void Water::render(){
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glTranslatef(m_pos.x, m_pos.y, m_pos.z);

		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);	glVertex3f(-(m_width / 2), 0.0f, -(m_length / 2));
			glTexCoord2f(0.0f, m_length);	glVertex3f(m_width / 2, 0.0f, -(m_length / 2));
			glTexCoord2f(m_width, m_length);	glVertex3f(m_width / 2, 0.0f, m_length / 2);
			glTexCoord2f(m_width, 0.0f);	glVertex3f(-(m_width / 2), 0.0f, m_length / 2);
		glEnd();

		glDisable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
}

void Water::setTexture(char* image){
	LoadTextures* lt = new LoadTextures(image);
	m_texture = lt->getTexture();
	delete lt;
}

void Water::setWidth(float width){
	m_width = width;
}

void Water::setLength(float length){
	m_length = length;
}