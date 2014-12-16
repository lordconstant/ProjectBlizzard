#include "SceneSelect.h"

SceneSelect::SceneSelect(HDC hdc){
	m_winner = "Default";
	setScene(START, hdc);
}


SceneSelect::~SceneSelect(){
	if (m_curScene){
		delete m_curScene;
	}
}

SceneSelect& SceneSelect::getInstance(HDC hdc){
	static SceneSelect instance(hdc);
	return instance;
}

void SceneSelect::setScene(int scene, HDC hdc){
	if (scene >= SCENE_COUNT || scene < 0){
		return;
	}

	if (m_curScene){
		delete m_curScene;
	}

	switch (scene){
	case START:
		m_curScene = new StartScreen(hdc);
		break;
	case OPTIONS:
		m_curScene = new OptionsScreen(hdc);
		break;
	case LOBBY:
		m_curScene = new StartScreen(hdc);
		break;
	case GAME:
		m_curScene = new GameScreen(hdc);
		break;
	case END:
		m_curScene = new EndScreen(hdc);
		break;
	default:
		break;
	}

	m_curScene->initialise();
}

Scene* SceneSelect::getCurScene(){
	return m_curScene;
}

string SceneSelect::getWinner(){
	return m_winner;
}

void SceneSelect::setWinner(string winner){
	m_winner = winner;
}