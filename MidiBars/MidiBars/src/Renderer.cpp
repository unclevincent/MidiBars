#include "Renderer.h"
#include <iostream>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GlLogCall(const char* function, const char* file, int line) 
{
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

void Renderer::draw(VertexArray const& vertexArray, IndexBuffer const& indexBuffer, Shader const& shader) const
{
    shader.bind();

    vertexArray.bind();
    indexBuffer.bind();

    GLCall(glDrawElements(GL_TRIANGLES, indexBuffer.getElementCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}
