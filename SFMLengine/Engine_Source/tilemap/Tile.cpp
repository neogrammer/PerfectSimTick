

#include <tilemap/Tile.hpp>


sf::Vector2f Tile::getTexPosition()
{
	return sf::Vector2f{ getWPos().x - getTexOff().x,getWPos().y - getTexOff().y };
}

bool Tile::isEmpty()
{
	return (!m_visible && !m_solid);
}

void Tile::setEmpty()
{
	m_visible = false;
	m_solid = false;
	setATex(Assets::Textures::EmptyTile);
}


Tile::Tile(obj::type type_, bool solid_, bool visible_, Assets::Textures tex_, sf::IntRect texRect_, sf::Vector2f worldPos_, sf::Vector2f texRectOff_)
	: VisObj{ type_ , tex_, texRect_, texRectOff_ }
	, m_solid{solid_}, m_visible{visible_}
{
	this->setWPos(worldPos_);
}

Tile::~Tile() = default;

Tile::Tile(const Tile& o)
	: Tile{o.getType(), o.m_solid, o.m_visible, o.getATex(), o.getTexRect(), o.getWPos(), o.getTexOff()}
{}

Tile& Tile::operator=(const Tile& o)
{
	if (this == &o) return *this;

	this->setType(o.getType());
	this->setATex(o.getATex());
	this->setTexRect(o.getTexRect());
	this->setWPos(o.getWPos());
	this->setWSize(o.getWSize());
	this->setTexOff(o.getTexOff());

	return *this;
}

Tile::Tile(Tile&& o) noexcept
	: Tile{ o.getType(), o.m_solid, o.m_visible, o.getATex(),o.getTexRect(), o.getWPos(), o.getTexOff()}
{}

Tile& Tile::operator=(Tile&& o) noexcept
{
	if (this == &o) return *this;

	this->setType(o.getType());
	this->setATex(o.getATex());
	this->setTexRect(o.getTexRect());
	this->setWPos(o.getWPos());
	this->setWSize(o.getWSize());
	this->setTexOff(o.getTexOff());

	return *this;
}
