#include "TerrainGenerator.h"


TerrainGenerator::TerrainGenerator(void){
}

TerrainGenerator::~TerrainGenerator(void){
}

Image TerrainGenerator::createIslands(int seed){
	Image image, image2;

	image = renderNoise(6, 10.0f, 1.0f, 1.0f, seed);

	for (int x = (image.GetWidth() / 4) + (image.GetWidth()/2); x <= image.GetWidth(); x++){
		for (int y = 0; y < image.GetHeight(); y++){
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

					if (curX <= (image.GetWidth() / 4) + (image.GetWidth() / 2)){
						done = true;
					}
				}
			}
		}
	}

	for (int x = (image.GetWidth() / 4) + (image.GetWidth() / 2); x >= image.GetWidth() / 2; x--){
		for (int y = 0; y < image.GetHeight(); y++){
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

					if (curX >= (image.GetWidth() / 4) + (image.GetWidth() / 2)){
						done = true;
					}
				}
			}
		}
	}

	for (int x = image.GetWidth() / 4; x <= image.GetWidth() / 2; x++){
		for (int y = 0; y < image.GetHeight(); y++){
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

					if (curX <= image.GetWidth() / 4){
						done = true;
					}
				}
			}
		}
	}

	for (int x = image.GetWidth() / 4; x > 0; x--){
		for (int y = 0; y < image.GetHeight(); y++){
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

					if (curX >= image.GetWidth() / 4){
						done = true;
					}
				}
			}
		}
	}

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
						image.SetValue(curX, curY, image.GetValue(curX, curY - 1));
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

	image2 = renderNoise(8, 2.0f, 0.1f, 2.0f, seed + 1);

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

Image TerrainGenerator::createLand(int seed){
	Image image, image2;

	image = renderNoise(8, 1.0f, 1.0f, 1.0f, seed);

	for (int x = image.GetWidth() / 2; x <= image.GetWidth(); x++){
		for (int y = 0; y < image.GetHeight(); y++){
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

					if (curX <= image.GetWidth() / 2){
						done = true;
					}
				}
			}
		}
	}

	for (int x = image.GetWidth() / 2; x > 0; x--){
		for (int y = 0; y < image.GetHeight(); y++){
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

					if (curX >= image.GetWidth() / 2){
						done = true;
					}
				}
			}
		}
	}

	image2 = renderNoise(4, 0.2f, 1.0f, 2.0f, seed+1);

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

Image TerrainGenerator::createFloatingIsland(int seed){
	Image image, image2;

	image = renderNoise(1, 2.0f, 0.5f, 1.0f, seed);

	for (int x = 0; x < image.GetWidth(); x++){
		for (int y = (image.GetHeight() / 2); y <= image.GetHeight(); y++){
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

					if (curY <= image.GetHeight() / 2){
						done = true;
					}
				}
			}
		}
	}

	for (int x = 0; x < image.GetWidth(); x++){
		for (int y = image.GetHeight() / 2; y > 0; y--){
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

					if (curY >= image.GetHeight()/2){
						done = true;
					}
				}
			}
		}
	}

	for (int x = image.GetWidth() / 2; x <= image.GetWidth(); x++){
		for (int y = 0; y < image.GetHeight(); y++){
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

					if (curX <= image.GetWidth()/2){
						done = true;
					}
				}
			}
		}
	}

	for (int x = image.GetWidth()/2; x > 0; x--){
		for (int y = 0; y < image.GetHeight(); y++){
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

					if (curX >= image.GetWidth()/2){
						done = true;
					}
				}
			}
		}
	}

	image2 = renderNoise(4, 0.4f, 1.0f, 2.0f, seed + 1);

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

Image TerrainGenerator::createBridge(int seed){
	Image image;

	image = renderNoise(8, 1.8f, 2.0f, 1.0f, seed);

	for (int x = 0; x <= image.GetWidth()/2; x++){
		for (int y = 0; y < image.GetHeight(); y++){
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

					if (curX <= 0){
						done = true;
					}
				}
			}
		}
	}

	for (int x = image.GetWidth(); x > image.GetWidth()/2; x--){
		for (int y = 0; y < image.GetHeight(); y++){
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

					if (curX >= image.GetWidth()){
						done = true;
					}
				}
			}
		}
	}

	for (int x = 0; x < image.GetWidth(); x++){
		for (int y = (image.GetHeight() / 2); y <= image.GetHeight(); y++){
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

					if (curY <= image.GetHeight() / 2){
						done = true;
					}
				}
			}
		}
	}

	for (int x = 0; x < image.GetWidth(); x++){
		for (int y = image.GetHeight() / 2; y > 0; y--){
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

					if (curY >= image.GetHeight() / 2){
						done = true;
					}
				}
			}
		}
	}

	return image;
}

Image TerrainGenerator::createRidges(int seed){
	Image image, image2;

	image = renderNoise(8, 1.0f, 0.7f, 4.0f, seed);

	for (int x = 0; x <= image.GetWidth() / 2; x++){
		for (int y = 0; y < image.GetHeight(); y++){
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

					if (curX <= 0){
						done = true;
					}
				}
			}
		}
	}

	for (int x = image.GetWidth(); x > image.GetWidth() / 2; x--){
		for (int y = 0; y < image.GetHeight(); y++){
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

					if (curX >= image.GetWidth()){
						done = true;
					}
				}
			}
		}
	}

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
						image.SetValue(curX, curY, image.GetValue(curX, curY - 1));
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
	
	image2 = renderNoise(8, 2.0f, 0.4f, 1.0f, seed + 1);

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