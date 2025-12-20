#ifndef ANIMTILE_HPP
#define ANIMTILE_HPP
#include <tilemap/Tile.hpp>
#include <vector>
#include <resources/Assets.hpp>
class AnimTile
{
	friend class Tileset;
	std::vector<float> m_delays{};
	std::vector<Tile*> m_tiles{};
	size_t m_index{ 0 };
	size_t m_numTiles{ 0 };
	Assets::Textures m_tex;
	size_t m_startIndex{};
	size_t m_endIndex{};
	double m_elapsed{ 0.0 };

	void animate();
public:
	AnimTile();
	AnimTile(std::vector<std::unique_ptr<Tile>>& tileset_, int startIdx_, int endIdx_, float delay_);
	~AnimTile();


	AnimTile(const AnimTile& o);
	AnimTile& operator=(const AnimTile& o);
	AnimTile(AnimTile&& o) noexcept = delete;
	AnimTile& operator=(AnimTile&& o) noexcept = delete;

	void update(double dt_);
	void render(sf::RenderWindow& wnd_);
	void setMapTile(Tile* mapTile_);
	void setDelays(std::vector<float> delays_);
	int getStartIndex();
	int getCount();
};

#endif