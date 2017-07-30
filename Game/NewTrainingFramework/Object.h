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

class Object
{
public:
	int ID;
	Model* model;
	int numTextures, mspf;
	float w, h;
	Texture* listTextures;
	Shaders* shader;
	void Draw();
	Matrix W;
	~Object();
};