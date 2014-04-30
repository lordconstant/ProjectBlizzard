#include "StartScreen.h"


StartScreen::StartScreen(HDC hdc) : Scene(hdc){
}

StartScreen::~StartScreen(){
	for(int i = 0; i < m_btns.size(); i++){
		if(m_btns[i]){
			delete m_btns[i];
		}
	}

	if(m_cam){
		delete m_cam;
	}
}

void StartScreen::initialise(){
	m_cam = new Camera();
	m_cam->move()->setPos(0, 0, 0);

	for (int i = 0; i < 3; i++){
		if(i == 0){
			m_btns.push_back(new Button3D("new_game", 1.0f, 0.25f, 0.00f));
		}

		if(i == 1){
			m_btns.push_back(new Button3D("options", 1.0f, 0.25f, 0.00f));
		}

		if(i == 2){
			m_btns.push_back(new Button3D("quit_game", 1.0f, 0.25f, 0.00f));
		}
		m_btns.back()->getCuboid()->setPos(-0.9f, -0.25f - (i*0.35f), 0.0f);
	}

	m_sEngine->play2D("Sounds/Monkeys Spinning Monkeys.mp3", true);
}

void StartScreen::update(float mouseX, float mouseY){
	updateMouse(mouseX, mouseY);

	for (int i = 0; i < m_btns.size(); i++){
		m_btns[i]->update(m_mousePos.x, m_mousePos.y);
	}
}

void StartScreen::render(){
	m_cam->update();

	for (int i = 0; i < m_btns.size(); i++){
		m_btns[i]->render();
	}
}

void StartScreen::render2D(){

}

void StartScreen::processKeyUp(int key){
	switch (key){
		default:
			break;
	}

}

void StartScreen::processKeyDown(int key){
	switch (key){
		default:
			break;
	}
}

void StartScreen::processMouse(int key, int state){
	switch(key){
		case WM_LBUTTONDOWN:
			if(m_btns[0]->checkArea(m_mousePos.x, m_mousePos.y)){
				SceneSelect::getInstance(m_hdc).setScene(GAME, m_hdc);
				break;
			}

			if(m_btns[1]->checkArea(m_mousePos.x, m_mousePos.y)){
				SceneSelect::getInstance(m_hdc).setScene(OPTIONS, m_hdc);
				break;
			}

			if(m_btns[2]->checkArea(m_mousePos.x, m_mousePos.y)){
				PostQuitMessage(0);
				break;
			}

			break;
		default:
			break;
	}
}