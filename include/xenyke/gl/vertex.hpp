# ifndef XKE_GL_VERTEX_HPP
# define XKE_GL_VERTEX_HPP

# include <xenyke/core/vec.hpp>
# include <xenyke/core/color.hpp>

XKE_NAMESPACE_BEGIN

struct Vertex
{
    Vec3d position;
    Color color;
    Vec2d texCoords;
};


XKE_NAMESPACE_END

# endif //XKE_GL_VERTEX_HPP
