XKE_NAMESPACE_BEGIN

// Vec2 Impl
template<class T_> requires std::is_arithmetic_v<T_>
Vec2<T_>& Vec2<T_>::operator+=(const Vec2<T_>& other)
{
    this->x += other.x;
    this->y += other.y;
    return *this;
}

template<class T_> requires std::is_arithmetic_v<T_>
Vec2<T_>& Vec2<T_>::operator-=(const Vec2<T_>& other)
{
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}

template<class T_> requires std::is_arithmetic_v<T_>
Vec2<T_>& Vec2<T_>::operator+=(float addend)
{
    this->x += addend;
    this->y += addend;
    return *this;
}

template<class T_> requires std::is_arithmetic_v<T_>
Vec2<T_>& Vec2<T_>::operator-=(float minuend)
{
    this->x -= minuend;
    this->y -= minuend;
    return *this;
}

template<class T_> requires std::is_arithmetic_v<T_>
    Vec2<T_>& Vec2<T_>::operator*=(float factor)
{
    this->x *= factor;
    this->y *= factor;
    return *this;
}

template<class T_> requires std::is_arithmetic_v<T_>
Vec2<T_>& Vec2<T_>::operator/=(float divisor)
{
    __xke_assert(divisor == 0, "Cannot divide by 0");

    this->x /= divisor;
    this->y /= divisor;
    return *this;
}

template<class T_> requires std::is_arithmetic_v<T_>
Vec2<T_> XKE_API operator+(const Vec2<T_>& lhs, const Vec2<T_>& rhs)
{
    Vec2<T_> result {lhs};
    return result += rhs;
}

template<class T_> requires std::is_arithmetic_v<T_>
Vec2<T_> XKE_API operator-(const Vec2<T_>& lhs, const Vec2<T_>& rhs)
{
    Vec2<T_> result {lhs};
    return result -= rhs;
}

template<class T_> requires std::is_arithmetic_v<T_>
Vec2<T_> XKE_API operator+(const Vec2<T_>& lhs, float addend)
{
    Vec2<T_> result {lhs};
    return result += addend;
}

template<class T_> requires std::is_arithmetic_v<T_>
Vec2<T_> XKE_API operator-(const Vec2<T_>& lhs, float minuend)
{
    Vec2<T_> result {lhs};
    return result -= minuend;
}

template<class T_> requires std::is_arithmetic_v<T_>
Vec2<T_> XKE_API operator*(const Vec2<T_>& lhs, float factor)
{
    Vec2<T_> result {lhs};
    return result *= factor;
}

template<class T_> requires std::is_arithmetic_v<T_>
Vec2<T_> XKE_API operator/(const Vec2<T_>& lhs, float divisor)
{
    Vec2<T_> result {lhs};
    return result /= divisor;
}

template<class T_> requires std::is_arithmetic_v<T_>
bool XKE_API operator==(const Vec2<T_>& lhs, const Vec2<T_>& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

template<class T_> requires std::is_arithmetic_v<T_>
bool XKE_API operator!=(const Vec2<T_>& lhs, const Vec2<T_>& rhs)
{
    return !(lhs == rhs);
}

XKE_NAMESPACE_END
