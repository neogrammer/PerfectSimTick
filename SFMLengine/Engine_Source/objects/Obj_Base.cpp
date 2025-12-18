#include <objects/Obj_Base.hpp>

obj::type Obj_Base::getType() const noexcept { return m_type; }

void Obj_Base::setType(obj::type type_)
{
	m_type = type_;
}

Obj_Base::Obj_Base(obj::type type_)
	: m_type{type_}
{}

Obj_Base::~Obj_Base() = default;

Obj_Base::Obj_Base(const Obj_Base& o) = default;

Obj_Base& Obj_Base::operator=(const Obj_Base& o)
{
	if (this == &o) return *this;
	this->m_type = o.m_type;
	return *this;
}

Obj_Base::Obj_Base(Obj_Base&& o) noexcept
	: m_type{o.m_type}
{}

Obj_Base& Obj_Base::operator=(Obj_Base&& o) noexcept
{
	if (this == &o) return *this;
	this->m_type = o.m_type;
	return *this;
}

