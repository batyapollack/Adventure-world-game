//---------------------------include--------------------------------------
#pragma once
#include "MediaSource.h"
#include "Macros.h"
#include "CommandMap.h"
#include <SFML\Graphics.hpp>
#include <string>
//----------------------const------------------------------------------------------------
const int FONTSIZE = 30;
const int SPACE = 40;
const float  MAIN_SCREEN_SIZE = 720.f;
const sf::Color BUTTON_DEFAULT_COLOR = sf::Color(102, 102, 0); // draw yellow color
const sf::Color BUTTON_SELECT_COLOR = sf::Color::Green;
const sf::Color QUESTION_TEXT_COLOR = sf::Color::Red;
const sf::Color TRANSPARENT_BLACK_COLOR = sf::Color(25, 25, 25, 5);	// ttansparent black color
const sf::Color GREEN_COLOR = sf::Color::Green; // green color for the game
//--------------------struct MenuItem----------------------------------------------------
struct MenuItem
{
	sf::Text _text; //text
	std::string  _cmd; //command
	MenuItem(const std::string &cmd, const std::string &text);//Ctor of MenuItem
};
//-------------------class Menu-----------------------------------------------------------
class Menu
{
public:
	Menu(); //Ctor of Menu
	bool askSure(std::string question); //askSure
	void openMainMenu(sf::RenderWindow &window);//openMainMenu
	void openPauseMenu(sf::RenderWindow &window);//openPauseMenu

private:
	//------------------------prive=ate function-----------------------------------------
	void makeMainMenu();//makeMainMenu
	void makePauseMenu();//makePauseMenu
	void makeSureMenu();//makeSureMenu
	void drawMenu(sf::RenderWindow &window, std::vector<MenuItem> menu);//drawMenu
	void moveLeft(int &selectBotton, std::vector<MenuItem> &currMenu);//moveLeft
	void moveRight(int &selectBotton, std::vector<MenuItem> &currMenu); //moveRight
	void moveUp(int &selectBotton, std::vector<MenuItem> &currMenu);//moveUp
	void moveDown(int &selectBotton, std::vector<MenuItem> &currMenu);//moveDown
	sf::Text gameTitle;//text of menu
	//--------------------------data members---------------------------------------------
	std::vector<MenuItem> mainMenu;//mainMenu
	std::vector<MenuItem>  pauseMenu;// pauseMenu
	std::vector<MenuItem>  sureMenu;// to ask if the user if he Sure the opsition he chose

};