
#include <tilemap/Tilemap.hpp>
#include <tilemap/Tile.hpp>
#include <misc/util.hpp>

Tilemap::Tilemap()
	: m_tileset{nullptr}
	, m_tiles{std::vector<std::unique_ptr<Tile>>{}}
	, m_colsInMap{}
	, m_rowsInMap{}
{

	
	m_tileset = std::make_unique<Tileset>(Assets::Textures::Tileset_Iso_1, 10 * 11, 11, sf::Vector2f{32.f,32.f});
	
	m_tiles.clear();

	

	
	
}

Tilemap::~Tilemap() = default;

std::vector<Tile*> Tilemap::getVisibleTiles()
{
	std::vector<Tile*> tmp;
	tmp.clear();
	tmp.reserve(this->m_tiles.size());
	for (int i = 0; i < this->m_tiles.size(); i++)
	{
		if (!m_tiles[i]->isEmpty())
			tmp.push_back(m_tiles[i].get());
	}
	tmp.shrink_to_fit();
	return tmp;
}

std::vector<Tile*> Tilemap::getTilesInArea(int top_, int left_, int width_, int height_)
{
	return std::vector<Tile*>();
}

void Tilemap::setTileset(Assets::Textures tex_, int numTiles_, int pitch_, sf::Vector2f size_)
{
	m_tileset.reset();
	m_tileset = std::make_unique<Tileset>(tex_, numTiles_, pitch_, size_);
}

void Tilemap::setMap(int* tileData, int numTiles_, int pitch_)
{
	
	m_colsInMap = pitch_;
	m_rowsInMap = numTiles_ / m_colsInMap;
	m_tiles.clear();
	m_tiles.reserve(numTiles_);

	int rows = numTiles_ / pitch_;

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < pitch_; x++)
		{
			int num = tileData[y * pitch_ + x];  // this will return the number corresponding to the tileset tiles index at the location in the map onscreen
	
			if (num == -1)
			{
				m_tiles.emplace_back(std::make_unique<Tile>(obj::type::tile, false, false, Assets::Textures::EmptyTile, sf::IntRect{ {0,0}, {1,1} }, sf::Vector2f{ 0.f,0.f }, sf::Vector2f{ 0.f,0.f }));
				m_tiles.back()->setWPos(sf::Vector2f{ (float)(x * 32.f), (float)(y * 32.f) });
				m_tiles.back()->setEmpty();
			}
			else
			{
				auto& tRef = m_tileset->getTiles().at(num);
				float xx = (float)(num % m_tileset->getCols());
				float yy = float(num / m_tileset->getCols());

				sf::Vector2f tmpTexPos = {xx * m_tileset->getTileSize().x,yy * m_tileset->getTileSize().y };

				m_tiles.emplace_back(std::make_unique<Tile>(obj::type::tile, true, true, m_tileset->getATex(),sf::IntRect{ sf::Vector2i{ (int)tmpTexPos.x,(int)tmpTexPos.y }, sf::Vector2i{tRef->getTexRect().size} }, sf::Vector2f{ (float)x * (float)m_tileset->getTileSize().x, (float)y * (float)m_tileset->getTileSize().y }, sf::Vector2f{ 0.f,0.f }));
				m_tiles.back()->m_solid = true;
				m_tiles.back()->m_visible = true;

			}

		}
	}
}

int Tilemap::getPitch()
{
	return m_colsInMap;
}

int Tilemap::getNumTiles()
{
	return m_colsInMap * m_rowsInMap;
}

sf::Vector2f Tilemap::getTileSize()
{
	return sf::Vector2f(m_tileset->getTiles().at(0)->getTexRect().size);
}

Assets::Textures Tilemap::getCurrTexType()
{
	return m_tileset->getATex();
}

void Tilemap::loadMap(const int cols_, const int rows_, const Assets::Textures tex_, const sf::Vector2f tileSize_,
	int numTilesInSheet_, int sheetPitch_, int** mapData)
{
}

std::unique_ptr<Tileset>& Tilemap::getTileset()
{
	return m_tileset;
}

void Tilemap::render(sf::RenderWindow& wnd_)
{
	//for (auto& i : tileset->getTiles())
	std::vector<int> skip;
	skip.clear();
	for (int i = 0; i < m_tileset->getAnimTiles().size(); i++)
	{
		
		skip.push_back(m_tileset->getAnimTile(i).getStartIndex());
		
	}
	int skipcount = 0;
	for (int i = 0; i < m_tiles.size(); i++)
	{
		bool found = false;
		for (auto j : skip)
		{
			if (i == j) { found = true; }
		}

		if (found)
		{
			m_tileset->getAnimTile(skipcount).render(wnd_);
			skipcount++;
		}
		else
		{
			sf::Sprite spr{ m_tileset->getTexture() };
			spr.setTextureRect(m_tiles[i]->getTexRect());
			spr.setPosition(utl::ToIso(sf::Vector2f(m_tiles[i]->getTexPosition().x, m_tiles[i]->getTexPosition().y)));
			spr.move({ (float)glb::WOX * (float)glb::TW,(float)glb::WOY * (float)glb::TH });
			wnd_.draw(spr);
		}
	}

	

}



//std::vector<Tile*> Tilemap::getTilesInArea(int top_, int left_, int width_, int height_)
//{
//}
//
//void Tilemap::setTileset(Assets::Textures tex_, int numTiles_, int pitch_, sf::Vector2f size_)
//{
//}
//
//void Tilemap::render(sf::RenderWindow& wnd_)
//{
//}
//
//void Tilemap::setMap(int* tileData, int numTiles_, int pitch_)
//{
//}
//
//int Tilemap::getPitch()
//{
//}
//
//int Tilemap::getNumTiles()
//{
//}
//
//sf::Vector2f Tilemap::getTileSize()
//{
//}
//
//Assets::Textures Tilemap::getCurrTexType()
//{
//}
