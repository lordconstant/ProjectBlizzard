#include "GameScreen.h"

GameScreen::GameScreen(HDC& hdc) : Scene(hdc){
}

GameScreen::~GameScreen(){
	if(m_cam){
		delete m_cam;
	}

	if(m_land){
		m_land->clear();
		delete m_land;
	}

	if (m_teams.size() > 0){
		m_teams.clear();
	}

	if (m_gameTimer){
		delete m_gameTimer;
	}

	if (m_turnTimer){
		delete m_turnTimer;
	}

	if (m_endTurnTimer){
		delete m_endTurnTimer;
	}
}

void GameScreen::initialise(){
	glewInit();

	m_cam = new Camera();
	m_cam->move()->setPos(0, 1, 0);

	m_turnTimer = new Timer();
	m_gameTimer = new Timer();
	m_endTurnTimer = new Timer();

	m_largeFont = new BFont(m_hdc, "Courier", 50);
	m_skySphere = new Sphere(10);
	m_skySphere->setTexture("Images/sky_sunbeams1.bmp");

	m_water = new Water("Images/water.bmp", 20, 30);
	m_quadTree = NULL;

	m_land = NULL;
	m_explo = NULL;
	m_curUnit = NULL;

	m_fired = m_hitTerrain = false;

	m_curTeam = 0;

	for (int i = 0; i < NBR_TEAMS; i++){
		m_teams.push_back(new Team(i));
		m_teams[i]->setCurrentUnit(0);

		Vector tCol = Vector(random::rnd.number(1.0f), random::rnd.number(1.0f), random::rnd.number(1.0f));
		for (int j = 0; j < NBR_UNITS; j++){
			Cube* temp;

			temp = new Cube(0.048f, tCol.x, tCol.y, tCol.z);
			char s[255];
			sprintf(s, "Pete %i", i);
			m_teams[i]->addUnit(new Unit(s, temp, 100, 2.0f));
		}
	}

	m_sEngine->play2D("Sounds/Electrodoodle.mp3", true);

	m_landCube = new Cube(0.05f, 0.0f, 0.8f, 0.25f);

	int gameType = rand() % 9;
	createGame(gameType);

	m_water->setPos(Vector(m_width / 2, 0 - m_landCube->getScale()/2, 0));

	changeUnit();
}

