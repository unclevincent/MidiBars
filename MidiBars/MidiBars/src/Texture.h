#pragma once

#include "Renderer.h"

class Texture {

public:
	Texture(std::string const& filepath);
	~Texture();

	void bind(unsigned int slot = 0);
	void unbind();

	int getWidth() const { return _width; }
	int getHeight() const { return _height; }

private:
	unsigned int _rendererID;
	std::string _filePath;
	unsigned char* _localBuffer;
	int _width;
	int _height;
	int _bpp;
};