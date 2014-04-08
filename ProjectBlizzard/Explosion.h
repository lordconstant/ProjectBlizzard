#pragma once
#include "Model.h"
#include <vector>
#include "DebugPrint.h"
#include "Rectangle.h"
#include "Unit.h"
#include "Team.h"

using namespace std;

class Explosion{
	vector<Vector>* m_terrain;
	vector<Team*>* m_teams;

public:
	Explosion(vector<Vector>& terrain, vector<Team*>& teams);
	~Explosion();

	Rect* explo;
	bool tempBool;

	void defineTerrain(vector<Vector>& terrain);
	void defineUnits(vector<Team*>& teams);

	void circularExplosion(Vector pos, float radius, int damage);
	void rectExplosion(Vector pos, float x, float y, int damage);
	void pyramidExplosion(Vector pos, float x, float y, int damage);
};

