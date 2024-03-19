export module triple.refl:member;
import :type;
import :type_of;
import :ref;
import :var;
import :utils;

import std;

namespace triple::refl {

export class Member {
  public:
    Member(std::string_view name, const Type* type, const Type* parent_type) :
        m_name(name), m_type(type), m_parent_type(parent_type) {}

    virtual Ref  get(Ref obj) const            = 0;
    virtual void set(Ref obj, Ref value) const = 0;

    std::string_view name() const {
        return m_name;
    }

    const Type& type() const {
        return *m_type;
    }

  protected:
    std::string_view m_name;
    const Type*      m_type;
    const Type*      m_parent_type;
};

export template<typename P>
class TMember : public Member {
    using MemberType                = typename MemberTrait<P>::Type;
    using ParentType                = typename MemberTrait<P>::ParentType;
    constexpr static bool is_static = MemberTrait<P>::is_static;

  public:
    TMember(std::string_view name, P ptr) : Member(name, refl::type<MemberType>(), refl::type<ParentType>()) {}

    Ref get(Ref obj) const override {
        if constexpr (is_static) {
            return Ref(*m_ptr);
        } else {
            auto& p = obj.value<ParentType>();
            return Ref(p.*m_ptr);
        }
    }

    void set(Ref obj, Ref value) const override {
        if constexpr (is_static) {
            *m_ptr = value.value<MemberType>();
        } else {
            auto& p  = obj.value<ParentType>();
            p.*m_ptr = value.value<MemberType>();
        }
    }

  private:
    P m_ptr;
};

} // namespace triple::refl
