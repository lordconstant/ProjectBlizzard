#include "TerrainGenerator.h"


TerrainGenerator::TerrainGenerator(void){
}

TerrainGenerator::~TerrainGenerator(void){
}

Image TerrainGenerator::createIslands(int seed){
	Image image, image2;

	image = renderNoise(6, 10.0f, 1.0f, 1.0f, seed);

	image = PushLeft(image, 0, image.GetHeight(), (image.GetWidth() / 4) + (image.GetWidth() / 2), image.GetWidth());

	image = PushRight(image, 0, image.GetHeight(), image.GetWidth() / 2, (image.GetWidth() / 4) + (image.GetWidth() / 2));

	image = PushLeft(image, 0, image.GetHeight(), image.GetWidth() / 4, image.GetWidth() / 2);

	image = PushRight(image, 0, image.GetHeight(), 0, image.GetWidth() / 4);

	image = PushBottom(image, 0, image.GetHeight(), 0, image.GetWidth());

	image2 = renderNoise(8, 2.0f, 0.1f, 2.0f, seed + 1);

	image = cutTerrain(image, image2, 0, image.GetHeight(), 0, image.GetWidth());

	return image;
}

Image TerrainGenerator::createLand(int seed){
	Image image, image2;

	image = renderNoise(8, 1.0f, 1.0f, 1.0f, seed);

	image = PushLeft(image, 0, image.GetHeight(), image.GetWidth() / 2, image.GetWidth());

	image = PushRight(image, 0, image.GetHeight(), 0, image.GetWidth() / 2);

	image2 = renderNoise(4, 0.2f, 1.0f, 2.0f, seed+1);

	image = cutTerrain(image, image2, 0, image.GetHeight(), 0, image.GetWidth());

	return image;
}

Image TerrainGenerator::createCaves(int seed){
	Image image;

	image = renderNoise(8, 1.8f, 2.0f, 1.0f, seed);

	return image;
}

Image TerrainGenerator::createCave(int seed){
	Image image;

	image = renderNoise(4, 3.0f, 1.0f, 1.0f, seed);

	image = PushBottom(image, 0, image.GetHeight() / 2, 0, image.GetWidth());

	image = PushTop(image, image.GetHeight() / 2, image.GetHeight(), 0, image.GetWidth());

	return image;
}

Image TerrainGenerator::createFloatingIsland(int seed){
	Image image, image2;

	image = renderNoise(1, 2.0f, 0.5f, 1.0f, seed);

	image = PushBottom(image, image.GetHeight() / 2, image.GetHeight(), 0, image.GetWidth());

	image = PushTop(image, 0, image.GetHeight() / 2, 0, image.GetWidth());

	image = PushLeft(image, 0, image.GetHeight(), image.GetWidth() / 2, image.GetWidth());

	image = PushRight(image, 0, image.GetHeight(), 0, image.GetWidth() / 2);

	image2 = renderNoise(4, 0.4f, 1.0f, 2.0f, seed + 1);

	image = cutTerrain(image, image2, 0, image.GetHeight(), 0, image.GetWidth());

	return image;
}

Image TerrainGenerator::createBridge(int seed){
	Image image;

	image = renderNoise(8, 1.8f, 2.0f, 1.0f, seed);

	image = PushLeft(image, 0, image.GetHeight(), 0, image.GetWidth() / 2);

	image = PushRight(image, 0, image.GetHeight(), image.GetWidth() / 2, image.GetWidth());

	image = PushBottom(image, image.GetHeight() / 2, image.GetHeight(), 0, image.GetWidth());

	image = PushTop(image, 0, image.GetHeight() / 2, 0, image.GetWidth());

	return image;
}

Image TerrainGenerator::createRidges(int seed){
	Image image, image2;

	image = renderNoise(8, 1.0f, 0.7f, 4.0f, seed);

	image = PushLeft(image, 0, image.GetHeight(), 0, image.GetWidth() / 2);

	image = PushRight(image, 0, image.GetHeight(), image.GetWidth() / 2, image.GetWidth());

	image = PushBottom(image, 0, image.GetHeight(), 0, image.GetWidth());

	image2 = renderNoise(8, 2.0f, 0.4f, 1.0f, seed + 1);

	image = cutTerrain(image, image2, 0, image.GetHeight(), 0, image.GetWidth());

	return image;
}

