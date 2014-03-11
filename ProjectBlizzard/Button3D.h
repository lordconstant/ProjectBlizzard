#pragma once
#include "Rectangle.h"
#include "DebugPrint.h"

class Button3D{
	char* m_img;
	Rect* m_rect;
	bool m_hover;
public:
	Button3D(char* img, float width, float height, float length);
	~Button3D();

	void render();
	void update(float mouseX, float mouseY);

	Rect* getRect();

	bool isMouseOver();

	bool checkArea(float mouseX, float mouseY);
};

