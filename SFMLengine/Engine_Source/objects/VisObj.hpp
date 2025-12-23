#ifndef VISOBJ_HPP
#define VISOBJ_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <objects/Obj.hpp>
#include <resources/Assets.hpp>

// All objects are physical manifestations of something
// thus might not have a size
class VisObj : public Obj
{
	Assets::Textures m_tex;
	sf::IntRect m_texRect;
	sf::Vector2f m_texOff;
protected:
	obj::type getType() const noexcept;
	VisObj* clone() const;
	
public:
	explicit VisObj(const Obj& obj);
	VisObj(obj::type type_ = obj::type::vis_obj, Assets::Textures tex_ = Assets::Textures::Invariant, sf::IntRect rect_ = { {0,0},{0,0} }, sf::Vector2f texOff_ = {0.f,0.f});
	virtual ~VisObj() override;

	VisObj(const VisObj& o);
	VisObj& operator=(const VisObj& o);
	VisObj(VisObj&& o);
	VisObj& operator=(VisObj&& o);

	const Assets::Textures& getATex() const;
	const sf::Texture& getTexure() const;
	void setATex(const Assets::Textures& tex_);
	const sf::IntRect& getTexRect() const;
	void setTexRect(const sf::IntRect rect_);
	const sf::Vector2f& getTexOff() const;
	void setTexOff(const sf::Vector2f off_);

};

#endif