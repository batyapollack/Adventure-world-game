//----------------------------include------------------------------------------
#include "StupidGuard.h"
#include"Factory.h"
#include "MediaSource.h"
#include <random>
//----------------------------static-------------------------------------------
bool StupidGuard::m_registerit =Factory::registerit(STUPID_GAURD_T,
	[]() -> std::unique_ptr<Creature> { return std::make_unique<StupidGuard>(); });
//--------------------------StupidGuard----------------------------------------
//Ctor of StupidGuard that update texture of Stupid Guard
StupidGuard::StupidGuard()
{
	m_Sprite.setTextureRect({ 0, 96, 48, 48 });
	m_Sprite.setTexture(MediaSource::instance().getTexture(STUPID_P));
}

StupidGuard::StupidGuard(const sf::Vector2f & pos)
	:Guard(pos)
{
}
//----------------------------moveEnemy----------------------------------------
//function that move the enemy
void StupidGuard::moveEnemy()
{
	m_Sprite.setPosition({ m_Sprite.getPosition().x + SPEED_GUARD * m_dir.x,m_Sprite.getPosition().y + SPEED_GUARD * m_dir.y });
}
//----------------------changeMove---------------------------------------------
//function that change Move of StupidGuard if collide if static obj
void StupidGuard::changeMove()
{
	int new_rand_dir = rand() % 4;
	switch (new_rand_dir)
	{
	case UP_SIGN:
		m_dir = { 0.0f,-1.0f };
		m_Sprite.setTextureRect({ 0,WALKING_UP, SIZE_TILE_ALIVE_HEIGHT, SIZE_TILE_ALIVE_HEIGHT });
		break;
	case RIGHT_SIGN:
		m_dir = { 1.0f, 0.0f };
			m_Sprite.setTextureRect({ 0,96, SIZE_TILE_ALIVE_HEIGHT, SIZE_TILE_ALIVE_HEIGHT });
		break;
	case DOWN_SIGN:
		m_dir = { 0.0f,1.0f };
		m_Sprite.setTextureRect({ 0,WALKING_DOWN, SIZE_TILE_ALIVE_HEIGHT, SIZE_TILE_ALIVE_HEIGHT });
		break;
	case LEFT_SIGN:
		m_dir = { -1.0f, 0.0f };
		m_Sprite.setTextureRect({ 0,48, SIZE_TILE_ALIVE_HEIGHT, SIZE_TILE_ALIVE_HEIGHT });
		break;
	default:
		break;
	}

}
//---------------------------changeTexture-------------------------------------
//function that change Texture when the stupid guards leave the house
void StupidGuard::changeTexture()
{
	m_Sprite.setTextureRect({ 0, 96, 48, 48 });
	m_Sprite.setTexture(MediaSource::instance().getTexture(WOLF_P));
	MediaSource::instance().getSound(WOLF_SD).play();
	MediaSource::instance().getSound(WOLF_SD).setVolume(100.0f);
}
//---------------------------~StupidGuard--------------------------------------
//Dtor of StupidGuard
StupidGuard::~StupidGuard()
{
}
