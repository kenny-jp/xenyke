# ifndef XKE_CORE_VEC_HPP
# define XKE_CORE_VEC_HPP

# include <xenyke/core/config.hpp>

XKE_NAMESPACE_BEGIN

template<class T_> requires std::is_arithmetic_v<T_>
class Vec2
{
public:
    explicit Vec2() noexcept : x(0), y(0) {}
    Vec2(T_ x, T_ y) noexcept : x(x), y(y) {}
    ~Vec2() noexcept = default;

    Vec2& operator+=(const Vec2& other) noexcept;
    Vec2& operator-=(const Vec2& other) noexcept;
    Vec2& operator+=(float addend) noexcept;
    Vec2& operator-=(float minuend) noexcept;
    Vec2& operator*=(float factor) noexcept;
    Vec2& operator/=(float divisor) noexcept;

    T_ x;
    T_ y;
};

template<class T_> requires std::is_arithmetic_v<T_>
Vec2<T_> XKE_API operator+(const Vec2<T_>& lhs, const Vec2<T_>& rhs);

template<class T_> requires std::is_arithmetic_v<T_>
Vec2<T_> XKE_API operator-(const Vec2<T_>& lhs, const Vec2<T_>& rhs);

template<class T_> requires std::is_arithmetic_v<T_>
Vec2<T_> XKE_API operator+(const Vec2<T_>& lhs, float addend);

template<class T_> requires std::is_arithmetic_v<T_>
Vec2<T_> XKE_API operator-(const Vec2<T_>& lhs, float minuend);

template<class T_> requires std::is_arithmetic_v<T_>
Vec2<T_> XKE_API operator*(const Vec2<T_>& lhs, float factor);

template<class T_> requires std::is_arithmetic_v<T_>
Vec2<T_> XKE_API operator/(const Vec2<T_>& lhs, float divisor);

template<class T_> requires std::is_arithmetic_v<T_>
bool XKE_API operator==(const Vec2<T_>& lhs, const Vec2<T_>& rhs);

template<class T_> requires std::is_arithmetic_v<T_>
bool XKE_API operator!=(const Vec2<T_>& lhs, const Vec2<T_>& rhs);


template<class T_> requires std::is_arithmetic_v<T_>
class Vec3
{
public:
    explicit Vec3() noexcept : x(0), y(0), z(0) {};
    Vec3(T_ x, T_ y, T_ z) noexcept : x(x), y(y), z(z) {}
    ~Vec3() noexcept = default;

    Vec3& operator+=(const Vec3& other);
    Vec3& operator-=(const Vec3& other);
    Vec3& operator+=(float addend);
    Vec3& operator-=(float minuend);
    Vec3& operator*=(float factor);
    Vec3& operator/=(float divisor);

    T_ x;
    T_ y;
    T_ z;
};

template<class T_> requires std::is_arithmetic_v<T_>
Vec2<T_> XKE_API operator+(const Vec3<T_>& lhs, const Vec3<T_>& rhs);

template<class T_> requires std::is_arithmetic_v<T_>
Vec2<T_> XKE_API operator-(const Vec3<T_>& lhs, const Vec3<T_>& rhs);

template<class T_> requires std::is_arithmetic_v<T_>
Vec2<T_> XKE_API operator+(const Vec3<T_>& lhs, float addend);

template<class T_> requires std::is_arithmetic_v<T_>
Vec2<T_> XKE_API operator-(const Vec3<T_>& lhs, float minuend);

template<class T_> requires std::is_arithmetic_v<T_>
Vec2<T_> XKE_API operator*(const Vec3<T_>& lhs, float factor);

template<class T_> requires std::is_arithmetic_v<T_>
Vec2<T_> XKE_API operator/(const Vec3<T_>& lhs, float divisor);

template<class T_>
bool XKE_API operator==(const Vec3<T_>& lhs, const Vec3<T_>& rhs);

template<class T_>
bool XKE_API operator!=(const Vec3<T_>& lhs, const Vec3<T_>& rhs);


using Vec2i = Vec2<int32_t>;
using Vec2u = Vec2<uint32_t>;
using Vec2f = Vec2<float>;
using Vec2d = Vec2<double>;

using Vec3i = Vec3<int32_t>;
using Vec3u = Vec3<uint32_t>;
using Vec3f = Vec3<float>;
using Vec3d = Vec3<double>;

XKE_NAMESPACE_END

# include "vec2.inl"
# include "vec3.inl"

# endif //XKE_CORE_VEC_HPP
