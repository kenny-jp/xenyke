# ifndef XKE_GL_PRIMITIVE_HPP
# define XKE_GL_PRIMITIVE_HPP

# include <xenyke/core/config.hpp>
# include <xenyke/gl/ext/gl.h>

XKE_NAMESPACE_BEGIN

enum class Primitive : enum_t {
    TRIANGLES = GL_TRIANGLES,
    LINES = GL_LINES
};

XKE_NAMESPACE_END

# endif //XKE_GL_PRIMITIVE_HPP
