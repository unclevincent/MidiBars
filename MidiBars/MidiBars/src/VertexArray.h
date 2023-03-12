#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray {
public:
	VertexArray();
	~VertexArray();

	void bind() const;
	void unbind() const;

	void addBuffer(VertexBuffer const& buffer, VertexBufferLayout const& layout);
private:
	unsigned int _rendererID;
};