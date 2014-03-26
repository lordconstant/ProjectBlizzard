#include "Movement.h"
Movement::Movement(Vector& pos, Vector& angle, float xVel, float yVel, float zVel){
	m_pos = &pos;
	m_angle = &angle;
	m_xVel = xVel;
	m_yVel = yVel;
	m_zVel = zVel;

	stopMoving();
}


Movement::~Movement(){
	m_pos = NULL;
	m_angle = NULL;
}

Vector Movement::getPos(){
	return *m_pos;
}

Vector Movement::getAngle(){
	return *m_angle;
}

void Movement::definePos(Vector& pos){
	if (!&pos){
		return;
	}

	m_pos = &pos;
}

void Movement::defineAngle(Vector& angle){
	if (!&angle){
		return;
	}

	m_angle = &angle;
}

void Movement::setPos(Vector pos){
	*m_pos = pos;
}

void Movement::setPos(float x, float y, float z){
	m_pos->x = x;
	m_pos->y = y;
	m_pos->z = z;
}

void Movement::setXvel(float speed){
	m_xVel = speed;
}

void Movement::setYvel(float speed){
	m_yVel = speed;
}

void Movement::setZvel(float speed){
	m_zVel = speed;
}

void Movement::setAllVel(float speed){
	m_xVel = m_yVel = m_zVel = speed;
}

void Movement::setAllVel(float xSpeed, float ySpeed, float zSpeed){
	m_xVel = xSpeed;
	m_yVel = ySpeed;
	m_zVel = zSpeed;
}

void Movement::moveXPos(float speed){
	float delta = TimeControl::getInstance().getDeltaTime();

	if (delta <= 0){
		delta = 0.0001;
	}

	m_pos->x += delta * speed;
}

void Movement::moveYPos(float speed){
	float delta = TimeControl::getInstance().getDeltaTime();

	if (delta <= 0){
		delta = 0.0001;
	}

	m_pos->y += delta * speed;
}

void Movement::moveZPos(float speed){
	float delta = TimeControl::getInstance().getDeltaTime();

	if (delta <= 0){
		delta = 0.0001;
	}

	m_pos->z += delta * speed;
}

void Movement::moveX(){
	if(m_right){
		moveXPos(m_xVel);
	}

	if(m_left){
		moveXPos(-m_xVel);
	}
}

void Movement::moveY(){
	if(m_up){
		moveYPos(m_yVel);
	}

	if(m_down){
		moveYPos(-m_yVel);
	}
}

void Movement::moveZ(){
	if(m_forwards){
		moveZPos(-m_zVel);
	}

	if(m_backwards){
		moveZPos(m_zVel);
	}
}

void Movement::move(float xSpeed, float ySpeed, float zSpeed){
	moveXPos(xSpeed);
	moveYPos(ySpeed);
	moveZPos(zSpeed);
}

void Movement::rotateBy(float angle, int axis){
	switch (axis){
	case XAXIS:
		rotateTo(m_angle->x + angle, axis);
		break;
	case YAXIS:
		rotateTo(m_angle->y + angle, axis);
		break;
	case ZAXIS:
		rotateTo(m_angle->z + angle, axis);
		break;
	default:
		break;
	}
}

void Movement::rotateTo(float angle, int axis){
	switch (axis){
	case XAXIS:
		m_angle->x = angle;

		while (m_angle->x > 360){
			m_angle->x -= 360;
		}

		while (m_angle->x < -360){
			m_angle->x += 360;
		}
		break;
	case YAXIS:
		m_angle->y = angle;

		while (m_angle->y > 360){
			m_angle->y -= 360;
		}

		while (m_angle->y < -360){
			m_angle->y += 360;
		}
		break;
	case ZAXIS:
		m_angle->z = angle;

		while (m_angle->z < 360){
			m_angle->z -= 360;
		}

		while (m_angle->z < -360){
			m_angle->z += 360;
		}
		break;
	default:
		break;
	}
}

void Movement::smoothRotateBy(float angle, float speed, int axis){
	//smoothRotateTo(*m_angle + angle, speed, axis);
}

void Movement::smoothRotateTo(float angle, float speed, int axis){
	/*if (speed <= 0 || *m_angle == angle){
		return;
	}

	if (*m_angle < angle){
		while (*m_angle < angle){
			*m_angle += TimeControl::getInstance().getDeltaTime() * speed;
		}
	}

	if (*m_angle > angle){
		while (*m_angle > angle){
			*m_angle -= TimeControl::getInstance().getDeltaTime() * speed;
		}
	}*/

	rotateTo(angle, axis);
}

void Movement::right(bool dir){
	m_right = dir;
}

void Movement::left(bool dir){
	m_left = dir;
}

void Movement::up(bool dir){
	m_up = dir;
}

void Movement::down(bool dir){
	m_down = dir;
}

void Movement::forward(bool dir){
	m_forwards = dir;
}

void Movement::backward(bool dir){
	m_backwards = dir;
}

void Movement::stopMoving(){
	m_left = m_right = m_up = m_down = m_forwards = m_backwards = false;
}