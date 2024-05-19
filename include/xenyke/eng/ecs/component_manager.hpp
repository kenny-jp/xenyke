# ifndef XKE_ENG_ECS_COMPONENT_MANAGER_HPP
# define XKE_ENG_ECS_COMPONENT_MANAGER_HPP

# include <xenyke/eng/ecs/component_pool.hpp>

XKE_NAMESPACE_BEGIN

namespace ecs {

class ComponentManager
{
public:
    ComponentManager()
        : nextComponentType_(0)
    {

    }

    template<class T_>
    void registerComponent()
    {
        ComponentType type = nextComponentType_++;
        pools_.insert({type, std::make_unique<ComponentPool<T_>>(/* capacity */)});
    }


private:
    template<class T_>
    sptr_t<ComponentPool<T_>> getPool()
    {
        return std::static_pointer_cast<ComponentPool<T_>>(pool_);
    }


    ComponentType nextComponentType_;
    std::unordered_map<ComponentType, sptr_t<ComponentPoolBase>> pools_;

};

} // namespace ecs

XKE_NAMESPACE_END

# endif //XKE_ENG_ECS_COMPONENT_MANAGER_HPP
