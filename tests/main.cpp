#include "_tests_entity_allocator.hpp"
#include "_tests_entity_manager.hpp"

int main()
{
    __xke_assert(_TESTS_EntityAllocator::__starts_all_tests());
    __xke_assert(_TESTS_EntityManager::__starts_all_tests());

    return 0;
}
