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

	m_quadTree = NULL;

	m_land = NULL;
	m_explo = NULL;
	
	m_fired = m_hitTerrain = false;

	m_curTeam = 0;

	for (int i = 0; i < NBR_TEAMS; i++){
		m_teams.push_back(new Team(i));

		m_teams[i]->setCurrentUnit(0);

		for (int j = 0; j < NBR_UNITS; j++){
			Cube* temp;

			if (i == 0){
				temp = new Cube(0.05f, 1.0f, 0.0f, 0.5f);
				m_teams[i]->addUnit(new Unit("Pete", temp, 100, 2.0f));
			}

			if (i == 1){
				temp = new Cube(0.05f, 0.0f, 0.0f, 1.0f);
				m_teams[i]->addUnit(new Unit("Pete", temp, 100, 2.0f));
			}

			m_teams[i]->getUnit(j)->setWepPos(temp->getScale() / 2, temp->getScale() / 2, 1);
		}
	}

	m_sEngine->play2D("Sounds/Electrodoodle.mp3", true);

	m_landCube = new Cube(0.05f, 0.0f, 1.0f, 0.25f);

	int gameType = rand() % 6;
	createGame(gameType);

	changeUnit();
}

void GameScreen::update(float mouseX, float mouseY){
	updateMouse(mouseX, mouseY);

	for (int i = 0; i < NBR_TEAMS; i++){
		m_teams[i]->update();
	}

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

			tempUnit->getModel()->setPos(tempUnit->getPhysics()->nextPos());

			BoxCollider* tempCol = (BoxCollider*)m_quadTree->processCollisions(tempUnit->getModel(), tempUnit->getPhysics()->nextPos());

			if (tempCol){
				if (tempUnit->getPhysics()->getVelX() < 0){
					if (tempCol->hitright((BoxCollider*)tempUnit->getModel()->getCollider())){
						tempUnit->getPhysics()->setAccelX(0.0f);
						tempUnit->getPhysics()->setVelocityX(0.0f);
					}
				}

				if (tempUnit->getPhysics()->getVelX() > 0){
					if (tempCol->hitLeft((BoxCollider*)tempUnit->getModel()->getCollider())){
						tempUnit->getPhysics()->setAccelX(0.0f);
						tempUnit->getPhysics()->setVelocityX(0.0f);
					}
				}

				if (tempUnit->getPhysics()->getVelY() < 0){
					if (tempCol->hitTop((BoxCollider*)tempUnit->getModel()->getCollider())){
						tempUnit->getPhysics()->setAccelY(0.0f);
						tempUnit->getPhysics()->setVelocityY(0.0f);

						tempUnit->getPhysics()->isGrounded(true);
					}
				}

				if (tempUnit->getPhysics()->getVelY() > 0){
					if (tempCol->hitBottom((BoxCollider*)tempUnit->getModel()->getCollider())){
						tempUnit->getPhysics()->setAccelY(0.0f);
						tempUnit->getPhysics()->setVelocityY(0.0f);
					}
				}
			}
			else{
				tempUnit->getPhysics()->isGrounded(false);
			}

			if (tempUnit->getPosition().y < 0 && !tempUnit->isDead()){
				tempUnit->setCurHealth(0);

				if (m_curUnit == tempUnit){
					changeUnit();
				}
			}

			if (!tempUnit->isDead() && tempUnit->getCurHealth() <= 0){
				tempUnit->setCurHealth(0);

				if (m_curUnit == tempUnit){
					changeUnit();
				}
			}

			if (!tempUnit->isDead()){
				tempUnit->update(m_mousePos);

				tempUnit = NULL;
			}
		}
	}

	m_cam->move()->setPos(m_curUnit->getPosition().x, m_curUnit->getPosition().y, m_cam->move()->getPos().z);

	if (m_gameTimer->getElapsedTime() >= GAME_TIME){
		SceneSelect::getInstance(m_hdc).setScene(START, m_hdc);
		return;
	}

	for (int i = 0; i < m_teams.size(); i++){
		if (m_teams[i]->isDead()){
			SceneSelect::getInstance(m_hdc).setScene(START, m_hdc);
			return;
		}
	}

	if (m_turnTimer->getElapsedTime() >= TURN_TIME){
		changeUnit();
	}

	if (m_hitTerrain && m_endTurnTimer->getElapsedTime() >= HIT_TURN_TIME || m_fired && m_endTurnTimer->getElapsedTime() >= FIRED_TURN_TIME){
		changeUnit();
	}
}

