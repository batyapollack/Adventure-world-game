//---------------------include---------------------------------
#include "Alive.h"
//--------------------------------------------------------------
Alive::Alive()
{

}
//---------------Ctor of Alive---------------------------------
//Call to Creature to update the data member
Alive::Alive(const sf::Vector2f & pos)
	:Creature(pos)
{
}

Alive::~Alive()
{
}
