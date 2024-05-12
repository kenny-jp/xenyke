# ifndef XKE_GL_CONFIG_HPP
# define XKE_GL_CONFIG_HPP

# define GLSL_VERSION 400
# define GLSL_VERSION_AS_STRING(x) #x
# define GLSL_SHADER_TYPE(x) #x

# define GLSL_SHADER_HEADER(version, type) \
    "#version " GLSL_VERSION_AS_STRING(version) \
    " core //" GLSL_SHADER_TYPE(type)

# define GLSL_VERT_SHADER_HEADER \
    GLSL_SHADER_HEADER(GLSL_VERSION, vertex)

# define GLSL_FRAG_SHADER_HEADER \
    GLSL_SHADER_HEADER(GLSL_VERSION, fragment)

# define GLFW_INCLUDE_NONE

# define STB_IMAGE_IMPLEMENTATION // for stb_image.h

# endif //XKE_GL_CONFIG_HPP
