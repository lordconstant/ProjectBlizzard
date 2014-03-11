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
	sceneSel = &SceneSelect::getInstance();
	sceneSel->getCurScene()->initialise();
}

void Game::Shutdown(){
	DebugOut("Game::Shutdown being called");
}

void Game::Update(){
	TimeControl::getInstance().updateTime();

	sceneSel->getCurScene()->update();
}

// Render the objects in their current state.
void Game::Render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	sceneSel->getCurScene()->render();

	glFlush();
}