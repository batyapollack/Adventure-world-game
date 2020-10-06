//----------------------------------include----------------------------------------
#pragma once
#include "SFML/Graphics.hpp"
#include "Macros.h"
#include <SFML/Audio.hpp>
//----------------------------class MediaSource------------------------------------
class MediaSource
{
public:
	static MediaSource& instance();//return single instance
	sf::Sound & getSound(const SOUNDS& sound);//getSound
	const sf::Texture & getTexture(PICTURE_TYPE t)const; //return type pic
	const sf::Font& getFont() const { return font; }// return the font that load for the game
	~MediaSource();//Dtor of MediaSource
private:
	//--------------------private function-------------------------------------------
	MediaSource();//Ctor of MediaSource
	void loadTexture();//loadTexture
	void loadSound();//loadSound
	MediaSource(const MediaSource&) = delete;//delete Copy Ctor
	MediaSource& operator = (const MediaSource&) = delete;// delete Assignment operator
	sf::SoundBuffer openSoundFile(const std::string & soundfile);//openSoundFile
	//------------------------data members------------------------------------------
	std::vector<sf::Texture> m_textures{ 16 }; //m_textures
	std::vector<sf::SoundBuffer> m_sounds;//m_sounds
	std::vector<sf::Sound> m_playSound;//m_playSound
	sf::Font font;	//font
};

