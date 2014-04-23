#include "OptionsScreen.h"


OptionsScreen::OptionsScreen(void){
}


OptionsScreen::~OptionsScreen(void){
}

void OptionsScreen::initialise(){
	m_cam = new Camera();

	m_btn = new Button3D("new_game", 1, 0.25f, 0.0f);
	m_btn->getCuboid()->setPos(0, 0, -1);

	m_cam->move()->setPos(0, 0, 0);
}

void OptionsScreen::update(float mouseX, float mouseY){
	updateMouse(mouseX, mouseY);
	m_btn->update(m_mousePos.x, m_mousePos.y);
}

void OptionsScreen::render(){
	m_btn->render();
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
			SceneSelect::getInstance().setScene(START);
		}

		break;
		default:
			break;
	}
}