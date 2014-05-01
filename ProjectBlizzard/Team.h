#pragma once
#include "Unit.h"
#include "Weapon.h"
#include "BFont.h"

#include <vector>

class Team
{
private:
	int m_maxHealth, m_curHealth, m_maxUnits, m_ID, m_curUnit;
	vector<Unit*> m_units;
	vector<Weapon*> m_weapons;
	string m_name;
	BFont* m_font;
	bool m_dead;
public:
	Team(int teamID);
	~Team(void);

	int getMaxHealth();
	int getCurHealth();
	int getID();
	int getTeamSize();
	int getCurrentUnit();

	bool isDead();

	string getName(); 

	Unit* getUnit(int unitNum);

	Weapon* getWeapon(int wepNum);

	void updateMaxHealth();
	void updateCurHealth();
	void setID(int ID);
	void setName(string name);
	void setSize(int size);
	void addUnit(Unit* unit);
	void setCurrentUnit(int curUnit);

	void update();
	void render();

	void renderHealthBar(HDC hdc,float x, float y, float w, float h);
};

