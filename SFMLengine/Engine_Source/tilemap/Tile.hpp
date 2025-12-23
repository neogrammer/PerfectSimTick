#ifndef TILE_HPP
#define TILE_HPP
#include <objects/VisObj.hpp>
#include <resources/Assets.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>


class Tile : public VisObj
{
	bool m_solid{true};
	bool m_visible{ true };
	int m_tileNum{ -1 };
public:
	friend class Tilemap;

	// square bounds should consider 0,0 to be top left of where the image will be drawn,  worldPos - texRectOff + squareBounds_.topLeft(), for example

	Tile(obj::type type_ = obj::type::tile, bool solid_ = true, bool visible_ = true, Assets::Textures tex_ = Assets::Textures::Tileset_Blocks_128
		, sf::IntRect texRect_ = sf::IntRect{sf::Vector2i{0,0}, sf::Vector2i{ 128,128 } }
	    , sf::Vector2f worldPos_ = sf::Vector2f{ 0.f,0.f }, sf::Vector2f texRectOff_ = sf::Vector2f{ 0.f,0.f }, int tileNum_ = -1);
	
	virtual ~Tile() override;

	Tile(const Tile& o);
	Tile& operator=(const Tile& o);
	Tile(Tile&& o) noexcept;
	Tile& operator=(Tile&& o) noexcept;


	sf::Vector2f getTexPosition();

	bool isEmpty();
	void setEmpty();

	int getTileNum();
	void setTileNum(int num_);
	Tile* clone();
	
};

#endif