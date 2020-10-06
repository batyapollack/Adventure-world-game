//--------------------------------include------------------------------
#pragma once
#include "Command.h"
#include "Controller.h"
//--------------------------class CommandOpenStartMenu ----------------
class CommandOpenStartMenu : public Command
{
public:
	CommandOpenStartMenu(Controller &obj) : m_obj(obj) {}; //CommandOpenStartMenu
	virtual void execute() { m_obj.openStartMenu(); }; //execute

private:
	//----------------------data members--------------------------------
	Controller & m_obj;//m_obj
};
