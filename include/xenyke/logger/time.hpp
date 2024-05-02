# ifndef XKE_LOGGER_TIME_HPP
# define XKE_LOGGER_TIME_HPP

# include <xenyke/core/config.hpp>

XKE_NAMESPACE_BEGIN

namespace logger {

enum class TimeFormat
{
    hhmmss,
    hhmm,
    hh,
    mmss,
    mm,
    ss,

    null
};

constexpr std::string getCurrentTimeString(TimeFormat tf)
{
    if (tf == TimeFormat::null) {
        return "";
    }
    std::time_t now {std::time(nullptr)};
    std::tm* localTime {std::localtime(&now)};
    char buffer[10];
    switch (tf) {
    case TimeFormat::hhmmss:
        std::strftime(buffer, 80, "%H:%M:%S ", localTime);
        break;
    case TimeFormat::hhmm:
        std::strftime(buffer, 80, "%H:%M ", localTime);
        break;
    case TimeFormat::hh:
        std::strftime(buffer, 80, "%H ", localTime);
        break;
    case TimeFormat::mmss:
        std::strftime(buffer, 80, "%M:%S ", localTime);
        break;
    case TimeFormat::mm:
        std::strftime(buffer, 80, "%M ", localTime);
        break;
    case TimeFormat::ss:
        std::strftime(buffer, 80, "%S ", localTime);
        break;
    case TimeFormat::null:
        break;
    }
    return buffer;
}

} // namespace logger

XKE_NAMESPACE_END

# endif //XKE_LOGGER_TIME_HPP
