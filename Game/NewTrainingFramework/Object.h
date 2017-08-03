#pragma once 
#include "../Utilities/utilities.h"
#include "Vertex.h"
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "define.h"
#include "Globals.h"

extern Matrix globalVP;
extern int currentTick;
extern float globalFadeRatio;

class Object
{
public:
	int ID;
	Model* model;
	int numTextures, mspf;
	float w, h, x, y, angle;
	MyEnum type;
	Texture* textures;
	Shaders* shader;
	Matrix R, S, T, F;
	void Draw();
	void SetScale(float x);
	void SetFlip(bool isFlipped);
	void SetRotation(float angle);
	void SetPosition(float x, float y);
	~Object();
};