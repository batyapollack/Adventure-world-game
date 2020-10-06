//-------------------------include------------------------------------
#pragma once
#include "Command.h"
#include "Controller.h"
//----------------------- CommandExitGame ----------------------------
class CommandExitGame : public Command
{
public:
	CommandExitGame(Controller &obj) : m_obj(obj) {}; //CommandExitGame
	virtual void execute() { m_obj.exit(); };//execute

private:
	//-------------------data members---------------------------------
	Controller & m_obj; //m_obj
};
