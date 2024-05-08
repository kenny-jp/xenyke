# ifndef XKE_LOGGER_LOGGER_HPP
# define XKE_LOGGER_LOGGER_HPP

# include <xenyke/logger/console/console.hpp>

# ifndef xkeDebug
#  ifdef XKE_DEBUG
#   define xkeDebug(...) xke::logger::console::console_default_t::debug(__VA_ARGS__)
#  else
#   define xkeDebug(...)
#  endif
# endif

# endif //XKE_LOGGER_LOGGER_HPP
