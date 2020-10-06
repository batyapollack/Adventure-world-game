//----------------------------------include----------------------------------------
#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <vector>
//------------------------------class Creature-------------------------------------
class Creature
{
public:
	Creature(); //Ctor of Creature
	virtual ~Creature(){} //virtual Dtor  of Creature
	Creature(const sf::Vector2f& pos);//C'TOR OBJECT THAT UPDATE THE POSITION
	 void draw(sf::RenderWindow& window) ;//draw
	 void setPosition(const sf::Vector2f& pos) { m_Sprite.setPosition(pos); }//setPosition
	 sf::Vector2f getPosition()const { return m_Sprite.getPosition(); }//getPosition
	 void setOriginal(const sf::Vector2f& pos) { m_Sprite.setOrigin(pos); }//setOriginal
	 bool isContains(const sf::Vector2f& pos)const { return m_Sprite.getGlobalBounds().contains(pos); }//isContains
	 const sf::FloatRect& getGlobalBound() {return m_Sprite.getGlobalBounds(); }//getGlobalBound
	 sf::Vector2i getBoardLocation();//getBoardLocation
	
protected:
	//---------------------------data membebrs-----------------------------------------
	sf::Texture m_Texture; //SFML TEXTURE THAT HOLD THE TEXTURE
	sf::Sprite m_Sprite;  //SFML SPRITE THAT HOLD THE SPRITE 
};

