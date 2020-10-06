//-------------------------include--------------------------------------
#pragma once
#include "Command.h"
#include "Controller.h"
//-----------------------class CommandNewGame---------------------------
class CommandNewGame : public Command
{
public:
	CommandNewGame(Controller &obj) : m_obj(obj) {}; //CommandNewGame
	virtual void execute() { m_obj.newGame(); };//execute

private:
	//------------------data members-----------------------------------
	Controller & m_obj; //m_obj
};

