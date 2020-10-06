//---------------------------------include-----------------------------------
#pragma once
#include "Enemy.h"
//-------------------------------class Guard---------------------------------
class Guard :public Enemy
{
public:
	Guard(); //default Ctor of Guard
	Guard(const sf::Vector2f& pos); //C'TOR OBJECT THAT UPDATE THE POSITION
	void setPrevLoc(sf::Vector2f pos) { m_prev_loc = pos; }//setPrevLoc
	const sf::Vector2f& getPrevLoc()const { return m_prev_loc; }//getPrevLoc
	virtual void moveEnemy() = 0;//moveEnemy
	virtual void changeMove() = 0;//change Move gurard if collide 
	void setPicAnime();//setPicAnime
	void changeGuradanime();//changeGuradanime
	~Guard(); //Dtor of Guard
protected:
	//---------------------data members--------------------------------------
	sf::Vector2f m_dir = { 1.0f,0.0f };//m_dir
	sf::Vector2f m_prev_loc;//m_prev_loc
	int i=0;// for step guard
};

