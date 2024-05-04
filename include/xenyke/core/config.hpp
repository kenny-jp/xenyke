# ifndef XKE_CORE_CONFIG_HPP
# define XKE_CORE_CONFIG_HPP

# if defined(__linux__)
#  include <unistd.h>
#  define __xke_write(OUTPUT, STR, STRLEN) ::write(OUTPUT, STR, STRLEN)
#  define __xke_write_console(STR, STRLEN) \
     ::write(STDOUT_FILENO, STR, STRLEN)
#  define __xke_write_console_error(STR, STRLEN) \
     ::write(STDERR_FILENO, STR, STRLEN)
#  define XKE_OS_UNIX
# else
#  error "Operating system not supported"
# endif
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

# include <exception>
# include <format>
# include <memory>

XKE_NAMESPACE_BEGIN

template<class T_> using uptr_t = std::unique_ptr<T_>;
template<class T_> using sptr_t = std::shared_ptr<T_>;

using handle_t = void*;
template<class T_>
T_ handle_cast(handle_t handle) {
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

class Exception : public std::exception
{
public:
    explicit Exception(const std::string& msg)
        : msg_("XKEException:: " + msg) {}

    template<class... Args>
    explicit Exception(std::format_string<Args...> msg, Args&&... args)
        : msg_("XKEException:: " + std::format(msg, std::forward<Args>(args)...)) {}

    virtual const char* what() const noexcept override {
        return msg_.c_str();
    }

private:
    std::string msg_;

};

XKE_NAMESPACE_END

# ifdef XKE_DEBUG
#  include <cassert>
#  define __xke_assert(EXPR, ...) assert(EXPR __VA_OPT__(&&) __VA_ARGS__)
# else
#  define __xke_assert(EXPR, ...)
# endif
# define __xke_throw(STR) throw Exception(STR)
# define __xke_throw_fmt(STR, ...) throw Exception(STR, __VA_ARGS__)

# define GLSL_VERSION 400
# define GLSL_VERSION_AS_STRING(x) #x
# define GLSL_SHADER_TYPE(x) #x
# define GLSL_SHADER_HEADER(version, type) "#version " GLSL_VERSION_AS_STRING(version) " core //" GLSL_SHADER_TYPE(type)
# define GLSL_VERT_SHADER_HEADER GLSL_SHADER_HEADER(GLSL_VERSION, vertex)
# define GLSL_FRAG_SHADER_HEADER GLSL_SHADER_HEADER(GLSL_VERSION, fragment)

# define GLFW_INCLUDE_NONE
# define STB_IMAGE_IMPLEMENTATION // for stb_image.h

# endif // XKE_CORE_CONFIG_HPP
