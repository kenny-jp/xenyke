# ifndef XKE_ENG_ECS_ENTITY_POOL_HPP
# define XKE_ENG_ECS_ENTITY_POOL_HPP

# include <xenyke/eng/ecs/entity.hpp>
# include <unordered_set>
# include <vector>
# include <algorithm>

XKE_NAMESPACE_BEGIN

namespace ecs {

class EntityPool
{
    using value_type = std::pair<EntityID, EntitySignature>;
    using container = std::vector<value_type>;
    using iterator = container::iterator;

public:
    explicit EntityPool() noexcept = default;
    ~EntityPool() noexcept = default;

    EntityPool(size_t capacity) : size_(0)
    {
        data_.reserve(capacity);
        data_.resize(capacity);
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

    void insert(Entity entity)
    {
        const EntityID id = get_entity_id(entity);
        const EntitySignature s = get_entity_signature(entity);

        bool insertSuccess = activeEntities_.insert(id).second;
        __xke_assert(insertSuccess);

        data_.push_back({id, s});

        size_++;
    }

    void destroy(Entity entity)
    {
        const EntityID id = get_entity_id(entity);

        auto it = std::find_if(data_.begin(), data_.end(), [id](const value_type& v)->bool{
            if(v.first == id) {
                return true;
            } else {
                return false;
            }
        });

        if (it != data_.end()) {
            data_.erase(it);
        }

        size_--;
    }


private:
    std::unordered_set<EntityID> activeEntities_;
    container data_;
    size_t size_;


};

} // namespace ecs

XKE_NAMESPACE_END

# endif //XKE_ENG_ECS_ENTITY_POOL_HPP
