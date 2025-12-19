
#include <tilemap/Tileset.hpp>

#include "Tile.hpp"
/*
#include "Tile.hpp"
Tileset::Tileset(Cfg::Textures tex_, int numTiles_, int pitch_, sf::Vector2f size_)
	: tileVec{}
	, numTiles{ numTiles_ }
	, cols{pitch_}
	, rows{}
	, tex{tex_}
	, tileSize{size_}
{
	tileVec.clear();
	tileVec.reserve(numTiles_);
	
	rows = (numTiles_ / pitch_) + 1;

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < pitch_; x++)
		{
			if ((y * pitch_ + x) >= numTiles_)
			{
				break;
			}
			else
			{
				tileVec.emplace_back(std::make_unique<Tile>(tex_, size_, sf::Vector2f( (float)x * size_.x, (float)y * size_.y ), sf::Vector2i(x * (int)size_.x, y * (int)size_.y)));
			}
		}
	}
}

Tileset::~Tileset()
{
}


std::vector<std::unique_ptr<Tile>>& Tileset::getTiles()
{
	return tileVec;
}

Cfg::Textures Tileset::getTexType()
{
	return tex;
}

sf::IntRect Tileset::getTileTexRect(int index)
{
	return sf::IntRect(sf::Vector2i(tileVec.at(index)->getTexPosition()), sf::Vector2i(tileVec.at(index)->getSize()));
}*/
Tileset::Tileset(Assets::Textures tex_, int numTiles_, int pitch_, sf::Vector2f size_)
	: m_tiles{}
	, m_tex{ tex_ },m_numTiles{numTiles_}, m_cols{pitch_}, m_rows{numTiles_ / pitch_}, m_tileSize{size_}
{
	for (int y = 0; y < m_rows; y++)
	{
		for (int x = 0; x < m_cols; x++)
		{
			m_tiles.emplace_back(std::make_unique<Tile>(obj::type::tile, true, true, m_tex, sf::IntRect{ {x * (int)size_.x, y * (int)size_.y}, {(int)size_.x, (int)size_.y} }, sf::Vector2f{ 0.f,0.f }, sf::Vector2f{ 0.f,0.f }));
		}
	}
}

Tileset::~Tileset() = default;

std::vector<std::unique_ptr<Tile>>& Tileset::getTiles()
{
	return m_tiles;
}

Assets::Textures Tileset::getATex()
{
	return m_tex;
}

const sf::Texture& Tileset::getTexture()
{
	return Assets::textures.get((int)m_tex);
}

void Tileset::setATex(Assets::Textures tex_)
{
	m_tex = tex_;
}

sf::IntRect Tileset::getTexRect(int index_)
{
	return m_tiles.at(index_)->getTexRect();
}

Tile& Tileset::getTile(int index_)
{
	return *m_tiles[index_];
}

float Tileset::getTW()
{
	return m_tileSize.x;
}

float Tileset::getTH()
{
	return m_tileSize.y;

}

const sf::Vector2f& Tileset::getTileSize()
{
	return m_tileSize;

}

void Tileset::setTileSize(const sf::Vector2f size_)
{
	m_tileSize = size_;
}

const int Tileset::getNumTiles() const noexcept
{
	return m_numTiles;
}

void Tileset::setNumtiles(const int numTiles_)
{
	m_numTiles = numTiles_;
}

const int Tileset::getCols() const noexcept
{
	return m_cols;
}

void Tileset::setCols(const int cols_)
{
	m_cols = cols_;
}

const int Tileset::getRows() const noexcept
{
	return m_rows;
}

void Tileset::setRows(const int rows_)
{
	m_rows = rows_;
}
