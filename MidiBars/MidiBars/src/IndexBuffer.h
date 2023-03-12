#pragma once

class IndexBuffer {
public:
	IndexBuffer(const unsigned int* data, unsigned int elementCount);
	~IndexBuffer();

	void bind() const;
	void unbind() const;

	unsigned int getElementCount() const { return _elementCount; }

private:
	unsigned int _rendererID;
	unsigned int _elementCount;
};