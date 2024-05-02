# ifndef XKE_LOGGER_CONSOLE_CONSOLE_LINE_HPP
# define XKE_LOGGER_CONSOLE_CONSOLE_LINE_HPP

# include <xenyke/logger/console/console_char_enum.hpp>

XKE_NAMESPACE_BEGIN

namespace logger::console {

template<CharColor ChColor_, CharStyle ChStyle_>
struct console_line_t
{
    constexpr static CharColor color = ChColor_;
    constexpr static CharStyle style = ChStyle_;
};

using console_line_no_color_t = console_line_t<CharColor::Default, CharStyle::Default>;

using console_line_default_debug_t      = console_line_t<CharColor::Blue, CharStyle::Default>;
using console_line_default_error_t      = console_line_t<CharColor::Red, CharStyle::Default>;
using console_line_default_fatalError_t = console_line_t<CharColor::Red, CharStyle::Bold>;
using console_line_default_info_t       = console_line_t<CharColor::Green, CharStyle::Default>;
using console_line_default_warning_t    = console_line_t<CharColor::Yellow, CharStyle::Bold>;

} // namespace logger::console

XKE_NAMESPACE_END

# endif //XKE_LOGGER_CONSOLE_CONSOLE_LINE_HPP
