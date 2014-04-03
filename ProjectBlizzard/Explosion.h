#pragma once
#include "Model.h"
#include <vector>
#include "DebugPrint.h"
#include "Rectangle.h"
#include "Unit.h"

using namespace std;

class Explosion{
	vector<Vector>* m_terrain;
	vector<Vector>* m_units;

public:
	Explosion(vector<Vector>& terrain, vector<Vector>& unit);
	~Explosion();

	Rect* explo;
	bool tempBool;

	void defineTerrain(vector<Vector>& terrain);
	//void defineUnits(vector<Unit*>& unit);

	void circularExplosion(Vector pos, float radius, int damage);
	void rectExplosion(Vector pos, float x, float y, int damage);
	void pyramidExplosion(Vector pos, float x, float y, int damage);
};

