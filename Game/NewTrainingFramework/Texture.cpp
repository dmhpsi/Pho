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
	else 
	{
		glGenTextures(1, &texId[0]);
		char* face[6];
		glBindTexture(GL_TEXTURE_CUBE_MAP, texId[0]);

		char *imgPtr, *facePtr;
		imgPtr = img;
		int faceW = width / 4 * bpp / 8;
		int faceH = height / bpp * 8;

		for (int i = 0; i < 6; i++)
		{
			face[i] = new char[faceW*faceH];
		}

		for (int i = 0; i < faceH; i++)
		{
			memcpy(face[2] + i*faceW, imgPtr + faceW, faceW);
			imgPtr += width * bpp / 8;
		}

		for (int i = 0; i < faceH; i++)
		{
			memcpy(face[1] + i*faceW, imgPtr, faceW);
			memcpy(face[4] + i*faceW, imgPtr + faceW, faceW);
			memcpy(face[0] + i*faceW, imgPtr + faceW * 2, faceW);
			memcpy(face[5] + i*faceW, imgPtr + faceW * 3, faceW);
			imgPtr += width * bpp / 8;
		}

		for (int i = 0; i < faceH; i++)
		{
			memcpy(face[3] + i*faceW, imgPtr + faceW, faceW);
			imgPtr += width * bpp / 8;
		}

		for (int i = 0; i<6; i++)
		{
			if (bpp == 24)
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, faceH, faceW / bpp * 8, 0, GL_RGB, GL_UNSIGNED_BYTE, face[i]);
			else				
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, faceH, faceW / bpp * 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, face[i]);
			
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, clampMode);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, clampMode);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			delete face[i];
		}
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
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