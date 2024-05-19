# ifndef XKE_ENG_ECS_FWD_HPP
# define XKE_ENG_ECS_FWD_HPP

# include <xenyke/eng/ecs/config.hpp>

XKE_NAMESPACE_BEGIN

namespace ecs {

enum class EntityID : uint32_t;

using EntitySignature = uint32_t;

static XKE_INLINE_CONSTEXPR EntitySignature NULL_ENTITY_SIGNATURE = 0;

using ComponentType = uint8_t;

} // namespace ecs

XKE_NAMESPACE_END

# endif //XKE_ENG_ECS_FWD_HPP
