# ifndef XKE_ENG_ECS_COMPONENT_OBJ_HPP
# define XKE_ENG_ECS_COMPONENT_OBJ_HPP

# include <xenyke/eng/ecs/fwd.hpp>

XKE_NAMESPACE_BEGIN

namespace ecs {

template<class T_>
class ComponentObj
{
public:
    ComponentObj() noexcept :
        data_(nullptr)
    {}

    template<class... Args>
    ComponentObj(Args&&... args)
    {
        make(std::forward<Args>(args)...);
    }

    ~ComponentObj() noexcept = default;

    ComponentObj(ComponentObj&& obj) noexcept
        : data_(std::move(obj.data_)) {}

    ComponentObj& operator=(ComponentObj&& obj)
    {
        if (this != &obj) {
            data_ = std::move(obj.data_);
        }
        return *this;
    }

    ComponentObj(const ComponentObj&) = delete;
    ComponentObj& operator=(const ComponentObj&) = delete;


    template<class... Args>
    void make(Args&&... args) noexcept
    {
        data_ = std::make_unique<T_>(std::forward<Args>(args)...);
    }

    void destroy() noexcept
    {
        data_.reset();
    }

    T_* getData() noexcept
    {
        return data_.get();
    }

    const T_* getData() const noexcept
    {
        return data_.get();
    }

private:
    uptr_t<T_> data_;
};

} // namespace ecs

XKE_NAMESPACE_END

# endif //XKE_ENG_ECS_COMPONENT_OBJ_HPP
