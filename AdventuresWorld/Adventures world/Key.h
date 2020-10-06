//---------------------------------include---------------------------------------------
#pragma once
#include "Items.h"
//------------------------------class Key----------------------------------------------
class Key: public Items
{
public:
	Key(); //Ctor of Key
	Key(const sf::Vector2f& pos); //C'TOR OBJECT THAT UPDATE THE POSITION
	void setKey(bool flag) { key_good = flag; }//setKey
	bool getKey() { return key_good; }// getKey
	~Key(); //Dtor of Key
private:
	//-------------------------------data members---------------------------------------
	bool key_good; //key_good
	static bool m_registerit;// m_registerit
};


