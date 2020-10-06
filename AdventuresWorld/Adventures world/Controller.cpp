//---------------------------------include----------------------------------
#include "Controller.h"
#include "WatchTower.h"
#include "Bullet.h"
#include "Scout.h"
#include "StupidGuard.h"
#include "CommandMap.h"
#include "CommandReStartLevel.h"
#include "CommandNextLevel.h"
#include "CommandExitGame.h"
#include "CommandNewGame.h"
#include "CommandOpenStartMenu.h"
#include <Windows.h>



void Controller::clockGame()
{
	if (m_player.getMinClock() <= 0)
	{
		m_player.setLife();
		m_collisions.returnAliveCreatureHome();
		m_player.resetClock();
	}
	else
	{
		std::string s = std::to_string(m_player.getMinClock());
		m_text.setString(s);
		m_text.setPosition(500, 500);
		m_text.setFillColor(sf::Color::Red);
		m_window.draw(m_text);
	}
}
void Controller::playerLoseGame()
{

	if (m_player.getLife() == 0)
	{

		MediaSource::instance().getSound(SOUND_TRACK_SD).stop();
		m_window.clear();
		sf::Sprite m_lose;
		m_lose.setTexture(MediaSource::instance().getTexture(LOSE_P));
		MediaSource::instance().getSound(LOSE_SD).play();
		MediaSource::instance().getSound(LOSE_SD).setVolume(55.0f);
		sf::View view(sf::Vector2f{ 0.0f,0.0f }, sf::Vector2f(m_window.getSize()));
		m_window.setView(view);
		m_lose.setPosition({ -150.0f,-150.0f });
		m_window.draw(m_lose);
		m_window.display();
		sf::sleep(sf::milliseconds(5000));
		exit();
	}



}
//------------------------Controller---------------------------------------------------
//Ctor that update data members , Loading background music,registering all commands and initializing clocks
Controller::Controller()
:m_curr_level(START),m_backGround(),m_board(m_curr_level, m_player,m_enemies,m_keys,m_snows, m_static_vec,m_boardGraph), m_window(sf::VideoMode::getDesktopMode() / 2, "Adventures World",
	sf::Style::Close | sf::Style::Titlebar ), m_collisions(m_player, m_enemies, m_keys,m_snows, m_static_vec, m_window)
{
	MediaSource::instance().getSound(SOUND_TRACK_SD).play();
	MediaSource::instance().getSound(SOUND_TRACK_SD).setLoop(true);
	MediaSource::instance().getSound(SOUND_TRACK_SD).setVolume(55.f);

	//------REGISTER TO MAP ---COMMAND--------------------------------------------------------------------
	CommandMap::getInstace().registerCommand(RESTART_LEVEL_CMD, std::make_unique<CommandRestartLevel>(*this));
	CommandMap::getInstace().registerCommand(NEXT_LEVEL_CMD, std::make_unique<CommandNextLevel>(*this));
	CommandMap::getInstace().registerCommand(NEW_GAME_CMD, std::make_unique<CommandNewGame>(*this));
	CommandMap::getInstace().registerCommand(EXIT_GAME_CMD, std::make_unique<CommandExitGame>(*this));
	CommandMap::getInstace().registerCommand(START_MENU_CMD, std::make_unique<CommandOpenStartMenu>(*this));
	//-----------------------------------------------------------------------------------------------------

	m_window.setVerticalSyncEnabled(true);
	myClockController.restart();
	demonBorn.restart();
}
//----------------------------snowActivate------------------------------------------
// function that erases Snow with the player took it
void Controller::snowActivate()
{

	if (m_player.getCountIce() > 0)
	{
		m_player.setCountIce( - 1);
		myClockFreeze.restart();
		MediaSource::instance().getSound(FREEZ_SD).play();
		MediaSource::instance().getSound(FREEZ_SD).setVolume(100.f);
	}
}
//--------------------------DemonBornFromHome---------------------------------------
//function that creates the guards who leave the house in the direction of the castle 
//and update the enemy's vector accordingly
void Controller::DemonBornFromHome()
{
	for (auto& stat : m_static_vec)
	{
		if (dynamic_cast<RandMachine*> (stat.get()))
		{
			auto a = dynamic_cast<RandMachine*> (stat.get());
			if (a->getClockMachine() >= 5.0f)
			{
				m_enemies.emplace_back(std::make_unique<StupidGuard>());
				m_enemies.back()->setPosition(sf::Vector2f{ a->getPosition().x + 80.0f,a->getPosition().y + 100.0f });
				auto b = dynamic_cast<StupidGuard*>(m_enemies.back().get());
				b->changeTexture();
				a->setmyClockMachine();
			}

		}
	}
}
//----------------------------movePlayer--------------------------------------------------------------
// function that updates the position of the player according to its movement
void Controller::movePlayer( sf::Keyboard::Key code)
{
	const int distance = 13;
	switch (code)
	{
	case sf::Keyboard::Left:
		m_player.setPosition({ m_player.getPosition().x - distance, m_player.getPosition().y });
		break;
	case sf::Keyboard::Right:
		m_player.setPosition({ m_player.getPosition().x + distance, m_player.getPosition().y });
		break;
	case sf::Keyboard::Up:
		m_player.setPosition({ m_player.getPosition().x , m_player.getPosition().y- distance });
		break;
	case sf::Keyboard::Down:
		m_player.setPosition({ m_player.getPosition().x , m_player.getPosition().y + distance });
		break;
	}
}
//-------------------------------setViewAndZoom----------------------------------------------------
//function that create view
void Controller::setViewAndZoom()
{
	std::string m_str_freeze = std::to_string(m_player.getCountIce());
	std::string m_str_life = std::to_string(m_player.getLife());
	std::string m_str_keys = std::to_string(m_player.getNextLevel());
	sf::View view(m_player.getPosition(), sf::Vector2f(m_window.getSize()));
	m_life_text.setPosition(m_player.getPosition().x, m_player.getPosition().y+40);
	m_life_text.setString("      life: "+ m_str_life+ '\n'+ "      ice: "+  m_str_freeze +'\n' + "      access: " + m_str_keys);
	m_life_text.setFont(MediaSource::instance().getFont());
	m_life_text.setFillColor(sf::Color::Yellow);
	m_life_text.setScale(0.4, 0.4);
	view.zoom(zoomFactor);
	m_window.setView(view);
}
//----------------------------drawall--------------------------------------------------------------
// function that draws all the objects on the screen
void Controller::drawall()
{
	for (int i = 0; i < NUM_BACKGROUND; i++)
		m_window.draw(m_backGround.getBackground(i) );
	drawStaticVec();
	drawKeys();
	drawSnows();
	drawEnemy();
	m_player.draw(m_window);
	drawBullets();
	m_window.draw(m_life_text);
}
//---------------------------drawEnemy---------------------------------------------------------------
//function that draws all the enemies on the screen
void Controller::drawEnemy()
{
	for (int i = 0; i < m_enemies.size(); i++)
	{
		auto a = dynamic_cast <WatchTower*> (m_enemies[i].get());
		if (a)
		{
			a->drawRange(m_window);
			break;
		}
	}
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->draw(m_window);
	}
}
//--------------------------drawKeys-------------------------------------------------------
//function that draws all the keys on the screen
void Controller::drawKeys()
{
	for (int i = 0; i < m_keys.size(); i++)
		m_keys[i]->draw(m_window);
}
//-------------------------drawSnows--------------------------------------------------------
//function that draws all the Snows on the screen
void Controller::drawSnows()
{
	for (int i = 0; i < m_snows.size(); i++)
	{
		m_snows[i]->draw(m_window);
	}
}
//-------------------------createMinimapview-----------------------------------
//function that create Mini map view
sf::View Controller::createMinimapview()
{
	sf::Vector2f start({ 0.0f,0.0f });
	sf::Vector2f end({ 5000.0f,2000.0f });
	sf::View minimapView((end - start) / 2.f + start, (end - start));
	minimapView.setViewport(sf::FloatRect(0.75f, 0, 0.50f, 0.50f));
	return minimapView;
}
//------------------------playerAnime-----------------------------------------
//function that according to the movement of the player updates his step
void Controller::playerAnime()
{
	if (i > 3)//for step of bomber
		i = 0;
	m_player.setDirectionPic(m_dir, i);
	m_dir = { 0.0f,0.0f };
}
//-----------------------run------------------------------------------------------
// function that manages the event loop
void Controller::run()
{
	m_window.clear();
	m_menu.openMainMenu(m_window);

	//function that run while window open 
	while (m_window.isOpen())
	{
		clockGame();

		playerLoseGame();

		if (levelRestart)
		{
		
			MediaSource::instance().getSound(SOUND_TRACK_SD).stop();
			MediaSource::instance().getSound(SOUND_TRACK_SD).play();
			MediaSource::instance().getSound(SOUND_TRACK_SD).setVolume(55.f);

			clearAllDataBase();
			m_board.insertToMatrix(m_curr_level, m_player, m_enemies, m_keys, m_snows, m_static_vec, m_boardGraph);
			levelRestart = false;
		}

		if (m_collisions.getEndLevel())
		{
			m_collisions.setEndLevel(false);
			newLevel();
		}
		m_player.setPrevLocPosition( m_player.getPosition());
		
		m_window.clear();
		setViewAndZoom();
		playerAnime();
		drawall();
		minimapHandle();
		m_window.display();

		if (myClockController.getElapsedTime().asSeconds() >= 0.03f)
		{
			if (demonBorn.getElapsedTime().asSeconds() >= 30.0f)
			{
				DemonBornFromHome();
				demonBorn.restart();
			}
			if (!(m_collisions.checkCollidePlayer(m_player.getPosition())) && m_player.getCollideEnemy())
			{
				m_player.setCollideEnemy(false);
				m_collisions.returnAliveCreatureHome();
			}
			if (myClockFreeze.getElapsedTime().asSeconds() >= 3.0f||first)
			{
				if (myClockFreeze.getElapsedTime().asSeconds() >= 3.0f)
					first = false;
				enemyCollide();
			
			}
			
			handleEvents();
			myClockController.restart();
		}

	}
}
//--------------------------------restart-----------------------------------------------------
//function of menu  that update levelRestart
void Controller::restart()
{
	levelRestart = true;

}
//-----------------------------nextLevel------------------------------------------------------
//function of menu  that increases the m_curr_level,That is load a new level
void Controller::nextLevel()
{
	m_curr_level++;
	levelRestart = true;
}
//----------------------------newGame---------------------------------------------------------
//function of menu that resets the m_curr_level to load the first level
void Controller::newGame()
{
	m_curr_level = 1; // to restart from level 1
	m_player.updateForNewGame();
	levelRestart = true;
}
//--------------------------------openStartMenu-----------------------------------------------
//function of menu that open the Start Menu
void Controller::openStartMenu()
{
	m_menu.openMainMenu(m_window);
}
//-----------------------------exit-----------------------------------------------------------
//function of menu that close the game
void Controller::exit()
{
	clearAllDataBase();
	m_window.close();
}
//-------------------------clearAllDataBase---------------------------------------------------
//funcction that clear all data base
void Controller::clearAllDataBase()
{
	m_enemies.clear();
	m_static_vec.clear();
	m_snows.clear();
	m_keys.clear();
	for (int i = 0; i < m_boardGraph.size(); i++)
		m_boardGraph[i].clear();
	m_boardGraph.clear();
	m_window.clear();

}
//-----------------------newLevel------------------------------------------------------------
//function that load new level and insert data from file to  data base
void Controller::newLevel()
{
	clearAllDataBase();
	m_curr_level++;
	if (!m_board.insertToMatrix(m_curr_level, m_player, m_enemies, m_keys, m_snows, m_static_vec, m_boardGraph))
	{
		//	m_backGround.clearBackground();
		m_player.setColor();
		MediaSource::instance().getSound(SOUND_TRACK_SD).stop();
		MediaSource::instance().getSound(WIN_SD).play();
		MediaSource::instance().getSound(WIN_SD).setVolume(55.0f);
		sf::Sprite m_win;
		m_win.setTexture(MediaSource::instance().getTexture(WIN_P));

		/*	sf::Vector2f m_pos= { sf::VideoMode::getDesktopMode().height / 2.0f, sf::VideoMode::getDesktopMode().width / 2.0f };
			m_win.setPosition(m_pos);*/
		sf::View view(sf::Vector2f{ 0.0f,0.0f }, sf::Vector2f(m_window.getSize()));
		m_win.setPosition({-150.f,-150.0f });
		view.zoom(zoomFactor);
		m_window.setView(view);
		m_window.draw(m_win);

		//m_window.draw(m_text);
		m_window.display();
		sf::sleep(sf::milliseconds(9000));
		exit();
	}
}

