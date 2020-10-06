//------------------------------include-------------------------------------
#pragma once
#include "Creature.h"
//---------------------------class NoneAlive---------------------------------
class NoneAlive:public Creature
{
public:
	NoneAlive();//Ctor of NoneAlive
	NoneAlive(const sf::Vector2f& pos);//C'TOR OBJECT THAT UPDATE THE POSITION
	~NoneAlive();//Dtor of NoneAlive
};

