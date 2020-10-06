//-------------------------incude----------------------------------------------
#include "Key.h"
#include "Factory.h" 
#include "MediaSource.h"
//----------------------static-------------------------------------------------
bool Key::m_registerit = Factory::registerit(KEY_T,
	[]() -> std::unique_ptr<Creature> { return std::make_unique<Key>(); });
//----------------------Key----------------------------------------------------
//Ctor of Key loading the texture
Key::Key()
{
	m_Sprite.setTexture(MediaSource::instance().getTexture(KEY_P));
}

Key::Key(const sf::Vector2f& pos)
	:Items(pos)
{
}
//------------------~Key-------------------------------------------------------
//Dtor of Key
Key::~Key()
{
}
