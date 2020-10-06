//------------------------------include-------------------------------------
#pragma once
#include "Guard.h"
//--------------------------class StupidGuard------------------------------
class StupidGuard: public Guard
{
public:
	StupidGuard(); //default Ctor of StupidGuard 
	StupidGuard(const sf::Vector2f& pos);//C'TOR OBJECT THAT UPDATE THE POSITION
	void moveEnemy() final;//moveEnemy
	void changeMove()final; //changeMove
	void changeTexture();//changeTexture
	~StupidGuard();//Dtor of StupidGuard

private:
	//---------------data members-------------------------------------------
	static bool m_registerit;//m_registerit
	bool m_wolf_tex_mode = false;//m_wolf_tex_mode
};

