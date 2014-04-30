#include "Weapon.h"

Weapon::Weapon(){
	m_name = "Wep";
	m_model = NULL;
	m_ammo = NULL;
	m_damage = 10;
	m_amount = 1;
	m_power = 1;
	m_curShot = NULL;
	m_infinite = m_hit = false;
	m_curPower = m_lastPower = 0;
	m_powerUp = true;
	m_generatePower = false;
}

Weapon::Weapon(string name, Model* model, Model* ammo, int damage, int amount){
	m_name = name;
	m_model = model;
	m_ammo = ammo;
	m_damage = damage;
	m_amount = amount;
	m_power = 1;
	m_curShot = NULL;
	m_hit = false;

	if(amount < 0){
		m_infinite = false;
	}

	if (m_model){
		m_model->setPos(0, 0, 0);
	}

	if (m_ammo){
		m_ammo->setPos(0, 0, 0);
	}

	m_curPower = m_lastPower = 0;
	m_powerUp = true;
	m_generatePower = false;
}

Weapon::~Weapon(){
}

int Weapon::getDamage(){
	return m_damage;
}

int Weapon::getAmountWeps(){
	return m_amount;
}

float Weapon::getPower(){
	return m_lastPower;
}

string Weapon::getName(){
	return m_name;
}

bool Weapon::isInfinite(){
	return m_infinite;
}

bool Weapon::hasModel(){
	if (m_model){
		return true;
	}

	return false;
}

bool Weapon::getPowerGen(){
	return m_generatePower;
}

Vector Weapon::getPos(){
	return m_pos;
}

Projectile* Weapon::getCurShot(){
	return m_curShot;
}

void Weapon::setDamage(int dmg){
	if (dmg < 0){
		return;
	}

	m_damage = dmg;
}

void Weapon::setAmountWeps(int amount){
	if (amount < 0){
		return;
	}

	m_amount = amount;
}

void Weapon::setPower(float power){
	if (power < 0){
		return;
	}

	m_power = power;
}

void Weapon::setName(string name){
	m_name = name;
}

void Weapon::isInfinite(bool infinite){
	m_infinite = infinite;
}

