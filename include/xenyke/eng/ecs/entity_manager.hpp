# ifndef XKE_ENG_ECS_ENTITY_MANAGER_HPP
# define XKE_ENG_ECS_ENTITY_MANAGER_HPP

# include <xenyke/eng/ecs/entity.hpp>
# include <xenyke/eng/ecs/entity_pool.hpp>
# include <queue>

XKE_NAMESPACE_BEGIN

namespace ecs {

class EntityManager
{
public:
    EntityManager() : nextEntityID_(0)
    {

    }

    Entity createEntity()
    {
        Entity entity;

        if (!freeIds_.empty()) {
            set_entity_id(entity, freeIds_.front());
            freeIds_.pop();
        } else {
            set_entity_id(entity, nextEntityID_++);
        }

        return entity;
    }

    void destroyEntity(Entity entity)
    {
        const EntityID id = get_entity_id(entity);
        if (id < nextEntityID_) {
            freeIds_.push(id);


        }
    }

private:
    EntityID nextEntityID_;
    std::queue<EntityID> freeIds_;
    EntityPool entityPool_;

};


} // namespace ecs

XKE_NAMESPACE_END

# endif //XKE_ENG_ECS_ENTITY_MANAGER_HPP

