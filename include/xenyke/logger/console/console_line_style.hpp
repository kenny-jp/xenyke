# ifndef XKE_LOGGER_CONSOLE_CONSOLE_LINE_STYLE_HPP
# define XKE_LOGGER_CONSOLE_CONSOLE_LINE_STYLE_HPP

# include <xenyke/logger/console/console_char_enum.hpp>
# include <xenyke/logger/console/console_esc_code.hpp>
# include <xenyke/logger/level.hpp>

XKE_NAMESPACE_BEGIN

namespace logger::console {

namespace internals {

template<CharColor CC_>
XKE_CONSTEXPR std::string_view get_char_color()
{
    switch (CC_) {
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
        return esc_code::color::Default;
    default:
        return "";
    }
}

template<CharStyle CS_>
XKE_CONSTEXPR std::string_view get_char_style()
{
    switch (CS_) {
    case CharStyle::Bold:
        return esc_code::style::Bold;
    case CharStyle::Underline:
        return esc_code::style::Underline;
    case CharStyle::Default:
        return esc_code::style::Default;
    default:
        return "";
    }
}

template<class T_, T_ Inst_>
struct get_esc_code;

template<CharColor CC_>
struct get_esc_code<CharColor, CC_>
{
    static constexpr std::string_view value = get_char_color<CC_>();
};

template<CharStyle CS_>
struct get_esc_code<CharStyle, CS_>
{
    static constexpr std::string_view value = get_char_style<CS_>();
};

} // namespace internals

template<Level L_, CharColor CC_, CharStyle CS_>
struct console_line_style
{
    static constexpr std::string_view color = internals::get_esc_code<CharColor, CC_>::value;
    static constexpr std::string_view style = internals::get_esc_code<CharStyle, CS_>::value;
};


using console_line_style_no_color_t = console_line_style<Level::null, CharColor::Default, CharStyle::Default>;

using console_line_style_default_debug_t      = console_line_style<Level::Debug,      CharColor::Blue,   CharStyle::Default>;
using console_line_style_default_error_t      = console_line_style<Level::Error,      CharColor::Red,    CharStyle::Default>;
using console_line_style_default_fatalError_t = console_line_style<Level::FatalError, CharColor::Red,    CharStyle::Bold>;
using console_line_style_default_info_t       = console_line_style<Level::Info,       CharColor::Green,  CharStyle::Default>;
using console_line_style_default_warning_t    = console_line_style<Level::Warning,    CharColor::Yellow, CharStyle::Bold>;

namespace internals {

template<Level Level_>
struct LevelToLine;

template<>
struct LevelToLine<Level::Debug> {
    using value = console_line_style_default_debug_t;
};

template<>
struct LevelToLine<Level::Error> {
    using value = console_line_style_default_error_t;
};

template<>
struct LevelToLine<Level::FatalError> {
    using value = console_line_style_default_fatalError_t;
};

template<>
struct LevelToLine<Level::Info> {
    using value = console_line_style_default_info_t;
};

template<>
struct LevelToLine<Level::Warning> {
    using value = console_line_style_default_warning_t;
};

template<>
struct LevelToLine<Level::null> {
    using value = console_line_style_no_color_t;
};

} // namespace internals

} // namespace logger::console

XKE_NAMESPACE_END

# endif //XKE_LOGGER_CONSOLE_CONSOLE_LINE_STYLE_HPP
