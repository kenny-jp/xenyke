# ifndef XKE_ENG_ECS_ENTITY_MANAGER_HPP
# define XKE_ENG_ECS_ENTITY_MANAGER_HPP

# include <xenyke/eng/ecs/entity_allocator.hpp>
# include <unordered_map>

XKE_NAMESPACE_BEGIN

namespace ecs {

class EntityManager
{
    using IDAllocator = EntityIDAllocator<EntityID>;
    using EntityMap   = std::unordered_map<EntityID, EntitySignature>;
    using Iterator    = EntityMap::iterator;

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
        return id;
    }

    std::vector<EntityID> createEntities(size_t n)
    {
        std::vector<EntityID> ids = idAlloc_.allocate(n);

        for (size_t i {0}; i < ids.size(); ++i) {
            allocatedEntities_.insert({ids[i], NULL_ENTITY_SIGNATURE});
        }

        return ids;
    }

    EntitySignature& getEntitySignature(EntityID id)
    {
        __xke_assert(allocatedEntities_.contains(id));

        return allocatedEntities_[id];
    }

    EntitySignature getEntitySignature(EntityID id) const
    {
        __xke_assert(allocatedEntities_.contains(id));

        return allocatedEntities_.at(id);
    }

    void entityDestroyed(EntityID id)
    {
        __xke_assert(allocatedEntities_.contains(id));

        allocatedEntities_.erase(id);
        idAlloc_.deallocate(id);
    }

    void reserve(size_t capacity)
    {
        allocatedEntities_.reserve(capacity);
    }

    void addComponentType(EntityID id, ComponentType type)
    {
        EntitySignature& sign = allocatedEntities_[id];
        sign |= (1 << type);
    }

    void removeComponentType(EntityID id, ComponentType type)
    {
        EntitySignature& sign = allocatedEntities_[id];
        sign ^= (1 << type);
    }

    size_t entitiesCount() const
    {
        return allocatedEntities_.size();
    }

    EntityMap entitiesMap() const
    {
        return allocatedEntities_;
    }

    Iterator begin()
    {
        return allocatedEntities_.begin();
    }

    Iterator end()
    {
        return allocatedEntities_.end();
    }

private:
    IDAllocator idAlloc_;
    EntityMap allocatedEntities_;
};


} // namespace ecs

XKE_NAMESPACE_END

# endif //XKE_ENG_ECS_ENTITY_MANAGER_HPP

