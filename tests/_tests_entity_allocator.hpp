#include <xenyke/eng/ecs/entity_allocator.hpp>
#include <xenyke/core/debug.hpp>

using namespace xke::ecs;

class _TESTS_EntityAllocator
{
public:
    static bool __starts_all_tests()
    {
        EntityIDAllocator<EntityID> allocator;

        __xke_assert(allocator.allocatedCount() == 0);
        allocator.reserve(1000);
        __xke_assert(allocator.allocatedCount() == 0);

        std::vector<EntityID> entities = allocator.allocate(1000);
        size_t allocatorCount = allocator.allocatedCount();
        __xke_assert(allocatorCount == 1000);
        __xke_assert(entities.size() == 1000);

        for(size_t i {0}; i < 400; ++i) {
            allocator.deallocate(entities[i]);
        }

        allocatorCount = allocator.allocatedCount();
        __xke_assert(allocatorCount == 600);

        for(size_t i {0}; i < allocatorCount; ++i) {
            allocator.deallocate(entities[i]);
        }

        __xke_assert(allocator.allocatedCount() == 0);

        allocator.allocate();
        auto ent = allocator.allocate();
        __xke_assert(static_cast<EntityIDAllocator<EntityID>::Traits::id_type>(ent) == 1);

        return true;
    }

};
