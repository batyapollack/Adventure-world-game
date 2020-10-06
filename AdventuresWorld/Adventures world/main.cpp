//--------------------------include--------------------------------------------
#ifdef _DEBUG
#pragma comment(lib, "sfml-main-d.lib")
#elif defined(NDEBUG)
#pragma comment(lib, "sfml-main.lib")
#else
#error "Unrecognized configuration!"
#endif

#include <SFML\Graphics.hpp>
#include "Controller.h"
//------------------------main-------------------------------------------------
int main()
{
	Controller::getInstace().run();
	return 0;
}