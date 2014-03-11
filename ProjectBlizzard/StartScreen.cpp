#include "StartScreen.h"


StartScreen::StartScreen(){
}


StartScreen::~StartScreen(){
}

void StartScreen::initialise(){
	m_cam = new Camera();

	for (int x = 0; x < 32; x++){
		for (int y = 0; y < 32; y++){
			m_cubes.push_back(new Cube(1.0f));
			m_cubes.back()->setPos(x, y, 0.0f);
		}
	}
}

void StartScreen::update(){
	//m_cam->update();
}

void StartScreen::render(){
	m_cam->update();

	for (int i = 0; i < m_cubes.size(); i++){
		m_cubes[i]->Render();
	}
}

void StartScreen::processKey(int key){

}