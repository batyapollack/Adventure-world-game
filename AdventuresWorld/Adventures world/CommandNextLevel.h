//------------------------------include--------------------------------
#pragma once
#include "Command.h"
#include "Controller.h"
//--------------------------class CommandNextLevel----------------------
class CommandNextLevel : public Command
{
public:
	CommandNextLevel(Controller &obj) : m_obj(obj) {}; //CommandNextLevel
	virtual void execute() { m_obj.nextLevel(); };//execute

private:
	//-----------------data members-------------------------------------
	Controller & m_obj;//m_obj
};
