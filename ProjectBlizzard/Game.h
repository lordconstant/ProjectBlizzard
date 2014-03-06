#pragma once
#include "BaseGame.h"
#include "DebugPrint.h"
#include "Sphere.h"
#include "Cube.h"
#include "Button3D.h"
#include "Camera.h"
#include "TimeControl.h"
#include "Explosion.h"

#include <vector>

#include <string>
using namespace std;

// forward declaration
class BaseObject;

/**
The class inherits from BaseGame and provides the game data model and the game logic
*/
class Game : public BaseGame{
	// Allow event handler direct access to these attributes
	// (copied from BaseGame since friendship is not inherited)
	friend LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
	// HERE WE DECLARE ANY FONTS, TIMERS OR OTHER VARIABLES WE WANT
	int mouseX, mouseY;

	// HERE WE DECLARE ANY GAME OBJECTS ("BASEOBJECTS") AND CREATE THEM
	// IN THE INITIALISE METHOD
	vector<Model*> m_sphere;
	Camera* m_cam;
	Explosion* explo;
	Button3D* m_btn;
public:
	Game(void);
	virtual ~Game(void);

	/**
	Use this method to perform any first time initialisation of OpenGL
	*/
	void InitOpenGL();

	/**
	Use this method to create timers, fonts and all game objects. Do NOT 
	execute any OpenGL commands in this method, use initOpenGL instead.
	*/
	void Initialise();

	/**
	Use this method to perform any clean up of objects created for 
	the game - including fonts and timers.
	*/
	void Shutdown();

	/**
	Use this method to create any game objects and initialise the
	game's state
	*/
	bool InitGame();

	/**
	Use this method to update the game's state, but do not use it for rendering
	*/
	void Game::Update();

	/**
	The main rendering method - renders a single frame
	*/
	void Game::Render();
};
