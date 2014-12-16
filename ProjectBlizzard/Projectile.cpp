#include "Projectile.h"


Projectile::Projectile(){
	m_model = NULL;
	m_phys = new Physics(&m_pos);
}

Projectile::Projectile(Model* model){
	m_model = model;

	if (!m_model){
		m_model = new Cube(0.1f);
	}

	m_phys = new Physics(&m_pos);
}

Projectile::~Projectile(){
	if (m_model){
		m_model = NULL;
	}

	if (m_phys){
		delete m_phys;
	}
}

void Projectile::setPos(Vector pos){
	m_pos = pos;
	m_model->setPos(pos);
}

void Projectile::setModel(Model* model){
	if (!model){
		return;
	}

	if (m_model){
		delete m_model;
		m_model = NULL;
	}

	m_model = model;

}

void Projectile::setVel(float velX, float velY){
	if (m_phys){
		m_phys->setVelocity(velX, velY);
	}
}

void Projectile::setVelX(float velX){
	if (m_phys){
		m_phys->setVelocityX(velX);
	}
}

void Projectile::setVelY(float velY){
	if (m_phys){
		m_phys->setVelocityX(velY);
	}
}

void Projectile::setAccel(float accX, float accY){
	if (m_phys){
		m_phys->setAccel(accX, accY);
	}
}

void Projectile::setAccelX(float acc){
	if (m_phys){
		m_phys->setAccelX(acc);
	}
}

void Projectile::setAccelY(float acc){
	if (m_phys){
		m_phys->setAccelY(acc);
	}
}

Model* Projectile::getModel(){
	if (!m_model){
		return NULL;
	}

	return m_model;
}

float Projectile::getVelX(){
	if (m_phys){
		return m_phys->getVelocity().x;
	}

	return NULL;
}

float Projectile::getVelY(){
	if (m_phys){
		return m_phys->getVelocity().y;
	}

	return NULL;
}

void Projectile::update(float wind){
	m_phys->setWind(wind);
	m_phys->update();
	m_model->setPos(m_pos);
}

Vector Projectile::nextPos(){
	return m_phys->nextPos();
}