Image TerrainGenerator::createValley(int seed){
	Image image, image2;

	image = renderNoise(8, 1.0f, 0.7f, 4.0f, seed);

	image = PushLeft(image, 0, image.GetHeight(), 0, image.GetWidth() / 2);

	image = PushRight(image, 0, image.GetHeight(), image.GetWidth() / 2, image.GetWidth());

	image = PushBottom(image, 0, image.GetHeight(), 0, image.GetWidth());

	image2 = renderNoise(8, 2.0f, 0.4f, 1.0f, seed + 1);

	image = mergeTerrain(image, image2, 0, image.GetHeight(), 0, image.GetWidth());

	image = PushBottom(image, 0, image.GetHeight(), 0, image.GetWidth());

	return image;
}

Image TerrainGenerator::createCave2(int seed){
	Image image;

	image = renderNoise(8, 3.0f, 1.0f, 1.0f, seed);

	image = PushBottom(image, 0, image.GetHeight() / 4, 0, image.GetWidth());

	image = PushTop(image, image.GetHeight() / 4, image.GetHeight() / 2, 0, image.GetWidth());

	image = PushBottom(image, image.GetHeight() / 2, (image.GetHeight() / 4) + (image.GetHeight() / 2), 0, image.GetWidth());

	image = PushTop(image, (image.GetHeight() / 4) + (image.GetHeight() / 2), image.GetHeight(), 0, image.GetWidth());

	return image;
}

Image TerrainGenerator::renderNoise(int oct, float freq, float pers, float lacun, int seed){
	module::Perlin myModule;
	NoiseMap heightMap;
	NoiseMapBuilderPlane heightMapBuilder;
	RendererImage renderer;
	Image image;

	myModule.SetOctaveCount(oct);
	myModule.SetFrequency(freq);
	myModule.SetPersistence(pers);
	myModule.SetLacunarity(lacun);
	myModule.SetSeed(seed);

	heightMapBuilder.SetSourceModule(myModule);
	heightMapBuilder.SetDestNoiseMap(heightMap);
	heightMapBuilder.SetDestSize(128, 64);
	heightMapBuilder.SetBounds(2.0f, 4.0f, 2.0f, 4.0f);
	heightMapBuilder.Build();

	renderer.SetSourceNoiseMap(heightMap);
	renderer.SetDestImage(image);
	renderer.ClearGradient();
	renderer.AddGradientPoint(0.1249, utils::Color(0, 0, 0, 255)); // sand
	renderer.AddGradientPoint(0.1250, utils::Color(255, 255, 255, 255)); // grass
	renderer.Render();

	return image;
}

Image TerrainGenerator::PushLeft(Image image, int bottom, int top, int left, int right){
	for (int x = left; x < right; x++){
		for (int y = bottom; y < top; y++){
			if (x > 0){
				bool done = false;
				int curX, curY;
				curX = x;
				curY = y;

				while (!done){
					int col1, col2;
					col1 = image.GetValue(curX, curY).red;
					col2 = image.GetValue(curX - 1, curY).red;

					if (col1 > col2){
						Color temp = image.GetValue(curX, curY);
						image.SetValue(curX, curY, image.GetValue(curX - 1, curY));
						image.SetValue(curX - 1, curY, temp);
					}

					curX--;

					if (curX <= left){
						done = true;
					}
				}
			}
		}
	}

	return image;
}

Image TerrainGenerator::PushRight(Image image, int bottom, int top, int left, int right){
	for (int x = right; x > left; x--){
		for (int y = bottom; y < top; y++){
			if (x < image.GetWidth()){
				bool done = false;
				int curX, curY;
				curX = x;
				curY = y;

				while (!done){
					int col1, col2;
					col1 = image.GetValue(curX, curY).red;
					col2 = image.GetValue(curX - 1, curY).red;

					if (col1 < col2){
						Color temp = image.GetValue(curX, curY);
						image.SetValue(curX, curY, image.GetValue(curX - 1, curY));
						image.SetValue(curX - 1, curY, temp);
					}

					curX++;

					if (curX >= right){
						done = true;
					}
				}
			}
		}
	}

	return image;
}

