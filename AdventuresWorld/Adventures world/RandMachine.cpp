//---------------------------include-------------------------------------------
#include "RandMachine.h"
#include "Factory.h" //
#include "MediaSource.h"
//---------------------------static--------------------------------------------
bool RandMachine::m_registerit = Factory::registerit(RAND_MACHINE_T,
	[]() -> std::unique_ptr<Creature> { return std::make_unique<RandMachine>(); });

//-------------------------RandMachine-----------------------------------------
//function that update texture and retart the clock
RandMachine::RandMachine()
{
	m_Sprite.setTexture(MediaSource::instance().getTexture(ENEMY_HOME_P));
	myClockMachine.restart();
}
//------------------------~RandMachine-----------------------------------------
//Dtor of RandMachine
RandMachine::~RandMachine()
{
}
//----------------------RandMachine--------------------------------------------
RandMachine::RandMachine(const sf::Vector2f & pos)
	:NoneAlive(pos)
{

}
