#include "Scene.h"


Scene::Scene(){
}


Scene::~Scene(){
}

void Scene::mouseToWorldCoord(float x, float y){
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;
 
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );
 
    winX = x;
    winY = (float)viewport[3] - y;
    glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
 
    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
 
	m_mousePos = Vector(posX, posY, posZ);   
}

void Scene::updateMouse(float mouseX, float mouseY){
	m_mouseX = mouseX;
	m_mouseY = mouseY;

	mouseToWorldCoord(mouseX, mouseY);
}