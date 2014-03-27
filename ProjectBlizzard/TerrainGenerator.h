#pragma once
#include <noiseutils.h>
#include <noiseutils.cpp>
#include "Cube.h"
#include <vector>
#include <ctime>

using namespace std;
using namespace noise;
using namespace noise::utils;

enum LAND_TYPE{ISLANDS = 0, LAND = 1, CAVES = 2, CAVE = 3, LTCOUNT = 4};

class TerrainGenerator{
public:
	TerrainGenerator(void);
	~TerrainGenerator(void);

	int box;

	vector<Model*>* generateMap(int seed, int type);
	vector<Model*>* generateMap(int type);
private:
	Image createIslands(int seed);
	Image createLand(int seed);
	Image createCaves(int seed);
	Image createCave(int seed);
	Image renderNoise(int oct, float freq, float pers, float lacun, int seed);
};

