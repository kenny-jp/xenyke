# ifndef XKE_ENG_ECS_ENTITY_HPP
# define XKE_ENG_ECS_ENTITY_HPP

# include <xenyke/eng/common.hpp>
# include <bitset>

XKE_NAMESPACE_BEGIN

namespace ecs {

using entity_id_t = int32_t;
static constexpr entity_id_t INVALID_ENTITY = -1;

using entity_signature_t = std::bitset<50>;

struct Entity
{
    entity_id_t id;
    entity_signature_t sign;
};

} // namespace ecs


XKE_NAMESPACE_END

# endif //XKE_ENG_ECS_ENTITY_HPP