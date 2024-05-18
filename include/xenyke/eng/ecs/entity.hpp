# ifndef XKE_ENG_ECS_ENTITY_HPP
# define XKE_ENG_ECS_ENTITY_HPP

# include <xenyke/eng/ecs/fwd.hpp>

XKE_NAMESPACE_BEGIN

namespace ecs {

using EntityID = uint32_t;
using EntitySignature = uint32_t;

using Entity = uint64_t;

XKE_INLINE_CONSTEXPR EntityID get_entity_id(Entity e)
{
    XKE_CONSTEXPR auto id_bits = sizeof(EntityID) * CHAR_BIT;
    return static_cast<EntityID>(e >> id_bits);
}

XKE_INLINE_CONSTEXPR EntitySignature get_entity_signature(Entity e)
{
    XKE_CONSTEXPR auto signature_mask = (1ULL << (sizeof(EntitySignature) * CHAR_BIT)) - 1;
    return static_cast<EntitySignature>(e & signature_mask);
}


XKE_INLINE_CONSTEXPR void set_entity_id(Entity& e, EntityID id)
{
    XKE_CONSTEXPR auto id_bits = sizeof(EntityID) * CHAR_BIT;
    XKE_CONSTEXPR auto signature_mask = (1ULL << (sizeof(EntitySignature) * CHAR_BIT)) - 1;

    e = (static_cast<Entity>(id) << id_bits) | (e & signature_mask);
}

XKE_INLINE_CONSTEXPR void set_entity_signature(Entity& e, EntitySignature signature)
{
    XKE_CONSTEXPR auto signature_mask = (1ULL << (sizeof(EntitySignature) * CHAR_BIT)) - 1;

    e = (e & ~signature_mask) | (static_cast<Entity>(signature) & signature_mask);
}

} // namespace ecs

XKE_NAMESPACE_END

# endif //XKE_ENG_ECS_ENTITY_HPP
