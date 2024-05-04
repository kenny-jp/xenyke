# include <xenyke/gl/vertex_array.hpp>

XKE_NAMESPACE_BEGIN

VertexArray::VertexArray() :
    primitive_(Primitive::TRIANGLES)
{
}

VertexArray::VertexArray(size_t count, Primitive primitiveType) :
    primitive_(primitiveType)
{
    vertices_.resize(count);
}

VertexArray::VertexArray(Primitive primitiveType) :
    primitive_(primitiveType)
{

}

VertexArray::~VertexArray() noexcept
{

}

void VertexArray::setPrimitive(Primitive primitive)
{
    primitive_ = primitive;
}

Primitive VertexArray::getPrimitive() const
{
    return primitive_;
}

const Vertex *VertexArray::data() const
{
    return vertices_.data();
}

size_t VertexArray::size() const
{
    return vertices_.size();
}

void VertexArray::addVertex(const Vertex &vertex)
{
    vertices_.push_back(vertex);
}

void VertexArray::setVertex(size_t index, const Vertex &vertex)
{
    vertices_[index] = vertex;
}

void VertexArray::setVertex(size_t index, const Vec3d &position, const Color &color, const Vec2d &texCoords)
{
    setVertexPosition(index, position);
    setVertexColor(index, color);
    setVertexTexCoords(index, texCoords);
}

void VertexArray::setVertexColor(size_t index, const Color &color)
{
    vertices_[index].color = color;
}

void VertexArray::setVertexPosition(size_t index, Vec3d position)
{
    vertices_[index].position = position;
}

void VertexArray::setVertexTexCoords(size_t index, Vec2d texCoords)
{
    vertices_[index].texCoords = texCoords;
}

void VertexArray::setVertexCount(size_t count)
{
    vertices_.resize(count);
}

Vertex &VertexArray::operator[](size_t index)
{
    __xke_assert(index < vertices_.size());
    return vertices_[index];
}

const Vertex& VertexArray::operator[](size_t index) const
{
    __xke_assert(index < vertices_.size());
    return vertices_[index];
}

XKE_NAMESPACE_END
