# ifndef XKE_CORE_RECT_HPP
# define XKE_CORE_RECT_HPP

# include <xenyke/core/vec.hpp>

XKE_NAMESPACE_BEGIN

template<class T_> requires std::is_arithmetic_v<T_>
struct Rect
{
    T_ x;
    T_ y;
    T_ width;
    T_ height;

    Rect() : x(0), y(0), width(0), height(0) {}

    Rect(T_ x, T_ y, T_ width, T_ height) :
        x(x), y(y), width(width), height(height)
    {}

    Rect(const Vec2<T_>& position, const Vec2<T_>& size) :
        x(position.x), y(position.y), width(size.x), height(size.y)
    {}
};

using RectInt = Rect<int32_t>;
using RectFloat = Rect<double>;

XKE_NAMESPACE_END

# include "rect.inl"

# endif // XKE_CORE_RECT_HPP
