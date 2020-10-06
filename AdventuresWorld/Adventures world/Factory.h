//----------------------------------include--------------------------------------
#include <algorithm>
#include <memory>
#include <map>
#include <vector>
#include <string>
#include "Creature.h"
#include "Macros.h"
//------------------------------using-------------------------------------------
using namespace std;
//---------------------------static mymap---------------------------------------
typedef std::map<CREATURE_T, std::unique_ptr<Creature>(*)()> mymap;
//-------------------------class Factory-----------------------------------------
class Factory {
public:
	static std::unique_ptr<Creature> create(CREATURE_T name); //create
	static bool registerit(CREATURE_T name, std::unique_ptr<Creature>(*)());//registerit
private:
	//----------------------private function------------------------------------
	//function that creates the map once and returns the map
	static mymap& getMap()
	{
		static mymap m_map;
		return m_map;
	}
};