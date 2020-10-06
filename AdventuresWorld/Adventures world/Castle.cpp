//---------------------------include-----------------------------------------
#include "Castle.h"
#include "Factory.h" 
#include"MediaSource.h"
//------------------------ static --------------------------------------------
bool Castle::m_registerit = Factory::registerit(CASTLE_T,
	[]() -> std::unique_ptr<Creature> { return std::make_unique<Castle>(); });

//----------------------Castle-----------------------------------------------
//default Ctor of Castle that loading his texture 
Castle::Castle()
{
	m_Sprite.setTexture(MediaSource::instance().getTexture(CASTLE_P));
	m_door.setTexture(MediaSource::instance().getTexture(DOOR_P));
	m_door.setColor(sf::Color::Red);
}
//--------------------Castle-----------------------------------------------------
//Cto of Castle that  Call to Creature to update the data member and set pos door
Castle::Castle(const sf::Vector2f& pos)
:NoneAlive(pos)
{
	setPosDoor();
}
//-------------------rangInDoor--------------------------------------------------
//function that return true if player collided with door 
bool Castle::rangInDoor(const sf::Vector2f & posplayer)
{
		return m_door.getGlobalBounds().contains(posplayer);
}
//--------------------setPosDoor--------------------------------------------------
//function that update pos door
void Castle::setPosDoor()
{
	m_door.setPosition({ m_Sprite.getPosition().x + 80,m_Sprite.getPosition().y + 174 });
}
//------------------~Castle---------------------------------------------------------
//default Dtor of Castle
Castle::~Castle()
{
}
