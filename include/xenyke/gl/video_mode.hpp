# ifndef XKE_GL_VIDEO_MODE_HPP
# define XKE_GL_VIDEO_MODE_HPP

# include <xenyke/core/config.hpp>

XKE_NAMESPACE_BEGIN

struct VideoMode
{
    explicit VideoMode() :
        width_(-1), height_(-1),
        redBits_(-1), greenBits_(-1), blueBits_(-1),
        refreshRate_(-1)
    {}

    int32_t width_;
    int32_t height_;
    int8_t redBits_;
    int8_t greenBits_;
    int8_t blueBits_;
    int8_t refreshRate_;
};


XKE_NAMESPACE_END

# endif //XKE_GL_VIDEO_MODE_HPP
