//-----------------------------include----------------------------------------
#pragma once
#include "Alive.h"
#include <iostream>
//--------------------------class Player--------------------------------------

class Player:public Alive
{
public:
	Player();//Ctor of Player
	~Player();//Dtor of Player
	void setPosition(const sf::Vector2f& pos) { m_Sprite.setPosition(pos); }//setPosition
	void setDirectionPic(const sf::Vector2f & dir, int i);//setDirectionPic
	void setIsDie(bool f) { m_is_die = f; }//setIsDie
	bool getIsDie()const { return m_is_die; }//getIsDie
	void setLife() { if (m_life > 0) m_life--; }//setLife
	int getLife()const { return m_life; }//getLife
	void setNextLevel(bool flag) { m_next_level = flag; }//setNextLevel
	bool getNextLevel()const { return m_next_level; }//getNextLevel
	unsigned int getCountIce()const { return m_count_ice; }
	void setCountIce( int count) {m_count_ice+=count ; }
	void setCollideEnemy(bool f) { m_collide_enemy = f; }
	bool getCollideEnemy()const { return m_collide_enemy; }
	void setColor() { m_Sprite.setColor(sf::Color::Transparent); }
	const int& getMinClock()const { return 180 - ( int)(m_min_game.getElapsedTime().asSeconds()); }
	void resetClock();
	void updateForNewGame();
	void setPrevLocPosition(const sf::Vector2f& f) { m_prevLoc = f; }
	const sf::Vector2f& getPrevLoc() { return m_prevLoc; }

private:
	//---------------------------data members------------------------------------------
	static bool m_registerit;//m_registerit
	int m_life = 3 ;//m_life
	bool m_is_die = false;//m_is_die
	bool m_next_level = false;//m_next_level
	 int m_count_ice = 0;
	bool m_collide_enemy= false;
	sf::Vector2f m_prevLoc;
	sf::Clock m_min_game;
};







