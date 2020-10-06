//-------------------------------include-------------------------------
#pragma once
#include "Command.h"
#include "Controller.h"
//-------------------------class CommandRestartLevel -----------------
class CommandRestartLevel : public Command
{
public:
	CommandRestartLevel(Controller &obj) : m_obj(obj) {};//CommandRestartLevel
	virtual void execute() { m_obj.restart(); };//execute

private:
	//-----------------------data members------------------------------
	Controller & m_obj; //m_obj
};