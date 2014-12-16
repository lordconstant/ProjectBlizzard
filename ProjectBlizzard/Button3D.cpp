#include "Button3D.h"


Button3D::Button3D(char* img, float width, float height, float length){
	char s[255];
	sprintf_s(s, "Images/Buttons/%s.bmp", img);
	m_cuboid = new Cuboid(1, width, height, length);

	sprintf_s(m_img, "%s", img);

	m_cuboid->setTexture(s);
}


Button3D::~Button3D(){
	if (m_cuboid){
		delete m_cuboid;
	}
}

void Button3D::render(){
	m_cuboid->Render();
}

void Button3D::update(float mouseX, float mouseY){
	if(checkArea(mouseX, mouseY)){
		if (!m_hover){
			m_hover = true;

			m_cuboid->setPos(m_cuboid->getPos().x, m_cuboid->getPos().y, m_cuboid->getPos().z - 0.05);
			char s[255];
			sprintf_s(s, "Images/Buttons/%s_hover.bmp", m_img);
			m_cuboid->setFaceTexture(s, FRONT_FACE);
		}
		return;
	}

	if (m_hover){
		char a[255];
		sprintf_s(a, "Images/Buttons/%s.bmp", m_img);
		m_cuboid->setFaceTexture(a, FRONT_FACE);
		m_cuboid->setPos(m_cuboid->getPos().x, m_cuboid->getPos().y, m_cuboid->getPos().z + 0.05);
	}

	m_hover = false;
}

Cuboid* Button3D::getCuboid(){
	return m_cuboid;
}

bool Button3D::isMouseOver(){
	return m_hover;
}

bool Button3D::checkArea(float mouseX, float mouseY){
	if (mouseX > m_cuboid->getPos().x - m_cuboid->getWidth() / 2 && mouseX < m_cuboid->getPos().x + m_cuboid->getWidth() / 2){
		if (mouseY > m_cuboid->getPos().y - m_cuboid->getHeight() / 2 && mouseY < m_cuboid->getPos().y + m_cuboid->getHeight() / 2){
			return true;
		}
	}

	return false;
}