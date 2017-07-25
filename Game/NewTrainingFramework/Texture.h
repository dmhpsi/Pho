#pragma once
#include "../Utilities/utilities.h"
#include "Shaders.h"
#include "define.h"
#include <vector>
using namespace std;

class Texture
{
	Shaders myShaders;
public:
	int ID;
	int numOfFragments;
	char* img;
	int width;
	int height;
	int bpp;
	GLuint *texId;
	void LoadToGPU(const char * FileName, MyEnum type, GLenum clampMode);
	void Bind();
	Texture();
	~Texture();
};