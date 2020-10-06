
//--------------------INCLUDE--------------------------------------------
#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
//---------------------class backGround--------------------------------
class backGround
{
public:
	backGround();//default Ctor of backGround
	~backGround();//Dtor of backGround
	sf::Sprite getBackground(int i)const { return m_background[i]; }//getBackground
	void setColorBackground(int i) { m_background[i].setColor({ 170,240,95 }); }//setColorBackground
	void clearBackground() { m_background.clear(); }

private:
	//--------------------private function----------------------------------
	void handleBackground();//handleBackground
	//-----------------data members-----------------------------------------
	std::vector<sf::Sprite>m_background{ 9 };// m_background
	sf::Vector2f  m_pos = { 0.0f,-150.0f };//m_pos

};
//-------------------------------------------------------------------------

