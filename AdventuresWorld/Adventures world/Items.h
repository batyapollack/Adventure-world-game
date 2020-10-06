//------------------------------include--------------------------------------
#pragma once
#include "NoneAlive.h"
//-----------------------------class Items-----------------------------------
class Items:public NoneAlive
{
public:
	Items(); //Ctor of Items
	Items(const sf::Vector2f& pos); //C'TOR OBJECT THAT UPDATE THE POSITION
	~Items();//Dtor of  Items
	void setTokenKey(bool f) { m_is_token = f; }// setTokenKey
	bool getTokenKey()const { return m_is_token; }// getTokenKey
	void setTransperent() { m_Sprite.setColor(sf::Color::Transparent); }//setTransperent
protected:
	//--------------------------data members---------------------------------
	bool m_is_token = false; //m_is_token
};