void GameScreen::update(float mouseX, float mouseY){
	updateMouse(mouseX, mouseY);

	for (int i = 0; i < NBR_TEAMS; i++){
		m_teams[i]->update();
	}

	//Causes an explosion at where the curShor hits
	if (m_curUnit->getWeapon()->getCurShot()){
		if (m_quadTree->processCollisions(m_curUnit->getWeapon()->getCurShot()->getModel())){
			if (m_explo){
				float exploForce = 0.0f;

				exploForce = m_curUnit->getWeapon()->getPower() * 0.5f;

				if (exploForce < 0.2f){
					exploForce = 0.2f;
				}

				m_explo->circularExplosion(Vector(m_curUnit->getWeapon()->getCurShot()->getModel()->getPos().x, m_curUnit->getWeapon()->getCurShot()->getModel()->getPos().y, 1), exploForce, m_curUnit->getWeapon()->getDamage() * m_curUnit->getWeapon()->getPower(), *m_quadTree);
				m_curUnit->getWeapon()->hitObject(NULL, 0, 0);
				m_hitTerrain = true;
				m_endTurnTimer->resetTimer();
			}
		}
	}

	for (int i = 0; i < NBR_TEAMS; i++){
		for (int j = 0; j < NBR_UNITS; j++){
			Unit* tempUnit = m_teams[i]->getUnit(j);

			//Smooths out physics
			tempUnit->getModel()->setPos(tempUnit->getPhysics()->nextPos());

			//Checks to see if collision occurs between current position and next
			BoxCollider* tempCol = (BoxCollider*)m_quadTree->processCollisions(tempUnit->getModel(), tempUnit->getPhysics()->nextPos());

			if (tempCol){
				//When going left, collide with right of terrain
				if (tempUnit->getPhysics()->getVelX() < 0){
					if (tempCol->hitright((BoxCollider*)tempUnit->getModel()->getCollider())){
						tempUnit->getPhysics()->setAccelX(0.0f);
						tempUnit->getPhysics()->setVelocityX(0.0f);
					}
				}

				//When going right collide with left of terrain
				if (tempUnit->getPhysics()->getVelX() > 0){
					if (tempCol->hitLeft((BoxCollider*)tempUnit->getModel()->getCollider())){
						tempUnit->getPhysics()->setAccelX(0.0f);
						tempUnit->getPhysics()->setVelocityX(0.0f);
					}
				}

				//When falling collide with top of terrain
				if (tempUnit->getPhysics()->getVelY() < 0){
					if (tempCol->hitTop((BoxCollider*)tempUnit->getModel()->getCollider())){
						tempUnit->getPhysics()->setAccelY(0.0f);
						tempUnit->getPhysics()->setVelocityY(0.0f);

						tempUnit->getPhysics()->isGrounded(true);
					}
				}

				//When jumping collide with bottom of terrain
				if (tempUnit->getPhysics()->getVelY() > 0){
					if (tempCol->hitBottom((BoxCollider*)tempUnit->getModel()->getCollider())){
						tempUnit->getPhysics()->setAccelY(0.0f);
						tempUnit->getPhysics()->setVelocityY(0.0f);
					}
				}
			}
			else{
				//If not colliding the unit is falling
				tempUnit->getPhysics()->isGrounded(false);
			}

			//If the unit goes below the water level they die
			if (tempUnit->getPosition().y < WATER_LEVEL && !tempUnit->isDead()){
				tempUnit->setCurHealth(0);

				if (m_curUnit == tempUnit){
					changeUnit();
				}
			}

			//When a unit is below 0 health set them to dead and change unit
			if (!tempUnit->isDead() && tempUnit->getCurHealth() <= 0){
				tempUnit->setCurHealth(0);

				if (m_curUnit == tempUnit){
					changeUnit();
				}
			}

			//If the unit is alive, run its update
			if (!tempUnit->isDead()){
				tempUnit->update(m_mousePos);

				tempUnit = NULL;
			}
		}
	}

	//Keeps camera on the unit
	m_cam->move()->setPos(m_curUnit->getPosition().x, m_curUnit->getPosition().y, m_cam->move()->getPos().z);

	if (m_cam->getPos().y <= m_landCube->getScale() * 2){
		m_cam->move()->setPos(m_cam->getPos().x, m_landCube->getScale() * 2, m_cam->getPos().z);
	}

	m_skySphere->setPos(m_cam->getPos().x, m_cam->getPos().y, 1);

	//If the game lasts longer than its allowed its a draw
	if (m_gameTimer->getElapsedTime() >= GAME_TIME){
		SceneSelect::getInstance(m_hdc).setWinner("draw");
		SceneSelect::getInstance(m_hdc).setScene(END, m_hdc);
		return;
	}


	int teamsAlive = 0;
	string teamName = "draw"; //if it does'nt change the game is a draw

	//Checks to see how many teams are alive
	for (int i = 0; i < NBR_TEAMS; i++){
		if (!m_teams[i]->isDead()){
			teamsAlive++;
			teamName = m_teams[i]->getName();
		}
	}

	//If there arent 2 teams alive, gameover
	if (teamsAlive < 2){
		SceneSelect::getInstance(m_hdc).setWinner(teamName);
		SceneSelect::getInstance(m_hdc).setScene(END, m_hdc);
		return;
	}

	//Changes unit at the end of the turn
	if (m_turnTimer->getElapsedTime() >= TURN_TIME){
		changeUnit();
	}

	//Changes the unit after it hits the terrain or after firing a projectile
	if (m_hitTerrain && m_endTurnTimer->getElapsedTime() >= HIT_TURN_TIME || m_fired && m_endTurnTimer->getElapsedTime() >= FIRED_TURN_TIME){
		changeUnit();
	}
}

void GameScreen::render(){
	m_cam->update();

	m_skySphere->Render();

	m_water->render();

	for (int i = 0; i < NBR_TEAMS; i++){
		m_teams[i]->render();
	}

	if (m_land){
		for (int i = 0; i < m_land->size(); i++){
			m_landCube->setPos(m_land->at(i));
			m_landCube->Render();
		}
	}

	if (m_curUnit->getWeapon()->getPowerGen()){
		m_curUnit->getWeapon()->generatePower();
	}
	
	for (int i = 0; i < NBR_TEAMS; i++){
		for (int j = 0; j < NBR_UNITS; j++){
			if (!m_teams[i]->getUnit(j)->isDead()){
				m_teams[i]->getUnit(j)->renderHealthBar();
			}
		}
	}
	//m_quadTree->render();
}

