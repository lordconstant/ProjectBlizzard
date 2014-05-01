#pragma once
#include "Scene.h"
#include "StartScreen.h"
#include "GameScreen.h"
#include "OptionsScreen.h"
#include "EndScreen.h"

enum SCENES {START = 0, OPTIONS, LOBBY, GAME, END, SCENE_COUNT};

class SceneSelect{
	Scene* m_curScene;
	string m_winner;
public:
	~SceneSelect();

	static SceneSelect& getInstance(HDC hdc);

	void setScene(int scene, HDC hdc);

	Scene* getCurScene();

	string getWinner();

	void setWinner(string winner);
private:
	SceneSelect(HDC hdc);
};

