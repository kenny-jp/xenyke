#include "_tests_entity_allocator.hpp"
#include "_tests_entity_manager.hpp"

#include <xenyke/eng/ecs/ecs_controller.hpp>

struct Transform
{
    int x;
    int y;
    int w;
    int h;
};

struct Sprite
{
    std::string filename;
};

int main()
{
    __xke_assert(_TESTS_EntityAllocator::__starts_all_tests());
    __xke_assert(_TESTS_EntityManager::__starts_all_tests());

    ECSController controller;
    controller.Init();

    Entity e0 = controller.createEntity();
    Entity e1 = controller.createEntity();
    Entity e2 = controller.createEntity();

    xkeDebug() << "entities cout: "
               << controller.entitiesCount()
               << xke::endl;

    controller.registerComponent<Transform>();
    controller.registerComponent<Sprite>();


    {
        Transform tr;
        tr.x = 10;
        Sprite sp;
        sp.filename = "ent0";
        controller.addComponentToEntity(e0, tr);
        controller.addComponentToEntity(e0, sp);
    }

    {
        Transform tr;
        tr.x = 20;
        Sprite sp;
        sp.filename = "ent1";
        controller.addComponentToEntity(e1, tr);
        controller.addComponentToEntity(e1, sp);
    }

    {
        Transform tr;
        tr.x = 30;
        Sprite sp;
        sp.filename = "ent2";
        controller.addComponentToEntity(e2, tr);
        controller.addComponentToEntity(e2, sp);
    }


    {
        const auto&[t,s] = controller.each<Transform, Sprite>(e1);
        xkeDebug() << t.x << " " << s.filename.c_str() << xke::endl;
        s.filename = "updated e1";
    }

    auto& s = controller.getComponentToEntity<Sprite>(e1);
    xkeDebug(s.filename.c_str());

    controller.Stop();
    return 0;
}
