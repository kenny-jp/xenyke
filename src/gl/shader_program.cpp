# include <xenyke/core/debug.hpp>
# include <xenyke/gl/shader_program.hpp>
# include <xenyke/gl/ext/glm/gtc/type_ptr.hpp>
# include <fstream>

XKE_NAMESPACE_BEGIN

namespace internals {

XKE_NODISCARD std::tuple<Shader, Shader> getShaders(std::string_view filename)
{
    std::ifstream file;
    std::string   fileContent;

    file.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    try {
        file.open(filename.data());
        fileContent.append((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
    } catch (const std::exception& e) {
        xkeDebug("ShaderProgram: cannot load shader: [{}] : {}", filename, e.what());
    }

    size_t indexVertShad = fileContent.find(GLSL_VERT_SHADER_HEADER);
    size_t indexFragShad = fileContent.find(GLSL_FRAG_SHADER_HEADER);

    __xke_assert(indexVertShad != std::string::npos);
    __xke_assert(indexFragShad != std::string::npos);

    const std::string::iterator beginIterVertShad = fileContent.begin() + indexVertShad;
    const std::string::iterator endIterVertShad   = beginIterVertShad + indexFragShad;
    const std::string::iterator beginIterFragShad = fileContent.begin() + indexFragShad;
    const std::string::iterator endIterFragShad   = std::end(fileContent);

    const std::string vertexShaderSource(beginIterVertShad, endIterVertShad);
    const std::string fragmentShaderSource(beginIterFragShad, endIterFragShad);

    Shader vshader(vertexShaderSource, ShaderType::VERTEX);
    Shader fshader(fragmentShaderSource, ShaderType::FRAGMENT);

    return {std::move(vshader), std::move(fshader)};
}

} // namespace internals

ShaderProgram::ShaderProgram() noexcept
    : id_(INVALID_ID)
{

}

ShaderProgram::ShaderProgram(const std::string &filename)
    : id_(INVALID_ID)
{
    create(filename);
}

void ShaderProgram::destroy() noexcept
{
    glDeleteProgram(id_);
    id_ = INVALID_ID;
}

void ShaderProgram::use()
{
    glUseProgram(id_);
}

void ShaderProgram::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(id_, name.c_str()), static_cast<int32_t>(value));
}

void ShaderProgram::setInt(const std::string &name, int32_t value) const
{
    glUniform1i(glGetUniformLocation(id_, name.c_str()), value);
}

void ShaderProgram::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(id_, name.c_str()), value);
}

void ShaderProgram::setMat4(const std::string &name, const glm::mat4 &mat)
{
    glUniformMatrix4fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

ProgramID ShaderProgram::operator()() const
{
    return id_;
}

void ShaderProgram::unuse()
{
    glUseProgram(0);
}

void ShaderProgram::create(const std::string& filename)
{
    auto[vshader, fshader] = internals::getShaders(filename);

    id_ = glCreateProgram();
    glAttachShader(id_, vshader.id_);
    glAttachShader(id_, fshader.id_);
    link();

    vshader.destroy();
    fshader.destroy();
}

void ShaderProgram::link()
{
    glLinkProgram(id_);
    int success;
    char log[512];
    glGetProgramiv(id_, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id_, 512, nullptr, log);
        xkeDebug() << "ShaderProgram::link(): "
                   << log
                   << '\n';
    }
}

XKE_NAMESPACE_END
