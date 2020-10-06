//---------------------------include---------------------------
#pragma once
#include "Creature.h"
//-------------------------class Alive--------------------------
class Alive:public Creature
{
public:
	Alive();//default Ctor of Alive
	Alive(const sf::Vector2f& pos); // Ctor of Alive
	void setHome() { m_Sprite.setPosition(m_Home_Location); } //setHome
	sf::Vector2f getHome()const { return m_Home_Location; }//getHome
	void setStartPos(const sf::Vector2f& pos) { m_Home_Location = pos; }//setStartPos
	~Alive();
protected:
	//------------data members------------------------------------
	sf::Vector2f m_Home_Location;//SFML VECTOR 2F THAT HOLDS THE HOME LOCATION
};

