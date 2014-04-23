#pragma once
#include "Cuboid.h"
#include "DebugPrint.h"

class Button3D{
	char* m_img;
	Cuboid* m_cuboid;
	bool m_hover;
public:
	Button3D(char* img, float width, float height, float length);
	~Button3D();

	void render();
	void update(float mouseX, float mouseY);

	Cuboid* getCuboid();

	bool isMouseOver();

	bool checkArea(float mouseX, float mouseY);
};

