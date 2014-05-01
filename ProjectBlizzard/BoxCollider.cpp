#include "BoxCollider.h"


BoxCollider::BoxCollider(){
}

BoxCollider::~BoxCollider(){
}

float BoxCollider::getWidth(){
	return m_width;
}

float BoxCollider::getHeight(){
	return m_height;
}

float BoxCollider::getLength(){
	return m_length;
}

void BoxCollider::setDimension(float width, float height, float length){
	m_width = width;
	m_height = height;
	m_length = length;
}

bool BoxCollider::checkCollision(Collider* col){
	Vector objAMin, objBMin, objAMax, objBMax;
	BoxCollider* bCol = (BoxCollider*)col;

	objAMin.x = this->getPos().x - m_width / 2;
	objAMax.x = this->getPos().x + m_width / 2;

	objBMin.x = bCol->getPos().x - bCol->getWidth() / 2;
	objBMax.x = bCol->getPos().x + bCol->getWidth() / 2;

	objAMin.y = this->getPos().y - m_height / 2;
	objAMax.y = this->getPos().y + m_height / 2;

	objBMin.y = bCol->getPos().y - bCol->getHeight() / 2;
	objBMax.y = bCol->getPos().y + bCol->getHeight() / 2;

	if (objAMin.x < objBMax.x && objAMax.x > objBMin.x){
		if (objAMin.y < objBMax.y && objAMax.y > objBMin.y){
			return true;
		}
	}

	return false;
}

bool BoxCollider::checkCollision(Vector pos){
	Vector objAMin, objAMax;

	objAMin.x = this->getPos().x - m_width / 2;
	objAMax.x = this->getPos().x + m_width / 2;

	objAMin.y = this->getPos().y - m_height / 2;
	objAMax.y = this->getPos().y + m_height / 2;

	if (objAMin.x < pos.x && objAMax.x > pos.x){
		if (objAMin.y < pos.y && objAMax.y > pos.y){
			return true;
		}
	}

	return false;
}

bool BoxCollider::hitLeft(BoxCollider* col){
	Vector objAMin, objBMin, objAMax, objBMax;

	objAMin.x = this->getPos().x - m_width / 2;
	objAMax.x = this->getPos().x;

	objBMin.x = col->getPos().x - col->getWidth() / 2;
	objBMax.x = col->getPos().x + col->getWidth() / 2;

	objAMin.y = this->getPos().y - (m_height * 0.45f);
	objAMax.y = this->getPos().y + (m_height * 0.45f);

	objBMin.y = col->getPos().y - col->getHeight() / 2;
	objBMax.y = col->getPos().y + col->getHeight() / 2;

	if (objAMin.x < objBMax.x && objAMax.x > objBMin.x){
		if (objAMin.y < objBMax.y && objAMax.y > objBMin.y){
			return true;
		}
	}

	return false;
}

bool BoxCollider::hitright(BoxCollider* col){
	Vector objAMin, objBMin, objAMax, objBMax;

	objAMin.x = this->getPos().x;
	objAMax.x = this->getPos().x + m_width / 2;

	objBMin.x = col->getPos().x - col->getWidth() / 2;
	objBMax.x = col->getPos().x + col->getWidth() / 2;

	objAMin.y = this->getPos().y - (m_height * 0.45f);
	objAMax.y = this->getPos().y + (m_height * 0.45f);

	objBMin.y = col->getPos().y - col->getHeight() / 2;
	objBMax.y = col->getPos().y + col->getHeight() / 2;

	if (objAMin.x < objBMax.x && objAMax.x > objBMin.x){
		if (objAMin.y < objBMax.y && objAMax.y > objBMin.y){
			return true;
		}
	}

	return false;
}

bool BoxCollider::hitTop(BoxCollider* col){
	Vector objAMin, objBMin, objAMax, objBMax;

	objAMin.x = this->getPos().x - m_width / 2;
	objAMax.x = this->getPos().x + m_width / 2;

	objBMin.x = col->getPos().x - col->getWidth() / 2;
	objBMax.x = col->getPos().x + col->getWidth() / 2;

	objAMin.y = this->getPos().y;
	objAMax.y = this->getPos().y + m_height / 2;

	objBMin.y = col->getPos().y - col->getHeight() / 2;
	objBMax.y = col->getPos().y + col->getHeight() / 2;

	if (objAMin.x < objBMax.x && objAMax.x > objBMin.x){
		if (objAMin.y < objBMax.y && objAMax.y > objBMin.y){
			return true;
		}
	}

	return false;
}

bool BoxCollider::hitBottom(BoxCollider* col){
	Vector objAMin, objBMin, objAMax, objBMax;

	objAMin.x = this->getPos().x - m_width / 2;
	objAMax.x = this->getPos().x + m_width / 2;

	objBMin.x = col->getPos().x - col->getWidth() / 2;
	objBMax.x = col->getPos().x + col->getWidth() / 2;

	objAMin.y = this->getPos().y - m_height / 2;
	objAMax.y = this->getPos().y + m_height;

	objBMin.y = col->getPos().y - col->getHeight() / 2;
	objBMax.y = col->getPos().y + col->getHeight() / 2;

	if (objAMin.x < objBMax.x && objAMax.x > objBMin.x){
		if (objAMin.y < objBMax.y && objAMax.y > objBMin.y){
			return true;
		}
	}

	return false;
}

void BoxCollider::render(){
	float w, h, l;

	w = m_width / 2;
	h = m_height / 2;
	l = m_length / 2;

	glPushMatrix();
		glTranslatef(getPos().x, getPos().y, getPos().z);
		glColor3f(1.0f, 1.0f, 1.0f);
		glLineWidth(5.0f);
		glBegin(GL_LINE_LOOP);
			glVertex3f(-w, h, l);
			glVertex3f(-w, -h, l);
			glVertex3f(w, -h, l);
			glVertex3f(w, h, l);
		glEnd();
	glPopMatrix();
}