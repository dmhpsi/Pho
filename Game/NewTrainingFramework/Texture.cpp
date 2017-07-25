#include "stdafx.h"
#include "Texture.h"

void Texture::LoadToGPU(const char * FileName, MyEnum type, GLenum clampMode)
{
	img = LoadTGA(FileName, &width, &height, &bpp);

	if (type == NORMAL_OBJ)
	{
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