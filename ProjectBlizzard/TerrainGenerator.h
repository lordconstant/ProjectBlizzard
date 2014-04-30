#pragma once
#include "noiseutils.h"
#include "Cube.h"
#include <vector>
#include <ctime>

using namespace std;
using namespace noise;
using namespace noise::utils;

enum LAND_TYPE{ISLANDS = 0, LAND = 1, CAVES = 2, CAVE = 3, FLOATING_ISLAND = 4, BRIDGE = 5, RIDGES = 6, VALLEY = 7, CAVE2 = 8, LTCOUNT};

class TerrainGenerator{
	int m_curType;
public:
	TerrainGenerator(void);
	~TerrainGenerator(void);

	int box;
	int getCurrentType();

	vector<Vector> generateMap(int seed, int type);
	vector<Vector> generateMap(int type);
private:
	Image createIslands(int seed);
	Image createLand(int seed);
	Image createCaves(int seed);
	Image createCave(int seed);
	Image createFloatingIsland(int seed);
	Image createBridge(int seed);
	Image createRidges(int seed);
	Image createValley(int seed);
	Image createCave2(int seed);

	Image renderNoise(int oct, float freq, float pers, float lacun, int seed);

	Image PushLeft(Image image, int bottom, int top, int left, int right);
	Image PushRight(Image image, int bottom, int top, int left, int right);
	Image PushTop(Image image, int bottom, int top, int left, int right);
	Image PushBottom(Image image, int bottom, int top, int left, int right);

	Image cutTerrain(Image image, Image image2, int bottom, int top, int left, int right);
	Image mergeTerrain(Image image, Image image2, int bottom, int top, int left, int right);
};

