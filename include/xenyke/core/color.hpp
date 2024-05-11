# ifndef XKE_CORE_COLOR_HPP
# define XKE_CORE_COLOR_HPP

# include <xenyke/core/config.hpp>

XKE_NAMESPACE_BEGIN

struct __color_rgb;
struct __color_rgba;

enum class ColorMask : uint32_t
{
    Red     = 0x00FFFFFF,
    Green   = 0xFF00FFFF,
    Blue    = 0xFFFF00FF,
    Alpha   = 0xFFFFFF00
};

template<class ColorType_>
struct __color_traits;

template<>
struct __color_traits<__color_rgb>
{
    using color_type = uint8_t[3];

    static XKE_INLINE_CONSTEXPR
    void _S_setColor(color_type& __color, uint8_t& __r, uint8_t& __g, uint8_t& __b, const uint8_t& = 0x0) noexcept
    {
        _S_setRed(__color, __r);
        _S_setGreen(__color, __g);
        _S_setBlue(__color, __b);
    }

    static XKE_INLINE_CONSTEXPR
    void _S_setRed(color_type& __color, uint8_t __r)
    {
        __color[0] = __r;
    }

    static XKE_INLINE_CONSTEXPR
    void _S_setGreen(color_type& __color, uint8_t __g)
    {
        __color[1] = __g;
    }

    static XKE_INLINE_CONSTEXPR
    void _S_setBlue(color_type& __color, uint8_t __b)
    {
        __color[2] = __b;
    }

    static XKE_INLINE_CONSTEXPR
    float _S_getRed(const color_type& __color)
    {
        return static_cast<float>(__color[0] / 255.f);
    }

    static XKE_INLINE_CONSTEXPR
    float _S_getGreen(const color_type& __color)
    {
        return static_cast<float>(__color[1] / 255.f);
    }

    static XKE_INLINE_CONSTEXPR
    float _S_getBlue(const color_type& __color)
    {
        return static_cast<float>(__color[2] / 255.f);
    }
};

template<>
struct __color_traits<__color_rgba>
{
    using color_type = uint32_t;

    static XKE_INLINE_CONSTEXPR
    void _S_setColor(color_type& __color, uint8_t& __r, uint8_t& __g, uint8_t& __b, uint8_t& __a) noexcept
    {
        _S_setRed(__color, __r);
        _S_setGreen(__color, __g);
        _S_setBlue(__color, __b);
        _S_setAlpha(__color, __a);
    }

    static XKE_INLINE_CONSTEXPR
    void _S_setRed(color_type& __color, uint8_t __r)
    {
        __color = (__color & static_cast<uint32_t>(ColorMask::Red)) | (static_cast<uint32_t>(__r) << 24);
    }

    static XKE_INLINE_CONSTEXPR
    void _S_setGreen(color_type& __color, uint8_t __g)
    {
        __color = (__color & static_cast<uint32_t>(ColorMask::Green)) | (static_cast<uint32_t>(__g) << 16);
    }

    static XKE_INLINE_CONSTEXPR
    void _S_setBlue(color_type& __color, uint8_t __b)
    {
        __color = (__color & static_cast<uint32_t>(ColorMask::Blue)) | (static_cast<uint32_t>(__b) << 8);
    }

    static XKE_INLINE_CONSTEXPR
    void _S_setAlpha(color_type& __color, uint8_t __a)
    {
        __color = (__color & static_cast<uint32_t>(ColorMask::Alpha)) | static_cast<uint32_t>(__a);
    }

    static XKE_INLINE_CONSTEXPR
    float _S_getRed(const color_type& __color)
    {
        return static_cast<float>(__color >> 24) / 255.f;
    }

    static XKE_INLINE_CONSTEXPR
    float _S_getGreen(const color_type& __color)
    {
        return static_cast<float>((__color >> 16) & 0xFF) / 255.f;
    }

    static XKE_INLINE_CONSTEXPR
    float _S_getBlue(const color_type& __color)
    {
        return static_cast<float>((__color >> 8) & 0xFF) / 255.f;
    }

    static XKE_INLINE_CONSTEXPR
    float _S_getAlpha(const color_type& __color)
    {
        return static_cast<float>(__color & 0xFF) / 255.f;
    }
};

template<class ColorType>
class __Color;


template<>
class __Color<__color_rgb>
{
public:
    using _Color = __color_traits<__color_rgb>;;
    using color_type = _Color::color_type;


public:
    static XKE_INLINE_CONSTEXPR uint32_t Black   = 0x000000ff;
    static XKE_INLINE_CONSTEXPR uint32_t Red     = 0xff0000ff;
    static XKE_INLINE_CONSTEXPR uint32_t Green   = 0x00ff00ff;
    static XKE_INLINE_CONSTEXPR uint32_t Blue    = 0x0000ffff;
    static XKE_INLINE_CONSTEXPR uint32_t Yellow  = 0xffff00ff;
    static XKE_INLINE_CONSTEXPR uint32_t Cyan    = 0x00ffffff;
    static XKE_INLINE_CONSTEXPR uint32_t Magenta = 0xff00ffff;
    static XKE_INLINE_CONSTEXPR uint32_t White   = 0xffffffff;
    static XKE_INLINE_CONSTEXPR uint32_t Orange  = 0xffa500ff;
    static XKE_INLINE_CONSTEXPR uint32_t Pink    = 0xffc0cbff;
    static XKE_INLINE_CONSTEXPR uint32_t Purple  = 0x800080ff;
    static XKE_INLINE_CONSTEXPR uint32_t Brown   = 0xa52a2aff;
    static XKE_INLINE_CONSTEXPR uint32_t Gray    = 0x808080ff;

