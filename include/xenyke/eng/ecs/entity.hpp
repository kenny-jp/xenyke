# ifndef XKE_ENG_ECS_ENTITY_HPP
# define XKE_ENG_ECS_ENTITY_HPP

# include <xenyke/eng/ecs/fwd.hpp>

XKE_NAMESPACE_BEGIN

namespace ecs {

class Entity
{
public:
    Entity();
    Entity(entity_id_t id, size_t componentCapacity);

    void set(entity_id_t id, size_t componentCapacity);

    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;
    Entity(const Entity&&) noexcept;
    Entity& operator=(const Entity&&) noexcept;

    virtual ~Entity() noexcept;

    operator entity_id_t() const
    {
        return id_;
    }

    bool operator==(const Entity& other);
    bool operator!=(const Entity& other);

    entity_signature_t operator&=(const ComponentType& t);
    entity_signature_t operator|=(const ComponentType& t);
    entity_signature_t operator^=(const ComponentType& t);

    XKE_INLINE entity_signature_t getSign() const noexcept
    { return sign_; }

    friend
    bool operator==(const Entity& lhs, const Entity& rhs);
    friend
    bool operator!=(const Entity& lhs, const Entity& rhs);

private:
    entity_id_t id_;
    entity_signature_t sign_;
};

struct EntityHash {
    std::size_t operator()(const Entity& entity) const {
        return std::hash<entity_id_t>()(entity);
    }
};

struct EntityKeyEqual {
    bool operator()(const Entity& lhs, const Entity& rhs) const {
        return lhs == rhs;
    }
};

} // namespace ecs

XKE_NAMESPACE_END

# endif //XKE_ENG_ECS_ENTITY_HPP
