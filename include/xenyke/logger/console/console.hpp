# ifndef XKE_LOGGER_CONSOLE_CONSOLE_HPP
# define XKE_LOGGER_CONSOLE_CONSOLE_HPP

# include <xenyke/logger/level.hpp>
# include <xenyke/logger/time.hpp>
# include <xenyke/logger/console/console_line_style.hpp>
# include <xenyke/logger/console/console_esc_code.hpp>

# ifdef XKE_DEBUG
#  define xkeDebug(...) xke::logger::console::console_default_t::debug(__VA_ARGS__)
# else
#  define xkeDebug(...)
# endif

# include <vector>

XKE_NAMESPACE_BEGIN

namespace logger::console {

using console_msg_buffer_t = std::vector<char>;

template<TimeFormat Tf_>
class console_t;

using console_default_t = console_t<TimeFormat::hhmmss>;
using console_notime_t = console_t<TimeFormat::null>;


template<TimeFormat Tf_>
class console_t
{
public:
    template<class... Args>
    static void debug(std::format_string<Args...> msg, Args&&... args) {
        write<Level::Debug>(std::format(msg, std::forward<Args>(args)...));
    }

    static void debug(const std::string& msg) {
        write<Level::Debug>(msg);
    }

    template<class... Args>
    static void error(std::format_string<Args...> msg, Args&&... args) {
        write<Level::Error>(std::format(msg, std::forward<Args>(args)...));
    }

    static void error(const std::string& msg) {
        write<Level::Error>(msg);
    }

    template<class... Args>
    static void fatalError(std::format_string<Args...> msg, Args&&... args) {
        write<Level::FatalError>(std::format(msg, std::forward<Args>(args)...));
    }

    static void fatalError(const std::string& msg) {
        write<Level::FatalError>(msg);
    }

    template<class... Args>
    static void info(std::format_string<Args...> msg, Args&&... args) {
        write<Level::Info>(std::format(msg, std::forward<Args>(args)...));
    }

    static void info(const std::string& msg) {
        write<Level::Info>(msg);
    }

    template<class... Args>
    static void warning(std::format_string<Args...> msg, Args&&... args) {
        write<Level::Warning>(std::format(msg, std::forward<Args>(args)...));
    }

    static void warning(const std::string& msg) {
        write<Level::Warning>(msg);
    }

private:
    template<Level Level_>
    static void write(const std::string& msg)
    {
        const std::string timestr = getCurrentTimeString(Tf_);
        const std::string_view levelstr = levelToString(Level_);

        const size_t bufferSize = calculateBufferSize<Level_>(timestr, levelstr, msg);
        console_msg_buffer_t buffer(bufferSize, '.');

        writeBuffer<Level_>(buffer, timestr, levelstr, msg);
        __xke_write_console(buffer.data(), buffer.size());
    }

    template<Level Level_, class... Args>
    static XKE_CONSTEXPR size_t calculateBufferSize(const Args&... args)
    {
        size_t bufferSize = (args.size() + ...);

        bufferSize += (internals::LevelToLine<Level_>::value::color != esc_code::color::Default ||
                               internals::LevelToLine<Level_>::value::color != esc_code::color::Default ?
                           std::size(esc_code::style::Default) : 0)
                      + (internals::LevelToLine<Level_>::value::color != esc_code::color::Default ? std::size(internals::LevelToLine<Level_>::value::color) : 0)
                      + (internals::LevelToLine<Level_>::value::style != esc_code::style::Default ? std::size(internals::LevelToLine<Level_>::value::style) : 0);

        return bufferSize + 1;
    }

    template<Level Level_, class... Args>
    static void writeBuffer(console_msg_buffer_t& buffer, Args&&... args)
    {
        std::vector<char>::iterator it = buffer.begin();

        if (internals::LevelToLine<Level_>::value::color != esc_code::color::Default) {
            it = std::copy(internals::LevelToLine<Level_>::value::color.begin(),
                           internals::LevelToLine<Level_>::value::color.end(), it);
        }

        if (internals::LevelToLine<Level_>::value::style != esc_code::style::Default) {
            it = std::copy(internals::LevelToLine<Level_>::value::style.begin(),
                           internals::LevelToLine<Level_>::value::style.end(), it);
        }

        ((it = std::copy(args.begin(), args.end(), it)), ...);

        if (internals::LevelToLine<Level_>::value::color != esc_code::color::Default) {
            it = std::copy(esc_code::style::Default.begin(), esc_code::style::Default.end(), it);
        }

        ++(*it) = '\n';
    }

};

} // namespace logger::console

XKE_NAMESPACE_END

# endif //XKE_LOGGER_CONSOLE_CONSOLE_HPP
