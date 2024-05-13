# ifndef XKE_ENG_ECS_FWD_HPP
# define XKE_ENG_ECS_FWD_HPP

# include <xenyke/eng/ecs/config.hpp>
# include <bitset>

XKE_NAMESPACE_BEGIN

namespace ecs {

static constexpr size_t MAX_COMPONENTS {XKE_ENG_ECS_MAX_COMPONENTS};
using Bitset = std::bitset<MAX_COMPONENTS>;

using entity_id_t = int32_t;
using entity_signature_t = uint64_t;

static constexpr entity_id_t INVALID_ENTITY_ID = -1;

class Entity;
using component_signature_t = entity_signature_t;


} // namespace ecs

XKE_NAMESPACE_END

# endif //XKE_ENG_ECS_FWD_HPP
