#include "Unit.h"


Unit::Unit(void){
	m_maxHealth = m_curHealth = 100;
	m_speed = 2;
	m_name = "Unit";
	m_model = NULL;
	m_wep = NULL;
	m_dead = false;
	m_wepPos = m_modelPos = m_pos = m_angle = Vector(0, 0, 0);
	m_move = new Movement(m_pos, m_angle, m_speed, m_speed, 0);
	m_phys = new Physics(m_pos);
	m_phys->isGrounded(true);
}

Unit::Unit(string name, Model* model, int health, float speed){
	m_maxHealth = health;
	m_curHealth = health;
	m_speed = speed;
	m_name = name;
	m_model = model;
	m_wep = new Weapon("Rocket", new Cube(0.04f), new Cube(0.02f), 10, 1);
	m_dead = false;
	Vector temp;
	temp.x = temp.y = temp.z = 0;
	m_wepPos = m_modelPos = temp;
	m_pos = m_angle = Vector(0, 0, 0);
	m_move = new Movement(m_pos, m_angle, m_speed, m_speed, 0);
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

Movement* Unit::move(){
	return m_move;
}

Physics* Unit::getPhysics(){
	return m_phys;
}

Vector Unit::getPosition(){
	return m_move->getPos();
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
	m_move->setPos(pos);

	if (m_model){
		setModelPos(pos);
	}

	if (m_wep){
		setWepPos(pos);
	}
}

void Unit::setModelPos(Vector pos){
	m_model->setPos(m_move->getPos());
	//m_modelPos = m_model->getPos();
}

void Unit::setWepPos(Vector pos){
	m_wep->setPos(m_move->getPos());
	//m_wepPos = pos;
}

void Unit::setPosition(float x, float y, float z){
	Vector temp;
	temp.x = x;
	temp.y = y;
	temp.z = z;

	setPosition(temp);
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
	m_move->moveX();
	m_move->moveY();
	m_move->moveZ();

	setPosition(m_move->getPos().x, m_move->getPos().y, m_move->getPos().z);

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