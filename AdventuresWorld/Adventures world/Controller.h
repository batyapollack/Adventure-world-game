//-----------------------------------include---------------------------
#pragma once
#include "Board.h"
#include "Player.h"
#include "Guard.h"
#include "backGround.h"
#include "Key.h"
#include "Wall.h"
#include "Castle.h"
#include "RandMachine.h"
#include"Collision.h"
#include "MediaSource.h"
#include "Snow.h"
#include "Menu.h"
//----------------------------------class--------------------------------
class Bullet;
//------------------------------global data------------------------------
const unsigned int START = 1;
//-----------------------------class Controller--------------------------
class Controller
{
public:
	~Controller(); //Dtor of Controller
	static	Controller& getInstace(); //getInstace
	Controller(const Controller &) = delete; // delete copy Ctpr
	auto operator=(const Controller &) = delete; //delete operator=
	void run(); //run
	//------------------function of Menu-------------------------------
	void restart(); //restart Level
	void nextLevel(); //next Level
	void newGame(); //newGame
	void openStartMenu();//openStartMenu
	void exit();//exit

private:
	//------------------ private function -------------------------------
	void clearAllDataBase();//clearAllDataBase
	void newLevel();//newLevel
	void enemyCollide();//enemyCollide
	void minimapHandle();//minimapHandle
	void DemonBornFromHome();//DemonBornFromHome
	void movePlayer(sf::Keyboard::Key code); //movePlayer
	void setViewAndZoom();//setViewAndZoom
	void drawall();//drawall
	void drawEnemy();//drawEnemy
	void drawKeys();//drawKeys
	void drawSnows();//drawSnows
	void drawStaticVec();//drawStaticVec
	void drawBullets();//drawBullets
	sf::View createMinimapview();//createMinimapview
	void playerAnime();//bomberAnime
	void handleEvents();//handleEvents
	void setIndexOfRandMachine(const int& i) { m_index_machine = i; }//setIndexOfRandMachine
	void snowActivate();//snowActivate
	void setHomeEnemtIndex(int i) { setHomeINdex = i; } //setHomeEnemtIndex
	void clockGame();//clockGame
	void playerLoseGame();//playerLoseGame
	Controller();//Ctor of Controller

    //-------------------data members-------------------------------------
	bool levelRestart; //levelRestart of Menu
	Menu m_menu;//m_menu
	unsigned int m_curr_level;//m_curr_level

	Player m_player;//m_player
	std::vector<std::unique_ptr <Enemy>> m_enemies;//m_enemies
	std::vector<std::unique_ptr <Key>> m_keys;//m_keys
	std::vector<std::unique_ptr <Snow>> m_snows;//m_snows
	std::vector<std::unique_ptr<NoneAlive>> m_static_vec;//m_static_vec
	std::vector <std::vector<bool>> m_boardGraph; // to view the boad as graph

	backGround m_backGround; //m_backGround
	Board m_board;//m_board
	Collision m_collisions;//m_collisions
	sf::RenderWindow m_window;//m_window
	sf::Clock myClockController;//myClockController
	sf::Clock  myClockFreeze;//myClockFreeze
	int i = 0;//for step player
	sf::Vector2f startPoint = {};//startPoint
	sf::Vector2f centerOfView = {};//centerOfView
	float zoomFactor = 1;//zoomFactor
	bool miniMap = false;//miniMap
	sf::Vector2f m_dir = { 0.0f,0.0f };//m_dir
	int m_index_machine; //m_index_machine
	bool first = true;//first
	int setHomeINdex = 0; //setHomeINdex
	sf::Clock demonBorn;//demonBorn
	sf::Sprite m_lose;//m_lose
	sf::Text m_text;//m_text
	sf::Text m_life_text;
	
};
// Scale down sf::VideoMode by dividing its elemnts by denom
sf::VideoMode operator/(const sf::VideoMode& mode, unsigned denom);
