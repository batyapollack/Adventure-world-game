//----------------------------------include------------------------------------
#pragma once
#include <SFML\Graphics.hpp>
//----------------------------Size of objects----------------------------------
const float SIZE_TILE = 40.0f;
const int SIZE_TILE_ALIVE = 25;
const int SIZE_TILE_ALIVE_HEIGHT =48;
const int SIZE_TILE_ALIVE_WIDTH = 32;
//---------------------------speed----------------------------------------------
const int SPEED_GUARD = 8;
//-----------------------------sign of obj--------------------------------------
const char EMPTY_SIGN = ' ';
const char PLAYER_SIGN = '/';
const char  STUPID_GAURD_SIGN = '}';
const char SCOUT_SIGN = '$';
const char WALL_SIGN = '#';
const char CASTLE_SIGN = 'c';
const char ROCK_SIGN = '@';
const char KEY_SIGN = 'k';
const char SPCACE_SIGN = ' ';
const char ARROW_SIGN = 'a';
const char WATCH_TOWER_SIGN = 't';
const char RAND_MACHINE_SIGN = 'r';
const char SNOW_SIGN = 's';
//-----------------------Direction of movement-------------------------
enum DIRECTION{ LEFT_D, RIGHT_D, UP_D, DOWN_D, NONE_D };
//---------------------side--------------------------------------------
const int UP_SIGN = 0;
const int RIGHT_SIGN = 1;
const int DOWN_SIGN = 2;
const int LEFT_SIGN = 3;
//------------------------Collision points-----------------------------
const sf::Vector2f RIGHT = { static_cast<float>(SIZE_TILE_ALIVE_WIDTH),0.0f };
const sf::Vector2f DOWN = { 0.0f, static_cast<float> (SIZE_TILE_ALIVE_HEIGHT) };
const sf::Vector2f RIGHT_SLANT = { static_cast<float>(SIZE_TILE_ALIVE_WIDTH), static_cast<float> (SIZE_TILE_ALIVE_HEIGHT) };
//--------------------For loading images---------------------------------
enum CREATURE_T{
	STUPID_GAURD_T,
	SCOUT_T,
	WACTH_TOWER_T ,
	WALL_T,
	CASTLE_T,
	ROCK_T,
	KEY_T,
	RAND_MACHINE_T,
	EMPTY_T,
	SNOW_T,
	WOLF_T
};
//-------------------For loading images---------------------------------
enum PICTURE_TYPE
{
	BACKGROUND_P,
	ENEMY_HOME_P,
	WALL_P,
	PLAYER_P, //player
	SCOUT_P,
	KEY_P,
	TOWER_P,
	CASTLE_P,
	STUPID_P, //guard
	SMART_P,
	DOOR_P,
	RANGE_TOWER_P,
	SNOW_P,
	WOLF_P,
	LOSE_P,////window of lose
	WIN_P,//window of win
};
//-------------------for step alive----------------------------------------- 
const int WALKING_RIGHT = SIZE_TILE_ALIVE_HEIGHT * 2;
const int WALKING_LEFT = SIZE_TILE_ALIVE_HEIGHT * 1;
const int WALKING_DOWN = SIZE_TILE_ALIVE_HEIGHT * 0;
const int WALKING_UP = SIZE_TILE_ALIVE_HEIGHT * 3;
//-----------------screen size--------------------------------------------
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;
//---------------SOUNDS------------------------------------------------
enum SOUNDS { SOUND_TRACK_SD, SOUND_TOWER_SD, KEY_SD,ICE_SD,FREEZ_SD,WIN_SD, COLLIDE_SD, WOLF_SD,LOSE_SD};

//----------------------------for menu---------------------------------
#define TEXTURE_FILE std::string("texture.png")
#define TEXTURE_DATA_FILE std::string("tilepos.txt")
const std::string RESTART_LEVEL_CMD = "restart level";
const std::string NEXT_LEVEL_CMD = "next level";
const std::string SHOOT_ARROW = "shoot arrow";
const std::string NEW_GAME_CMD = "new game";
const std::string EXIT_GAME_CMD = "exit game";
const std::string CONTINUE_CMD = "contine game";
const std::string START_MENU_CMD = "nmeun";
//--------------------------------------------------------------------------
const float EPSILON = 10.0f;//EPSILON
const int NUM_BACKGROUND = 9;//NUM_BACKGROUND