void GameScreen::render2D(){
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.0f, 0.0f, 0.8f, 0.5f);
		glBegin(GL_QUADS);
			glVertex2f(m_sWidth, m_sHeight);
			glVertex2f(m_sWidth, m_sHeight - 50);
			glVertex2f(m_sWidth - 100, m_sHeight - 50);
			glVertex2f(m_sWidth - 100, m_sHeight);
		glEnd();

		glBegin(GL_QUADS);
			glVertex2f(m_sWidth/2 - 50, 0);
			glVertex2f(m_sWidth/2 - 50, 50);
			glVertex2f(m_sWidth/2 + 50, 50);
			glVertex2f(m_sWidth/2 + 50, 0);
		glEnd();
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDisable(GL_BLEND);

	int gap = m_sHeight / 20;
	for (int i = 0; i < NBR_TEAMS; i++){
		m_teams[i]->renderHealthBar(m_hdc, m_sWidth / 4, m_sHeight - (gap * (i + 1)), m_sWidth / 2, m_sHeight / 40);
	}

	m_largeFont->setColor(1.0f, 1.0f, 1.0f);
	char s[255];
	sprintf(s, "%i", (TURN_TIME - (int)m_turnTimer->getElapsedTime()));
	m_largeFont->printString(m_sWidth - 100, m_sHeight, s);

	sprintf(s, "%i", (GAME_TIME - (int)m_gameTimer->getElapsedTime()));
	m_largeFont->printString(m_sWidth/2 - 50, 50, s);
}

void GameScreen::processKeyUp(int key){
	switch (key){
	case VK_W:
		break;
	case VK_S:
		break;
	case VK_A:
		m_curUnit->getPhysics()->setAccelX(0);
		break;
	case VK_D:
		m_curUnit->getPhysics()->setAccelX(0);
		break;
	default:
		break;
	}

}

void GameScreen::processKeyDown(int key){
	switch (key){
	case VK_W:
		break;
	case VK_S:
		break;
	case VK_A:
		if (m_curUnit->getPhysics()->getVelX() > -0.5f){
			m_curUnit->getPhysics()->setAccelX(-1);
		}

		break;
	case VK_D:
		if (m_curUnit->getPhysics()->getVelX() < 0.5f){
			m_curUnit->getPhysics()->setAccelX(1);
		}
		break;
	case VK_SPACE:
		m_curUnit->jump();
		break;
	default:
		break;
	}
}

void GameScreen::processMouse(int key, int state){
	switch (key){
	case WM_LBUTTONDOWN:
		if (m_explo){
			m_explo->circularExplosion(Vector(m_mousePos.x, m_mousePos.y, 1), 0.5f, 5, *m_quadTree);
		}
		break;
	case WM_RBUTTONDOWN:
		if (!m_fired){
			m_curUnit->getWeapon()->setPowerGen(true);
		}
		break;
	case WM_RBUTTONUP:
		if (!m_fired){
			m_curUnit->getWeapon()->setPowerGen(false);
			m_curUnit->fireWeapon();
			m_fired = true;
			m_endTurnTimer->resetTimer();
		}
		break;
	case WM_MOUSEWHEEL:
		if (state < 0){
			if (m_cam->getPos().z < 0.5f){
				m_cam->move()->backward(true);
			}
		}else{
			if (m_cam->getPos().z > -1.0f){
				m_cam->move()->forward(true);
			}
		}
		break;
	default:
		break;
	}
}

void GameScreen::createGame(int type){
	genTerrain(type);

	m_width = m_height = 0;

	//Makes sure we are getting the first unit
	for (int i = 0; i < NBR_TEAMS; i++){
		m_teams[i]->setCurrentUnit(0);
	}

	m_curTeam = 0;

	//Sets the overall width and height of the terrain
	for (int i = 0; i < m_land->size(); i++){
		if (m_land->at(i).x > m_width){
			m_width = m_land->at(i).x;
		}

		if (m_land->at(i).y > m_height){
			m_height = m_land->at(i).y;
		}
	}

	BuildQuadTree();

	for (int i = 0; i < NBR_TEAMS; i++){
		for (int j = 0; j < NBR_UNITS; j++){
			placeUnit(m_teams[i]->getUnit(j));
		}
	}
}

void GameScreen::genTerrain(int type){
	//Removes existing land
	if (m_land){
		delete m_land;
	}

	//Generates a new map from the selected type
	m_land = new vector<Vector>;
	*m_land = m_tGen.generateMap(type);

	//Initialises the explosions
	if (!m_explo){
		m_explo = new Explosion(*m_land, m_teams);
	}

	m_explo->defineTerrain(*m_land);
}

