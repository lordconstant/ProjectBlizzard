#include "StartScreen.h"


StartScreen::StartScreen(){
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
		m_btns.back()->getRect()->setPos(-0.9f, -0.25f - (i*0.35f), 0.0f);
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

void StartScreen::processKeyUp(int key){
	switch (key){
		case VK_W:
			m_cam->move()->up(false);
			break;
		case VK_S:
			m_cam->move()->down(false);
			break;
		case VK_A:
			m_cam->move()->left(false);
			break;
		case VK_D:
			m_cam->move()->right(false);
			break;
		default:
			break;
	}

}

void StartScreen::processKeyDown(int key){
	switch (key){
		case VK_W:
			m_cam->move()->up(true);
			break;
		case VK_S:
			m_cam->move()->down(true);
			break;
		case VK_A:
			m_cam->move()->left(true);
			break;
		case VK_D:
			m_cam->move()->right(true);
			break;
		default:
			break;
	}
}

void StartScreen::processMouse(int key, int state){
	switch(key){
		case WM_LBUTTONDOWN:
			if(m_btns[0]->checkArea(m_mousePos.x, m_mousePos.y)){
				SceneSelect::getInstance().setScene(GAME);
				break;
			}

			if(m_btns[1]->checkArea(m_mousePos.x, m_mousePos.y)){
				SceneSelect::getInstance().setScene(OPTIONS);
				break;
			}

			if(m_btns[2]->checkArea(m_mousePos.x, m_mousePos.y)){
				PostQuitMessage(0);
				break;
			}

			break;
		case WM_RBUTTONDOWN:
			break;
		case WM_MOUSEWHEEL:
			((short) HIWORD(state) < 0) ? m_cam->move()->forward(true) : m_cam->move()->backward(true);
			break;
		default:
			break;
	}
}