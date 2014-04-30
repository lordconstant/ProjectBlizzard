#include "Sphere.h"


Sphere::Sphere():Model(0.2f){
	m_sphere = gluNewQuadric();
}

Sphere::Sphere(float radius):Model(radius){
	m_sphere = gluNewQuadric();
}

Sphere::~Sphere(){
	if (m_sphere){
		gluDeleteQuadric(m_sphere);
	}
}

void Sphere::Render(){
	glPushMatrix();
		glTranslatef(getPos().x, getPos().y, getPos().z);
		glColor3f(1.0f, 1.0f, 1.0f);
		gluSphere(m_sphere, getScale(), SMOOTH, SMOOTH);
	glPopMatrix();
}