# ifndef XKE_GL_SHADER_PROGRAM_HPP
# define XKE_GL_SHADER_PROGRAM_HPP

# include <xenyke/gl/shader.hpp>


XKE_NAMESPACE_BEGIN

using ProgramID = uint32_t;

class ShaderProgram : public GlObject
{
public:
    explicit ShaderProgram() noexcept;
    ShaderProgram(const std::string& filename);

    ~ShaderProgram() noexcept = default;

    void use();
    static void unuse();

    void destroy() noexcept override;

    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int32_t value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, const glm::mat4& mat);

    ProgramID operator()() const;

private:
    void create(const std::string &filename);
    void link();

    ProgramID id_;
};

XKE_NAMESPACE_END

# endif //XKE_GL_SHADER_PROGRAM_HPP
