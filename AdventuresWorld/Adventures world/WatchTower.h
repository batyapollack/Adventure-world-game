//------------------------------include----------------------------------------
#pragma once
#include "Enemy.h"
#include <vector>
#include "Bullet.h"
//-------------------------------class-----------------------------------------
class NoneAlive;
class Player;
//---------------------------class WatchTower----------------------------------
class WatchTower:public Enemy
{
public:
	WatchTower();//default Ctor of WatchTower 
	~WatchTower();// Dtor  of WatchTower
	void setIsFire() { m_isFire = true; }//setIsFire
	bool getIsFire()const { return m_isFire; }//getIsFire
	sf::Sprite getCirc()const {return m_range_tower; }//getCirc
	bool isContains(sf::Sprite circ, sf::Vector2f pos) { return circ.getGlobalBounds().contains(pos); }//isContains
	void setPosTowerCenter() { towerCenter = { m_Sprite.getPosition().x +50,m_Sprite.getPosition().y+25 }; }//setPosTowerCenter
	void setPosPlayer(sf::Vector2f pos) { posPlayer = pos; }//setPosPlayer
	void setDir() { aimDir = posPlayer - towerCenter; }//setDir
	void setDirNorm(){ aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)); }// (Direction / distance )setDirNorm
	void setDeg(){ deg = atan2(aimDirNorm.y, aimDirNorm.x) * 180 / PI; }//setDeg
	void setVectors(sf::Vector2f posplayer); //setVectors
    void PlayerInRange();//PlayerInRange
	bool moveBullets(sf::RenderWindow & window, std::vector<std::unique_ptr<NoneAlive>>& static_vec, Player& p);//moveBullets
	void drawBullets(sf::RenderWindow & window);//drawBullets
	void drawRange(sf::RenderWindow & window);//drawRange
	void setPosRange() { m_range_tower.setPosition(m_Sprite.getPosition().x-150, m_Sprite.getPosition().y-130 ); }//setPosRange
private:
	//---------------------------------datat members---------------------------------------------
	static bool m_registerit;//m_registerit
	bool m_isFire;//m_isFire
	sf::Sprite m_range_tower;//m_range_tower
	Bullet b1;//bullet
	std::vector <std::unique_ptr<Bullet>> m_bullets;//m_bullets
	sf::Vector2f towerCenter;//tower center
	sf::Vector2f posPlayer;//pos player
	sf::Vector2f aimDir;//dir
	sf::Vector2f aimDirNorm;//distance
	float deg;//deg
	float PI = 3.14159265f;//pi
	sf::Clock m_clock;//m_clock
};

