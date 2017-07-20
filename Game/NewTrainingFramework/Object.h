#pragma once 
#include "../Utilities/utilities.h"
#include "Vertex.h"
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "define.h"

class Object
{
public:
	int ID;
	Model* model;
	int numTextures;
	Texture** listTextures;
	Shaders* shader;
	void Draw();
	Matrix W;
	~Object();
};