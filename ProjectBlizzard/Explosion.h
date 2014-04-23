#pragma once
#include "Model.h"
#include <vector>
#include "DebugPrint.h"
#include "Cuboid.h"
#include "Unit.h"
#include "Team.h"
#include "QuadTree.h"

using namespace std;

class Explosion{
	vector<Vector>* m_terrain;
	vector<Team*>* m_teams;

public:
	Explosion(vector<Vector>& terrain, vector<Team*>& teams);
	~Explosion();

	Cuboid* explo;
	bool tempBool;

	void defineTerrain(vector<Vector>& terrain);
	void defineTeams(vector<Team*>& teams);

	void circularExplosion(Vector pos, float radius, int damage, QuadTree& quadTree);
	void rectExplosion(Vector pos, float x, float y, int damage);
};

