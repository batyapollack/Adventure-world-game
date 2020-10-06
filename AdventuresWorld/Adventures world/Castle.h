//-----------------------------include-------------------------------------
#pragma once
#include "NoneAlive.h"
//-------------------------class Castle------------------------------------
class Castle: public NoneAlive
{
public:
	Castle();//default Ctor of Castle
	Castle(const sf::Vector2f& pos);//C'TOR OBJECT THAT UPDATE THE  POSITION
	bool rangInDoor(const sf::Vector2f& posplayer);//rangInDoor
	sf::Sprite getDoor()const { return m_door; }//getDoor
	void setPosDoor();//setPosDoor
	~Castle();//Dtor of Castle
private:
	//-----------------------data members----------------------------------
	sf::Sprite m_door;//m_door
	static bool m_registerit;//m_registerit
};

