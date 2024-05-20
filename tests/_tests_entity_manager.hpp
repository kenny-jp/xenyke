#include <xenyke/eng/ecs/entity_manager.hpp>
#include <xenyke/core/debug.hpp>

using namespace xke::ecs;

class _TESTS_EntityManager
{
public:
    static bool __starts_all_tests()
    {
        EntityManager mngr(1024);

        auto entities = mngr.createEntities(1024);

        __xke_assert(mngr.entitiesCount() == 1024);

        __xke_assert(entities.size() == 1024);

        mngr.addComponentType(entities[0], 0);
        mngr.addComponentType(entities[0], 3);

        __xke_assert(mngr.getEntitySignature(entities[0]) == 9);

        mngr.removeComponentType(entities[0], 3);
        __xke_assert(mngr.getEntitySignature(entities[0]) == 1);

        mngr.removeComponentType(entities[0], 0);
        __xke_assert(mngr.getEntitySignature(entities[0]) == 0);

        mngr.entityDestroyed(entities[0]);
        mngr.entityDestroyed(entities[1]);
        mngr.entityDestroyed(entities[2]);
        mngr.entityDestroyed(entities[3]);
        __xke_assert(mngr.entitiesCount() == 1020);


        return true;
    }

};
