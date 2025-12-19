#ifndef TILESET_H__
#define TILESET_H__
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <resources/Assets.hpp>
class Tile;
class Tileset
{

	std::vector<std::unique_ptr<Tile>> m_tiles;
	Assets::Textures m_tex;
	
	int m_numTiles{1};
	int m_cols{1};
	int m_rows{1};

	sf::Vector2f m_tileSize{32.f,32.f};

public:
	Tileset(Assets::Textures tex_ = Assets::Textures::Invariant, int numTiles_ = 1, int pitch = 1, sf::Vector2f size_ = { 32.f,32.f });
    ~Tileset();

	std::vector<std::unique_ptr<Tile>>& getTiles();
	Assets::Textures getATex();
	const sf::Texture& getTexture();
	void setATex(Assets::Textures tex_);

	sf::IntRect getTexRect(int index_);
	Tile& getTile(int index_);

	float getTW();
	float getTH();
	const sf::Vector2f& getTileSize();
	void setTileSize(const sf::Vector2f size_);

	const int getNumTiles() const noexcept;
	void setNumtiles(const int numTiles_);
	const int getCols() const noexcept;
	void setCols(const int cols_);
	const int getRows() const noexcept;
	void setRows(const int rows_);



};


#endif