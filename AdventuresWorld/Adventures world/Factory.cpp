#include "Factory.h"



std::unique_ptr<Creature> Factory::create(CREATURE_T name) {
	auto it = getMap().find(name);
	if (it == getMap().end())
		return nullptr;
	return it->second();
}

bool Factory::registerit(CREATURE_T name, std::unique_ptr<Creature>(*f)())
{
	getMap().emplace(name, f);
	return true;
}