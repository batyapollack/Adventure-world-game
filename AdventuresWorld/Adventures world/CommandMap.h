//---------------------------include------------------------------------
#pragma once
#include <map>
#include <memory>
#include "Command.h"
#include "Macros.h"
//--------------------------Class CommandMap----------------------------
class CommandMap
{
public:
	static CommandMap& getInstace();//getInstace
	bool registerCommand(const std::string &cmdName, std::unique_ptr<Command> && cmd); // add new cmd
	void doCommand(const std::string &cmdName); //doCommand
	CommandMap(const CommandMap&) = delete; //delete Copy Cotr
	auto operator=(const CommandMap&) = delete; //delete Assignment operator

private:
	//--------------------private function-------------------------------
	CommandMap() {}; //default Ctor
	//--------------------data members-----------------------------------
	std::map<std::string, std::unique_ptr<Command> >  m_map; // map to return object
};
