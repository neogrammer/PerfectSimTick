#ifndef STATICOBJECT_HPP
#define STATICOBJECT_HPP
#include "Obj.hpp"

class StaticObject : Obj
{
protected:
	sf::Vector2f worldPos_;
	sf::Vector2f worldSize_;
public:
	StaticObject();
	virtual ~StaticObject() override;

};

#endif

