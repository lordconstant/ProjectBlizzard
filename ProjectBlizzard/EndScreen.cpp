#include "EndScreen.h"


EndScreen::EndScreen(HDC hdc) : Scene(hdc){
}


EndScreen::~EndScreen(void){
	for (int i = 0; i < NBR_BTNS; i++){
		delete m_btns[i];
	}

	if (m_largeFont){
		delete m_largeFont;
	}

	if (m_cam){
		delete m_cam;
	}
}

void EndScreen::initialise(){
	m_cam = new Camera();

	m_btns[0] = new Button3D("new_game", 1.0f, 0.25f, 0.0f);
	m_btns[1] = new Button3D("main_menu", 1.0f, 0.25f, 0.0f);
	m_btns[2] = new Button3D("quit_game", 1.0f, 0.25f, 0.0f);

	m_btns[0]->getCuboid()->setPos(-1.25f, 0.0f, 0.0f);
	m_btns[1]->getCuboid()->setPos(1.25f, 0.0f, 0.0f);
	m_btns[2]->getCuboid()->setPos(0.0f, -1.0f, 0.0f);

	m_largeFont = new BFont(m_hdc, "Courier", 50);
}

void EndScreen::update(float mouseX, float mouseY){
	updateMouse(mouseX, mouseY);

	for (int i = 0; i < NBR_BTNS; i++){
		m_btns[i]->update(m_mousePos.x, m_mousePos.y);
	}
}

void EndScreen::render(){
	m_cam->update();

	for (int i = 0; i < NBR_BTNS; i++){
		m_btns[i]->render();
	}
}

void EndScreen::render2D(){
	m_largeFont->setColor(1.0f, 1.0f, 1.0f);
	string txt1, txt2, txt3;
	txt1 = " is the winner";
	txt2 = SceneSelect::getInstance(m_hdc).getWinner() + txt1;
	txt3 = "CONGRATULATIONS";

	char s[255];
	strcpy_s(s, txt2.c_str());
	int px = m_sWidth / 2 - (txt2.size() * 29) / 2;
	m_largeFont->printString(px, m_sHeight / 2 - m_sHeight / 3, s);

	strcpy_s(s, txt3.c_str());
	m_largeFont->printString(m_sWidth / 2 - (txt3.size() * 29) / 2, m_sHeight / 2 - m_sHeight / 4, s);
}

void EndScreen::processKeyUp(int key){
	switch (key){
	default:
		break;
	}
}

void EndScreen::processKeyDown(int key){
	switch (key){
	default:
		break;
	}
}

void EndScreen::processMouse(int key, int state){
	switch (key){
	case WM_LBUTTONDOWN:
		if (m_btns[0]->checkArea(m_mousePos.x, m_mousePos.y)){
			SceneSelect::getInstance(m_hdc).setWinner("default");
			SceneSelect::getInstance(m_hdc).setScene(GAME, m_hdc);
			break;
		}

		if (m_btns[1]->checkArea(m_mousePos.x, m_mousePos.y)){
			SceneSelect::getInstance(m_hdc).setWinner("default");
			SceneSelect::getInstance(m_hdc).setScene(START, m_hdc);
			break;
		}

		if (m_btns[2]->checkArea(m_mousePos.x, m_mousePos.y)){
			PostQuitMessage(0);
			break;
		}
		break;
	default:
		break;
	}
}
