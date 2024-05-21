# ifndef XKE_ENG_ECS_ENTITY_POOL_HPP
# define XKE_ENG_ECS_ENTITY_POOL_HPP

# include <xenyke/eng/ecs/fwd.hpp>
# include <limits>
# include <queue>
# include <atomic>

XKE_NAMESPACE_BEGIN

namespace ecs {


template<class T_, bool isEnum_ = std::is_enum_v<T_>>
struct IDAllocatorTraits;

template<class T_>
struct IDAllocatorTraits<T_, true>
{
    using id_type = std::underlying_type_t<T_>;
    using entity_id_type = T_;
};

template<class T_>
struct IDAllocatorTraits<T_, false>
{
    using id_type = T_;
    using entity_id_type = T_;
};


template<class EntityType_>
class EntityIDAllocator
{
public:
    using Traits = IDAllocatorTraits<EntityType_>;

    using IDType = Traits::id_type;
    using EntityIDType = Traits::entity_id_type;

    static XKE_INLINE_CONSTEXPR
    EntityIDType INVALID_ENTITY_ID = static_cast<EntityIDType>(std::numeric_limits<IDType>::max());

public:
    EntityIDAllocator() : nextEntityID_(0)
    {}

    EntityIDType allocate()
    {
        EntityIDType id;

        if (freeIds_.empty()) {
            id = static_cast<EntityIDType>(nextEntityID_++);
        } else {
            id = freeIds_.front();
            freeIds_.pop();
        }

        __xke_assert(id != INVALID_ENTITY_ID);

        return id;
    }

    std::vector<EntityIDType> allocate(size_t n)
    {
        std::vector<EntityIDType> allocatedEntities;
        allocatedEntities.reserve(n);

        for (; n > 0; --n) {
            allocatedEntities.push_back(allocate());
        }

        return allocatedEntities;
    }

    void deallocate(EntityIDType id)
    {
        freeIds_.push(id);
    }

    size_t allocatedCount() const
    {
        __xke_assert(nextEntityID_ >= freeIds_.size());
        return nextEntityID_ - freeIds_.size();
    }

private:
    std::atomic<IDType> nextEntityID_;
    // IDType nextEntityID_;
    std::queue<EntityIDType> freeIds_;
};

} // namespace ecs

XKE_NAMESPACE_END

# endif //XKE_ENG_ECS_ENTITY_POOL_HPP
