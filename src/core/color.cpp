# include <xenyke/core/color.hpp>
# include <xenyke/core/ostream.hpp>

XKE_NAMESPACE_BEGIN

xke::ostream &operator<<(ostream &os, const ColorRgb &color)
{
    os << "xke::ColorRgb: "
       << static_cast<int32_t>(color.red()   * 255) << ":"
       << static_cast<int32_t>(color.green() * 255) << ":"
       << static_cast<int32_t>(color.blue()  * 255);

    return os;
}

xke::ostream &operator<<(ostream &os, const ColorRgba &color)
{
    os << "xke::ColorRgba: "
       << static_cast<int32_t>(color.red()   * 255) << ":"
       << static_cast<int32_t>(color.green() * 255) << ":"
       << static_cast<int32_t>(color.blue()  * 255) << ":"
       << static_cast<int32_t>(color.alpha() * 255);

    return os;
}

XKE_NAMESPACE_END

