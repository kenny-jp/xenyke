# ifndef XKE_GL_TEXTURE_HPP
# define XKE_GL_TEXTURE_HPP

# include <xenyke/core/vec.hpp>

XKE_NAMESPACE_BEGIN

class Texture
{
public:
    explicit Texture() noexcept;
    ~Texture() noexcept;

    void destroy() noexcept;

    void loadFromFile(const std::string& filename);
    void use() const;
    void stopUse() const;
    bool isLoaded() const;

private:
    idnumber_t id_;
    Vec2i size_;
    int32_t nrChannels_;
    bool isLoaded_;

};

XKE_NAMESPACE_END

# endif //XKE_GL_TEXTURE_HPP
