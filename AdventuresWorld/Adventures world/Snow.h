//----------------------------include--------------------------------------------
#pragma once
#include "Items.h"
//-------------------------class Snow---------------------------------------------
class Snow:public Items
{
public:
	Snow(); //default Ctor of  Snow
	Snow(const sf::Vector2f& pos);//C'TOR OBJECT THAT UPDATE THE POSITION
	~Snow();//Dtor of Snow
	void setActivate() { m_activate = true; }//setActivate
	bool getActivate() { return m_activate; }//getActivate

private:
	//----------------------data members------------------------------------------
	bool m_activate = false;//m_activate
	static bool m_registerit;//m_registerit
};

