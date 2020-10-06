//--------------------------include--------------------------------------------
#include "Wall.h"
#include "Factory.h" 
#include "MediaSource.h"
//---------------------------static--------------------------------------------
bool Wall::m_registerit = Factory::registerit(WALL_T,
	[]() -> std::unique_ptr<Creature> { return std::make_unique<Wall>(); });
//----------------------------Wall---------------------------------------------
//Ctor of Wall that update texture of Wall
Wall::Wall()
{
	m_Sprite.setTexture(MediaSource::instance().getTexture(WALL_P));
	m_Sprite.setColor(sf::Color::Red);
}

Wall::Wall(const sf::Vector2f& pos)
	:NoneAlive(pos)
{
	
}


Wall::~Wall()
{
}
