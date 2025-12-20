#include <algorithm>
#include <objects/Obj.hpp>

obj::type Obj::getType() const noexcept
{
	return Obj_Base::getType();
}

const sf::Vector2f& Obj::getWPos() const
{
	return m_worldPos;
}

void Obj::setWPos(const sf::Vector2f pos_)
{
	m_worldPos = pos_;
}

void Obj::moveWPos(const sf::Vector2f amt_)
{
	m_worldPos += amt_;
}

const sf::Vector2f& Obj::getWSize() const
{
	return m_worldSize;
}

void Obj::setWSize(const sf::Vector2f size_)
{
	m_worldSize = size_;
}

Obj* Obj::clone() const
{
	return new Obj{ *this };
}


Obj::Obj(obj::type type_)
	: Obj_Base{type_}
{
	m_worldPos = {0.f,0.f};
	m_worldSize = {0.f,0.f};
}

Obj::~Obj() = default;

Obj::Obj(const Obj& o)
	: Obj_Base(static_cast<const Obj_Base&>(o))
	, m_worldPos(o.m_worldPos)
	, m_worldSize(o.m_worldSize)
{
}

Obj& Obj::operator=(const Obj& o)
{
	if (this == &o) return *this;
	
	Obj* ptrToThis = this;
	Obj* old = ptrToThis;
	ptrToThis = o.clone();
	old->setType(ptrToThis->getType());
	old->setWPos(ptrToThis->getWPos());
	old->setWSize(ptrToThis->getWSize());

	delete ptrToThis;
	ptrToThis = nullptr;
	old = nullptr;
	return *this;
}

Obj::Obj(Obj&& o)
	: Obj_Base{ static_cast<Obj_Base&&>(o) }
	, m_worldPos{ o.m_worldPos }
	, m_worldSize{ o.m_worldSize }
{
}

Obj& Obj::operator=(Obj&& o)
{
	if (this == &o) return *this;
	this->setType(o.getType());
	this->m_worldPos = o.m_worldPos;
	this->m_worldSize = o.m_worldSize;
	return *this;
}

