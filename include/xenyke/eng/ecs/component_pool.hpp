# ifndef XKE_ENG_ECS_COMPONENT_POOL_HPP
# define XKE_ENG_ECS_COMPONENT_POOL_HPP

# include <xenyke/eng/ecs/entity.hpp>
# include <xenyke/eng/ecs/component.hpp>
# include <unordered_map>
# include <vector>

XKE_NAMESPACE_BEGIN

namespace ecs {

class ComponentPoolBase
{
public:
    explicit ComponentPoolBase() = default;
    virtual ~ComponentPoolBase() = default;

    virtual void entityDeleted(Entity entity) = 0;
};

template<class T_> requires std::is_trivial_v<T_>
class ComponentPool : public ComponentPoolBase
{
    using containter = std::vector<ComponentObj<T_>>;
    using iterator = containter::iterator;
    using const_iterator = containter::const_iterator;

public:
    ComponentPool(size_t capacity) :
        capacity_(capacity),
        size_(0)
    {
        componentsData_.reserve(capacity_);
        componentsData_.resize(capacity_);
    }

    iterator begin()
    {
        return componentsData_.begin();
    }

    iterator end()
    {
        return &componentsData_.begin() + size_;
    }

    const_iterator cbegin() const
    {
        return componentsData_.cbegin();
    }

    const_iterator cend() const
    {
        return componentsData_.cbegin() + size_;
    }

    size_t size() const
    {
        return size_;
    }

    void insertData(Entity entity, const T_& data)
    {
        __xke_assert(!entityToIndex_.contains(entity));
        __xke_assert(size_ < capacity_);

        size_t newIndex = size_;

        componentsData_[entity].make(data);

        entityToIndex_[entity] = newIndex;
        indexToEntity_[newIndex] = entity;

        ++size_;
    }

    void removeData(Entity entity)
    {
        __xke_assert(entityToIndex_.contains(entity));

        size_t indexOfRemovedEntity = entityToIndex_[entity];
        size_t indexOfLastElement = size_ - 1;

        std::swap(componentsData_[indexOfRemovedEntity], componentsData_[indexOfLastElement]);

        Entity entityOfLastElement = indexToEntity_[indexOfLastElement];
        entityToIndex_[entityOfLastElement] = indexOfRemovedEntity;
        indexToEntity_[indexOfRemovedEntity] = entityOfLastElement;

        componentsData_[indexOfLastElement].destroy();
        entityToIndex_.erase(entity);
        indexToEntity_.erase(indexOfLastElement);

        --size_;
    }

    T_& getData(Entity entity)
    {
        __xke_assert(entityToIndex_.contains(entity));

        return *componentsData_[entityToIndex_[entity]].getData();
    }

    const T_& getData(Entity entity) const
    {
        __xke_assert(entityToIndex_.contains(entity));

        return *componentsData_[entityToIndex_.at(entity)].getData();
    }

    void entityDeleted(Entity entity) override
    {
        removeData(entity);
    }

private:
    containter componentsData_;
    std::unordered_map<Entity, size_t> entityToIndex_;
    std::unordered_map<size_t, Entity> indexToEntity_;
    size_t capacity_;
    size_t size_;


};

} // namespace ecs

XKE_NAMESPACE_END

# endif //XKE_ENG_ECS_COMPONENT_POOL_HPP
