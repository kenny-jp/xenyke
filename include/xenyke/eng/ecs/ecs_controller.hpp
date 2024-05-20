# ifndef XKE_ENG_ECS_ECS_CONTROLLER_HPP
# define XKE_ENG_ECS_ECS_CONTROLLER_HPP

# include <xenyke/eng/ecs/entity_manager.hpp>
# include <xenyke/eng/ecs/component_manager.hpp>

XKE_NAMESPACE_BEGIN

namespace ecs {

using Entity  = EntityID;
using EntSign = EntitySignature;

class ECSController
{
public:
    explicit ECSController() noexcept = default;
    ~ECSController() noexcept = default;

    void Init()
    {
        entityMngr_ = std::make_unique<ecs::EntityManager>();
        componentMngr_ = std::make_unique<ecs::ComponentManager>();
    }

    void Init(size_t preallocated_entities, size_t preallocated_components)
    {
        entityMngr_ = std::make_unique<ecs::EntityManager>(preallocated_entities);
        componentMngr_ = std::make_unique<ecs::ComponentManager>(preallocated_components);
    }

    void Stop()
    {
        entityMngr_.reset();
        componentMngr_.reset();
    }

    Entity createEntity()
    {
        return entityMngr_->createEntity();
    }

    void deleteEntity(Entity entity)
    {
        entityMngr_->entityDestroyed(entity);
        componentMngr_->entityDestroyed(entity);
    }

    template<class T_>
    void registerComponent()
    {
        componentMngr_->registerComponent<T_>();
    }

    template<class T_>
    void addComponentToEntity(Entity entity, const T_& cmp)
    {
        componentMngr_->addComponent(entity, cmp);
    }

    template<class T_>
    void removeComponentToEntity(Entity entity)
    {
        componentMngr_->removeComponent<T_>(entity);
    }

    template<class T_>
    T_& getComponentToEntity(Entity entity)
    {
        return componentMngr_->getComponent<T_>(entity);
    }

    template<class T_>
    const T_& getComponentToEntity(Entity entity) const
    {
        return componentMngr_->getComponent<T_>(entity);
    }

    template<class... Args>
    std::tuple<Args&...> each(Entity entity)
    {
        return componentMngr_->each<Args...>(entity);
    }

    template<class... Args>
    const std::tuple<const Args&...> each(Entity entity) const
    {
        return componentMngr_->each<Args...>(entity);
    }

    size_t entitiesCount() const
    {
        return entityMngr_->entitiesCount();
    }

private:
    uptr_t<ecs::EntityManager> entityMngr_;
    uptr_t<ecs::ComponentManager> componentMngr_;

};

} // namespace ecs

XKE_NAMESPACE_END

# endif //XKE_ENG_ECS_ECS_CONTROLLER_HPP
