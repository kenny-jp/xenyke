XKE_NAMESPACE_BEGIN

/*
*********************
 vertexBuffer Impl
*********************
*/

template<BufferUsage U_, Primitive P_>
VertexBuffer<U_, P_>::VertexBuffer() :
    size_(0)
{
    glGenVertexArrays(1, &arrayID_);
    glGenBuffers(1, &bufferID_);

    __xke_assert(arrayID_ != 0);
    __xke_assert(bufferID_ != 0);
}

template<BufferUsage U_, Primitive P_>
VertexBuffer<U_, P_>::~VertexBuffer()
{

}

template<BufferUsage U_, Primitive P_>
void VertexBuffer<U_, P_>::write(const VertexArray &array)
{
    bind();

    glBufferData(GL_ARRAY_BUFFER,
                 array.size() * sizeof(Vertex),
                 array.data(),
                 static_cast<enum_t>(U_));

    glVertexAttribPointer(0, 3,
                          GL_DOUBLE, GL_FALSE,
                          sizeof(Vertex),
                          (void*)0);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4,
                          GL_UNSIGNED_BYTE, GL_TRUE,
                          sizeof(Vertex),
                          (void*)offsetof(Vertex, color));

    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2,
                          GL_DOUBLE, GL_FALSE,
                          sizeof(Vertex),
                          (void*)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(2);

    size_ = array.size();

    unbind();
}

template<BufferUsage U_, Primitive P_>
void VertexBuffer<U_, P_>::destroy()
{
    glDeleteBuffers(1, &bufferID_);
    glDeleteVertexArrays(1, &arrayID_);
}

template<BufferUsage U_, Primitive P_>
void VertexBuffer<U_, P_>::draw() const
{
    bind();
    glDrawArrays(static_cast<enum_t>(P_), 0, size_);
    unbind();
}

template<BufferUsage U_, Primitive P_>
void VertexBuffer<U_, P_>::bind() const
{
    __xke_assert(arrayID_ != 0);
    __xke_assert(bufferID_ != 0);

    glBindVertexArray(arrayID_); // First

    glBindBuffer(GL_ARRAY_BUFFER, bufferID_);
}

template<BufferUsage U_, Primitive P_>
void VertexBuffer<U_, P_>::unbind() const
{
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/*
*********************
 EvertexBuffer Impl
*********************
*/

template<BufferUsage U_, Primitive Pri_, size_t I_>
EVertexBuffer<U_, Pri_, I_>::EVertexBuffer() :
    VertexBuffer<U_, Pri_>()
{
    glGenBuffers(1, &elementArrayID_);
    for (size_t i {0}; i < I_; ++i)
        indexes_[i] = i;

    __xke_assert(elementArrayID_ != 0);
}

template<BufferUsage U_, Primitive Pri_, size_t I_>
EVertexBuffer<U_, Pri_, I_>::~EVertexBuffer()
{

}

template<BufferUsage U_, Primitive Pri_, size_t I_>
void EVertexBuffer<U_, Pri_, I_>::destroy()
{
    glDeleteBuffers(1, &elementArrayID_);
    VertexBuffer<U_, Pri_>::destroy();
}

template<BufferUsage U_, Primitive Pri_, size_t I_>
void EVertexBuffer<U_, Pri_, I_>::draw() const
{
    bind();
    glDrawElements(static_cast<enum_t>(Pri_), indexes_.size(), GL_UNSIGNED_INT, 0);
    unbind();
}

template<BufferUsage U_, Primitive Pri_, size_t I_>
void EVertexBuffer<U_, Pri_, I_>::bind() const
{
    VertexBuffer<U_, Pri_>::bind();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementArrayID_);
}

template<BufferUsage U_, Primitive Pri_, size_t I_>
void EVertexBuffer<U_, Pri_, I_>::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    VertexBuffer<U_, Pri_>::unbind();
}

template<BufferUsage U_, Primitive Pri_, size_t I_>
void EVertexBuffer<U_, Pri_, I_>::setIndex(size_t index, uint32_t value)
{
    __xke_assert(index < I_);
    indexes_[index] = value;
}

template<BufferUsage U_, Primitive Pri_, size_t I_>
void EVertexBuffer<U_, Pri_, I_>::setIndexes(std::initializer_list<uint32_t> l)
{
    __xke_assert(l.size() <= I_);
    std::copy(l.begin(), l.end(), indexes_.begin());
}

template<BufferUsage U_, Primitive Pri_, size_t I_>
void EVertexBuffer<U_, Pri_, I_>::writeIndexes() const
{
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes_.size() * sizeof(uint32_t), indexes_.data(), static_cast<enum_t>(U_));
    unbind();
}

XKE_NAMESPACE_END
