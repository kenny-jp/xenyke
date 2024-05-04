# ifndef XKE_GL_VERTEX_ARRAY_HPP
# define XKE_GL_VERTEX_ARRAY_HPP

# include <xenyke/gl/primitive.hpp>
# include <xenyke/gl/vertex.hpp>
# include <vector>

XKE_NAMESPACE_BEGIN

class VertexArray
{
public:
    explicit VertexArray();
    VertexArray(size_t count, Primitive primitiveType);
    VertexArray(Primitive primitiveType);
    ~VertexArray() noexcept;

    void setPrimitive(Primitive primitive);
    Primitive getPrimitive() const;

    const Vertex *data() const;
    size_t size() const;

    void addVertex(const Vertex& vertex);

    void setVertex(size_t index, const Vertex& vertex);
    void setVertex(size_t index, const Vec3d& position, const Color& color, const Vec2d& texCoords);
    void setVertexColor(size_t index, const Color& color);
    void setVertexPosition(size_t index, Vec3d position);
    void setVertexTexCoords(size_t index, Vec2d texCoords);
    void setVertexCount(size_t count);

    Vertex& operator[](size_t index);
    const Vertex& operator[](size_t index) const;

private:
    Primitive primitive_;
    std::vector<Vertex> vertices_;
};

XKE_NAMESPACE_END

# endif //XKE_GL_VERTEX_ARRAY_HPP
