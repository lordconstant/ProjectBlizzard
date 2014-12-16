#include "Sphere.h"


Sphere::Sphere():Model(0.2f){
	m_sphere = gluNewQuadric();
	gluQuadricDrawStyle(m_sphere, GLU_FILL);
	gluQuadricNormals(m_sphere, GLU_SMOOTH);
	m_texture = 0;
}

Sphere::Sphere(float radius):Model(radius){
	m_sphere = gluNewQuadric();
	gluQuadricDrawStyle(m_sphere, GLU_FILL);
	gluQuadricNormals(m_sphere, GLU_SMOOTH);
	m_texture = 0;
}

Sphere::~Sphere(){
	if (m_sphere){
		gluDeleteQuadric(m_sphere);
	}

	glDeleteTextures(1, &m_texture);
}

void Sphere::Render(){
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_texture);

		glTranslatef(getPos().x, getPos().y, getPos().z);
		glRotatef(-90.0f, 1.0f, 0.0f, 1.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		gluSphere(m_sphere, getScale(), VERYSMOOTH, VERYSMOOTH);
		gluQuadricTexture(m_sphere, true);

		glDisable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
}

void Sphere::setTexture(char* image){
	LoadTextures* lt = new LoadTextures(image);
	m_texture = lt->getTexture();
	delete lt;
}