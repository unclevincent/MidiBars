#pragma once

#include "VertexBuffer.h"

class VertexBufferLayout;

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