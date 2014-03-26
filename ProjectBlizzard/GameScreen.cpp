#include "GameScreen.h"


GameScreen::GameScreen(){
}


GameScreen::~GameScreen(){
	if(m_cam){
		delete m_cam;
	}

	if(m_timer){
		delete m_timer;
	}

	if(m_land){
		delete m_land;
	}
}

void GameScreen::initialise(){
	m_cam = new Camera();
	m_cam->move()->setPos(0, 1, 0);

	m_land = NULL;

	//m_timer = new Timer();
	//m_timer->play();

	m_sEngine->play2D("Sounds/Electrodoodle.mp3");
}

void GameScreen::update(float mouseX, float mouseY){
	updateMouse(mouseX, mouseY);
	m_cam->firstPerson(2, mouseX, mouseY, m_sHeight, m_sWidth);
	//m_timer->update();
}

void GameScreen::render(){
	m_cam->update();

	if(m_land != NULL){
		for(int i = 0; i < m_land->size(); i++){
			m_land->at(i).Render();
		}
	}
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
	case VK_1:
		genTerrain(ISLANDS);
		break;
	case VK_2:
		genTerrain(LAND);
		break;
	case VK_3:
		genTerrain(CAVES);
		break;
	case VK_4:
		genTerrain(CAVE);
		break;
	case VK_SPACE:
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
		//m_timer->reset();
		break;
	case WM_RBUTTONDOWN:
		//m_timer->play();
		break;
	case WM_MOUSEWHEEL:
		((short)HIWORD(state) < 0) ? m_cam->move()->forward(true) : m_cam->move()->backward(true);
		break;
	default:
		break;
	}
}

void GameScreen::genTerrain(int type){
	if(m_land){
		delete m_land;
	}

	m_land = m_tGen.generateMap(type);
}