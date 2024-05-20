# ifndef XKE_ENG_ECS_SYSTEM_HPP
# define XKE_ENG_ECS_SYSTEM_HPP

# include <xenyke/eng/ecs/fwd.hpp>

XKE_NAMESPACE_BEGIN

namespace ecs {

using SystemID = ComponentType;

class SystemBase
{
public:
    explicit SystemBase() = default;
    virtual ~SystemBase() = default;

    virtual void update() = 0;
};

template<class T_, class... Cmp>
class ConcretSystem : public T_
{
    using Tuple = std::tuple<Cmp...>;

    template<class... Args>
    std::tuple<Args&...> each()
    {

    }

};

} // namespace ecs

XKE_NAMESPACE_END

# endif //XKE_ENG_ECS_SYSTEM_HPP
