# include <xenyke/eng/ecs/entity.hpp>

XKE_NAMESPACE_BEGIN

namespace ecs {

Entity::Entity() : id_(INVALID_ENTITY_ID), sign_(0) {}

Entity::Entity(entity_id_t id, size_t componentCapacity) : id_(id), sign_(componentCapacity) {}

Entity::~Entity() noexcept
{

}

Entity::Entity(const Entity&& other) noexcept :
    id_(other.id_), sign_(std::move(other.sign_))
{

}

Entity& Entity::operator=(const Entity&& other) noexcept
{
    id_ = other.id_;
    sign_ = std::move(other.sign_);
    return *this;
}

void Entity::set(entity_id_t id, size_t componentCapacity)
{
    id_ = id;
    // sign_.init(componentCapacity);
}

bool Entity::operator==(const Entity &other)
{
    return id_ == other.id_;
}

bool Entity::operator!=(const Entity &other)
{
    return !(id_ == other.id_);
}

entity_signature_t Entity::operator&=(const ComponentType &t)
{
    return sign_ &= t;
}

entity_signature_t Entity::operator|=(const ComponentType &t)
{
    return sign_ |= t;
}

entity_signature_t Entity::operator^=(const ComponentType &t)
{
    return sign_ ^= t;
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
