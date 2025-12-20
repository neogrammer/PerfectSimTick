#include <objects/VisObj.hpp>
#include <algorithm>

#include "resources/Assets.hpp"
#include <iostream>

obj::type VisObj::getType() const noexcept
{
	return Obj::getType();
}

VisObj::VisObj(const Obj& obj)
	: Obj{obj}
	, m_tex{Assets::Textures::Invariant}
	, m_texRect( { {0,0},{0,0} } )
	, m_texOff{0.f,0.f}
{
	auto* vo = dynamic_cast<VisObj*>(const_cast<Obj*>(&obj));
	if (vo)
	{
		this->m_tex = vo->m_tex;
		this->m_texRect = vo->m_texRect;
		this->m_texOff = vo->m_texOff;
	}
	else
	{
		std::cout << "VisObj made using Obj was not clean!  Tread Carefully" << std::endl;
	}
}

VisObj* VisObj::clone() const
{
	return new VisObj{*this};
}


VisObj::VisObj(obj::type type_, Assets::Textures tex_, sf::IntRect rect_, sf::Vector2f texOff_)
	: Obj{ type_ }
	, m_tex{ tex_ }
	, m_texRect(rect_)
	, m_texOff{ texOff_ }
{
}

VisObj::~VisObj() = default;

VisObj::VisObj(const VisObj& o)
	: Obj(static_cast<const Obj&>(o))
	, m_tex{o.m_tex}
	, m_texRect{o.m_texRect}
	, m_texOff{o.m_texOff}
{
}

VisObj& VisObj::operator=(const VisObj& o)
{
	if (this == &o) return *this;
	
	auto* ptrToThis = this;
	VisObj* old = ptrToThis;
	ptrToThis = o.clone();
	old->setType(ptrToThis->getType());
	old->setWPos(ptrToThis->getWPos());
	old->setWSize(ptrToThis->getWSize());

	delete ptrToThis;
	ptrToThis = nullptr;
	old = nullptr;
	return *this;
}

VisObj::VisObj(VisObj&& o)
	: Obj{ std::move(static_cast<Obj&&>(o)) }
	, m_tex{o.m_tex}
	, m_texRect{o.m_texRect}
	, m_texOff{o.m_texOff}
{}

const Assets::Textures& VisObj::getATex() const
{
	return m_tex;
}

const sf::Texture& VisObj::getTexure() const
{
	return Assets::textures.get(static_cast<int>(m_tex));
}

void VisObj::setATex(const Assets::Textures& tex_)
{
	m_tex = tex_;
}

const sf::IntRect& VisObj::getTexRect() const
{
	return m_texRect;
}

void VisObj::setTexRect(const sf::IntRect rect_)
{
	m_texRect = rect_;
}

const sf::Vector2f& VisObj::getTexOff() const
{
	return m_texOff;
}

void VisObj::setTexOff(const sf::Vector2f off_)
{
	m_texOff = off_;
}

VisObj& VisObj::operator=(VisObj&& o)
{
	if (this == &o) return *this;
	Obj* thisPtr = this;
	if (thisPtr)
	{
		thisPtr->setType(o.getType());
		thisPtr->setWPos(o.getWPos());
		thisPtr->setWSize(o.getWSize());
	}
	this->m_tex = o.m_tex;
	this->m_texRect = o.m_texRect;
	this->m_texOff = o.m_texOff;
	return *this;
}

