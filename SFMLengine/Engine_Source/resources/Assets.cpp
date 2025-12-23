
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
	textures.load((int)Assets::Textures::Invariant, "Assets/Textures/Invariant.png");
	textures.load((int)Assets::Textures::Tileset_Objects_1, "Assets/Textures/Tilesets/object_tiles_32_32.png");
	textures.load((int)Assets::Textures::EmptyTile, "Assets/Textures/Tilesets/EmptyTile.png");
	textures.load((int)Assets::Textures::Tileset_Iso_1, "Assets/Textures/Tilesets/tileset_iso_1.png");
	textures.load((int)Assets::Textures::Knight_Attack, "Assets/Textures/Knight/knight_attack_sheet_18.png");
	textures.load((int)Assets::Textures::Knight_Attack_Shadow, "Assets/Textures/Knight/Shadow/knight_shadow_attack_sheet_18.png");
	textures.load((int)Assets::Textures::Knight_Block, "Assets/Textures/Knight/knight_block_sheet_16.png");
	textures.load((int)Assets::Textures::Knight_Block_Shadow, "Assets/Textures/Knight/Shadow/knight_shadow_block_sheet_16.png");
	textures.load((int)Assets::Textures::Knight_Death, "Assets/Textures/Knight/knight_death_sheet_9.png");
	textures.load((int)Assets::Textures::Knight_Death_Shadow, "Assets/Textures/Knight/Shadow/knight_shadow_death_sheet_9.png");
	textures.load((int)Assets::Textures::Knight_GotHit, "Assets/Textures/Knight/knight_got_hit_sheet_13.png");
	textures.load((int)Assets::Textures::Knight_GotHit_Shadow, "Assets/Textures/Knight/Shadow/knight_shadow_got_hit_sheet_13.png");
	textures.load((int)Assets::Textures::Knight_Idle, "Assets/Textures/Knight/knight_idle_sheet_16.png");
	textures.load((int)Assets::Textures::Knight_Idle_Shadow, "Assets/Textures/Knight/Shadow/knight_shadow_idle_sheet_16.png");
	textures.load((int)Assets::Textures::Knight_Jump, "Assets/Textures/Knight/knight_jump_sheet_16.png");
	textures.load((int)Assets::Textures::Knight_Jump_Shadow, "Assets/Textures/Knight/Shadow/knight_shadow_jump_sheet_16.png");
	textures.load((int)Assets::Textures::Knight_Run, "Assets/Textures/Knight/knight_run_sheet_17.png");
	textures.load((int)Assets::Textures::Knight_Run_Shadow, "Assets/Textures/Knight/Shadow/knight_shadow_run_sheet_17.png");
	textures.load((int)Assets::Textures::Knight_Walk, "Assets/Textures/Knight/knight_walk_sheet_15.png");
	textures.load((int)Assets::Textures::Knight_Walk_Shadow, "Assets/Textures/Knight/Shadow/knight_shadow_walk_sheet_15.png");




}

void Assets::initFonts()
{

}