Image TerrainGenerator::PushTop(Image image, int bottom, int top, int left, int right){
	for (int x = left; x < right; x++){
		for (int y = top; y >= bottom; y--){
			if (y < image.GetHeight()){
				bool done = false;
				int curX, curY;
				curX = x;
				curY = y;

				while (!done){
					int col1, col2;
					col1 = image.GetValue(curX, curY).red;
					col2 = image.GetValue(curX, curY - 1).red;

					if (col1 < col2){
						Color temp = image.GetValue(curX, curY);
						image.SetValue(curX, curY, image.GetValue(curX, curY - 1));
						image.SetValue(curX, curY - 1, temp);
					}

					curY++;

					if (curY >= top){
						done = true;
					}
				}
			}
		}
	}

	return image;
}

Image TerrainGenerator::PushBottom(Image image, int bottom, int top, int left, int right){
	for (int x = left; x < right; x++){
		for (int y = bottom; y < top; y++){
			if (y > 0){
				bool done = false;
				int curX, curY;
				curX = x;
				curY = y;

				while (!done){
					int col1, col2;
					col1 = image.GetValue(curX, curY).red;
					col2 = image.GetValue(curX, curY - 1).red;

					if (col1 > col2){
						Color temp = image.GetValue(curX, curY);
						image.SetValue(curX, curY, image.GetValue(curX, curY - 1));
						image.SetValue(curX, curY - 1, temp);
					}

					curY--;

					if (curY <= bottom){
						done = true;
					}
				}
			}
		}
	}

	return image;
}

Image TerrainGenerator::cutTerrain(Image image, Image image2, int bottom, int top, int left, int right){
	for (int x = left; x < right; x++){
		for (int y = bottom; y < top; y++){
			int col1, col2;
			col1 = image.GetValue(x, y).red;
			col2 = image2.GetValue(x, y).red;

			if (col1 == 255){
				if (col1 == col2){
					image.SetValue(x, y, Color(0, 0, 0, 255));
				}
			}
		}
	}

	return image;
}

Image TerrainGenerator::mergeTerrain(Image image, Image image2, int bottom, int top, int left, int right){
	for (int x = left; x < right; x++){
		for (int y = bottom; y < top; y++){
			int col1, col2;
			col1 = image.GetValue(x, y).red;
			col2 = image2.GetValue(x, y).red;

			if (col1 == 0){
				if (col1 != col2){
					image.SetValue(x, y, Color(255, 255, 255, 255));
				}
			}
		}
	}

	return image;
}

int TerrainGenerator::getCurrentType(){
	return m_curType;
}

vector<Vector> TerrainGenerator::generateMap(int seed, int type){
	if (type < 0 || type > LTCOUNT){
		vector<Vector> temp; 
		temp.push_back(Vector(0, 0, 0));
		return temp;
	}

	Image image;

	switch (type){
	case ISLANDS:
		image = createIslands(seed);
		break;
	case LAND:
		image = createLand(seed);
		break;
	case CAVES:
		image = createCaves(seed);
		break;
	case CAVE:
		image = createCave(seed);
		break;
	case FLOATING_ISLAND:
		image = createFloatingIsland(seed);
		break;
	case BRIDGE:
		image = createBridge(seed);
		break;
	case RIDGES:
		image = createRidges(seed);
		break;
	case VALLEY:
		image = createValley(seed);
		break;
	case CAVE2:
		image = createCave2(seed);
		break;
	default:
		image = createIslands(seed);
		break;
	}

	m_curType = type;

	vector<Vector> cubVec;
	for (int x = 0; x < image.GetWidth(); x++){
		for (int y = 0; y < image.GetHeight(); y++){
			if (image.GetValue(x, y).red == 255){
				cubVec.push_back(Vector(x*0.05f, y*0.05f, 1));
			}
		}
	}

	return cubVec;
}

vector<Vector> TerrainGenerator::generateMap(int type){
	srand(time(NULL));
	return generateMap(rand() % 1000000, type);
}