//-------------------------include---------------------------------------------
#include "WatchTower.h"
#include "Factory.h"
#include "MediaSource.h"
#include "Player.h"
#include "Bullet.h"
#include "NoneAlive.h"
//----------------------------static-------------------------------------------
bool WatchTower::m_registerit = Factory::registerit(WACTH_TOWER_T,
	[]() -> std::unique_ptr<Creature> { return std::make_unique<WatchTower>(); });
//----------------------------WatchTower---------------------------------------
//Ctor of WatchTower that update texture of Watch Tower and rang tower
WatchTower::WatchTower()
	:b1()
{
	m_clock.restart();
	m_range_tower.setTexture(MediaSource::instance().getTexture(RANGE_TOWER_P));//range
	m_range_tower.setColor({255, 255, 153, 130});
	m_Sprite.setTexture(MediaSource::instance().getTexture(TOWER_P));//tower

}
//-------------------------~WatchTower-----------------------------------------
//Dtor of WatchTower
WatchTower::~WatchTower()
{
}
//--------------------------setVectors-----------------------------------------
//function that update vectors of bullet  So we get the ball aimed at the player 
void WatchTower::setVectors(sf::Vector2f posplayer)
{
	setPosPlayer(posplayer);
	setDir();
	setDirNorm();
	setDeg();

}
//-----------------------PlayerInRange-----------------------------------------
// function works when the player is existing range of the tower and therefore the tower shoots at it
void WatchTower::PlayerInRange()
{
	if (m_clock.getElapsedTime().asSeconds() >=0.2)
	{
		b1.setPosition(towerCenter);
		b1.setVelocity(aimDirNorm * b1.getSpeed());
		m_bullets.emplace_back(std::make_unique <Bullet>(b1));
		MediaSource::instance().getSound(SOUND_TOWER_SD).play();
		MediaSource::instance().getSound(SOUND_TOWER_SD).setVolume(70.f);
		m_clock.restart();
	}
}
//-----------------------moveBullets-------------------------------------------
//Function move Bullets towards the player, if the Bullet collides with the player, decreases the player's life
bool WatchTower::moveBullets(sf::RenderWindow & window, std::vector<std::unique_ptr<NoneAlive>>& static_vec, Player& p)
{
	static bool enter;
	for (int i = 0; i < m_bullets.size(); i++)//collide bullet with the limits of window
	{
		auto a = m_bullets[i]->getShape();
		a.move(m_bullets[i]->getCurrVelocity());
		m_bullets[i]->setShape(a);
		
		for(int j=0; j < static_vec.size(); j++ )
			if (static_vec[j]->isContains(m_bullets[i]->getPositionShape()))
			{	if (m_bullets.size() == 0)
					break;
				m_bullets[i]->setDell();
			}
	}
	if (m_bullets.empty() == false) {
		for (int i = m_bullets.size() - 1; i >= 0; i--) {
			if (m_bullets.at(i)->getDell()) {
				m_bullets.erase(m_bullets.begin() + i);
			}
		}


	}
	for (int i = 0; i < m_bullets.size(); i++)
			if (p.isContains(m_bullets[i]->getPositionShape()))
			return true;
		
	return false;
}
//----------------------------drawBullets--------------------------------------
//function that draws all Bullets
void WatchTower::drawBullets(sf::RenderWindow & window)
{
	for (size_t i = 0; i < m_bullets.size(); i++)
		window.draw(m_bullets[i]->getShape());

}
//--------------------------drawRange------------------------------------------
//function that draw the range g tower
void WatchTower::drawRange(sf::RenderWindow & window)
{
	window.draw(m_range_tower);
}
