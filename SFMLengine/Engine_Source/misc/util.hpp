#ifndef UTIL_HPP
#define UTIL_HPP
#include <misc/globals.hpp>
static class utl
{
public:
	static sf::Vector2f ToIso(sf::Vector2f cart_)
	{
		cart_.x /= glb::TW;
		cart_.y /= glb::TH;

		float isoX, isoY;
		isoX = (cart_.x - cart_.y) * (glb::TW / 2.f);
		isoY = (cart_.x + cart_.y) * (glb::TH / 4.f);

		return { isoX, isoY };
	}

	static sf::Vector2f ToScreen(sf::Vector2f iso_)
	{
		return {};

	}

};


#endif // UTIL_HPP
