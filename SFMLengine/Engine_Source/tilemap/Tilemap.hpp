#ifndef TILEMAP_HPP
#define TILEMAP_HPP
#include <tilemap/Tileset.hpp>
#include <resources/Assets.hpp>
#include <memory>
#include <misc/util.hpp>
class Tile;
class Tilemap
{
	std::unique_ptr<Tileset> m_tileset{nullptr};
	std::vector<std::unique_ptr<Tile> > m_tiles{std::vector<std::unique_ptr<Tile>>{}};
	int m_colsInMap{};
	int m_rowsInMap{};
	
public:
	
	Tilemap();
	~Tilemap();


	std::vector<Tile*> getVisibleTiles();
	std::vector<Tile*> getTilesInArea(int top_, int left_, int width_, int height_);
	void setTileset(Assets::Textures tex_, int numTiles_, int pitch_, sf::Vector2f size_);
	void render(sf::RenderWindow& wnd_);
	void setMap(int* tileData_, int numTiles_, int pitch_);
	int getPitch();
	int getNumTiles();
	sf::Vector2f getTileSize();
	Assets::Textures getCurrTexType();
	void loadMap(const int cols_, const int rows_, const Assets::Textures tex_, const sf::Vector2f tileSize_, int numTilesInSheet_, int sheetPitch_, int** mapData);
	std::unique_ptr<Tileset>& getTileset();
};


#endif