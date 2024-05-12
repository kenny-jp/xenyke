// # include <xenyke/eng/ecs/entity_manager.hpp>

// XKE_NAMESPACE_BEGIN

// namespace ecs {

// EntityManager::EntityManager(int32_t capacity, size_t maxComponentPerEntity) :
//     capacity_(capacity), maxComponentPerEntity_(maxComponentPerEntity),
//     entitiesCount_(0)
// {
//     for (int i {capacity_ - 1}; i >= 0; --i){
//         availableEntityIds_.push(i);
//     }
// }

// EntityManager::~EntityManager() noexcept
// {

// }

// Entity& EntityManager::newEntity()
// {
//     __xke_assert(!availableEntityIds_.empty());

//     const entity_id_t newId = availableEntityIds_.top();
//     availableEntityIds_.pop();

//     Entity newEntity(newId, maxComponentPerEntity_);

//     __xke_assert(activeEntities_.insert(std::move(newEntity)).second);

//     entitiesCount_++;

//     return activeEntities_.find(newEntity)._M_cur->_M_v();
// }

// void EntityManager::deleteEntity(const Entity &entity)
// {
//     __xke_assert(entity.id_ >= 0);
//     __xke_assert(entity.id_ < capacity_);


//     if (activeEntities_.contains(entity)) {
//         activeEntities_.erase(entity);
//         availableEntityIds_.push(entity.id_);
//         entitiesCount_--;
//     }
// }


// EntityManager::unordered_entity_set EntityManager::getEntityList() const
// {
//     return list;
// }

// int32_t EntityManager::getEntitiesCount() const
// {
//     return entitiesCount_;
// }

// } // namespace ecs

// XKE_NAMESPACE_END
