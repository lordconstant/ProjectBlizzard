#include "Explosion.h"


Explosion::Explosion(vector<Vector>& terrain, vector<Team*>& teams){
	m_terrain = &terrain;
	m_teams = &teams;
	tempBool = false;
}


Explosion::~Explosion()
{
}

void Explosion::circularExplosion(Vector pos, float radius, int damage, QuadTree& quadTree){
	tempBool = true;

	radius *= radius;

	for (int i = 0; i < m_terrain->size(); i++){
		/*if (pos.x + radius*2 < m_terrain->at(i).x){
			continue;
		}
		else if (pos.x - radius*2 > m_terrain->at(i).x){
			continue;
		}
		
		if (pos.y + radius*2 < m_terrain->at(i).y){
			continue;
		}
		else if (pos.y - radius*2 > m_terrain->at(i).y){
			continue;
		}*/

		float dist;
		dist = pos.Dist2(m_terrain->at(i));

		if (dist < 0){
			dist = -dist;
		}

		if (dist <= radius){
			quadTree.removeObject(m_terrain->at(i));
			m_terrain->erase(m_terrain->begin() + i);
			i--;
		}
	}

	for (int i = 0; i < m_teams->size(); i++){
		for (int j = 0; j < m_teams->at(i)->getTeamSize(); j++){
			float dist;

			dist = pos.Dist2(m_teams->at(i)->getUnit(j)->getPosition());

			if (dist < 0){
				dist = -dist;
			}

			if (dist <= radius){
				int curDamage;
				float xForce, yForce, angle, opp, adj;

				xForce = 0;
				yForce = 0;

				opp = pos.UnitVector().y - m_teams->at(i)->getUnit(j)->getModel()->getPos().UnitVector().y;
				adj = pos.UnitVector().x - m_teams->at(i)->getUnit(j)->getModel()->getPos().UnitVector().x;

				angle = atan(opp / adj);
				xForce = cos(angle);
				yForce = sin(angle);

				if (adj < 0){
					xForce = -xForce;
					yForce = -yForce;
				}

				if (opp == 0){
					yForce = -1;
				}

				if (adj == 0){
					xForce = 0;
				}

				if (dist >= 1){
					curDamage = (damage - ((float)damage / dist));
				}
				else if (dist < 1){
					curDamage = (damage - ((float)damage * dist));
				}

				if (curDamage < 0){
					curDamage = -curDamage;
				}

				m_teams->at(i)->getUnit(j)->getPhysics()->setVelocity(-xForce*2.0f, -yForce*2.0f);
					
				m_teams->at(i)->getUnit(j)->setCurHealth(m_teams->at(i)->getUnit(j)->getCurHealth() - curDamage);
			}
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
				m_terrain->erase(m_terrain->begin() + i);
				i--;
			}
		}
	}
}

void Explosion::defineTerrain(vector<Vector>& terrain){
	if (!&terrain){
		return;
	}

	m_terrain = &terrain;
}

void Explosion::defineTeams(vector<Team*>& teams){
	if (!&teams){
		return;
	}

	m_teams = &teams;
}