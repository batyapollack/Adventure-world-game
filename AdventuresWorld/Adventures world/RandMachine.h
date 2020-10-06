//-----------------------------include----------------------------------------
#pragma once
#include "NoneAlive.h"
//---------------------------class RandMachine---------------------------------
class RandMachine:public NoneAlive
{
public:
	RandMachine(); //default ctor of RandMachine
	~RandMachine();//Dtor of RandMachine
	RandMachine(const sf::Vector2f& pos);//C'TOR OBJECT THAT UPDATE THE POSITION
	const float&   getClockMachine()const { return myClockMachine.getElapsedTime().asSeconds(); } //getClockMachine
	void setmyClockMachine() { myClockMachine.restart(); } //setmyClockMachine

private:
	//-----------------data members---------------------------------------------
	sf::Clock myClockMachine;//myClockMachine
	static bool m_registerit;//m_registerit
};

