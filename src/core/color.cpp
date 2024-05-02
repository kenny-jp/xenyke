# include <xenyke/core/color.hpp>

XKE_NAMESPACE_BEGIN

Color::Color() noexcept
    : r_(0.f), g_(0.f), b_(0.f), a_(1.f)
{
}

Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) noexcept
{
    setColor(red, green, blue, alpha);
}

Color::Color(uint32_t color) noexcept
{
    setColor(color);
}

uint32_t Color::getColor() const noexcept
{
    uint8_t red   = r_ * 255;
    uint8_t green = g_ * 255;
    uint8_t blue  = b_ * 255;
    uint8_t alpha = a_ * 255;

    uint32_t color = (red << 24) |
            (green << 16) |
            (blue << 8) |
            alpha;

    return color;
}

void Color::setColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) noexcept
{
    setRed(red);
    setGreen(green);
    setBlue(blue);
    setAlpha(alpha);
}

void Color::setColor(uint32_t color) noexcept
{
    const uint8_t red   = color >> 24;
    const uint8_t green = color >> 16;
    const uint8_t blue  = color >> 8;
    const uint8_t alpha = color;

    setColor(red, green, blue, alpha);
}

void Color::setRed(uint8_t value) noexcept
{
    r_ = static_cast<float>(value) / 255.f;
}

void Color::setGreen(uint8_t value) noexcept
{
    g_ = static_cast<float>(value) / 255.f;
}

void Color::setBlue(uint8_t value) noexcept
{
    b_ = static_cast<float>(value) / 255.f;
}

void Color::setAlpha(uint8_t value) noexcept
{
    a_ = static_cast<float>(value) / 255.f;
}

float Color::red() const noexcept
{
    return r_;
}

float Color::green() const noexcept
{
    return g_;
}

float Color::blue() const noexcept
{
    return b_;
}

float Color::alpha() const noexcept
{
    return a_;
}

XKE_NAMESPACE_END
