//-----------------------------include-----------------------------------------
#include "Scout.h"
#include "Factory.h"
#include "MediaSource.h"
#include "Macros.h"
#include "PathFinder.h"
//---------------------------static--------------------------------------------
bool Scout::m_registerit = Factory::registerit(SCOUT_T,
	[]() -> std::unique_ptr<Creature> { return std::make_unique<Scout>(); });
//------------------------Scout------------------------------------------------
//Ctor of Scout that update texture and start pos of scout
Scout::Scout()
{
	m_Sprite.setTextureRect({ 0, 0, 48, 48 });
	m_Sprite.setTexture(MediaSource::instance().getTexture(SCOUT_P));
	m_startPoint = m_Sprite.getPosition();
}
//-----------------------------------------------------------------------------
Scout::Scout(const sf::Vector2f & pos)
	:Guard(pos)
{
}
//-----------------moveScout---------------------------------------------------
//function that move the scout 
void Scout::moveScout(  const std::vector<std::vector<bool>>& m_boardGraph,const sf::Vector2i posP)
{
	if (static_cast<int>(m_Sprite.getPosition().x) % static_cast<int>(SIZE_TILE) == 0
		&& static_cast<int>(m_Sprite.getPosition().y) % static_cast<int>(SIZE_TILE) == 0)
	{
		if (path.empty()) // if the path is empty
		{
			makeNewPath(m_boardGraph,posP);
		}
		m_moveDirection = path.front(); // get the first item from the list
		path.pop_front(); // remove the front of the list
		changeMoveVector(m_moveDirection); // change scout move direction
	}
		m_prevPosition = m_Sprite.getPosition(); // save prevPotision
		m_Sprite.move(m_moveTo); // move the scout
}
//-----------------------------clearPath---------------------------------------
//function that clear Path
void Scout::clearPath()
{
	path.clear();
}
//----------------------------makeNewPath--------------------------------------
//function that make New Path
void Scout::makeNewPath( const std::vector <std::vector<bool>>& m_boardGraph,const sf::Vector2i posP)
{
	path = PathFinder::searchPath(m_boardGraph, this->getBoardLocation(), posP); // get path to temp

	if (path.empty()) // if didn't find path
	{
		//make for scout not to move as tile size
		for (int i = 0; i < SIZE_TILE; i++)
			path.push_front(NONE_D);
	}
}
//------------------------changeMoveVector-------------------------------------
// function that changes the direction of the scout according to its movement and load the correct texture
void Scout::changeMoveVector(DIRECTION dircetion)
{
	switch (dircetion)
	{
	case LEFT_D:
		m_moveTo = sf::Vector2f(-1*10, 0);
		m_dir = { -1.0f,0.0f };
		m_Sprite.setTextureRect({ i*0,48, SIZE_TILE_ALIVE_HEIGHT, SIZE_TILE_ALIVE_HEIGHT });
		break;
	case RIGHT_D:
		m_moveTo = sf::Vector2f(1*10, 0);
		m_dir = { 1.0f,0.0f };
		m_Sprite.setTextureRect({ i*0,96, SIZE_TILE_ALIVE_HEIGHT, SIZE_TILE_ALIVE_HEIGHT });
		break;
	case UP_D:
		m_moveTo = sf::Vector2f(0, -1*10);
		m_dir = { 0.0f, -1.0f};
		m_Sprite.setTextureRect({ i*0,WALKING_UP, SIZE_TILE_ALIVE_HEIGHT, SIZE_TILE_ALIVE_HEIGHT });
		break;
	case DOWN_D:
		m_moveTo = sf::Vector2f(0, 1*10);
		m_dir = { 0.0f,1.0f };
		m_Sprite.setTextureRect({ i*0,WALKING_DOWN, SIZE_TILE_ALIVE_HEIGHT, SIZE_TILE_ALIVE_HEIGHT });
		break;
	case NONE_D:
	default:
		m_moveTo = sf::Vector2f(0, 0);
		break;
	}
}
//--------------------------~Scout---------------------------------------------
//Dtor of Scout
Scout::~Scout()
{
}
