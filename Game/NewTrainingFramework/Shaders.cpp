#include "stdafx.h"
#include "Shaders.h"

void Shaders::SetFade(GLfloat ratio)
{
	glUniform1f(fadeUniform, ratio);
}

int Shaders::Init(char * fileVertexShader, char * fileFragmentShader)
{
	vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

	if ( vertexShader == 0 )
		return -1;

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if ( fragmentShader == 0 )
	{
		glDeleteShader( vertexShader );
		return -2;
	}

	program = esLoadProgram(vertexShader, fragmentShader);

	//finding location of uniforms / attributes
	positionAttribute = glGetAttribLocation(program, "a_posL");
	colorAttribute = glGetAttribLocation(program, "a_uv");
	fadeUniform = glGetUniformLocation(program, "u_fadeRatio");
	if (positionAttribute == -1)
		positionAttribute = glGetAttribLocation(program, "a_CubeVertexPos");

	return 0;
}

Shaders::~Shaders()
{
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}