# ifndef XKE_CORE_CONFIG_HPP
# define XKE_CORE_CONFIG_HPP

# ifndef NDEBUG
# define XKE_DEBUG
# endif
# ifndef XKE_VERSION_MAJOR
#  define XKE_VERSION_MAJOR 1
# endif
# ifndef XKE_VERSION_MINOR
#  define XKE_VERSION_MINOR 0
# endif
# ifndef XKE_VERSION_PATCH
#  define XKE_VERSION_PATCH 0
# endif
# define XKE_VERSION \
    ((XKE_VERSION_MAJOR << 16) |\
    (XKE_VERSION_MINOR << 8 )  |\
    (XKE_VERSION_PATCH))

# ifndef XKE_NAMESPACE
#  define XKE_NAMESPACE xke
# endif
# ifdef XKE_NAMESPACE
#  define XKE_NAMESPACE_BEGIN namespace XKE_NAMESPACE {
#  define XKE_NAMESPACE_END }
# else
#  define XKE_NAMESPACE_BEGIN
#  define XKE_NAMESPACE_END
# endif
# define XKE_ALIGN(n)           __attribute__((aligned(n)))
# define XKE_API                __attribute__((visibility("default")))
# define XKE_DEPRECATED(msg)    __attribute__((deprecated(msg)))
# define XKE_FUNC_ATTR(attr)    __attribute__((attr))
# define XKE_PURE_FUNC          __attribute__((pure))
# define XKE_NO_RETURN          __attribute__((noreturn))
# define XKE_CONSTEXPR          constexpr
# define XKE_INLINE             inline
# define XKE_INLINE_CONSTEXPR   XKE_INLINE XKE_CONSTEXPR
# define XKE_NODISCARD [[nodiscard]]
# define XKE_CURRENT_CLASS_NAME __PRETTY_FUNCTION__
# define XKE_PRINTF_FORMAT(fmt_idx, var_args_idx) __attribute__((format(printf, fmt_idx, var_args_idx)))
# define XKE_UNUSED(x) (void)(x)

# if defined(__linux__)
#  include <unistd.h>
#  define __xke_write(OUTPUT, STR, STRLEN) ::write(OUTPUT, STR, STRLEN)
#  define __xke_write_stdout(STR, STRLEN)  ::write(STDOUT_FILENO, STR, STRLEN)
#  define __xke_write_stderr(STR, STRLEN)  ::write(STDERR_FILENO, STR, STRLEN)
#  define XKE_OS_UNIX
# else
#  error "Operating system not supported"
# endif

# ifdef XKE_DEBUG
#  include <cassert>
#  define __xke_assert(EXPR, ...) assert(EXPR __VA_OPT__(&&) __VA_ARGS__)
#  define XKE_DEBUG_STREAMBUF_SIZE 512
# else
#  define __xke_assert(EXPR, ...)
#  define XKE_DEBUG_STREAMBUF_SIZE 0
# endif

# include <memory>

XKE_NAMESPACE_BEGIN

template<class T_> using uptr_t = std::unique_ptr<T_>;
template<class T_> using sptr_t = std::shared_ptr<T_>;
template<class T_> using obs_ptr_t = T_*;

using handle_t = void*;
template<class T_> T_ handle_cast(handle_t handle) {
    return reinterpret_cast<T_>(handle);
}

using int8_t  = /* signed */ char;
using int16_t = /* signed */ short int;
using int32_t = /* signed */ int;
using int64_t = /* signed */ long long int;

using uint8_t  = unsigned char;
using uint16_t = unsigned short int;
using uint32_t = unsigned int;
using uint64_t = unsigned long long int;

using size_t = uint64_t;
using enum_t = uint32_t;
using idnumber_t = uint32_t;
XKE_INLINE_CONSTEXPR idnumber_t INVALID_ID = UINT32_MAX;

class ostream;

XKE_NAMESPACE_END



# endif // XKE_CORE_CONFIG_HPP
