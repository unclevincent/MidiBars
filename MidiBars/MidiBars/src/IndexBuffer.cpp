#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int elementCount) :
    _elementCount(elementCount)
{
    GLCall(glGenBuffers(1, &_rendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementCount * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &_rendererID));
}

void IndexBuffer::bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererID));
}

void IndexBuffer::unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
