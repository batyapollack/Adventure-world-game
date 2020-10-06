#include "Menu.h"

//-------------------Menu------------------------------------------------------
//Ctor of Menu that create a game menu 
Menu::Menu()

	:gameTitle(std::string("Advantures World"), MediaSource::instance().getFont())
{
	makeMainMenu();
	makePauseMenu();
	makeSureMenu();

	gameTitle.setCharacterSize(70);	// make the font size
	gameTitle.setFillColor(sf::Color::Transparent); // the color
	gameTitle.setOutlineThickness(2);
	gameTitle.setOutlineColor({169,169,169});

}
//------------------------askSure----------------------------------------------
bool Menu::askSure(std::string question)
// ask the user if he sure to do someing return user answer
{
	sf::Text questionText; // make question text
	questionText.setFont(MediaSource::instance().getFont()); // get font
	questionText.setCharacterSize(FONTSIZE);	// make the font size
	questionText.setFillColor(QUESTION_TEXT_COLOR); // the color
	questionText.setString(question);
	questionText.setPosition(20, 10);

	sureMenu[0]._text.setPosition(questionText.getGlobalBounds().width / 3, 40); // set position to the options
	sureMenu[1]._text.setPosition(sureMenu[0]._text.getPosition().x + 3 * SPACE, 40);

	int selectBotton = 0; // the first selet botton
	sureMenu[selectBotton]._text.setFillColor(BUTTON_SELECT_COLOR); //  select color

																	// ask sure window
	sf::RenderWindow window(sf::VideoMode(
		static_cast<unsigned int> (questionText.getGlobalBounds().width) + SPACE, 80), question);


	while (window.isOpen())
	{
		sf::Event event; // sfml event
		while (window.pollEvent(event))
		{

			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				// return the botton to defaut status
				sureMenu[selectBotton]._text.setFillColor(BUTTON_DEFAULT_COLOR);
				return false;
				break;
			case sf::Event::Resized:
				window.setView(sf::View(sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height)));
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Left:
					moveLeft(selectBotton, sureMenu); // move Botton left
					break;
				case sf::Keyboard::Right:
					moveRight(selectBotton, sureMenu); // move Botton Right
					break;

				case sf::Keyboard::Return: // case user press Enter
					window.close(); // close the window
									// return the botton to defaut status
					sureMenu[selectBotton]._text.setFillColor(BUTTON_DEFAULT_COLOR);
					if (selectBotton == 0) // return what user chose
						return false;
					else
						return true;
					break;
				default:
					break;
				}
			default:
				break;
			}
		}

		window.clear(); // clear window
		window.draw(questionText); // draw the question
		drawMenu(window, sureMenu); // draw the menu
		window.display(); // display the menu

	}

	return false;
}
//--------------------------openMainMenu---------------------------------------
// function that open the mainMenu
void Menu::openMainMenu(sf::RenderWindow & window)
{
	for (size_t i = 0; i < mainMenu.size(); i++) // make text size
		mainMenu[i]._text.setCharacterSize(60);

	gameTitle.setPosition(160, 200);
	mainMenu[0]._text.setPosition(MAIN_SCREEN_SIZE / 3, gameTitle.getPosition().y + SPACE * 3); // set text Position

	for (size_t i = 1; i < mainMenu.size(); i++)
		mainMenu[i]._text.setPosition(mainMenu[i - 1]._text.getPosition().x,
			mainMenu[i - 1]._text.getPosition().y + SPACE * 3); // set text Position

	int selectBotton = 0; // the first selet botton
	mainMenu[selectBotton]._text.setFillColor(BUTTON_SELECT_COLOR); //  select color


	sf::View temp(window.getView());
	temp.setCenter(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	window.setView(temp);

	while (window.isOpen())
	{
		sf::Event event; // sfml event
		while (window.pollEvent(event))
		{

			switch (event.type)
			{
			case sf::Event::Closed:
			{
				if (askSure("You want to exit?   ")) // case user press X
				{
					window.close();
					return;
				}
			}
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Down:
					moveDown(selectBotton, mainMenu); // move Botton down
					break;
				case sf::Keyboard::Up:
					moveUp(selectBotton, mainMenu); // move Botton up
					break;
				case sf::Keyboard::Return: // case user press Enter
										   // return the botton to defaut status
					mainMenu[selectBotton]._text.setFillColor(BUTTON_DEFAULT_COLOR);
					if (selectBotton == 0)
						return;
					else
						CommandMap::getInstace().doCommand(mainMenu[selectBotton]._cmd); // return the botton that press
					return;
					break;
				default:
					break;
				}
			default:
				break;
			}
		}
		window.clear(); // clear window
		window.draw(gameTitle); // draw the game title
		drawMenu(window, mainMenu); // draw the menu
		window.display(); // display the menu
	}

}
//------------------openPauseMenu----------------------------------------------
//function that open Pause Menu
void Menu::openPauseMenu(sf::RenderWindow & window)
{
	for (size_t i = 0; i < pauseMenu.size(); i++) // make text size
		pauseMenu[i]._text.setCharacterSize(40);

	sf::RectangleShape transparentBox(sf::Vector2f(window.getSize())); // make transparebox
	transparentBox.setFillColor(TRANSPARENT_BLACK_COLOR);

	pauseMenu[0]._text.setPosition(static_cast<float>(window.getSize().x / 3),
		static_cast<float>(window.getSize().y / 3)); // set text Position

	for (size_t i = 1; i < pauseMenu.size(); i++)
		pauseMenu[i]._text.setPosition(pauseMenu[i - 1]._text.getPosition().x,
			pauseMenu[i - 1]._text.getPosition().y + SPACE * 3); // set text Position

	int selectBotton = 0; // the first selet botton
	pauseMenu[selectBotton]._text.setFillColor(BUTTON_SELECT_COLOR); //  select color


	sf::View temp(window.getView());
	temp.setCenter(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	temp.reset(sf::FloatRect(0.f, 0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT)));
	temp.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
	window.setView(temp);


	while (window.isOpen())
	{
		sf::Event event; // sfml event
		while (window.pollEvent(event))
		{

			switch (event.type)
			{
			case sf::Event::Closed:
			{
				if (askSure("You want to exit?")) // case user press X
				{
					window.close();
					return;
				}
			}

			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Escape: // when user select esc back to game
					pauseMenu[selectBotton]._text.setFillColor(BUTTON_DEFAULT_COLOR);
					return;
					break;
				case sf::Keyboard::Down:
					moveDown(selectBotton, pauseMenu); // move Botton down
					break;
				case sf::Keyboard::Up:
					moveUp(selectBotton, pauseMenu); // move Botton up
					break;
				case sf::Keyboard::Return: // case user press Enter
										   // return the botton to defaut status

					if (selectBotton == 0) // ask user if he press main screen
						return;

					if (selectBotton == 1) // case new game
						if (askSure("You want new game ?"))
						{
							CommandMap::getInstace().doCommand(pauseMenu[selectBotton]._cmd); // return the botton that press

							return;
						}
						else
							break; // when he select no back to loop
					else if (selectBotton = 2) // ask user if he press exit
						if (askSure("You want to exit?"))
						{
							CommandMap::getInstace().doCommand(pauseMenu[selectBotton]._cmd); // return the botton that press
							return;
						}
						else
							break;  // when he select no back to loop
					pauseMenu[selectBotton]._text.setFillColor(BUTTON_DEFAULT_COLOR);

					CommandMap::getInstace().doCommand(mainMenu[selectBotton]._cmd); // return the botton that press
					break;
				default:
					break;
				}
			default:
				break;
			}
		}
		window.draw(transparentBox); // draw transparentBox on the game
		drawMenu(window, pauseMenu); // draw the menu
		window.display(); // display the menu
	}
}
//--------------------makeMainMenu---------------------------------------------
// make the Main Menu to the Game
void Menu::makeMainMenu()
{
	mainMenu.push_back(MenuItem(NEW_GAME_CMD, "New Game")); // make new game botton
	mainMenu.push_back(MenuItem(EXIT_GAME_CMD, "Exit")); // make exit botton

}
//------------------makePauseMenu----------------------------------------------
void Menu::makePauseMenu()
// make the Pause Menu to the Game
{
	pauseMenu.push_back(MenuItem(CONTINUE_CMD, "Countine")); // make Countine botton
	pauseMenu.push_back(MenuItem(NEW_GAME_CMD, "New Game")); // make exit botton
	pauseMenu.push_back(MenuItem(EXIT_GAME_CMD, "Exit")); // make exit botton
}
//--------------makeSureMenu---------------------------------------------------
// make the SureMenu
void Menu::makeSureMenu()
{
	sureMenu.push_back(MenuItem("No", "No")); // make No botton
	sureMenu.push_back(MenuItem("Yes", "Yes")); // make No botton

}
//----------------drawMenu-----------------------------------------------------
//function that  draw menu to the screen
void Menu::drawMenu(sf::RenderWindow & window, std::vector<MenuItem> menu)
{
	for (size_t i = 0; i < menu.size(); i++)
		window.draw(menu[i]._text);
}
//------------------moveLeft---------------------------------------------------
//function that move the Menu left
void Menu::moveLeft(int &selectBotton, std::vector<MenuItem>& currMenu)
{
	moveUp(selectBotton, currMenu);
}
//-------------------moveRight-------------------------------------------------
// function that move the Menu Right
void Menu::moveRight(int &selectBotton, std::vector<MenuItem>& currMenu)
{
	moveDown(selectBotton, currMenu);
}
//--------------------moveUp---------------------------------------------------
//function that move the Menu Up
void Menu::moveUp(int &selectBotton, std::vector<MenuItem>& currMenu)
{
	currMenu[selectBotton]._text.setFillColor(BUTTON_DEFAULT_COLOR); // return to orgianl color
	selectBotton--; // move up

	if (selectBotton < 0) // case uderflow
		selectBotton = static_cast<int>(currMenu.size()) - 1;

	currMenu[selectBotton]._text.setFillColor(BUTTON_SELECT_COLOR); //  select color
}
//-----------------------moveDown----------------------------------------------
//function that move the Menu Down
void Menu::moveDown(int &selectBotton, std::vector<MenuItem>& currMenu)
{
	currMenu[selectBotton]._text.setFillColor(BUTTON_DEFAULT_COLOR); // return to orgianl color
	selectBotton++; // move bottom down

	if (selectBotton >= static_cast<int>(currMenu.size())) // case overflow
		selectBotton = 0;

	currMenu[selectBotton]._text.setFillColor(BUTTON_SELECT_COLOR); //  select color

}
//-------------------MenuItem--------------------------------------------------
//Ctor of MenuItem that update data to text
MenuItem::MenuItem(const std::string &cmd, const std::string & text) : _cmd(cmd)
{
	_text.setFont(MediaSource::instance().getFont()); // get font
	_text.setCharacterSize(FONTSIZE);	// make the font size
	_text.setFillColor(BUTTON_DEFAULT_COLOR); // the color
	_text.setString(text); // the string
}
