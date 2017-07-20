#pragma once
#include "../Utilities/utilities.h"
#include "Shaders.h"
#include "define.h"

class Texture
{
	Shaders myShaders;
public:
	int ID;
	char* img;
	int width;
	int height;
	int bpp;
	GLuint texId;
	void LoadToGPU(const char * FileName, MyEnum type, GLenum clampMode);
	void Bind();
	Texture();
	~Texture();
};