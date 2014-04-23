#include "GameScreen.h"


GameScreen::GameScreen(){
}


GameScreen::~GameScreen(){
	if(m_cam){
		delete m_cam;
	}

	if(m_land){
		while(m_land->size() > 0){
			m_land->pop_back();
		}

		delete m_land;
	}
}

void GameScreen::initialise(){
	glewInit();

	m_cam = new Camera();
	m_cam->move()->setPos(0, 1, 0);

	m_quadTree = NULL;

	m_land = NULL;
	m_explo = NULL;
	
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

	int gameType = rand() % LTCOUNT;
	createGame(gameType);

	changeUnit();

	renderCubes = true;
}

void GameScreen::update(float mouseX, float mouseY){
	updateMouse(mouseX, mouseY);

	for (int i = 0; i < NBR_TEAMS; i++){
		m_teams[i]->update();
	}

	if (m_curUnit->getWeapon()->getCurShot()){
		if (m_quadTree->processCollisions(m_curUnit->getWeapon()->getCurShot()->getModel())){
			if (m_explo){
				m_explo->circularExplosion(Vector(m_curUnit->getWeapon()->getCurShot()->getModel()->getPos().x, m_curUnit->getWeapon()->getCurShot()->getModel()->getPos().y, 1), m_curUnit->getWeapon()->getPower() * 0.5f, 50, *m_quadTree);
				m_curUnit->getWeapon()->hitObject(NULL, 0, 0);

				//changeUnit();
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

			tempUnit->update(m_mousePos);

			tempUnit = NULL;
		}
	}

	m_cam->move()->setPos(m_curUnit->getPosition().x, m_curUnit->getPosition().y, m_cam->move()->getPos().z);

	for (int i = 0; i < NBR_TEAMS; i++){
		if (m_teams[i]->isDead()){
			SceneSelect::getInstance().setScene(START);
			break;
		}
	}
}

void GameScreen::render(){
	m_cam->update();
	
	if(renderCubes){
		for (int i = 0; i < NBR_TEAMS; i++){
			m_teams[i]->render();
		}
	}

	if (m_land){
		for (int i = 0; i < m_land->size(); i++){
			m_landCube->setPos(m_land->at(i));
			m_landCube->Render();
		}
	}

	//m_quadTree->render();
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
		m_curUnit->fireWeapon();
		break;
	case WM_MOUSEWHEEL:
		((short)HIWORD(state) < 0) ? m_cam->move()->backward(true) : m_cam->move()->forward(true);
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
				SceneSelect::getInstance().setScene(START);
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