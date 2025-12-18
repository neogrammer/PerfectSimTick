#ifndef ASSETS_HPP__
#define ASSETS_HPP__

#ifdef TX
#undef TX
#endif

#define TX(name) Assets::textures.get(static_cast<int>(Assets::Textures::name))
#include <SFML/Graphics.hpp>
#include <resources/ResourceManager.hpp>

struct Assets
{
	Assets() = delete;
	Assets(const Assets&) = delete;
	Assets& operator=(const Assets&) = delete;


	//globals 
	//static sol::state lua; // globals are bad, but we'll use it for simpler implementation
	static void Initialize();

	// Resource Enums 
	enum class Textures : int { BG_Animated_Stars, Invariant, Count };
	enum class Fonts : int {  Invariant, Count };
	enum class Music : int { Invariant, Count };
	enum class Sounds : int { Invariant, Count };


	// resource buckets for each type of resource
	static ResourceManager<sf::Texture, int> textures;
	static ResourceManager<sf::Music, int> music;
	static ResourceManager<sf::SoundBuffer, int> sounds;
	static ResourceManager<sf::Font, int> fonts;

private:
	// initalize the resources for the entire game
	static void initFonts();
	static void initMusic();
	static void initSounds();
	static void initTextures();
};


#endif