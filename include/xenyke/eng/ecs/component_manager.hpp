# ifndef XKE_ENG_ECS_COMPONENT_MANAGER_HPP
# define XKE_ENG_ECS_COMPONENT_MANAGER_HPP

# include <xenyke/eng/ecs/component_pool.hpp>

XKE_NAMESPACE_BEGIN

namespace ecs {

class ComponentManager
{
    using hash_code_type = size_t;

public:
    ComponentManager(size_t capacity)
        : capacity_(capacity), nextComponentId_(0)
    {

    }

    template<class T_>
    void registerComponent()
    {
        hash_code_type hash = get_hash_type<T_>();
        componentTypes_.insert({hash, nextComponentId_});
        componentPools_.insert({hash, std::make_unique<ComponentPool<T_>>(capacity_)});
        nextComponentId_++;
    }

    template<class T_>
    void add_component(Entity& entity, const T_& cmp)
    {
        ComponentPool<T_>& pool = getPool<T_>();
        pool.insertData(entity, cmp);
    }

    template<class T_, class... Args>
    void make_component(Entity& entity, Args&&... args)
    {
        ComponentPool<T_>& pool = getPool<T_>();
        pool.insertData(entity, T_(std::forward<Args>(args)...));
    }

private:
    template<class T_>
    ComponentPool<T_>& getPool()
    {
        hash_code_type hash = get_hash_type<T_>();
        return *componentPools_[hash].get();
    }

    template<class T_>
    static XKE_INLINE hash_code_type get_hash_type()
    {
        return typeid(T_).hash_code();
    }

    const size_t capacity_;
    component_type_id nextComponentId_;
    std::unordered_map<hash_code_type, component_type_id> componentTypes_;
    std::unordered_map<hash_code_type, uptr_t<ComponentPoolBase>> componentPools_;

};

} // namespace ecs

XKE_NAMESPACE_END

# endif //XKE_ENG_ECS_COMPONENT_MANAGER_HPP