void Weapon::setModel(Model* model){
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

void Weapon::setPos(Vector pos){
	m_pos = pos;
	m_model->setPos(pos);
}

void Weapon::setPos(float x, float y, float z){
	setPos(Vector(x, y, z));
}

void Weapon::setColor(float r, float g, float b){
	m_model->setColor(r, g, b);
}

bool Weapon::useWeapon(){
	if(!m_ammo){
		m_curPower = 0;
		return false;
	}

	if(m_curShot){
		delete m_curShot;
		m_curShot = NULL;
	}

	m_curShot = new Projectile(m_ammo);
	m_curShot->setPos(m_pos);

	float opp, adj, angle;

	if ((m_direction.y > 10 && m_direction.y < -10) || (m_direction.x > 10 && m_direction.x < -10)){
		opp = m_direction.y - m_pos.y;
		adj = m_direction.x - m_pos.x;

	}
	else{
		opp = m_direction.y;
		adj = m_direction.x;
	}

	angle = atan(opp / adj);
	m_shotDir.x = cos(angle);
	m_shotDir.y = sin(angle);
	m_shotDir.z = 1;

	if (adj < 0){
		m_shotDir.x = -m_shotDir.x;
		m_shotDir.y = -m_shotDir.y;
	}

	m_curShot->setVel(m_shotDir.x * m_curPower * 3.0f, m_shotDir.y * m_curPower * 3.0f);

	m_curShot->setAccel(m_shotDir.x * m_curPower * 3.0f, m_shotDir.y * m_curPower * 3.0f);

	m_lastPower = m_curPower;
	m_curPower = 0;

	return true;
}

bool Weapon::hitObject(Vector pos, float width, float height){
	/*if(!m_curShot){
		return false;
	}

	Vector tempPos;
	tempPos = m_curShot->getModel()->getPos();

	Vector objAMin, objBMin, objAMax, objBMax;
	objAMin.x = tempPos.x - (m_curShot->getModel()->getScale() / 2);
	objAMax.x = tempPos.x + (m_curShot->getModel()->getScale() / 2);

	objBMin.x = pos.x - (width / 2);
	objBMax.x = pos.x + (width / 2);

	objAMin.y = tempPos.y - (m_curShot->getModel()->getScale() / 2);
	objAMax.y = tempPos.y + (m_curShot->getModel()->getScale() / 2);

	objBMin.y = pos.y - (height / 2);
	objBMax.y = pos.y + (height / 2);

	if (objAMin.x < objBMax.x && objAMax.x > objBMin.x){
		if (objAMin.y < objBMax.y && objAMax.y > objBMin.y){*/
			delete m_curShot;
			m_curShot = NULL;
			return true;
		/*}
	}
	return false;
	*/
}

bool Weapon::checkAhead(Vector pos, float width, float height){
	if (!m_curShot){
		return false;
	}

	Vector point1, point2, point3, stepInc;
	float steps, curStep;
	curStep = 0;
	steps = 8;
	point1 = m_curShot->getModel()->getPos();
	point2 = m_curShot->nextPos();
	point2.z = 1;
	point1.z = 1;
	stepInc = point1 - point2;

	if (point2.x < point1.x){
		point3 = point1;
	}
	else{
		point3 = point2;
	}

	stepInc /= steps;

	while (curStep < steps){
		point3 += stepInc;

		Vector objAMin, objBMin, objAMax, objBMax;
		objAMin.x = point3.x - (m_curShot->getModel()->getScale() / 2);
		objAMax.x = point3.x + (m_curShot->getModel()->getScale() / 2);

		objBMin.x = pos.x - (width / 2);
		objBMax.x = pos.x + (width / 2);

		objAMin.y = point3.y - (m_curShot->getModel()->getScale() / 2);
		objAMax.y = point3.y + (m_curShot->getModel()->getScale() / 2);

		objBMin.y = pos.y - (height / 2);
		objBMax.y = pos.y + (height / 2);

		if (objAMin.x < objBMax.x && objAMax.x > objBMin.x){
			if (objAMin.y < objBMax.y && objAMax.y > objBMin.y){
				m_hit = true;
				m_curShot->setPos(point3);
				return true;
			}
		}
		curStep++;
	}

	return false;
}

void Weapon::render(){
	if(m_model){
		m_model->Render();
	}

	if(m_curShot){
		m_curShot->getModel()->Render();
	}
}

void Weapon::update(Vector mouse){
	m_direction = mouse;

	if(m_curShot && !m_hit){
		if (m_curShot->getModel()->getPos().y < 0){
			delete m_curShot;
			m_curShot = NULL;
		}

		if (m_curShot){
			m_curShot->update(0.0f);
		}
	}

	m_hit = false;
}

void Weapon::generatePower(){
	if (m_curPower >= m_power){
		m_powerUp = false;
	}

	if (m_curPower <= 0){
		m_powerUp = true;
	}

	if (m_powerUp){
		m_curPower += TimeControl::getInstance().getDeltaTime();
	}
	else{
		m_curPower -= TimeControl::getInstance().getDeltaTime();
	}

	if (m_curPower < 0){
		m_curPower = 0;
	}

	float length = (0.05f / m_power) * m_curPower;

	glPushMatrix();
		glTranslatef(m_pos.x - 0.025f, m_pos.y + 0.05f, 1.1f);
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_QUADS);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(length, 0.0f, 0.0f);
			glVertex3f(length, 0.01f, 0.0f);
			glVertex3f(0.0f, 0.01f, 0.0f);
		glEnd();
	glPopMatrix();
}

void Weapon::setPowerGen(bool power){
	m_generatePower = power;
}

void Weapon::reduceAmount(){
	if (m_infinite || m_amount <= 0){
		return;
	}

	m_amount--;
}