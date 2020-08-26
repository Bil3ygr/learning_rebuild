#pragma once

#include "main.h"

struct ImageData
{
	int width, height;
	unsigned char *data;
	GLenum colorType;

	ImageData(int _width, int _height, unsigned char *_data, GLenum _colorType)
	{
		width = _width;
		height = _height;
		data = _data;
		colorType = _colorType;
	}

	GLint getWrapS()
	{
		if (colorType == GL_RGBA)
			return GL_CLAMP_TO_EDGE;
		else
			return GL_REPEAT;
	}

	GLint getWrapT()
	{
		if (colorType == GL_RGBA)
			return GL_CLAMP_TO_EDGE;
		else
			return GL_REPEAT;
	}

	GLint getMinFilter()
	{
		return GL_LINEAR;
	}

	GLint getMaxFilter()
	{
		return GL_LINEAR;
	}
};

unsigned int create2DTextureFromData(ImageData data, bool useMipmap = false, float *borderColor = new float[4]{1.0f, 1.0f, 1.0f, 1.0f});
unsigned int create2DTextureFromFile(const char *filepath, const std::string &directory = "");
