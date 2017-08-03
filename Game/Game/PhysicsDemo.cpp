#include "stdafx.h"
#include "PhysicsDemo.h"

NewObj::NewObj()
{
}

NewObj::NewObj(Object &obj)
{
	ID = obj.ID;
	model = obj.model;
	numTextures = obj.numTextures;
	mspf = obj.mspf;
	w = obj.w;
	h = obj.h;
	type = obj.type;
	textures = obj.textures;
	shader = obj.shader;
	R = Matrix(obj.R);
	S = Matrix(obj.S);
	T = Matrix(obj.T);
	x = obj.x;
	y = obj.y;
}

void NewObj::Update(float ms)
{
	if (type == MAN_OBJ)
	{
		float sw = SceneManager::GetInstance()->sceneWidth;
		//float sh = SceneManager::GetInstance()->sceneHeight;
		if (speed > 0)
		{
			if (x >= sw / 2)
			{
				speed = -speed;
				SetFlip(false);
			}
		}
		else
		{
			if (x <= -sw / 2)
			{
				speed = -speed;
				SetFlip(true);
			}
		}
		x += speed*ms*50;
		SetPosition(x, y);
	}
}
