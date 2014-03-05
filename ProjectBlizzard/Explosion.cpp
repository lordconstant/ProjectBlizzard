#include "Explosion.h"


Explosion::Explosion(vector<Model*>& terrain, vector<Model*>& unit){
	m_terrain = &terrain;
	m_units = &unit;
}


Explosion::~Explosion()
{
}

void Explosion::circularExplosion(Vector pos, float radius, int damage){
	radius *= radius;
	for (int i = 0; i < m_terrain->size(); i++){
		float dist;
		dist = pos.Dist2(m_terrain->at(i)->getPos());

		if (dist < 0){
			dist = -dist;
		}

		if (dist <= radius){
			delete m_terrain->at(i);
			m_terrain->erase(m_terrain->begin() + i);
			i--;
		}
	}
}

void Explosion::rectExplosion(Vector pos, float x, float y, int damage){

}

void Explosion::pyramidExplosion(Vector pos, float x, float y, int damage){

}