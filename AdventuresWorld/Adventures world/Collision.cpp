//--------------------------------include-----------------------------------------
#pragma once
#include "Collision.h"
#include "Player.h"
#include "Enemy.h"
#include "Key.h"
#include "NoneAlive.h"
#include "Macros.h"
#include "Castle.h"
#include "WatchTower.h"
#include "Guard.h"
#include "Scout.h"
#include "Controller.h"
#include "Snow.h"
#include "RandMachine.h"
#include "StupidGuard.h"
//------------------------------Collision--------------------------------------------------------------
//Ctor  of Collision that get data and update data members 
Collision::Collision(Player & player, std::vector<std::unique_ptr<Enemy>>& enemies,
	std::vector<std::unique_ptr<Key>>& keys,  std::vector<std::unique_ptr <Snow>> &snows, 
	std::vector<std::unique_ptr<NoneAlive>>& static_vec,sf::RenderWindow& window)
:m_player(player),m_enemys(enemies),m_keys(keys),m_snows(snows),m_static_vec(static_vec), m_window(window)
{
}
//-------------------------checkCollidePlayer----------------------------------------------------------
// function that returns true if the player can collide with the second object, otherwise false
bool Collision::checkCollidePlayer(const sf::Vector2f & posPlayer)
{
	keysHandleCollide(posPlayer);
	snowHandleCollide(posPlayer);
	if (!enemyHandleCollide(posPlayer))
	{
		m_player.setCollideEnemy(true);
		returnAliveCreatureHome();
		return false;//enemy->isContains with posPlayer
	}
	//collision with static obj
	for (auto &stat : m_static_vec)
	{
		if (
			stat->isContains(posPlayer)
			|| stat->isContains(sf::Vector2f{ posPlayer.x + m_player.getGlobalBound().width ,posPlayer.y })//right
			|| stat->isContains(sf::Vector2f{ posPlayer.x + SIZE_TILE_ALIVE_WIDTH,posPlayer.y + SIZE_TILE_ALIVE_HEIGHT })//slant right
			|| stat->isContains(sf::Vector2f{ posPlayer.x ,posPlayer.y + SIZE_TILE_ALIVE_HEIGHT })//down
			)
		{

			auto castle = dynamic_cast<Castle*> (stat.get());
			if (castle)
			{
				if (m_player.getNextLevel() &&
					(castle->rangInDoor(m_player.getPosition())
						||
						castle->rangInDoor(sf::Vector2f{ posPlayer.x + SIZE_TILE_ALIVE_WIDTH ,posPlayer.y })
						||
						castle->rangInDoor(sf::Vector2f{ m_player.getPosition().x + SIZE_TILE_ALIVE_WIDTH,m_player.getPosition().y + SIZE_TILE_ALIVE_HEIGHT })
						||
						castle->rangInDoor(sf::Vector2f{ posPlayer.x ,posPlayer.y + SIZE_TILE_ALIVE_HEIGHT })))
				{
					setEndLevel(true);
					return true;
				}
				else
					return false;

			}
			else
			{
				return false;
			}

		}
	}

}
//--------------------------checkCollideEnemies--------------------------------------------------------------
// function that returns true if the enemy can collide with the second object, otherwise false
bool Collision::checkCollideEnemies(int i)
{
	auto guard = dynamic_cast<Guard*>(m_enemys[i].get());
		for (auto &stat : m_static_vec)
		{
			
			if ((guard) && (
				stat->isContains(m_enemys[i]->getPosition())
				|| stat->isContains(sf::Vector2f{ m_enemys[i]->getPosition().x + SIZE_TILE_ALIVE_WIDTH ,m_enemys[i]->getPosition().y })//right
				|| stat->isContains(sf::Vector2f{ m_enemys[i]->getPosition().x + SIZE_TILE_ALIVE_WIDTH,m_enemys[i]->getPosition().y + SIZE_TILE_ALIVE_HEIGHT })//slant right
				|| stat->isContains(sf::Vector2f{ m_enemys[i]->getPosition().x ,m_enemys[i]->getPosition().y + SIZE_TILE_ALIVE_HEIGHT })
				))//down
				
			{
				guard->setPosition(guard->getPrevLoc());
				guard->changeMove();
				return false;
			}
		}
		

		if (guard)
		{
			if (m_player.isContains(sf::Vector2f{ m_enemys[i]->getPosition().x + SIZE_TILE_ALIVE_WIDTH ,m_enemys[i]->getPosition().y })//right
				|| m_player.isContains(sf::Vector2f{ m_enemys[i]->getPosition().x + SIZE_TILE_ALIVE_WIDTH,m_enemys[i]->getPosition().y + SIZE_TILE_ALIVE_HEIGHT })//slant right
				|| m_player.isContains(sf::Vector2f{ m_enemys[i]->getPosition().x ,m_enemys[i]->getPosition().y + SIZE_TILE_ALIVE_HEIGHT }))
			{
				m_player.setLife();
				returnAliveCreatureHome();
			}
			guard->setPrevLoc(guard->getPosition());
			return true;
		}
		return true;
}
//-----------------------returnAliveCreatureHome--------------------------------------------------------
//function that return all alive obj to start pos
void Collision::returnAliveCreatureHome()
{
		m_player.setHome();

		m_player.setPrevLocPosition(m_player.getPosition());
		for (int i = 0; i < m_enemys.size(); i++)
		{
			m_enemys[i]->setHome();
			auto s = dynamic_cast <Scout*>(m_enemys[i].get());
			if (s)
				s->clearPath();
		}
}
//-------------------------Collision-----------------------------------------------------------
//Dtor of Collision
Collision::~Collision()
{
}
//--------------------keysHandleCollide--------------------------------------------------------
//function that is checked if the player collides with a key, then updates him if he has the correct key
void Collision::keysHandleCollide(const sf::Vector2f& posPlayer)const
{
	for (auto &key : m_keys)
	{
		if (key->isContains(sf::Vector2f{ posPlayer.x, posPlayer.y+12 })
			|| key->isContains(sf::Vector2f{ posPlayer.x + 32,posPlayer.y+5 })//right
			|| key->isContains(sf::Vector2f{ posPlayer.x + 32,posPlayer.y + 40 })//slant right
			|| key->isContains(sf::Vector2f{ posPlayer.x ,posPlayer.y + 40 }))//down
		{
			key->setTokenKey(true);//get key
			MediaSource::instance().getSound(KEY_SD).play();
			MediaSource::instance().getSound(KEY_SD).setVolume(20.f);
		}
	}
	for (int i = 0; i < m_keys.size(); i++)
	{//  running on loop to update permission
		if (m_keys[i]->getTokenKey() && m_keys[i]->getKey())
		{
			m_player.setNextLevel(true);
		}
	}
	for (int i = 0; i < m_keys.size(); i++)//  running on loop to update permission
		if (m_keys[i]->getTokenKey())
		{
			m_keys.erase(m_keys.begin() + i);
		}
}
//--------------------snowHandleCollide---------------------------------------------------
//function that is checked if the player collides with ice, then updates him that he has the ability to freeze the enemies
void Collision::snowHandleCollide(const sf::Vector2f & posPlayer)const
{
	for (int i =0; i < m_snows.size();i++)
	{
		if (m_snows[i]->isContains(posPlayer)
			|| m_snows[i]->isContains(sf::Vector2f{ posPlayer.x + 32,posPlayer.y })//right
			|| m_snows[i]->isContains(sf::Vector2f{ posPlayer.x + 32,posPlayer.y + 35 })//slant right
			|| m_snows[i]->isContains(sf::Vector2f{ posPlayer.x ,posPlayer.y + 35 }))//down
		{
			//m_snows[i]->setTokenKey(true);//get key
			m_player.setCountIce(1);
			m_snows.erase(m_snows.begin() + i);
			MediaSource::instance().getSound(ICE_SD).play();
			MediaSource::instance().getSound(ICE_SD).setVolume(70.f);
		}
	}
}
//----------------------------enemyHandleCollide-------------------------------------------------
// function that returns false if the player collide with enemy, otherwise true
bool Collision::enemyHandleCollide(const sf::Vector2f & posPlayer) 
{

	for (auto &enemy : m_enemys)
	{
		auto a = dynamic_cast<WatchTower*>(enemy.get());
		if (a)
		{
			if (a->isContains(a->getCirc(), posPlayer))
			{
				a->setVectors({ m_player.getPosition().x + 16,m_player.getPosition().y + 24 });
				a->PlayerInRange();
				
			}
		}
		if (enemy->isContains(posPlayer)
			|| enemy->isContains(sf::Vector2f{ posPlayer.x + SIZE_TILE_ALIVE_WIDTH,posPlayer.y })//right
			|| enemy->isContains(sf::Vector2f{ posPlayer.x + SIZE_TILE_ALIVE_WIDTH,posPlayer.y + SIZE_TILE_ALIVE_HEIGHT })//slant right
			|| enemy->isContains(sf::Vector2f{ posPlayer.x ,posPlayer.y + SIZE_TILE_ALIVE_HEIGHT }))//down

		{
			MediaSource::instance().getSound(COLLIDE_SD).play();
			MediaSource::instance().getSound(COLLIDE_SD).setVolume(70.f);
			m_player.setLife();
			returnAliveCreatureHome();
			return false;
		}
	}
	return true;
}
