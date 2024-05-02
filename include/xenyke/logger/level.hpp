# ifndef XKE_LOGGER_LEVEL_HPP
# define XKE_LOGGER_LEVEL_HPP

# include <xenyke/core/config.hpp>

XKE_NAMESPACE_BEGIN

namespace logger {

enum class Level : enum_t
{
    Debug,
    Error,
    FatalError,
    Info,
    Warning,

    __level_count,
    null
};

XKE_CONSTEXPR std::string_view levelToString(Level level) noexcept
{
    switch (level) {
    case Level::Debug:
        return "[DEBUG] ";
    case Level::Error:
        return "[ERROR] ";
    case Level::FatalError:
        return "[FATAL ERROR] ";
    case Level::Info:
        return "[INFO] ";
    case Level::Warning:
        return "[WARNING] ";
    default:
        return "";
    }
}

} // namespace logger

XKE_NAMESPACE_END

# endif //XKE_LOGGER_LEVEL_HPP
