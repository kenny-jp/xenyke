# ifndef XKE_ENG_ECS_ENTITY_MANAGER_HPP
# define XKE_ENG_ECS_ENTITY_MANAGER_HPP

# include <xenyke/eng/ecs/entity.hpp>
# include <stack>
# include <unordered_map>
# include <unordered_set>

XKE_NAMESPACE_BEGIN

namespace ecs {

class EntityManager
{
    using unordered_entity_set = std::unordered_set<Entity, EntityHash, EntityKeyEqual>;
    using entity_stack = std::stack<entity_id_t>;

public:
    EntityManager(int32_t capacity);
    ~EntityManager() noexcept;

    Entity& newEntity();
    void deleteEntity(const Entity& entity);
    void deleteEntity(entity_id_t entityID);

    void addComponent(Entity& entity, component_signature_t cmp);
    void removeComponent(Entity& entity, component_signature_t cmp);
    bool hasComponent(Entity& entity, component_signature_t cmp);

    const unordered_entity_set& getEntityList() const;
    int32_t getEntitiesCount() const;

private:
    const int32_t capacity_;
    int32_t entitiesCount_;

    entity_stack availableEntityIds_;
    unordered_entity_set activeEntities_;
};

} // namespace ecs

XKE_NAMESPACE_END

# endif //XKE_ENG_ECS_ENTITY_MANAGER_HPP
