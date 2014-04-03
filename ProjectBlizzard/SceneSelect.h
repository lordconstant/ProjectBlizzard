#pragma once
#include "Scene.h"
#include "StartScreen.h"
#include "GameScreen.h"
#include "OptionsScreen.h"

enum SCENES {START = 0, OPTIONS, LOBBY, GAME, END, SCENE_COUNT};

class SceneSelect{
	Scene* m_curScene;
public:
	~SceneSelect();

	static SceneSelect& getInstance();

	void setScene(int scene);

	Scene* getCurScene();
private:
	SceneSelect();
};

