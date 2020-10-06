//----------------------------include------------------------------------------------
#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
//-----------------------------class-------------------------------------------------
class Player;
class Enemy;
class Key;
class NoneAlive;
class Snow;
class Castle;
//----------------------------class Collision-----------------------------------------
class Collision
{
public:
	Collision(Player& player, std::vector<std::unique_ptr <Enemy>>&enemies,
		std::vector<std::unique_ptr <Key>> &keys, std::vector<std::unique_ptr <Snow>> &snows, 
		std::vector<std::unique_ptr<NoneAlive>>& static_vec,sf::RenderWindow& window); //Ctor of Collision
	bool checkCollidePlayer(const sf::Vector2f& pos); //checkCollidePlayer
	bool checkCollideEnemies(int i);//checkCollideEnemies
	void setEndLevel(bool flag) { m_end_level = flag; }//setEndLevel
	bool getEndLevel() { return m_end_level; }//getEndLevel
	void returnAliveCreatureHome();//returnAliveCreatureHome
	~Collision(); //Dtor of Collision

private:
	//---------------------private function-----------------------------
	void keysHandleCollide(const sf::Vector2f& posPlayer)const;//keysHandleCollide
	void snowHandleCollide(const sf::Vector2f& posPlayer)const;//snowHandleCollide
	bool enemyHandleCollide(const sf::Vector2f& posPlayer);//enemyHandleCollide
	//---------------------data members---------------------------------
	sf::RenderWindow& m_window; //m_window
	Player & m_player;//m_player
	std::vector<std::unique_ptr <Enemy>>& m_enemys;//m_enemys
	std::vector<std::unique_ptr <Key>>& m_keys;//m_keys
	std::vector<std::unique_ptr <Snow>>& m_snows;//m_snows
	std::vector<std::unique_ptr<NoneAlive>>& m_static_vec;//m_static_vec
	bool m_end_level = false;//m_end_level
	bool m_collide_player=false;//m_collide_player
	
};

