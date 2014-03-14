#include "GameScreen.h"


GameScreen::GameScreen(){
}


GameScreen::~GameScreen(){
}

void GameScreen::initialise(){
	m_cam = new Camera();
	m_cam->move()->setPos(0, 1, 0);

	m_land = new Rect(1, 10, 0.05, 10);

	m_timer = new Timer();
	m_timer->play();
}

void GameScreen::update(float mouseX, float mouseY){
	updateMouse(mouseX, mouseY);
	m_cam->firstPerson(2, mouseX, mouseY, m_sHeight, m_sWidth);
	m_timer->update();
	char s[255];
	sprintf(s, "%.2f", m_timer->getElapsedTime());
	DebugOut(s);
}

void GameScreen::render(){
	m_cam->update();

	m_land->Render();
}

void GameScreen::processKeyUp(int key){
	switch (key){
	case VK_W:
		m_cam->move()->forward(false);
		break;
	case VK_S:
		m_cam->move()->backward(false);
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

void GameScreen::processKeyDown(int key){
	switch (key){
	case VK_W:
		m_cam->move()->forward(true);
		break;
	case VK_S:
		m_cam->move()->backward(true);
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

void GameScreen::processMouse(int key, int state){
	switch (key){
	case WM_LBUTTONDOWN:
		m_timer->reset();
		break;
	case WM_RBUTTONDOWN:
		m_timer->play();
		break;
	case WM_MOUSEWHEEL:
		((short)HIWORD(state) < 0) ? m_cam->move()->forward(true) : m_cam->move()->backward(true);
		break;
	default:
		break;
	}
}