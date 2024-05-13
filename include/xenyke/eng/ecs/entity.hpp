# ifndef XKE_ENG_ECS_ENTITY_HPP
# define XKE_ENG_ECS_ENTITY_HPP

# include <xenyke/eng/ecs/fwd.hpp>

XKE_NAMESPACE_BEGIN

namespace ecs {

class Entity
{
public:
    Entity() = default;
    ~Entity() noexcept = default;

    void init(entity_id_t id);

    XKE_INLINE entity_id_t getId() const {
        return id_;
    }

    void and_sign(const Entity& other);
    void or_sign(const Entity& other);
    void xor_sign(const Entity& other);

    friend
    bool operator==(const Entity& lhs, const Entity& rhs);
    friend
    bool operator!=(const Entity& lhs, const Entity& rhs);

private:
    entity_id_t id_;
    entity_signature_t sign_;

    friend struct EntityHash;
    friend struct EntityKeyEqual;
    friend class EntityManager;
};

struct EntityHash {
    std::size_t operator()(const Entity& entity) const {
        return std::hash<entity_id_t>()(entity.id_);
    }
};

struct EntityKeyEqual {
    bool operator()(const Entity& lhs, const Entity& rhs) const {
        return lhs.id_ == rhs.id_;
    }
};

} // namespace ecs

XKE_NAMESPACE_END

# endif //XKE_ENG_ECS_ENTITY_HPP
