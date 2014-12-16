#include "OptionsScreen.h"


OptionsScreen::OptionsScreen(HDC hdc) : Scene(hdc){
}


OptionsScreen::~OptionsScreen(void){
	if (m_btn){
		delete m_btn;
	}

	if (m_cam){
		delete m_cam;
	}

	if (m_font){
		delete m_font;
	}
}

void OptionsScreen::initialise(){
	m_cam = new Camera();

	m_btn = new Button3D("main_menu", 1, 0.25f, 0.0f);
	m_btn->getCuboid()->setPos(0, -1, -1);

	m_font = new BFont(m_hdc, "Courier", 14);

	m_cam->move()->setPos(0, 0, 0);
}

void OptionsScreen::update(float mouseX, float mouseY){
	updateMouse(mouseX, mouseY);
	m_btn->update(m_mousePos.x, m_mousePos.y);
}

void OptionsScreen::render(){
	m_cam->update();
	m_btn->render();
}

void OptionsScreen::render2D(){
	m_font->setColor(1.0f, 1.0f, 1.0f);
	m_font->printString(m_sWidth/2 - 55, m_sHeight/2 - m_sHeight/4, "HOW TO PLAY");
	m_font->printString(m_sWidth/2 - 160, m_sHeight/2 - m_sHeight/4 + 28, "A to move left | D to move right");
	m_font->printString(m_sWidth/2 - 95, (m_sHeight/2 - m_sHeight/4) + 42, "Press Space to jump");
	m_font->printString(m_sWidth/2 - 165, (m_sHeight/2 - m_sHeight/4) + 56, "Hold right click to charge a shot");
	m_font->printString(m_sWidth/2 - 75, (m_sHeight/2 - m_sHeight/4) + 70, "Release to fire");
}

void OptionsScreen::processKeyUp(int key){
	switch (key){
		default:
			break;
	}
}

void OptionsScreen::processKeyDown(int key){
	switch (key){
		default:
			break;
	}
}

void OptionsScreen::processMouse(int key, int state){
	switch (key){
	case WM_LBUTTONDOWN:
		if(m_btn->checkArea(m_mousePos.x, m_mousePos.y)){
			SceneSelect::getInstance(m_hdc).setScene(START, m_hdc);
		}

		break;
		default:
			break;
	}
}