# ifndef XKE_GL_GL_OBJECT_HPP
# define XKE_GL_GL_OBJECT_HPP

# include <xenyke/gl/fwd.hpp>

XKE_NAMESPACE_BEGIN

class GlObject
{
public:
    GlObject() = default;
    virtual ~GlObject() = default;

    virtual void destroy() noexcept = 0;
};

XKE_NAMESPACE_END

# endif //XKE_GL_GL_OBJECT_HPP
