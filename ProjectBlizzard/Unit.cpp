#include "Unit.h"


Unit::Unit(void){
	m_maxHealth = m_curHealth = 100;
	m_speed = 2;
	m_name = "Unit";
	m_model = NULL;
	m_wep = NULL;
	m_dead = false;
	m_wepPos = m_modelPos = m_angle = Vector(0.0f, 0.0f, 0.0f);
	m_pos = new Vector(0.0f, 0.0f, 0.0f);
	m_phys = new Physics(m_pos);
	m_phys->isGrounded(true);
}

Unit::Unit(string name, Model* model, int health, float speed){
	m_maxHealth = health;
	m_curHealth = health;
	m_speed = speed;
	m_name = name;
	m_model = model;
	m_wep = new Weapon("Rocket", new Cube(0.02f), new Cube(0.02f), 55, 1);
	m_dead = false;

	m_wepPos = m_modelPos = m_angle = Vector(0.0f, 0.0f, 0.0f);
	m_pos = new Vector(0.0f, 0.0f, 0.0f);
	m_phys = new Physics(m_pos);
	m_phys->isGrounded(true);
}

Unit::~Unit(void){
	if (m_model){
		delete m_model;
		m_model = NULL;
	}

	if (m_wep){
		delete m_wep;
		m_wep = NULL;
	}

	if (m_pos){
		delete m_pos;
	}

	if (m_phys){
		delete m_phys;
	}
}

int Unit::getMaxHealth(){
	return m_maxHealth;
}

int Unit::getCurHealth(){
	return m_curHealth;
}

float Unit::getSpeed(){
	return m_speed;
}

string Unit::getName(){
	return m_name;
}

Weapon* Unit::getWeapon(){
	return m_wep;
}

Physics* Unit::getPhysics(){
	return m_phys;
}

Vector Unit::getPosition(){
	return *m_pos;
}

Model* Unit::getModel(){
	return m_model;
}

void Unit::setMaxHealth(int hp){
	if (hp < 1){
		return;
	}

	m_maxHealth = hp;
}

void Unit::setCurHealth(int hp){
	if (hp > m_maxHealth){
		resetHealth();
		return;
	}

	if (hp <= 0){
		m_curHealth = 0;
		m_dead = true;
		return;
	}

	m_curHealth = hp;
}

void Unit::resetHealth(){
	m_curHealth = m_maxHealth;
}

void Unit::setSpeed(float speed){
	if (speed < 0){
		return;
	}

	m_speed = speed;
}

void Unit::setName(string name){
	m_name = name;
}

void Unit::setModel(Model* model){
	if (!model){
		return;
	}

	if (m_model){
		delete m_model;
		m_model = NULL;
	}

	m_model = new Model();
	*m_model = *model;
}

void Unit::setWeapon(Weapon* wep){
	if (!wep){
		return;
	}

	if (m_wep){
		delete m_wep;
		m_wep = NULL;
	}

	m_wep = new Weapon;
	*m_wep = *wep;
}

void Unit::setColor(float r, float g, float b){
	m_model->setColor(r, g, b);
}

void Unit::setPosition(Vector pos){
	*m_pos = pos;

	if (m_model){
		setModelPos(m_modelPos);
	}

	if (m_wep){
		setWepPos(m_wepPos);
	}
}

void Unit::setModelPos(Vector pos){
	m_model->setPos(*m_pos + pos);
	m_modelPos = pos;
}

void Unit::setWepPos(Vector pos){
	m_wep->setPos(*m_pos + pos);
	m_wepPos = pos;
}

void Unit::setPosition(float x, float y, float z){
	setPosition(Vector(x, y, z));
}

void Unit::setModelPos(float x, float y, float z){
	Vector temp;
	temp.x = x;
	temp.y = y;
	temp.z = z;

	setModelPos(temp);
}

void Unit::setWepPos(float x, float y, float z){
	Vector temp;
	temp.x = x;
	temp.y = y;
	temp.z = z;

	setWepPos(temp);
}

bool Unit::hasModel(){
	if (m_model){
		return true;
	}

	return false;
}

bool Unit::fireWeapon(){
	if (!m_wep){
		return false;
	}

	m_wep->useWeapon();

	return true;
}

bool Unit::isDead(){
	return m_dead;
}

void Unit::update(Vector mouse){
	setPosition(*m_pos);
	m_wep->update(mouse);
	m_phys->update();

	if (m_curHealth <= 0){
		m_dead = true;
	}
	else{
		m_dead = false;
	}
}

void Unit::render(){
	if(m_model){
		m_model->Render();
	}

	if (m_wep){
		m_wep->render();
	}
}

void Unit::jump(){
	if (m_phys->isGrounded()){
		m_phys->setVelocityY(JUMP_POWER);
		m_phys->isGrounded(false);
	}
}

void Unit::renderHealthBar(){
	float height = 0.05f;
	double height2 = (height / m_maxHealth) * m_curHealth;

	glPushMatrix();
		glTranslatef(m_model->getPos().x - 0.05f, m_model->getPos().y - 0.026f, 1.04f);

		glColor3f(1.0f, 1.0f, 1.0f);

		glBegin(GL_QUADS);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.02f, 0.0f, 0.0f);
			glVertex3f(0.02f, height + 0.002f, 0.0f);
			glVertex3f(0.0f, height + 0.002f, 0.0f);
		glEnd();

	glPopMatrix();

	glPushMatrix();
		glTranslatef(m_model->getPos().x - 0.05f, m_model->getPos().y - 0.026f, 1.041f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_QUADS);
			glVertex3f(0.002f, 0.002f, 0.0f);
			glVertex3f(0.018f, 0.002f, 0.0f);
			glVertex3f(0.018f, height2, 0.0f);
			glVertex3f(0.002f, height2, 0.0f);
		glEnd();
	glPopMatrix();
}