//------------------------include-------------------------------
#include "CommandMap.h"
//----------------------getInstace------------------------------
//function that Create a single Instance of CommandMap
CommandMap& CommandMap::getInstace()
{
	static CommandMap cmdMap; // singleton
	return cmdMap;
}
//--------------------registerCommand----------------------------
//function that insert to map the command(string and object coomnd)
//and return true for static object
bool CommandMap::registerCommand(const std::string & cmdName, std::unique_ptr<Command> && cmd)//rValue
{
	m_map.emplace(cmdName, std::move(cmd));
	return true;
}
//-------------------doCommand-----------------------------------
//function that get string of command and find if exists in map,
//If so execute the command
void CommandMap::doCommand(const std::string &cmdName)
{
	auto currCmd = m_map.find(cmdName);

	if (currCmd != m_map.end())
	currCmd->second->execute(); // do the cmd
}

