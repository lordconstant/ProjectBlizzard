#include "GameScreen.h"


GameScreen::GameScreen(){
}


GameScreen::~GameScreen(){
	if(m_cam){
		delete m_cam;
	}

	if(m_timer){
		delete m_timer;
	}

	if(m_land){
		while(m_land->size() > 0){
			//delete m_land->back();
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
	m_unit =  new Unit("Pete", new Cube(1), 100, 2.0f);

	m_sEngine->play2D("Sounds/Electrodoodle.mp3", true);

	genTerrain(CAVES);

	m_landCube = new Cube(0.05f);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &m_landCube->m_VBVerts);
	glColorPointer(3, GL_FLOAT, 0, m_landCube->m_Colours);
}

void GameScreen::update(float mouseX, float mouseY){
	updateMouse(mouseX, mouseY);

	m_unit->update(m_mousePos);

	if (m_land){
		for (int i = 0; i < m_land->size(); i++){
			if (m_unit->getWeapon()->hitObject(m_land->at(i), m_landCube->getScale(), m_landCube->getScale())){
				if (m_explo){
					m_explo->circularExplosion(Vector(m_land->at(i).x, m_land->at(i).y, 1), 0.5f, 5);
				}
			}

			if (m_unit->getWeapon()->checkAhead(m_land->at(i), m_landCube->getScale(), m_landCube->getScale())){
				break;
			}
		}
	}

	m_cam->move()->setPos(m_unit->getPosition().x, m_unit->getPosition().y, m_cam->move()->getPos().z);
}

void GameScreen::render(){
	m_cam->update();
	
	m_unit->render();

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
		m_unit->move()->up(false);
		break;
	case VK_S:
		//m_cam->move()->down(false);
		m_unit->move()->down(false);
		break;
	case VK_A:
		//m_cam->move()->left(false);
		m_unit->move()->left(false);
		break;
	case VK_D:
		//m_cam->move()->right(false);
		m_unit->move()->right(false);
		break;
	case VK_1:
		genTerrain(ISLANDS);
		break;
	case VK_2:
		genTerrain(LAND);
		break;
	case VK_3:
		genTerrain(CAVES);
		break;
	case VK_4:
		genTerrain(CAVE);
		break;
	case VK_5:
		genTerrain(FLOATING_ISLAND);
		break;
	case VK_6:
		genTerrain(BRIDGE);
		break;
	case VK_7:
		genTerrain(RIDGES);
		break;
	case VK_SPACE:
		break;
	default:
		break;
	}

}

void GameScreen::processKeyDown(int key){
	switch (key){
	case VK_W:
		//m_cam->move()->up(true);
		m_unit->move()->up(true);
		break;
	case VK_S:
		//m_cam->move()->down(true);
		m_unit->move()->down(true);
		break;
	case VK_A:
		//m_cam->move()->left(true);
		m_unit->move()->left(true);
		break;
	case VK_D:
		//m_cam->move()->right(true);
		m_unit->move()->right(true);
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
		m_unit->fireWeapon();

		//m_timer->play();
		break;
	case WM_MOUSEWHEEL:
		((short)HIWORD(state) < 0) ? m_cam->move()->backward(true) : m_cam->move()->forward(true);
		break;
	default:
		break;
	}
}

void GameScreen::createGame(int type, vector<Unit*>* units){
	genTerrain(type);

	m_width = m_height = 0;

	for (int i = 0; i < m_land->size(); i++){
		if (m_land->at(i).x > m_width){
			m_width = m_land->at(i).x;
		}

		if (m_land->at(i).y > m_height){
			m_height = m_land->at(i).y;
		}
	}

	for (int i = 0; i < units->size(); i++){
		placeUnit(units->at(i));
	}
}

void GameScreen::genTerrain(int type){
	if (m_land){
		delete m_land;
	}

	m_land = new vector<Vector>;
	*m_land = m_tGen.generateMap(type);

	if (!m_explo){
		m_explo = new Explosion(*m_land, *m_land);
	}

	m_explo->defineTerrain(*m_land);
}

void GameScreen::placeUnit(Unit* unit){
	bool done;
	done = false;

	while (!done){
		unit->setPosition(rand() % (int)m_width, rand() % (int)m_height, 1);

		for (int i = m_land->size()-1; i >= 0; i--){
			if (unit->getPosition().x == m_land->at(i).x){
				if (unit->getPosition().y > m_land->at(i).y){
					unit->setPosition(m_land->at(i).x, m_land->at(i).y+m_landCube->getScale()/2, 1);
					done = true;
					break;
				}
			}
		}
	}
}