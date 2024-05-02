# ifndef XKE_CORE_COLOR_HPP
# define XKE_CORE_COLOR_HPP

# include <xenyke/core/config.hpp>

XKE_NAMESPACE_BEGIN

class Color
{
public:
    enum : uint32_t
    {
        Black   = 0x000000ff,
        Red     = 0xff0000ff,
        Green   = 0x00ff00ff,
        Blue    = 0x0000ffff,
        Yellow  = 0xffff00ff,
        Cyan    = 0x00ffffff,
        Magenta = 0xff00ffff,
        White   = 0xffffffff,
        // Other
        Orange  = 0xffa500ff,
        Pink    = 0xffc0cbff,
        Purple  = 0x800080ff,
        Brown   = 0xa52a2aff,
        Gray    = 0x808080ff,
    };

public:
    explicit Color() noexcept;
    Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha=255) noexcept;
    Color(uint32_t color) noexcept;

    uint32_t getColor() const noexcept;

    void setColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha=255) noexcept;
    void setColor(uint32_t color) noexcept;
    void setRed(uint8_t value) noexcept;
    void setGreen(uint8_t value) noexcept;
    void setBlue(uint8_t value) noexcept;
    void setAlpha(uint8_t value) noexcept;

    float red() const noexcept;
    float green() const noexcept;
    float blue() const noexcept;
    float alpha() const noexcept;

private:
    float r_;
    float g_;
    float b_;
    float a_;

};

XKE_NAMESPACE_END

# endif //XKE_CORE_COLOR_HPP
