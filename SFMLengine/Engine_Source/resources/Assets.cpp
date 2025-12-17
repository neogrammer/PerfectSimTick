#include <resources/Assets.hpp>
#include <resources/ResourceManager.hpp>


ResourceManager<sf::Texture, int> Assets::textures = {};
ResourceManager<sf::Font, int> Assets::fonts = {};
ResourceManager<sf::Music, int> Assets::music = {};
ResourceManager<sf::SoundBuffer, int> Assets::sounds = {};


void Assets::Initialize()
{
	initTextures();
	initFonts();
	initMusic();
	initSounds();
}

void Assets::initMusic()
{


}

void Assets::initSounds()
{



}

void Assets::initTextures()
{
	
	//textures.load((int)Assets::Textures::Invariant, "assets/textures/invariant.png");





}

void Assets::initFonts()
{

}