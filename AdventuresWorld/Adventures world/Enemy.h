//----------------------------include----------------------------------------
#pragma once
#include "Alive.h"
//------------------------class Enemy----------------------------------------
class Enemy : public Alive
{
public:
	Enemy();// Ctor of Enemy
	Enemy(const sf::Vector2f& pos); //C'TOR OBJECT THAT UPDATE THE POSITION
	~Enemy();//Dtor of Enemy
};

