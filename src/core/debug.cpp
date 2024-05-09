# include <xenyke/core/debug.hpp>

XKE_NAMESPACE_BEGIN

ostream& __xke_debug::operator()()
{
    return os_;
}

__xke_debug& __xke_get_static_debug_t()
{
    static __xke_debug debug;
    return debug;
}

XKE_NAMESPACE_END

xke::ostream& xkeDebug()
{
    return xke::__xke_get_static_debug_t()();
}

xke::ostream& xkeDebug(const char* str)
{
    return xke::__xke_get_static_debug_t()() << str;
}
