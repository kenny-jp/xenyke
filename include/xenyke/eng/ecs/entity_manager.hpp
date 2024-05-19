# ifndef XKE_ENG_ECS_ENTITY_MANAGER_HPP
# define XKE_ENG_ECS_ENTITY_MANAGER_HPP

# include <xenyke/eng/ecs/entity_allocator.hpp>
# include <unordered_map>

# include <xenyke/core/debug.hpp>

XKE_NAMESPACE_BEGIN

namespace ecs {

class EntityManager
{
    using IDAllocator = EntityIDAllocator<EntityID>;

public:
    explicit EntityManager() noexcept = default;

    EntityManager(size_t preallocated_entities)
    {
        reserve(preallocated_entities);
    }

    EntityID createEntity()
    {
        EntityID id = idAlloc_.allocate();
        allocatedEntities_.insert({id, NULL_ENTITY_SIGNATURE});
        xkeDebug() << "Entity " << static_cast<IDAllocator::IDType>(id) << " created.\n";
        return id;
    }

    std::vector<EntityID> createEntities(size_t n)
    {
        std::vector<EntityID> ids = idAlloc_.allocate(n);

        for (size_t i {0}; i < ids.size(); ++i) {
            allocatedEntities_.insert({ids[i], NULL_ENTITY_SIGNATURE});
            xkeDebug() << "Entity " << static_cast<IDAllocator::IDType>(ids[i]) << " created.\n";
        }

        return ids;
    }

    void destroyEntity(EntityID id)
    {
        __xke_assert(allocatedEntities_.contains(id));

        allocatedEntities_.erase(id);
        idAlloc_.deallocate(id);

        xkeDebug() << "Entity " << static_cast<IDAllocator::IDType>(id) << " deleted.\n";
    }

// protected:
    void reserve(size_t capacity)
    {
        idAlloc_.reserve(capacity);
        allocatedEntities_.reserve(capacity);
    }

private:
    IDAllocator idAlloc_;
    std::unordered_map<EntityID, EntitySignature> allocatedEntities_;
};


} // namespace ecs

XKE_NAMESPACE_END

# endif //XKE_ENG_ECS_ENTITY_MANAGER_HPP

