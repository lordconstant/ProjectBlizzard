#include "Explosion.h"


Explosion::Explosion(vector<Vector>& terrain, vector<Vector>& unit){
	m_terrain = &terrain;
	m_units = &unit;
	tempBool = false;
}


Explosion::~Explosion()
{
}

void Explosion::circularExplosion(Vector pos, float radius, int damage){
	explo = new Rect(1, radius * 2, radius * 2, 0.05);
	explo->setTexture("Images/Explosions/Cloud.bmp");
	explo->setPos(pos);
	tempBool = true;

	radius *= radius;

	for (int i = 0; i < m_terrain->size(); i++){
		float dist;
		dist = pos.Dist2(m_terrain->at(i));

		if (dist < 0){
			dist = -dist;
		}

		if (dist <= radius){
			//delete m_terrain->at(i);
			m_terrain->erase(m_terrain->begin() + i);
			i--;
		}
	}
}

void Explosion::rectExplosion(Vector pos, float x, float y, int damage){
	float hx, hy;
	hx = x / 2;
	hy = y / 2;

	for (int i = 0; i < m_terrain->size(); i++){
		float tx, ty;
		tx = m_terrain->at(i).x;
		ty = m_terrain->at(i).y;

		if (tx > pos.x - hx && tx < pos.x + hx){
			if (ty > pos.y - hy && ty < pos.y + hy){
				//delete m_terrain->at(i);
				m_terrain->erase(m_terrain->begin() + i);
				i--;
			}
		}
	}
}

void Explosion::pyramidExplosion(Vector pos, float x, float y, int damage){

}

void Explosion::defineTerrain(vector<Vector>& terrain){
	if (!&terrain){
		return;
	}

	m_terrain = &terrain;
}

//void Explosion::defineUnits(vector<Unit*>& unit){
//	if (!&unit){
//		return;
//	}
//
//	m_units = &unit;
//}