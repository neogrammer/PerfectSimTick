#include <tilemap/AnimTile.hpp>
#include <cassert>

void AnimTile::animate()
{
	++m_index %= m_numTiles;
}

AnimTile::AnimTile() = default;

AnimTile::AnimTile(std::vector<std::unique_ptr<Tile>>& tileset_, int startIdx_, int endIdx_, float delay_)
	: m_delays{}
	, m_tiles {}
	, m_index{}
	, m_startIndex{(size_t)startIdx_}
	, m_endIndex{(size_t)endIdx_}
{
	int numFrames = endIdx_ - startIdx_ + 1;
	
	m_delays.clear();
	m_delays.reserve(numFrames);

	m_tiles.clear();
	m_tiles.reserve(numFrames);


	for (int i = 0; i < numFrames; i++)
	{
		if (startIdx_ + i <= endIdx_)
		{
			m_delays.emplace_back(delay_);
			m_tiles.push_back(tileset_[startIdx_ + i].get());
		}
		else
		{
			break;
		}
	}
	m_index = 0;
	m_numTiles = numFrames;

	m_tex = tileset_.at(0)->getATex();
}

AnimTile::~AnimTile() = default;

void AnimTile::update(double dt_)
{
	m_elapsed += dt_;

	if(m_elapsed >= m_delays[m_index])
	{
		m_elapsed = 0;
		animate();
	}
	
}

void AnimTile::render(sf::RenderWindow& wnd_)
{
	sf::Sprite spr{ Assets::textures.get((int)m_tex) };
	spr.setPosition(m_tiles[m_index]->getWPos()- m_tiles[m_index]->getTexOff());
	spr.setTextureRect(m_tiles[m_index]->getTexRect());
	wnd_.draw(spr);
}

void AnimTile::setDelays(std::vector<float> delays_)
{

	assert(delays_.size() == m_numTiles);

	for (size_t i = 0; i < m_delays.size(); i++)
	{
		m_delays[i] = delays_[i];
	}
}

int AnimTile::getStartIndex()
{
	return (int)m_startIndex;
}

int AnimTile::getCount()
{
	return (int)m_numTiles;
}
