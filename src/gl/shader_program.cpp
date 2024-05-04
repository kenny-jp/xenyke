# include <xenyke/gl/ext/glm/gtc/type_ptr.hpp>
# include <xenyke/gl/shader_program.hpp>
# include <xenyke/logger/debug.hpp>
# include <fstream>

XKE_NAMESPACE_BEGIN

ShaderProgram::ShaderProgram(const Shader &vertexShader, const Shader &fragmentShader)
{
    id_ = glCreateProgram();
    glAttachShader(id_, vertexShader.getID());
    glAttachShader(id_, fragmentShader.getID());
    link();
}

ShaderProgram::ShaderProgram(const std::string &filename)
{

    auto[vshader, fshader] = getShaders(filename);

    id_ = glCreateProgram();
    glAttachShader(id_, vshader.getID());
    glAttachShader(id_, fshader.getID());
    link();

    vshader.destroy();
    fshader.destroy();
}

void ShaderProgram::destroy()
{
    glDeleteProgram(id_);
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
    glUniformMatrix4fv(glad_glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

ProgramID ShaderProgram::operator()() const
{
    return id_;
}

void ShaderProgram::stopUse()
{
    glUseProgram(0);
}

void ShaderProgram::link()
{
    glLinkProgram(id_);
    int success;
    char log[512];
    glGetProgramiv(id_, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id_, 512, nullptr, log);
        xkeDebug(log);
    }
}

XKE_NODISCARD std::tuple<Shader, Shader> ShaderProgram::getShaders(std::string_view filename) const
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

    Shader vshader(vertexShaderSource, ShaderType::Vertex);
    Shader fshader(fragmentShaderSource, ShaderType::Fragment);

    return {std::move(vshader), std::move(fshader)};
}

XKE_NAMESPACE_END
