//---------------------------include----------------------------------------
#pragma once
#include <SFML/Graphics.hpp>
#include<vector>
#include "NoneAlive.h"
//-------------------------class Bullet-------------------------------------
class Bullet:public NoneAlive
{
public:
	Bullet(float radius = 5.f); //Ctor of Bullet
	void setPosition(const sf::Vector2f& pos) { m_shape.setPosition(pos); }//setPosition
	const sf::Vector2f& getPositionShape()const { return m_shape.getPosition(); }//getPositionShape
	float getSpeed()const { return m_maxSpeed; }//getSpeed
	void setVelocity(const sf::Vector2f& velocity) { m_currVelocity = velocity;}//setVelocity
	const sf::CircleShape& getShape()const { return m_shape; }//getShape
	const sf::Vector2f& getCurrVelocity()const { return m_currVelocity; }//getCurrVelocity
	void setShape(const sf::CircleShape& shape) { m_shape = shape; }//setShape
	bool getDell()const { return m_isDell; }//getDell
	void setDell() { m_isDell = true; }//setDell
private:
	//-------------------------data members-------------------------------------
	sf::CircleShape m_shape; //m_shape
	sf::Vector2f m_currVelocity; //m_currVelocity
	float m_maxSpeed;//m_maxSpeed
	bool m_isDell = false;//m_isDell
};




