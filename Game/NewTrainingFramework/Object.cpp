#include "stdafx.h"
#include "Object.h"

void Object::Draw()
{
	if (timeVisibleSet > currentTick)
	{
		visible = visibleSet;
	}
	else
	{
		visible = !visibleSet;
	}
	if (visible)
	{
		glUseProgram(shader->program);

		GLint uniform = glGetUniformLocation(shader->program, "u_WVP");

		Matrix WVP;
		if (type != SKY_OBJ)
		{
			WVP = S*F*R*T*globalVP;
		}
		else
		{
			WVP = S*F*R*T*absoluteView;
		}
		glUniformMatrix4fv(uniform, 1, GL_FALSE, &WVP.m[0][0]);

		uniform = glGetUniformLocation(shader->program, "u_fadeRatio");
		if (uniform != -1)
		{
			glUniform1f(uniform, globalFadeRatio);
		}

		glBindBuffer(GL_ARRAY_BUFFER, model->vboId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->iboId);

		glBindTexture(GL_TEXTURE_2D, textures[status]->texId[currentTick / mspf % textures[status]->numOfFragments]);

		//glBindTexture(GL_TEXTURE_CUBE_MAP, textures[status]->texId[0]);

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
}

void Object::SetStatus(MyEnum inStatus)
{
	if (inStatus >= numTextures)
	{
		inStatus = OBJ_IDLE;
	}
	status = inStatus;
}

void Object::SetScale(float x)
{
	x *= 0.5;
	S.SetScale(x*w, x*h, 1);
}

void Object::SetFlip(bool isFlipped)
{
	if (isFlipped)
	{
		F.SetScale(-1, 1, 1);
	}
	else
	{
		F.SetScale(1, 1, 1);
	}
}

void Object::SetRotation(float angle)
{
	angle *= PI / 180;
	Object::angle = angle;
	R.SetRotationZ(angle);
}

void Object::SetPosition(float x, float y)
{
	T.SetTranslation(floor(x), floor(y), type);
	//T.SetTranslation(x, y, z);
}

void Object::SetVisible(bool isVisible, float ms)
{
	visibleSet = isVisible;
	timeVisibleSet = currentTick + ms;
}

Object::Object()
{
	status = OBJ_IDLE;
	F.SetIdentity();
	visible = true;
	visibleSet = false;
	timeVisibleSet = 0;
}

Object::~Object()
{
	delete[] textures;
}