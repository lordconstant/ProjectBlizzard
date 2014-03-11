#include "SceneSelect.h"


SceneSelect::SceneSelect(){
	setScene(START);
}


SceneSelect::~SceneSelect(){
}

SceneSelect& SceneSelect::getInstance(){
	static SceneSelect instance;
	return instance;
}

void SceneSelect::setScene(int scene){
	if (scene >= SCENE_COUNT || scene < 0){
		return;
	}

	if (m_curScene){
		delete m_curScene;
	}

	switch (scene){
	case START:
		m_curScene = new StartScreen;
		break;
	case OPTIONS:
		m_curScene = new StartScreen;
		break;
	case LOBBY:
		m_curScene = new StartScreen;
		break;
	case GAME:
		m_curScene = new StartScreen;
		break;
	case END:
		m_curScene = new StartScreen;
		break;
	default:
		break;
	}
}

Scene* SceneSelect::getCurScene(){
	return m_curScene;
}