#include "stdafx.h"
#include "Object.h"

void Object::Draw()
{
	glUseProgram(shader->program);
	
	GLint uniform = glGetUniformLocation(shader->program, "u_WVP");

	Matrix WVP;
	WVP = W*globalVP;
	glUniformMatrix4fv(uniform, 1, GL_FALSE, &WVP.m[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, model->vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->iboId);
				
	glBindTexture(GL_TEXTURE_2D, listTextures->texId[currentTick / mspf % listTextures->numOfFragments]);

	glBindTexture(GL_TEXTURE_CUBE_MAP, listTextures->texId[0]);

	if (shader->positionAttribute != -1)
	{
		glEnableVertexAttribArray(shader->positionAttribute);
		glVertexAttribPointer(shader->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	if (shader->colorAttribute != -1)
	{
		glEnableVertexAttribArray(shader->colorAttribute);
		glVertexAttribPointer(shader->colorAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)52);
	}

	glDrawElements(GL_TRIANGLES, model->numIndices, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Object::~Object()
{
}