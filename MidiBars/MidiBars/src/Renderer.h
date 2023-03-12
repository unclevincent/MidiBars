#pragma once

#include <GL/glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GlLogCall(#x, __FILE__, __LINE__))

void GLClearError();


bool GlLogCall(const char* function, const char* file, int line);

class Renderer {
public:
    void draw(VertexArray const& vertexArray, IndexBuffer const& indexBuffer, Shader const& shader) const;
    void clear() const;
};