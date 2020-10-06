//-------------------------include---------------------------------------------
#include "MediaSource.h"
#include <iostream>
//------------------------MediaSource------------------------------------------
// Ctor of MediaSource that load Texture and load Sound
MediaSource::MediaSource()
{
	loadTexture();
	loadSound();
}
//----------------------loadTexture--------------------------------------------
//unction that loading textures from files and inserts everything into the vector
void MediaSource::loadTexture()
{
	bool flag = true;
	flag = flag && (m_textures[0].loadFromFile("background.png"));
	flag = flag && (m_textures[1].loadFromFile("home.png"));
	flag = flag && (m_textures[2].loadFromFile("wall.png"));
	flag = flag && (m_textures[3].loadFromFile("player.png"));
	flag = flag && (m_textures[4].loadFromFile("scout.png"));
	flag = flag && (m_textures[5].loadFromFile("key.png"));
	flag = flag && (m_textures[6].loadFromFile("tower.png"));
	flag = flag && (m_textures[7].loadFromFile("castle.png"));
	flag = flag && (m_textures[8].loadFromFile("guards.png"));
	flag = flag && (m_textures[9].loadFromFile("guards.png"));
	flag = flag && (m_textures[10].loadFromFile("door.png"));
	flag = flag && (m_textures[11].loadFromFile("rangetower.png"));
	flag = flag && (m_textures[12].loadFromFile("snow.png"));
	flag = flag && (m_textures[13].loadFromFile("wolf.png"));
	flag = flag && (m_textures[14].loadFromFile("lose.png"));
	flag = flag && (m_textures[15].loadFromFile("win.png"));
	flag = flag && (font.loadFromFile("font.ttf"));
	if (!flag)
	{
		std::cout << "Cannot allocate the texture";
		exit(EXIT_FAILURE);
	}
}
//-----------------------loadSound---------------------------------------------
//function that load sounds  from files and inserts everything into the vector
void MediaSource::loadSound()
{
	

	m_sounds.emplace_back(openSoundFile("sound_track2.ogg"));
	m_sounds.emplace_back(openSoundFile("gun.ogg"));
	m_sounds.emplace_back(openSoundFile("key.ogg"));
	m_sounds.emplace_back(openSoundFile("ice.ogg"));
	m_sounds.emplace_back(openSoundFile("freeze.ogg"));
	m_sounds.emplace_back(openSoundFile("win.ogg"));
	m_sounds.emplace_back(openSoundFile("collide.ogg"));
	m_sounds.emplace_back(openSoundFile("Wolf.ogg"));
	m_sounds.emplace_back(openSoundFile("lose.ogg"));
	for (auto &x : m_sounds)
		m_playSound.push_back(sf::Sound(x));
}
//-------------------------openSoundFile---------------------------------------
//function that open Sound from File
sf::SoundBuffer MediaSource::openSoundFile(const std::string & soundfile)
{
	sf::SoundBuffer temp;
	temp.loadFromFile(soundfile);
	return std::move(temp);
}
//-----------------------instance----------------------------------------------
//function that Create a single Instance of MediaSource
MediaSource & MediaSource::instance()
{
	static MediaSource master;
	return master;
}
//---------------------getSound------------------------------------------------
//function that get index of cell and return the music in the cell 
sf::Sound & MediaSource::getSound(const SOUNDS & sound)
{
	return m_playSound[sound];
}
//--------------------getTexture-----------------------------------------------
//function that get index of cell and return the texture in the cell 
const sf::Texture & MediaSource::getTexture(PICTURE_TYPE t) const
{
	return m_textures[t];	
}
//-------------------~MediaSource----------------------------------------------
//Dtor of MediaSource
MediaSource::~MediaSource()
{
}
