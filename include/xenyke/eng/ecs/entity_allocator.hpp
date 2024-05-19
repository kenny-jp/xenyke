# ifndef XKE_ENG_ECS_ENTITY_POOL_HPP
# define XKE_ENG_ECS_ENTITY_POOL_HPP

# include <xenyke/eng/ecs/entity.hpp>
# include <limits>
# include <queue>


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
    IDType INVALID_ENTITY_ID = std::numeric_limits<IDType>::max();

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

        __xke_assert(static_cast<IDType>(id) != INVALID_ENTITY_ID);

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

    void reserve(size_t capacity)
    {
        std::vector<EntityIDType> preallocated;
        preallocated.reserve(capacity);

        while (!freeIds_.empty()) {
            preallocated.push_back(freeIds_.front());
            freeIds_.pop();
        }

        freeIds_ = std::queue<EntityIDType>(std::deque<EntityIDType>(preallocated.begin(), preallocated.end()));
    }

private:
    IDType nextEntityID_;
    std::queue<EntityIDType> freeIds_;
};

} // namespace ecs

XKE_NAMESPACE_END

# endif //XKE_ENG_ECS_ENTITY_POOL_HPP