# ifndef XKE_ENG_ECS_COMPONENTS_HPP
# define XKE_ENG_ECS_COMPONENTS_HPP

# include <xenyke/eng/ecs/fwd.hpp>

XKE_NAMESPACE_BEGIN

namespace ecs {

template<class T_>
class ComponentObj
{
public:
    ComponentObj() noexcept
        : obj_(nullptr)
    {}

    ComponentObj(const ComponentObj&) = delete;
    ComponentObj& operator=(const ComponentObj&) = delete;

    ComponentObj(ComponentObj&& other) noexcept
        : obj_(std::move(other.obj_))
    {

    }

    ComponentObj& operator=(const ComponentObj&& other) noexcept
    {
        this->obj_ = std::move(other.obj_);
        return *this;
    }

    ~ComponentObj() noexcept = default;

    template<class... Args>
    void init(Args&&... args)
    {
        obj_ = std::make_unique<T_>(std::forward<Args>(args)...);
    }

    void destroy() noexcept
    {
       obj_.reset();
    }

    T_* getData() noexcept
    {
        return *obj_.get();
    }

    const T_* getData() const noexcept
    {
        return *obj_.get();
    }

private:
    uptr_t<T_> obj_;

};

} // namespace ecs

XKE_NAMESPACE_END

# endif //XKE_ENG_ECS_COMPONENTS_HPP