    XKE_CONSTEXPR explicit __Color() noexcept
        : color_(0)
    {
    }

    XKE_CONSTEXPR __Color(uint8_t red, uint8_t green, uint8_t blue) noexcept
    {
        setColor(red, green, blue);
    }

    XKE_CONSTEXPR __Color(uint32_t color) noexcept
    {
        color_[0] = color >> 24;
        color_[1] = color >> 16;
        color_[2] = color >> 8;
    }

    XKE_CONSTEXPR void setColor(const color_type& color) noexcept
    {
        color_[0] = color[0];
        color_[1] = color[1];
        color_[2] = color[2];
    }

    XKE_CONSTEXPR
    void setColor(uint8_t red, uint8_t green, uint8_t blue) noexcept
    {
        _Color::_S_setColor(color_, red, green, blue);
    }

    XKE_INLINE_CONSTEXPR
    void setRed(uint8_t value) noexcept
    {
        _Color::_S_setRed(color_, value);
    }

    XKE_INLINE_CONSTEXPR
    void setGreen(uint8_t value) noexcept
    {
        _Color::_S_setGreen(color_, value);
    }

    XKE_INLINE_CONSTEXPR
    void setBlue(uint8_t value) noexcept
    {
        _Color::_S_setBlue(color_, value);
    }

    XKE_INLINE_CONSTEXPR float red() const noexcept
    {
        return _Color::_S_getRed(color_);
    }

    XKE_INLINE_CONSTEXPR float green() const noexcept
    {
        return _Color::_S_getGreen(color_);
    }

    XKE_INLINE_CONSTEXPR float blue() const noexcept
    {
        return _Color::_S_getBlue(color_);
    }

private:
    color_type color_;

};


template<>
class __Color<__color_rgba>
{
public:
    using _Color = __color_traits<__color_rgba>;;
    using color_type = _Color::color_type;


public:
    static XKE_INLINE_CONSTEXPR uint32_t Black   = 0x000000ff;
    static XKE_INLINE_CONSTEXPR uint32_t Red     = 0xff0000ff;
    static XKE_INLINE_CONSTEXPR uint32_t Green   = 0x00ff00ff;
    static XKE_INLINE_CONSTEXPR uint32_t Blue    = 0x0000ffff;
    static XKE_INLINE_CONSTEXPR uint32_t Yellow  = 0xffff00ff;
    static XKE_INLINE_CONSTEXPR uint32_t Cyan    = 0x00ffffff;
    static XKE_INLINE_CONSTEXPR uint32_t Magenta = 0xff00ffff;
    static XKE_INLINE_CONSTEXPR uint32_t White   = 0xffffffff;
    static XKE_INLINE_CONSTEXPR uint32_t Orange  = 0xffa500ff;
    static XKE_INLINE_CONSTEXPR uint32_t Pink    = 0xffc0cbff;
    static XKE_INLINE_CONSTEXPR uint32_t Purple  = 0x800080ff;
    static XKE_INLINE_CONSTEXPR uint32_t Brown   = 0xa52a2aff;
    static XKE_INLINE_CONSTEXPR uint32_t Gray    = 0x808080ff;

    XKE_CONSTEXPR explicit __Color() noexcept
        : color_(Black)
    {}

    XKE_CONSTEXPR __Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha=255) noexcept
    {
        setColor(red, green, blue, alpha);
    }

    XKE_CONSTEXPR __Color(uint32_t color) noexcept
        :  color_(color)
    {}

    XKE_CONSTEXPR void setColor(const color_type& color) noexcept
    {
        color_ = color;
    }

    XKE_CONSTEXPR
    void setColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha=255) noexcept
    {
        _Color::_S_setColor(color_, red, green, blue, alpha);
    }

    XKE_INLINE_CONSTEXPR
    void setRed(uint8_t value) noexcept
    {
        _Color::_S_setRed(color_, value);
    }

    XKE_INLINE_CONSTEXPR
    void setGreen(uint8_t value) noexcept
    {
        _Color::_S_setGreen(color_, value);
    }

    XKE_INLINE_CONSTEXPR
    void setBlue(uint8_t value) noexcept
    {
        _Color::_S_setBlue(color_, value);
    }

    XKE_INLINE_CONSTEXPR
    void setAlpha(uint8_t value) noexcept
    {
        _Color::_S_setAlpha(color_, value);
    }

    XKE_INLINE_CONSTEXPR float red() const noexcept
    {
        return _Color::_S_getRed(color_);
    }

    XKE_INLINE_CONSTEXPR float green() const noexcept
    {
        return _Color::_S_getGreen(color_);
    }

    XKE_INLINE_CONSTEXPR float blue() const noexcept
    {
        return _Color::_S_getBlue(color_);
    }

    XKE_INLINE_CONSTEXPR float alpha() const noexcept
    {
        return _Color::_S_getAlpha(color_);
    }

private:
    color_type color_;

};

using ColorRgb = __Color<__color_rgb>;
using ColorRgba = __Color<__color_rgba>;

ostream& operator<<(ostream& os, const ColorRgb& color);
ostream& operator<<(ostream& os, const ColorRgba& color);

XKE_NAMESPACE_END

# endif //XKE_CORE_COLOR_HPP
