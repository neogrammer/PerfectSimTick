#ifndef OBJ_HPP
#define OBJ_HPP

#include <SFML/System/Vector2.hpp>

#include "Obj_Base.hpp"

// All objects are physical manifestations of something
// thus might not have a size
class Obj : public Obj_Base
{
	sf::Vector2f m_worldPos{0.f,0.f};
	sf::Vector2f m_worldSize{1.f,1.f};
protected:
	Obj* clone() const;
	obj::type getType() const noexcept;

public:
	Obj(obj::type type_ = obj::type::obj);
	virtual ~Obj();

	Obj(const Obj& o);
	Obj& operator=(const Obj& o);
	Obj(Obj&& o);
	Obj& operator=(Obj&& o);

public:
	const sf::Vector2f& getWPos() const;
	void setWPos(const sf::Vector2f pos_);
	void moveWPos(const sf::Vector2f amt_);
	const sf::Vector2f& getWSize() const;
	void setWSize(const sf::Vector2f size_);

};

#endif