# ifndef XKE_GL_FWD_HPP
# define XKE_GL_FWD_HPP

# include <xenyke/core/config.hpp>
# include <xenyke/core/color.hpp>
# include <xenyke/core/rect.hpp>
# include <xenyke/core/vec.hpp>

# include <xenyke/gl/config.hpp>
# include <xenyke/gl/ext/gl.h>
# include <xenyke/gl/ext/glm/fwd.hpp>

XKE_NAMESPACE_BEGIN

enum class Primitive : enum_t {
    TRIANGLES = GL_TRIANGLES,
    LINES = GL_LINES
};

using GlObjectID = idnumber_t;

enum class ShaderType : enum_t {
    FRAGMENT = GL_FRAGMENT_SHADER,
    VERTEX = GL_VERTEX_SHADER,
    NONE = GL_NONE
};

enum class BufferUsage : enum_t {
    STATIC = GL_STATIC_DRAW,
    DYNAMIC = GL_DYNAMIC_DRAW,
    STREAM = GL_STREAM_DRAW
};

using Color = ColorRgba;

class VideoMode;

XKE_NAMESPACE_END

# endif //XKE_GL_FWD_HPP
