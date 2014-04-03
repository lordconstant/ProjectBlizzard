#include "Button3D.h"


Button3D::Button3D(char* img, float width, float height, float length){
	char s[255];
	sprintf(s, "Images/Buttons/%s.bmp", img);
	m_rect = new Rect(1, width, height, length);

	m_img = img;

	m_rect->setTexture(s);
}


Button3D::~Button3D(){
}

void Button3D::render(){
	m_rect->Render();
}

void Button3D::update(float mouseX, float mouseY){
	if(checkArea(mouseX, mouseY)){
		if (!m_hover){
			m_hover = true;

			m_rect->setPos(m_rect->getPos().x, m_rect->getPos().y, m_rect->getPos().z-0.05);
			DebugOut("mousedOver");
			char s[255];
			sprintf(s, "Images/Buttons/%s_hover.bmp", m_img);
			m_rect->setFaceTexture(s, LEFT_FACE);
		}
		return;
	}

	if (m_hover){
		char a[255];
		sprintf(a, "Images/Buttons/%s.bmp", m_img);
		m_rect->setFaceTexture(a, LEFT_FACE);
		m_rect->setPos(m_rect->getPos().x, m_rect->getPos().y, m_rect->getPos().z+0.05);
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

bool Button3D::checkArea(float mouseX, float mouseY){
	if (mouseX > m_rect->getPos().x - m_rect->getWidth() / 2 && mouseX < m_rect->getPos().x + m_rect->getWidth() / 2){
		if (mouseY > m_rect->getPos().y - m_rect->getHeight() / 2 && mouseY < m_rect->getPos().y + m_rect->getHeight() / 2){
			return true;
		}
	}

	return false;
}