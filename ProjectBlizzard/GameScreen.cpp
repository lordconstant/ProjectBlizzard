#include "GameScreen.h"


GameScreen::GameScreen(){
}


GameScreen::~GameScreen(){
	if(m_cam){
		delete m_cam;
	}

	///*if(m_timer){
	//	delete m_timer;
	//*/}

	if(m_land){
		while(m_land->size() > 0){
			m_land->pop_back();
		}

		delete m_land;
	}
}

void GameScreen::initialise(){
	m_cam = new Camera();
	m_cam->move()->setPos(0, 1, 0);

	m_land = NULL;
	m_explo = NULL;
	
	m_curTeam = 0;

	for (int i = 0; i < NBR_TEAMS; i++){
		m_teams.push_back(new Team(i));

		m_teams[i]->setCurrentUnit(0);

		for (int j = 0; j < NBR_UNITS; j++){
			m_teams[i]->addUnit(new Unit("Pete", new Cube(0.05f), 100, 2.0f));
		}
	}

	//m_sEngine->play2D("Sounds/Electrodoodle.mp3", true);

	m_landCube = new Cube(0.05f);

	createGame(CAVE);

	changeUnit();

	renderCubes = true;

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &m_landCube->m_VBVerts);
	glColorPointer(3, GL_FLOAT, 0, m_landCube->m_Colours);
}

void GameScreen::update(float mouseX, float mouseY){
	updateMouse(mouseX, mouseY);

	for (int i = 0; i < NBR_TEAMS; i++){
		m_teams[i]->update();
	}

	m_curUnit->update(m_mousePos);

	if (m_land){
		for (int i = 0; i < m_land->size(); i++){
			if (m_curUnit->getWeapon()->hitObject(m_land->at(i), m_landCube->getScale(), m_landCube->getScale())){
				if (m_explo){
					m_explo->circularExplosion(Vector(m_land->at(i).x, m_land->at(i).y, 1), 1.0f, 50);
					changeUnit();
					break;
				}
			}

			if (m_curUnit->getWeapon()->checkAhead(m_land->at(i), m_landCube->getScale(), m_landCube->getScale())){
				break;
			}
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
			glPushMatrix();
				glTranslatef(m_land->at(i).x, m_land->at(i).y, m_land->at(i).z);
				glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, m_landCube->m_bytes);
			glPopMatrix();
		}
	}
}

void GameScreen::processKeyUp(int key){
	switch (key){
	case VK_W:
		//m_cam->move()->up(false);
		m_curUnit->move()->up(false);
		break;
	case VK_S:
		//m_cam->move()->down(false);
		m_curUnit->move()->down(false);
		break;
	case VK_A:
		//m_cam->move()->left(false);
		m_curUnit->move()->left(false);
		break;
	case VK_D:
		//m_cam->move()->right(false);
		m_curUnit->move()->right(false);
		break;
	case VK_SPACE:
		if(renderCubes){
			renderCubes = false;
		}else{
			renderCubes = true;
		}
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
		m_curUnit->move()->up(true);
		break;
	case VK_S:
		//m_cam->move()->down(true);
		m_curUnit->move()->down(true);
		break;
	case VK_A:
		//m_cam->move()->left(true);
		m_curUnit->move()->left(true);
		break;
	case VK_D:
		//m_cam->move()->right(true);
		m_curUnit->move()->right(true);
		break;
	default:
		break;
	}
}

void GameScreen::processMouse(int key, int state){
	switch (key){
	case WM_LBUTTONDOWN:
		//m_timer->reset();
		if (m_explo){
			m_explo->circularExplosion(Vector(m_mousePos.x, m_mousePos.y, 1), 0.5f, 5);
		}
		break;
	case WM_RBUTTONDOWN:
		m_curUnit->fireWeapon();

		//m_timer->play();
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
		unit->setPosition((float)(rand() % (int)m_width), (float)(rand() % (int)m_height), 1);

		for (int i = 0; i < m_land->size(); i++){
			if(unit->getPosition().x == m_land->at(i).x){
				unit->setPosition(m_land->at(i).x, m_land->at(i).y + (m_landCube->getScale() / 2), 1);

				for (int j = 0; j < m_land->size(); j++){
					if(unit->getPosition().x == m_land->at(j).x){
						if(unit->getPosition().y < m_land->at(j).y){
							float temp;

							temp = m_land->at(j).y - unit->getPosition().y;

							if(temp < 0.1f){
								unit->setPosition(m_land->at(j).x, m_land->at(j).y + (m_landCube->getScale() / 2), 1);
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

	m_curUnit = m_teams[m_curTeam]->getUnit(m_teams[m_curTeam]->getCurrentUnit());

	while (m_curUnit->isDead() || !run){
		m_curUnit = m_teams[m_curTeam]->getUnit(m_teams[m_curTeam]->getCurrentUnit());

		if (m_teams[m_curTeam]->getCurrentUnit() == NBR_UNITS - 1){
			m_teams[m_curTeam]->setCurrentUnit(0);
		}
		else{
			m_teams[m_curTeam]->setCurrentUnit(m_teams[m_curTeam]->getCurrentUnit() + 1);
		}

		if (m_curTeam == NBR_TEAMS - 1){
			m_curTeam = 0;
		}
		else if (m_curTeam < NBR_TEAMS){
			m_curTeam++;
		}

		run = true;
	}

	m_curUnit->move()->stopMoving();
}