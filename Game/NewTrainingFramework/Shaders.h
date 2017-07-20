#pragma once
#include "../Utilities/utilities.h"

class Shaders 
{
public:
	int ID;
	GLuint program, vertexShader, fragmentShader;
	char fileVS[260];
	char fileFS[260];
	GLint positionAttribute;
	GLint colorAttribute;

	int Init(char * fileVertexShader, char * fileFragmentShader);
	~Shaders();
};