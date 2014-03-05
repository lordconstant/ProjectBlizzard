#pragma once
#include "Unit.h"
//#include "Weapon.h"

#include <vector>

class Team
{
private:
	int m_maxHealth, m_curHealth, m_ID, m_size;
	vector<Unit*> m_units;
//	vector<Weapon*> m_weapons;
	string m_name;
public:
	Team(void);
	~Team(void);

	int getMaxHealth();
	int getCurHealth();
	int getID();
	int getSize();

	string getName(); 

	Unit* getUnit(int unitNum);

	//Weapon* getWeapon(int wepNum);

	void updateMaxHealth();
	void updateCurHealth();
	void setID(int ID);
	void setSize(int size);
	void setName(string name);

	void addUnit(Unit* unit);
};

