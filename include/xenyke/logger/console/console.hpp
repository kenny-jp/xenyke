# ifndef XKE_LOGGER_CONSOLE_CONSOLE_HPP
# define XKE_LOGGER_CONSOLE_CONSOLE_HPP

# include <xenyke/logger/level.hpp>
# include <xenyke/logger/time.hpp>
# include <xenyke/logger/console/console_line.hpp>
# include <xenyke/logger/console/console_esc_code.hpp>

# include <vector>

XKE_NAMESPACE_BEGIN

namespace logger::console {

using console_msg_buffer_t = std::vector<char>;

template<TimeFormat Tf_, class DebugStyle, class ErrorStyle,
        class FatalErrorStyle, class InfoStyle, class WarningStyle>
class console_t;

using console_default_t = console_t<TimeFormat::hhmmss, console_line_no_color_t,
                                console_line_no_color_t, console_line_no_color_t,
                                console_line_no_color_t,console_line_no_color_t>;

using console_color_t = console_t<TimeFormat::hhmmss, console_line_default_debug_t,
                                console_line_default_error_t, console_line_default_fatalError_t,
                                console_line_default_info_t, console_line_default_warning_t>;

template<TimeFormat Tf_, class DebugStyle, class ErrorStyle,
        class FatalErrorStyle, class InfoStyle, class WarningStyle>
class console_t
{
public:
    template<class... Args>
    static void writeConsole(std::format_string<Args...> fmt, Args&&... args)
    {
        std::string msg = std::format(fmt, std::forward<Args>(args)...);
        __xke_write_console(msg.data(), msg.size());
    }

    static void writeConsole(const Level level, std::string_view msg)
    {
        auto timestr = getCurrentTimeString(Tf_);
        auto levelstr = levelToString(level);

        std::string buffer;
        buffer += timestr;
        buffer += levelstr;
        buffer += msg;

        __xke_write_console(buffer.data(), buffer.size());
    }

private:


    template<CharColor ChColor_, CharStyle ChStyle_, class... Args>
    static constexpr size_t calculateBufferSize(const Args&... args)
    {
        size_t bufferSize = (args.size() + ... ) + 2;

        bufferSize += std::size(esc_code::style::Reset)
                      + ((ChColor_ != CharColor::Default ? std::size(get_char_color(ChColor_)) : 0))
                      + ((ChStyle_ != CharStyle::Default ? std::size(get_char_style(ChStyle_)) : 0));

        return bufferSize;
    }

    template<CharColor ChColor_, CharStyle ChStyle_, class... Args>
    static void writeBuffer(console_msg_buffer_t& buffer, Args&&... args)
    {
        auto it = buffer.begin();

        if XKE_CONSTEXPR (ChColor_ != CharColor::Default) {
            XKE_CONSTEXPR auto color = get_char_color(ChColor_);
            it = std::copy(color.begin(), color.end(), it);
        }

        if XKE_CONSTEXPR (ChStyle_ != CharStyle::Default) {
            XKE_CONSTEXPR auto style = get_char_style(ChStyle_);
            it = std::copy(style.begin(), style.end(), it);
        }

        (..., (it = std::copy(args.begin(), args.end(), it)));

        if XKE_CONSTEXPR (ChColor_ != CharColor::Default) {
            it = std::copy(esc_code::style::Reset.begin(), esc_code::style::Reset.end(), it);
        }

        ++(*it) = '\n';
        buffer.back() = '\0';
    }

};

} // namespace logger::console

XKE_NAMESPACE_END

# endif //XKE_LOGGER_CONSOLE_CONSOLE_HPP
