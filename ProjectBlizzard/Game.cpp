#include "Game.h"

Game::Game(void){
	mouseX = mouseY = 0;
}

Game::~Game(void){
}

void Game::InitOpenGL(){
	DebugOut("Game::InitOpenGL being called");
	Set3D(80, 0.1f, 100.0f);
}

void Game::Initialise(){
	DebugOut("Game::Initialise being called");
	char s[256];
	sprintf_s(s, "Version : %s", gluGetString(GLU_VERSION));
	DebugOut(s);

	sceneSel = &SceneSelect::getInstance(hDC);
}

void Game::Shutdown(){
	DebugOut("Game::Shutdown being called");
}

void Game::Update(){
	TimeControl::getInstance().updateTime();

	if (sceneSel->getCurScene()){
		sceneSel->getCurScene()->update(mouseX, mouseY);
	}

	if (sceneSel->getCurScene()){
		sceneSel->getCurScene()->setScreenSize(m_width, m_height);
	}
}

// Render the objects in their current state.
void Game::Render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	if (sceneSel->getCurScene()){
		sceneSel->getCurScene()->render();
	}

	Render2D();

	glFlush();
}

void Game::Render2D(){
	Set2D(0, m_width, m_height, 0); // Change to 2D view and use 1:1 pixel resolution with [0,0] origin being at the top-left corner.
	glDisable(GL_DEPTH_TEST);  // Disable depth testing so the HUD will not be hidden by the 3D graphics
	glDisable(GL_BLEND);
	glDisable(GL_LIGHTING);
	if (sceneSel->getCurScene()){
		sceneSel->getCurScene()->render2D();
	}

	Set3D(80, 0.1f, 100.0f); // Set back to 3D
}