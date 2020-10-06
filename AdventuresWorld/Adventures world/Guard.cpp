#include "Guard.h"
#include "Macros.h"
#include "MediaSource.h"


Guard::Guard()
{
}

Guard::Guard(const sf::Vector2f & pos)
	:Enemy(pos)
{
}







void Guard::setPicAnime()
{
	if (m_dir.x > 0.0f)//walking right
	{

		m_Sprite.setTextureRect({ i*SIZE_TILE_ALIVE_HEIGHT,WALKING_RIGHT,SIZE_TILE_ALIVE_HEIGHT, SIZE_TILE_ALIVE_HEIGHT });
	}

	else if (m_dir.x < 0.0f)//walkingLeft
	{
		m_Sprite.setTextureRect({ i * SIZE_TILE_ALIVE_HEIGHT ,WALKING_LEFT, SIZE_TILE_ALIVE_HEIGHT, SIZE_TILE_ALIVE_HEIGHT });
		//m_Sprite.setTexture(Media_source::instance().get(t_bomber));

	}
	else if (m_dir.y < 0.0f)//walkingUp
	{
		m_Sprite.setTextureRect({ i * SIZE_TILE_ALIVE_HEIGHT,WALKING_UP,SIZE_TILE_ALIVE_HEIGHT, SIZE_TILE_ALIVE_HEIGHT });
		//m_Sprite.setTexture(Media_source::instance().get(t_bomber));
	}
	else if (m_dir.y > 0.0f)//walkingDown
	{
		m_Sprite.setTextureRect({ i * SIZE_TILE_ALIVE_HEIGHT, WALKING_DOWN,SIZE_TILE_ALIVE_HEIGHT, SIZE_TILE_ALIVE_HEIGHT });
	}
}

void Guard::changeGuradanime()
{
-	i++;
	if (i > 3)
		i = 0;
	setPicAnime();
	//m_dir = { 0.0f,0.0f };
}

Guard::~Guard()
{
}
