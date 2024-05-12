# ifndef XKE_ENG_ECS_FWD_HPP
# define XKE_ENG_ECS_FWD_HPP

# include <xenyke/core/config.hpp>
# include <bitset>

XKE_NAMESPACE_BEGIN

namespace ecs {

using entity_id_t = int32_t;
using entity_signature_t = std::bitset<XKE_BITSET_CAPACITY>;

static constexpr entity_id_t INVALID_ENTITY_ID = -1;

class Entity;
using ComponentType = entity_signature_t;


} // namespace ecs

XKE_NAMESPACE_END

# endif //XKE_ENG_ECS_FWD_HPP
