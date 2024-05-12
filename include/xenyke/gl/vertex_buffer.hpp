# ifndef XKE_GL_VERTEX_BUFFER_HPP
# define XKE_GL_VERTEX_BUFFER_HPP

# include <xenyke/gl/vertex_array.hpp>

XKE_NAMESPACE_BEGIN

template<BufferUsage U_, Primitive Pri_>
class VertexBuffer
{
public:
    explicit VertexBuffer();
    virtual ~VertexBuffer();

    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;
    VertexBuffer(VertexBuffer&&) = default;
    VertexBuffer& operator=(VertexBuffer&&) = default;

    void destroy();
    virtual void draw() const;

    void write(const VertexArray& array);

// protected:
    void bind() const;
    void unbind() const;

private:
    GlObjectID arrayID_;
    GlObjectID bufferID_;
    size_t size_;
};

template<BufferUsage U_, Primitive Pri_, size_t I_>
class EVertexBuffer : public VertexBuffer<U_, Pri_>
{
public:
    explicit EVertexBuffer();
    virtual ~EVertexBuffer();

    void destroy();
    virtual void draw() const override;

    void setIndex(size_t index, uint32_t value);
    void setIndexes(std::initializer_list<uint32_t> l);
    void writeIndexes() const;

// protected:
    void bind() const;
    void unbind() const;

private:
    GlObjectID elementArrayID_;
    std::array<uint32_t, I_> indexes_;

};

XKE_NAMESPACE_END

# include "vertex_buffer.inl"

# endif //XKE_GL_VERTEX_BUFFER_HPP
