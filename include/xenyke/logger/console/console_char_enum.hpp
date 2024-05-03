# ifndef XKE_LOGGER_CONSOLE_CONSOLE_CHAR_ENUM_HPP
# define XKE_LOGGER_CONSOLE_CONSOLE_CHAR_ENUM_HPP

# include <xenyke/core/config.hpp>

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

} // namespace logger::console

XKE_NAMESPACE_END

# endif //XKE_LOGGER_CONSOLE_CONSOLE_CHAR_ENUM_HPP
