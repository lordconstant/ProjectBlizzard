#include "TerrainGenerator.h"


TerrainGenerator::TerrainGenerator(void){
}


TerrainGenerator::~TerrainGenerator(void){
}

Image TerrainGenerator::createIslands(int seed){
	Image image;

	image = renderNoise(1, 0.5f, 0.2f, 1.0f, seed);

	for (int x = 0; x < image.GetWidth(); x++){
		for (int y = 0; y < image.GetHeight(); y++){
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
						image.SetValue(curX, curY, image.GetValue(curX, curY-1));
						image.SetValue(curX, curY - 1, temp);
					}

					curY--;

					if (curY <= 0){
						done = true;
					}
				}
			}
		}
	}

	return image;
}

Image TerrainGenerator::createLand(int seed){
	Image image, image2;

	image = renderNoise(3, 0.8f, 1.0f, 1.0f, seed);

	for (int x = 0; x < image.GetWidth(); x++){
		for (int y = 0; y < image.GetHeight(); y++){
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
						image.SetValue(curX, curY, image.GetValue(curX, curY-1));
						image.SetValue(curX, curY - 1, temp);
					}

					curY--;

					if (curY <= 0){
						done = true;
					}
				}
			}
		}
	}

	image2 = renderNoise(3, 0.4f, 1.0f, 1.0f, seed+1);

	for (int x = 0; x < image.GetWidth(); x++){
		for (int y = 0; y < image.GetHeight(); y++){
			int col1, col2;
			col1 = image.GetValue(x, y).red;
			col2 = image2.GetValue(x, y).red;

			if (col1 = 255){
				if (col1 == col2){
					image.SetValue(x, y, Color(0, 0, 0, 255));
				}
			}
		}
	}

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

	for (int x = 0; x < image.GetWidth(); x++){
		for (int y = 0; y < image.GetHeight()/2; y++){
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
						image.SetValue(curX, curY, image.GetValue(curX, curY-1));
						image.SetValue(curX, curY - 1, temp);
					}

					curY--;

					if (curY <= 0){
						done = true;
					}
				}
			}
		}
	}

	for (int x = 0; x < image.GetWidth(); x++){
		for (int y = image.GetHeight(); y >= image.GetHeight()/2; y--){
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

					if (curY >= image.GetHeight()){
						done = true;
					}
				}
			}
		}
	}

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
	heightMapBuilder.SetDestSize(256, 128);
	heightMapBuilder.SetBounds(2.0f, 4.5f, 2.0f, 4.5f);
	heightMapBuilder.Build();

	renderer.SetSourceNoiseMap(heightMap);
	renderer.SetDestImage(image);
	renderer.ClearGradient();
	renderer.AddGradientPoint(0.1249, utils::Color(0, 0, 0, 255)); // sand
	renderer.AddGradientPoint(0.1250, utils::Color(255, 255, 255, 255)); // grass
	renderer.Render();

	return image;
}

vector<Cube>* TerrainGenerator::generateMap(int seed, int type){
	if(type < 0 || type > LTCOUNT){
		return NULL;
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
	default:
		break;
	}

	vector<Cube>* cubVec;
	cubVec = new vector<Cube>;
	for(int x = 0; x < image.GetWidth(); x++){
		for(int y = 0; y < image.GetHeight(); y++){
			if(image.GetValue(x, y).red == 255){
				Cube cube(0.05);

				cube.setPos(x*0.05, y*0.05, 1);

				cubVec->push_back(cube);
			}
		}
	}

	return cubVec;
}

vector<Cube>* TerrainGenerator::generateMap(int type){
	srand(time(NULL));
	return generateMap(rand() % 100000, type);
}