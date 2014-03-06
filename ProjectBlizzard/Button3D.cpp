#include "Button3D.h"


Button3D::Button3D(char* img, int width, int height, int length){
	m_rect = new Rect(1, width, height, length);

	m_rect->setTexture(img);
}


Button3D::~Button3D(){
}

void Button3D::render(){
	m_rect->Render();
}

void Button3D::update(float mouseX, float mouseY){
	mouseX /= 100;
	mouseY /= 100;
	char s[255];
	sprintf(s, "MouseX: %f", mouseX);
	DebugOut(s);
	sprintf(s, "MouseY: %f", mouseY);
	DebugOut(s);
	if (mouseX > m_rect->getPos().x && mouseX < m_rect->getPos().x + m_rect->getWidth()){
		if (mouseY > m_rect->getPos().y && mouseY < m_rect->getPos().y + m_rect->getHeight()){
			if (!m_hover){
				m_hover = true;

				m_rect->setPos(m_rect->getPos().x, m_rect->getPos().y, 0);
				DebugOut("mousedOver");
				//char s[255];
				//sprintf(s, "%c_hover", m_img);
				//m_rect->setFaceTexture(s, FRONT_FACE);
			}

			return;
		}
	}

	if (m_hover){
		//m_rect->setFaceTexture(m_img, FRONT_FACE);
		m_rect->setPos(m_rect->getPos().x, m_rect->getPos().y, 1);
		DebugOut("mousedOut");
	}

	m_hover = false;
}

Rect* Button3D::getRect(){
	return m_rect;
}

bool Button3D::isMouseOver(){
	return m_hover;
}