# ifndef XKE_CORE_DEBUG_HPP
# define XKE_CORE_DEBUG_HPP

# include <xenyke/core/ostream.hpp>

XKE_NAMESPACE_BEGIN

class __xke_debug
{
public:
    ostream& operator()();

    template<class... Args>
    ostream& operator()(std::format_string<Args...> fmt, Args&&... args)
    {
        const std::string str = std::format(fmt, std::forward<Args>(args)...);
        os_ << str.c_str();
        return os_;
    }

private:
    ostream os_;
};

__xke_debug& __xke_get_static_debug_t();

XKE_NAMESPACE_END

xke::ostream& xkeDebug();
xke::ostream& xkeDebug(const char* str);

template<class... Args>
xke::ostream& xkeDebug(std::format_string<Args...> fmt, Args&&... args)
{
    return xke::__xke_get_static_debug_t()(fmt, std::forward<Args>(args)...);
}


# endif //XKE_CORE_DEBUG_HPP
