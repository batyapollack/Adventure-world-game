//-------------INCLUDE----------------------------------------------------
#include "Creature.h"
#include "Macros.h"
//---------------Creature--------------------------------------------------
//default Ctor 
Creature::Creature()
{
}
//--------------------Creature---------------------------------------------
Creature::Creature(const sf::Vector2f& pos)
{
}
//-------------------draw--------------------------------------------------
//function that darw obj on screen
void Creature::draw(sf::RenderWindow & window)
{
	window.draw(m_Sprite);
}
//----------------getBoardLocation------------------------------------------
//function that return pos on board
sf::Vector2i Creature::getBoardLocation()
{
	sf::Vector2i temp;
	temp.y = static_cast<int> ((m_Sprite.getPosition().x) / (int)SIZE_TILE);
	temp.x = static_cast<int> ((m_Sprite.getPosition().y) /(int) SIZE_TILE);
	return temp;
}
//---------------------------------------------------------------------------



