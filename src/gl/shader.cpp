# include <xenyke/gl/shader.hpp>
# include <xenyke/core/debug.hpp>

XKE_NAMESPACE_BEGIN

Shader::Shader() noexcept
    : id_(INVALID_ID), type_(ShaderType::NONE)
{

}

Shader::Shader(const std::string &source, ShaderType type)
{
    set(source, type);
}

Shader::~Shader() noexcept
{

}

bool Shader::set(const std::string& source, ShaderType type)
{
    const char* s = source.c_str();
    type_ = type;
    id_ = glCreateShader(static_cast<enum_t>(type_));
    glShaderSource(id_, 1, &s, nullptr);
    return compile();
}


void Shader::destroy() noexcept
{
    glDeleteShader(id_);
    type_ = ShaderType::NONE;
}

bool Shader::compile()
{
    glCompileShader(id_);
    int success;
    char log[128];
    glGetShaderiv(id_, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(id_, 512, nullptr, log);
        xkeDebug() << "Shader::compile(): \n"
                   << log
                   << '\n';
        return false;
    }
    return true;
}

XKE_NAMESPACE_END
