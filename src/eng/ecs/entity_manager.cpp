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

    const entity_id_t newId = availableEntityIds_.top();
    availableEntityIds_.pop();

    Entity newEntity;
    newEntity.init(newId);

    __xke_assert(activeEntities_.insert(std::move(newEntity)).second);

    entitiesCount_++;

    return activeEntities_.find(newEntity)._M_cur->_M_v();
}

void EntityManager::deleteEntity(const Entity &entity)
{
    __xke_assert(entity.id_ >= 0);
    __xke_assert(entity.id_ < capacity_);


    if (activeEntities_.contains(entity)) {
        activeEntities_.erase(entity);
        availableEntityIds_.push(entity.id_);
        entitiesCount_--;
    }
}

void EntityManager::addComponent(Entity &entity, component_signature_t cmp)
{
    entity.sign_ |= (1 << cmp);
}

void EntityManager::removeComponent(Entity &entity, component_signature_t cmp)
{
    entity.sign_ ^= (1 << cmp);
}

bool EntityManager::hasComponent(Entity &entity, component_signature_t cmp)
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
