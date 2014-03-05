#pragma once
#include "Model.h"
#include <vector>
#include "DebugPrint.h"

using namespace std;

class Explosion{
	vector<Model*>* m_terrain;
	vector<Model*>* m_units;
public:
	Explosion(vector<Model*>& terrain, vector<Model*>& unit);
	~Explosion();

	void circularExplosion(Vector pos, float radius, int damage);
	void rectExplosion(Vector pos, float x, float y, int damage);
	void pyramidExplosion(Vector pos, float x, float y, int damage);
};

