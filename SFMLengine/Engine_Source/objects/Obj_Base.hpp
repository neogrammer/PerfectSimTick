#ifndef OBJ_BASE_HPP
#define OBJ_BASE_HPP
#include <cstdint>

namespace obj
{
	enum class type : std::uint8_t
	{
		obj_base = 0Ui8,
		obj,
		vis_obj,
		tile,
		count,
		unknown
	};
}
class Obj_Base
{
	friend class VisObj;
	obj::type m_type{obj::type::obj_base};
protected:
	obj::type getType() const noexcept;
	Obj_Base* clone() const;
	void setType(obj::type type_);
	~Obj_Base();
public:
	Obj_Base(obj::type type_ = obj::type::unknown);
	Obj_Base(const Obj_Base& o);
	Obj_Base& operator=(const Obj_Base& o);
	Obj_Base(Obj_Base&& o) noexcept;
	Obj_Base& operator=(Obj_Base&& o) noexcept;
};
#endif