#include "Game.h"

Game::Game(void){
	mouseX = mouseY = 0;
}

Game::~Game(void){
}

void Game::InitOpenGL(){
	DebugOut("Game::InitOpenGL being called");
	Set3D();
}

void Game::Initialise(){
	DebugOut("Game::Initialise being called");
	for(int i = 0; i < 256; i++){
		for(int j = 0; j < 256; j++){
			Model* temp;
			temp = new Rect(1, 0.05, 0.05, 0.05);
			temp->setPos(0.05 * i, 0.05 * j, 0);
			m_sphere.push_back(temp);
			temp = NULL;
		}
	}

	m_cam = new Camera();
	explo = new Explosion(m_sphere, m_sphere);
	m_btn = new Button3D("Images/Buttons/new_game.bmp", 4, 1, 0.05);
	m_btn->getRect()->setPos(6.4, 6.4, 0);
}

void Game::Shutdown(){
	DebugOut("Game::Shutdown being called");
}

void Game::Update(){
	TimeControl::getInstance().updateTime();

	m_btn->update(mouseX, mouseY);
}

// Render the objects in their current state.
void Game::Render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//gluLookAt(10.0f, 10.0f, 10.0f, 5.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	m_cam->update();
	for(int i = 0; i < m_sphere.size(); i++){
		m_sphere[i]->Render();
	}

	m_btn->render();

	glFlush();
}