void GameScreen::placeUnit(Unit* unit){
	bool done = false, regen = false;
	int attempts = 0;

	while (!done){
		unit->setPosition(random::rnd.number(m_width), random::rnd.number(m_height), 1);

		for (int i = 0; i < m_land->size(); i++){
			if ((unit->getPosition().x - 0.025f) < m_land->at(i).x + (m_landCube->getScale() / 2) && (unit->getPosition().x + 0.025f) > m_land->at(i).x - (m_landCube->getScale() / 2)){
				unit->setPosition(m_land->at(i).x, m_land->at(i).y + m_landCube->getScale(), 1);

				for (int j = 0; j < m_land->size(); j++){
					if (unit->getPosition().x == m_land->at(j).x){
						if (unit->getPosition().y < m_land->at(j).y){
							float temp;

							temp = m_land->at(j).y - unit->getPosition().y;

							if (temp <= 0.1f){
								unit->setPosition(m_land->at(j).x, m_land->at(j).y, 1);
							}
						}
					}
				}

				if (unit->getPosition().y < m_height){
					done = true;
				}

				for (int k = 0; k < NBR_TEAMS; k++){
					for (int l = 0; l < NBR_UNITS; l++){
						if (m_teams[k]->getUnit(l) == unit){
							continue;
						}

						if (m_teams[k]->getUnit(l)->getPosition() == unit->getPosition()){
							done = false;
						}
					}
				}

				break;
			}
		}

		if (attempts >= 100){
			done = true;
			regen = true;
		}

		attempts++;
	}

	if (regen){
		createGame(m_tGen.getCurrentType());
	}
	char s[255];
	sprintf(s, "Before: %3.3f", unit->getPosition().y);
	DebugOut(s);
	unit->setPosition(unit->getPosition().x, unit->getPosition().y + 0.3f, 1);
	sprintf(s, "After: %3.3f", unit->getPosition().y);
	DebugOut(s);
}

void GameScreen::changeUnit(){
	bool run = false;

	if (m_curUnit){
		m_curUnit->getPhysics()->setAccelX(0);
	}

	m_teams[m_curTeam]->update();

	m_curUnit = m_teams[m_curTeam]->getUnit(m_teams[m_curTeam]->getCurrentUnit());

	while (m_curUnit->isDead() || !run){
		m_curUnit = m_teams[m_curTeam]->getUnit(m_teams[m_curTeam]->getCurrentUnit());

		if (m_teams[m_curTeam]->getCurrentUnit() == NBR_UNITS - 1){
			m_teams[m_curTeam]->setCurrentUnit(0);
		}
		else{
			m_teams[m_curTeam]->setCurrentUnit(m_teams[m_curTeam]->getCurrentUnit() + 1);
		}

		int teamsAlive = 0;
		string teamName = "draw"; //if it does'nt change the game is a draw

		for (int i = 0; i < NBR_TEAMS; i++){
			if (!m_teams[i]->isDead()){
				teamsAlive++;
				teamName = m_teams[i]->getName();
			}
		}

		if (teamsAlive < 2){
			SceneSelect::getInstance(m_hdc).setWinner(teamName);
			SceneSelect::getInstance(m_hdc).setScene(END, m_hdc);
			break;
		}

		run = true;
	}

	if (m_curTeam == NBR_TEAMS - 1){
		m_curTeam = 0;
	}
	else if (m_curTeam < NBR_TEAMS){
		m_curTeam++;
	}

	m_turnTimer->resetTimer();
	m_hitTerrain = false;
	m_fired = false;
}

void GameScreen::BuildQuadTree(){
	if (m_quadTree){
		delete m_quadTree;
		m_quadTree = NULL;
	}

	m_quadTree = new QuadTree();

	m_quadTree->buildFullTree(NBR_LEVELS, (m_width + 0.1f) / 2, (m_height + 0.1f) / 2, 0.5f, m_width + 0.1f, m_height + 0.1f, 1);

	for (int i = 0; i < m_land->size(); i++){
		BoxCollider* temp = new BoxCollider;
		temp->setDimension(m_landCube->getScale(), m_landCube->getScale(), m_landCube->getScale());
		temp->setPos(m_land->at(i));
		m_quadTree->addObject(temp);
	}
}