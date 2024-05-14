# include <xenyke/eng/ecs/entity_manager.hpp>

XKE_NAMESPACE_BEGIN

namespace ecs {

EntityManager::EntityManager(int32_t capacity)
    : capacity_(capacity), entitiesCount_(0)
{
    for (int i {capacity_ - 1}; i >= 0; --i){
        availableEntityIds_.push(i);
    }
}

EntityManager::~EntityManager() noexcept
{

}

Entity& EntityManager::newEntity()
{
    __xke_assert(!availableEntityIds_.empty());

    const entity_id newId = availableEntityIds_.top();
    availableEntityIds_.pop();
    Entity newEntity;
    newEntity.init(newId);

    const auto& pair = activeEntities_.insert(std::move(newEntity));
    Entity& refEntity = pair.first._M_cur->_M_v();

    entitiesMap_.insert({newId, refEntity});

    entitiesCount_++;

    return refEntity;
}

void EntityManager::deleteEntity(const Entity &entity)
{
    __xke_assert(entity.id_ >= 0);
    __xke_assert(entity.id_ < capacity_);


    if (activeEntities_.contains(entity)) {
        activeEntities_.erase(entity);
        entitiesMap_.erase(entity.id_);
        availableEntityIds_.push(entity.id_);
        entitiesCount_--;
    }
}

Entity& EntityManager::getEntityType(entity_id id)
{
    __xke_assert(entitiesMap_.contains(id));
    return entitiesMap_.find(id)->second;
}

const Entity& EntityManager::getEntityType(entity_id id) const
{
    __xke_assert(entitiesMap_.contains(id));
    return entitiesMap_.find(id)->second;
}

void EntityManager::addComponent(Entity &entity, component_type_id cmp)
{
    entity.sign_ |= (1 << cmp);
}

void EntityManager::removeComponent(Entity &entity, component_type_id cmp)
{
    entity.sign_ ^= (1 << cmp);
}

bool EntityManager::hasComponent(Entity &entity, component_type_id cmp)
{
    return (entity.sign_ & cmp) == cmp;
}


const EntityManager::unordered_entity_set& EntityManager::getEntityList() const
{
    return activeEntities_;
}

int32_t EntityManager::getEntitiesCount() const
{
    return entitiesCount_;
}

} // namespace ecs

XKE_NAMESPACE_END
