#pragma once
#include "Rectangle.h"
#include "DebugPrint.h"

class Button3D{
	char* m_img;
	Rect* m_rect;
	bool m_hover, m_clicked;
public:
	Button3D(char* img, int width, int height, int length);
	~Button3D();

	void render();
	void update(float mouseX, float mouseY);
	void setClicked(bool clicked);

	Rect* getRect();

	bool isMouseOver();
};

