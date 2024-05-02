# ifndef XKE_LOGGER_CONSOLE_CONSOLE_ESC_CODE_HPP
# define XKE_LOGGER_CONSOLE_CONSOLE_ESC_CODE_HPP

# include <xenyke/core/config.hpp>

XKE_NAMESPACE_BEGIN

namespace logger::console::esc_code {

namespace style {
static XKE_INLINE_CONSTEXPR const std::string_view Bold      = "\033[1m";
static XKE_INLINE_CONSTEXPR const std::string_view Underline = "\033[4m";
static XKE_INLINE_CONSTEXPR const std::string_view Reset     = "\033[0m";
} // namespace style

namespace color {
static XKE_INLINE_CONSTEXPR const std::string_view Black     = "\033[38;2;0;0;0m";
static XKE_INLINE_CONSTEXPR const std::string_view Red       = "\033[38;2;255;0;0m";
static XKE_INLINE_CONSTEXPR const std::string_view Green     = "\033[38;2;0;255;0m";
static XKE_INLINE_CONSTEXPR const std::string_view Blue      = "\033[38;2;0;0;255m";
static XKE_INLINE_CONSTEXPR const std::string_view Yellow    = "\033[38;2;255;255;0m";
static XKE_INLINE_CONSTEXPR const std::string_view Cyan      = "\033[38;2;0;255;255m";
static XKE_INLINE_CONSTEXPR const std::string_view Magenta   = "\033[38;2;255;0;255m";
static XKE_INLINE_CONSTEXPR const std::string_view White     = "\033[38;2;255;255;255m";
static XKE_INLINE_CONSTEXPR const std::string_view Reset     = style::Reset;

} // namespace color

} // namespace logger::console::esc_code

XKE_NAMESPACE_END

# endif //XKE_LOGGER_CONSOLE_CONSOLE_ESC_CODE_HPP
