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
	for(int i = 0; i < 64; i++){
		for(int j = 0; j < 64; j++){
			Model* temp;
			temp = new Rect(1, 0.2, 0.2, 0.05);
			temp->setPos(0.2 * i, 0.2 * j, 0);
			m_sphere.push_back(temp);
			temp = NULL;
		}
	}

	m_cam = new Camera();
	explo = new Explosion(m_sphere, m_sphere);
}

void Game::Shutdown(){
	DebugOut("Game::Shutdown being called");
}

void Game::Update(){
	TimeControl::getInstance().updateTime();
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

	glFlush();
}