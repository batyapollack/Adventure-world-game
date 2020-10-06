//----------------------------include------------------------------------------
#include "Snow.h"
#include "Factory.h" 
#include "MediaSource.h"
//----------------------------static-------------------------------------------
bool Snow::m_registerit = Factory::registerit(SNOW_T,
	[]() -> std::unique_ptr<Creature> { return std::make_unique<Snow>(); });

//---------------------------Snow----------------------------------------------
//Ctor of Snow that update texture of Snow
Snow::Snow()
{
	m_Sprite.setTexture(MediaSource::instance().getTexture(SNOW_P));
}
//-----------------------------------Snow--------------------------------------
Snow::Snow(const sf::Vector2f & pos)
{
}




Snow::~Snow()
{
}
