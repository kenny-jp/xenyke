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

    ComponentManager(size_t preallocated_component)
        : nextComponentType_(0)
    {
        reserve(preallocated_component);
    }

    template<class T_>
    void registerComponent()
    {
        const char* typeName = typeid(T_).name();

        __xke_assert(!registeredComponentTypes_.contains(typeName));

        registeredComponentTypes_.insert({typeName, nextComponentType_++});

        componentPools_.insert({typeName, std::make_unique<ComponentPool<T_>>(/* capacity */)});
    }

    template<class T_>
    void addComponent(EntityID id, const T_& component)
    {
        sptr_t<ComponentPool<T_>> pool = getComponentPool<T_>();
        pool->insertData(id, component);
    }

    template<class T_>
    void removeComponent(EntityID id)
    {
        sptr_t<ComponentPool<T_>> pool = getComponentPool<T_>();
        pool->removeData(id);
    }

    template<class T_>
    T_& getComponent(EntityID id)
    {
        sptr_t<ComponentPool<T_>> pool = getComponentPool<T_>();
        return pool->getData(id);
    }

    template<class T_>
    const T_& getComponent(EntityID id) const
    {
        sptr_t<ComponentPool<T_>> pool = getComponentPool<T_>();
        return pool->getData(id);
    }

    template<class... Args>
    std::tuple<Args&...> each(EntityID id)
    {
        return std::tie(getComponent<Args>(id)...);
    }

    template<class... Args>
    const std::tuple<const Args&...> each(EntityID id) const
    {
        return std::tie(getComponent<Args>(id)...);
    }

    template<class T_>
    ComponentType getComponentType() const
    {
        const char* typeName = typeid(T_).name();

        __xke_assert(registeredComponentTypes_.contains(typeName));

        return registeredComponentTypes_.at(typeName);
    }

    void entityDestroyed(EntityID id)
    {
        for (const auto& pair : componentPools_) {
            pair.second->entityDestroyed(id);
        }
    }

    void reserve(size_t capacity)
    {
        registeredComponentTypes_.reserve(capacity);
        componentPools_.reserve(capacity);
    }

private:
    template<class T_>
    sptr_t<ComponentPool<T_>> getComponentPool()
    {
        const char* typeName = typeid(T_).name();

        __xke_assert(registeredComponentTypes_.contains(typeName));

        return std::static_pointer_cast<ComponentPool<T_>>(componentPools_.at(typeName));
    }


    ComponentType nextComponentType_;
    std::unordered_map<const char*, ComponentType> registeredComponentTypes_;
    std::unordered_map<const char*, sptr_t<ComponentPoolBase>> componentPools_;

};

} // namespace ecs

XKE_NAMESPACE_END

# endif //XKE_ENG_ECS_COMPONENT_MANAGER_HPP
