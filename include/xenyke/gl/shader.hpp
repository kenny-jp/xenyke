# ifndef XKE_GL_SHADER_HPP
# define XKE_GL_SHADER_HPP

# include <xenyke/core/config.hpp>
# include <xenyke/gl/ext/gl.h>

XKE_NAMESPACE_BEGIN

using ShaderID = uint32_t;

enum class ShaderType : enum_t
{
    Fragment = GL_FRAGMENT_SHADER,
    Vertex = GL_VERTEX_SHADER
};

class Shader
{
public:
    explicit Shader(const std::string& source, ShaderType type);
    ~Shader() noexcept;

    ShaderID getID() const noexcept;
    void destroy() noexcept;

private:
    void compile();

    ShaderID id_;
};

XKE_NAMESPACE_END

# endif //XKE_GL_SHADER_HPP
