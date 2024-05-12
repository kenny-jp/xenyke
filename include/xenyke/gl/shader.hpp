# ifndef XKE_GL_SHADER_HPP
# define XKE_GL_SHADER_HPP

# include <xenyke/gl/gl_object.hpp>

XKE_NAMESPACE_BEGIN

class Shader : public GlObject
{
public:
    explicit Shader() noexcept;
    Shader(const std::string& source, ShaderType type);
    ~Shader() noexcept;

    bool set(const std::string& source, ShaderType type);

    void destroy() noexcept override;

private:
    bool compile();

    GlObjectID id_;
    ShaderType type_;

    friend class ShaderProgram;
};

XKE_NAMESPACE_END

# endif //XKE_GL_SHADER_HPP
