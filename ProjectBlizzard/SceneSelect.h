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

	static SceneSelect& getInstance(HDC hdc);

	void setScene(int scene, HDC hdc);

	Scene* getCurScene();
private:
	SceneSelect(HDC hdc);
};

