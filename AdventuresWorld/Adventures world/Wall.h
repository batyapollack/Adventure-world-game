//-----------------------------------include-----------------------------------
#pragma once
#include "NoneAlive.h"
//-------------------------------class Wall-------------------------------------
class Wall:public NoneAlive
{
public:
	Wall();//default Ctor of Wall
	Wall(const sf::Vector2f& pos);//C'TOR OBJECT THAT UPDATE THE POSITION
	~Wall();//Dtor of Wall
private:
	//---------------------data members-----------------------------------------
	static bool m_registerit;//m_registerit
};

