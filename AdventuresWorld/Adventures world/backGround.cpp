//--------------------------inclde-----------------------------------
#include "backGround.h"
#include "Macros.h"
#include "MediaSource.h"
//----------------------backGround------------------------------------
//Ctor that call function handleBackground
backGround::backGround()
{
	handleBackground();
}

backGround::~backGround()
{
}




























































































void backGround::handleBackground()
{
	for (int i = 0; i < m_background.size(); i++)
	{
		if (i != 0 && i % 3 == 0)
			m_pos = { m_pos.x = 0,m_pos.y + 450 };

		m_background[i].setTexture(MediaSource::instance().getTexture(BACKGROUND_P));
		m_background[i].setPosition(m_pos);
		m_background[i].setColor(sf::Color::Green);
		m_pos = { m_pos.x + 800,m_pos.y };
	}

}

