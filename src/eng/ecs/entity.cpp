# include <xenyke/eng/ecs/entity.hpp>

XKE_NAMESPACE_BEGIN

namespace ecs {

void Entity::init(entity_id id)
{
    id_ = id;
    sign_ = 0;
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
