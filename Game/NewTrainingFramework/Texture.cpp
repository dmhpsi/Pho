#include "stdafx.h"
#include "Texture.h"
<<<<<<< HEAD
#include "TextManager.h"

void Texture::LoadToGPU(const char * FileName, MyEnum type, GLenum clampMode)
{
	// If texture is a .tga file
	if (type == NORMAL_OBJ)
	{
		img = LoadTGA(FileName, &width, &height, &bpp);
=======

void Texture::LoadToGPU(const char * FileName, MyEnum type, GLenum clampMode)
{
	img = LoadTGA(FileName, &width, &height, &bpp);

	if (type == NORMAL_OBJ)
	{
>>>>>>> dmhpsi/huynx
		int totalPixelsPerFrag = width * (height / numOfFragments) * bpp / 8;
		texId = new GLuint[numOfFragments];
		for (int i = 0; i < numOfFragments; i++)
		{
			glGenTextures(1, &texId[i]);
			glBindTexture(GL_TEXTURE_2D, texId[i]);

			// Crop a children texture
			//memcpy(fragment, img + sizeof(char) * totalPixelsPerFrag * i, totalPixelsPerFrag);

			if (bpp == 24)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height / numOfFragments, 0, GL_RGB, GL_UNSIGNED_BYTE, img + sizeof(char)* totalPixelsPerFrag * i);
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height / numOfFragments, 0, GL_RGBA, GL_UNSIGNED_BYTE, img + sizeof(char)* totalPixelsPerFrag * i);
			}

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, clampMode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, clampMode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
<<<<<<< HEAD
	// if teture is font type
	else if (type == OBJ_FONT)
	{
		texId = new GLuint;
		TextManager::GetInstance()->Initialize(FileName);
		TextManager::GetInstance()->fontShader = new Shaders();
		TextManager::GetInstance()->fontShader->Init("../Resources/Shaders/FontShaderVS.vs", "../Resources/Shaders/FontShaderFS.fs");
	}
=======
>>>>>>> dmhpsi/huynx
	if (img)
		delete img;
}

Texture::Texture()
{
	img = NULL;
	width = 0;
	height = 0;
	bpp = 0;
	texId = 0;
}

Texture::~Texture()
{
	delete [] texId;
}