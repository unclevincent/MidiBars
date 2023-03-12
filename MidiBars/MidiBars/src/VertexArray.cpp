#include "VertexArray.h"
#include "Renderer.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &_rendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &_rendererID));
}

void VertexArray::bind() const
{
	GLCall(glBindVertexArray(_rendererID));
}

void VertexArray::unbind() const
{
	GLCall(glBindVertexArray(0));
}

void VertexArray::addBuffer(VertexBuffer const& buffer, VertexBufferLayout const& layout)
{
	bind();
	buffer.bind();
	const auto& elements = layout.getElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); ++i) {
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset)); // this links vertexArrayObject to currently bound buffer, layout of vertex buffer
		offset += element.count * VertexBufferElement::getSizeOfType(element.type);
	}

}
