# include <xenyke/eng/ecs/entity.hpp>

XKE_NAMESPACE_BEGIN

namespace ecs {

void Entity::init(entity_id_t id)
{
    id_ = id;
    sign_ = 0;
}

void Entity::and_sign(const Entity &other)
{
    sign_ &= other.sign_;
}

void Entity::or_sign(const Entity &other)
{
    sign_ |= other.sign_;
}

void Entity::xor_sign(const Entity &other)
{
    sign_ ^= other.sign_;
}

bool operator==(const Entity &lhs, const Entity &rhs)
{
    return lhs.id_ == rhs.id_;
}

bool operator!=(const Entity &lhs, const Entity &rhs)
{
    return !(lhs == rhs);
}


} // namespace ecs

XKE_NAMESPACE_END