void GameScreen::render(){
	m_cam->update();
	
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
	glDisable(GL_BLEND);

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
		//m_cam->move()->up(false);
		//m_curUnit->move()->up(false);
		break;
	case VK_S:
		//m_cam->move()->down(false);
		//m_curUnit->move()->down(false);
		break;
	case VK_A:
		//m_cam->move()->left(false);
		//m_curUnit->move()->left(false);
		m_curUnit->getPhysics()->setAccelX(0);
		break;
	case VK_D:
		//m_cam->move()->right(false);
		//m_curUnit->move()->right(false);
		m_curUnit->getPhysics()->setAccelX(0);
		break;
	case VK_SPACE:
		m_curUnit->jump();
		break;
	case VK_1:
		createGame(ISLANDS);
		break;
	case VK_2:
		createGame(LAND);
		break;
	case VK_3:
		createGame(CAVES);
		break;
	case VK_4:
		createGame(CAVE);
		break;
	case VK_5:
		createGame(FLOATING_ISLAND);
		break;
	case VK_6:
		createGame(BRIDGE);
		break;
	case VK_7:
		createGame(RIDGES);
		break;
	case VK_8:
		createGame(VALLEY);
		break;
	case VK_9:
		createGame(CAVE2);
		break;
	default:
		break;
	}

}

void GameScreen::processKeyDown(int key){
	switch (key){
	case VK_W:
		//m_cam->move()->up(true);
		//m_curUnit->move()->up(true);
		break;
	case VK_S:
		//m_cam->move()->down(true);
		//m_curUnit->move()->down(true);
		break;
	case VK_A:
		//m_cam->move()->left(true);
		//m_curUnit->move()->left(true);
		if (m_curUnit->getPhysics()->getVelX() > -0.5f){
			m_curUnit->getPhysics()->setAccelX(-1);
		}

		break;
	case VK_D:
		//m_cam->move()->right(true);
		//m_curUnit->move()->right(true);
		if (m_curUnit->getPhysics()->getVelX() < 0.5f){
			m_curUnit->getPhysics()->setAccelX(1);
		}
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
	for (int i = 0; i < NBR_TEAMS; i++){
		m_teams[i]->setCurrentUnit(0);
	}

	m_curTeam = 0;

	for (int i = 0; i < m_land->size(); i++){
		if (m_land->at(i).x > m_width){
			m_width = m_land->at(i).x;
		}

		if (m_land->at(i).y > m_height){
			m_height = m_land->at(i).y;
		}
	}

	for (int i = 0; i < NBR_TEAMS; i++){
		for (int j = 0; j < NBR_UNITS; j++){
			placeUnit(m_teams[i]->getUnit(j));
		}
	}

	for (int i = 0; i < NBR_TEAMS; i++){
		for (int j = 0; j < NBR_UNITS; j++){
			m_teams[i]->getUnit(j)->setPosition(m_teams[i]->getUnit(j)->getPosition().x, m_teams[i]->getUnit(j)->getPosition().y + (0.05f), m_teams[i]->getUnit(j)->getPosition().z);
		}
	}

	BuildQuadTree();
}

void GameScreen::genTerrain(int type){
	if (m_land){
		delete m_land;
	}

	m_land = new vector<Vector>;
	*m_land = m_tGen.generateMap(type);

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
				unit->setPosition(m_land->at(i).x, m_land->at(i).y + (m_landCube->getScale() / 2), 1);

				for (int j = 0; j < m_land->size(); j++){
					if(unit->getPosition().x == m_land->at(j).x){
						if(unit->getPosition().y < m_land->at(j).y){
							float temp;

							temp = m_land->at(j).y - unit->getPosition().y;

							if(temp <= 0.1f){
								unit->setPosition(m_land->at(j).x, m_land->at(j).y, 1);
							}
						}
					}
				}

				if(unit->getPosition().y < m_height){
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
}

void GameScreen::changeUnit(){
	bool run = false;

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

		for (int i = 0; i < NBR_TEAMS; i++){
			if (m_teams[i]->isDead()){
				SceneSelect::getInstance(m_hdc).setScene(START, m_hdc);
				break;
			}
		}

		run = true;
	}

	if (m_curTeam == NBR_TEAMS - 1){
		m_curTeam = 0;
	}
	else if (m_curTeam < NBR_TEAMS){
		m_curTeam++;
	}

	m_curUnit->move()->stopMoving();
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

	m_quadTree->buildFullTree(NBR_LEVELS, m_width / 2, m_height / 2, 0.5f, m_width, m_height, 1);

	for (int i = 0; i < m_land->size(); i++){
		BoxCollider* temp = new BoxCollider;
		temp->setDimension(m_landCube->getScale(), m_landCube->getScale(), m_landCube->getScale());
		temp->setPos(m_land->at(i));
		m_quadTree->addObject(temp);
	}
}