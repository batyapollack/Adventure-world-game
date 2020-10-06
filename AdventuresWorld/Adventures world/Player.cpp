//--------------------------include--------------------------------------------
#include "Player.h"
#include "Factory.h"
#include "MediaSource.h"
//-------------------------Player----------------------------------------------
//Ctor of Player that update texture
Player::Player()
{
	m_Sprite.setTextureRect({ 0, 0, 48, 48 });
	m_Sprite.setTexture(MediaSource::instance().getTexture(PLAYER_P));
	m_min_game.restart();
}
//------------------------~Player----------------------------------------------
//Dtpr of Player
Player::~Player()
{
}
//-----------------------setDirectionPic---------------------------------------
//function that updates the pic of the player according to its movement
void Player::setDirectionPic(const sf::Vector2f & dir, int i)
{
	if (dir.x > 0.0f)//walking right
	{
		m_Sprite.setTexture(MediaSource::instance().getTexture(PLAYER_P));
		m_Sprite.setTextureRect({ i*SIZE_TILE_ALIVE_HEIGHT,WALKING_RIGHT,SIZE_TILE_ALIVE_HEIGHT, SIZE_TILE_ALIVE_HEIGHT});
	}

	else if (dir.x < 0.0f)//walkingLeft
	{
		m_Sprite.setTextureRect({ i * SIZE_TILE_ALIVE_HEIGHT ,WALKING_LEFT, SIZE_TILE_ALIVE_HEIGHT, SIZE_TILE_ALIVE_HEIGHT });
	}
	else if (dir.y < 0.0f)//walkingUp
	{
		m_Sprite.setTextureRect({ i * SIZE_TILE_ALIVE_HEIGHT,WALKING_UP,SIZE_TILE_ALIVE_HEIGHT, SIZE_TILE_ALIVE_HEIGHT });
	}
	else if (dir.y > 0.0f)//walkingDown
	{
		m_Sprite.setTextureRect({ i * SIZE_TILE_ALIVE_HEIGHT, WALKING_DOWN,SIZE_TILE_ALIVE_HEIGHT, SIZE_TILE_ALIVE_HEIGHT });
	}


}

void Player::resetClock()
{
	m_min_game.restart();
}

void Player::updateForNewGame()
{
	m_life = 3; 
	m_count_ice = 0;

}
