
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
	
	textures.load((int)Assets::Textures::BG_Animated_Stars, "Assets/Textures/Backgrounds/Animated_Stars/bg_stars_sheet_final.png");





}

void Assets::initFonts()
{

}