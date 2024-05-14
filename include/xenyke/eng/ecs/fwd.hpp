# ifndef XKE_ENG_ECS_FWD_HPP
# define XKE_ENG_ECS_FWD_HPP

# include <xenyke/eng/ecs/config.hpp>
# include <bitset>

XKE_NAMESPACE_BEGIN

namespace ecs {

static constexpr size_t MAX_COMPONENTS {XKE_ENG_ECS_MAX_COMPONENTS};
using Bitset = std::bitset<MAX_COMPONENTS>;

using entity_id = int32_t;
using component_type_id = int16_t;

using entity_signature = uint64_t;
using component_signature = entity_signature;

static constexpr entity_id INVALID_ENTITY_ID = -1;

class Entity;

template<class T_>
class ComponentObj;

} // namespace ecs

XKE_NAMESPACE_END

# endif //XKE_ENG_ECS_FWD_HPP
