# include <xenyke/gl/shader.hpp>
# include <xenyke/core/debug.hpp>

XKE_NAMESPACE_BEGIN

Shader::Shader(const std::string& source, ShaderType type)
    : id_(0)
{
    const char* s = source.c_str();
    id_ = glCreateShader(static_cast<enum_t>(type));
    glShaderSource(id_, 1, &s, nullptr);
    compile();
}

Shader::~Shader() noexcept
{
}

void Shader::destroy() noexcept
{
    glDeleteShader(id_);
}

ShaderID Shader::getID() const noexcept
{
    return id_;
}

void Shader::compile()
{
    glCompileShader(id_);
    int success;
    char log[512];
    glGetShaderiv(id_, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(id_, 512, nullptr, log);
        xkeDebug(log);
    }
}

XKE_NAMESPACE_END