//--------------------enemyCollide------------------------------------------------------------
//function that moves the enemies (each one and its movement) and checks whether the move is normal
void Controller::enemyCollide()
{
	for (int i = 0; i < m_enemies.size(); i++)
	{
		auto tower = dynamic_cast<WatchTower*> (m_enemies[i].get());
		if (tower)
		{
			if (tower->moveBullets(m_window, m_static_vec, m_player))
			{
				MediaSource::instance().getSound(COLLIDE_SD).play();
				MediaSource::instance().getSound(COLLIDE_SD).setVolume(70.f);
				m_player.setLife();
				m_collisions.returnAliveCreatureHome();
				break;
			
			}
		}
		auto scout = dynamic_cast<Scout*>(m_enemies[i].get());
		if (scout)
		{
			scout->moveScout(m_boardGraph, m_player.getBoardLocation());
			continue;
		}
		auto guard = dynamic_cast<Guard*>(m_enemies[i].get());
		if (guard)
		{
			if (m_collisions.checkCollideEnemies(i))
				guard->moveEnemy();

				guard->changeGuradanime();
			
			m_collisions.checkCollideEnemies(i);
		}

	}

}
//-----------------------------minimapHandle--------------------------------------------------
//function that updates the position of the mini map
void Controller::minimapHandle()
{
	if (miniMap)
	{
		auto view = m_window.getView();
		m_window.setView(createMinimapview());
		drawall();
		sf::RectangleShape frame(m_window.getView().getSize() - sf::Vector2f(2.f, 2.f));
		frame.setPosition(m_window.getView().getCenter() - frame.getSize() / 2.f);
		frame.setFillColor(sf::Color::Transparent);
		frame.setOutlineColor(sf::Color::Yellow);
		frame.setOutlineThickness(2);
		m_window.draw(frame);
		m_window.setView(view);
	}
}
//-----------------------handleEvents---------------------------------------------------------
// function that checks the state of events in the game and works accordingly
void Controller::handleEvents()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_dir.x += 1.0f;
			i++;
			if (m_collisions.checkCollidePlayer(m_player.getPosition()))//curent position
			{
				movePlayer(sf::Keyboard::Right);// move step
					if (!m_collisions.checkCollidePlayer(m_player.getPosition()))//check the new step
						m_player.setPosition(m_player.getPrevLoc());// if fail return curent position
			}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_dir.x -= 1.0f;
		i++;
		if (m_collisions.checkCollidePlayer(m_player.getPosition()))
		{
			movePlayer(sf::Keyboard::Left);
			if (!m_collisions.checkCollidePlayer(m_player.getPosition()))
				m_player.setPosition(m_player.getPrevLoc());
		}
	}
	 else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{

		m_dir.y -= 1.0f;
		i++;
		if (m_collisions.checkCollidePlayer(m_player.getPosition()))
		{
			movePlayer(sf::Keyboard::Up);
			if (!m_collisions.checkCollidePlayer(m_player.getPosition()))
				m_player.setPosition(m_player.getPrevLoc());
		}
	}

	 else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{

		m_dir.y += 1.0f;
		i++;
		 if (m_collisions.checkCollidePlayer(m_player.getPosition()))
		{
			movePlayer(sf::Keyboard::Down);
			if (!m_collisions.checkCollidePlayer(m_player.getPosition()))
				m_player.setPosition(m_player.getPrevLoc());
		}
	}
		
	sf::Event event;
	srand((unsigned)time(NULL));
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window.close();

		if (event.type==sf::Event::TextEntered)
			switch (event.text.unicode)
			{
			case '+':
			case '-':
				zoomFactor *= (event.text.unicode == '+' ? .5f : 2.f);
				break;
			case 'm':
				miniMap = !miniMap;
				break;

			case 'f':
				snowActivate();
				break;
			}
		if (event.type == sf::Event::KeyPressed)//KeyPressed
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				m_menu.openPauseMenu(m_window);
				break;
			case 'm':
				miniMap = !miniMap;
				break;


		

			}
	}
}
//-----------------------~Controller----------------------------------------------------------
//Dtor of Controller
Controller::~Controller()
{
}
//------------------------getInstace----------------------------------------------------------
//function that Create a single Instance of Controller
Controller & Controller::getInstace()
{
	static Controller master;//singleton
	return master;
}
//-----------------------operator/------------------------------------------------------------
//function that return pos of mini map
sf::VideoMode operator/(const sf::VideoMode & mode, unsigned denom)
{
	return { mode.width / denom, mode.height / denom, mode.bitsPerPixel };
}

//-----------------------drawStaticVec--------------------------------------------------------
//function that draw all static obj
void Controller::drawStaticVec()
{
	for (int i = 0; i < m_static_vec.size(); i++)
			(m_static_vec[i])->draw(m_window);
	
}
//------------------------drawBullets---------------------------------------------------------
//function that draw all bullets
void Controller::drawBullets()
{
	for (int i = 0; i < m_enemies.size(); i++)
	{
		auto a = dynamic_cast <WatchTower*> (m_enemies[i].get());
		if (a)
			a->drawBullets(m_window);
	}
}





