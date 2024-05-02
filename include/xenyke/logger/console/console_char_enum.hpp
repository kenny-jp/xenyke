# ifndef XKE_LOGGER_CONSOLE_CONSOLE_CHAR_ENUM_HPP
# define XKE_LOGGER_CONSOLE_CONSOLE_CHAR_ENUM_HPP

# include <xenyke/logger/console/console_esc_code.hpp>

XKE_NAMESPACE_BEGIN

namespace logger::console {

enum class CharColor
{
    Black,
    Red,
    Green,
    Blue,
    Yellow,
    Cyan,
    Magenta,
    White,
    Default
};

enum class CharStyle
{
    Bold,
    Underline,
    Default
};

XKE_CONSTEXPR std::string_view get_char_color(CharColor color)
{
    switch (color) {
    case CharColor::Black:
        return esc_code::color::Black;
    case CharColor::Red:
        return esc_code::color::Red;
    case CharColor::Green:
        return esc_code::color::Green;
    case CharColor::Blue:
        return esc_code::color::Blue;
    case CharColor::Yellow:
        return esc_code::color::Yellow;
    case CharColor::Cyan:
        return esc_code::color::Cyan;
    case CharColor::Magenta:
        return esc_code::color::Magenta;
    case CharColor::White:
        return esc_code::color::White;
    case CharColor::Default:
        return esc_code::color::Reset;
    default:
        return "";
    }
}

XKE_CONSTEXPR std::string_view get_char_style(CharStyle style)
{
    switch (style) {
    case CharStyle::Bold:
        return esc_code::style::Bold;
    case CharStyle::Underline:
        return esc_code::style::Underline;
    case CharStyle::Default:
        return esc_code::style::Reset;
    default:
        return "";
    }
}

} // namespace logger::console

XKE_NAMESPACE_END

# endif //XKE_LOGGER_CONSOLE_CONSOLE_CHAR_ENUM_HPP
