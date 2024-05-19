# ifndef XKE_ENG_ECS_COMPONENT_POOL_HPP
# define XKE_ENG_ECS_COMPONENT_POOL_HPP

# include <xenyke/eng/ecs/entity.hpp>
# include <xenyke/eng/ecs/component.hpp>
# include <unordered_map>
# include <vector>

# include  <xenyke/core/debug.hpp>

XKE_NAMESPACE_BEGIN

namespace ecs {

class ComponentPoolBase
{
public:
    virtual ~ComponentPoolBase() = default;

    virtual void entityDestroyed(EntityID id) = 0;
};

template<class T_>
class ComponentPool : public ComponentPoolBase
{
    using container = std::vector<ComponentObj<T_>>;
    using iterator  = container::iterator;

public:
    ComponentPool()
        : size_(0)
    {

    }

    ComponentPool(size_t capacity)
        : size_(0)
    {
        reserve(capacity);
    }

    iterator begin()
    {
        return data_.begin();
    }

    iterator end()
    {
        return data_.begin() + size_;
    }

    size_t size() const
    {
        return size_;
    }

    void reserve(size_t capacity)
    {
        data_.reserve(capacity);
        entityToIndex_.reserve(capacity);
        indexToEntity_.reserve(capacity);
    }

    void insertData(EntityID id, const T_& data)
    {
        __xke_assert(!entityToIndex_.contains(id));

        size_t index = size_;

        ComponentObj<T_> obj(data);

        if (data_.size() <= size_) {
            data_.push_back(std::move(obj));
            xkeDebug() << "Data insered via push_back\n";
        } else {
            data_[size_] = std::move(obj);
            xkeDebug() << "Data insered via replace end data\n";
        }

        entityToIndex_[id] = index;
        indexToEntity_[index] = id;
        size_++;
    }

    void removeData(EntityID id)
    {
        __xke_assert(entityToIndex_.contains(id));

        size_t indexOfRemovedEntity = entityToIndex_[id];
        size_t indexOfLastElement = size_ - 1;

        if (indexOfRemovedEntity != indexOfLastElement) {
            std::swap(data_[indexOfRemovedEntity], data_[indexOfLastElement]);

            EntityID entityOfLastElement = indexToEntity_[indexOfLastElement];
            entityToIndex_[entityOfLastElement] = indexOfRemovedEntity;
            indexToEntity_[indexOfRemovedEntity] = entityOfLastElement;
        }

        data_.back().destroy();
        entityToIndex_.erase(id);
        indexToEntity_.erase(indexOfLastElement);

        xkeDebug() << "Data removed\n";

        size_--;
    }

    void entityDestroyed(EntityID id) override
    {
        if(entityToIndex_.contains(id)) {
            removeData(id);
        }
    }

private:
    size_t size_;
    container data_;
    std::unordered_map<EntityID, size_t> entityToIndex_;
    std::unordered_map<size_t, EntityID> indexToEntity_;

};


} // namespace ecs

XKE_NAMESPACE_END

# endif //XKE_ENG_ECS_COMPONENT_POOL_HPP
