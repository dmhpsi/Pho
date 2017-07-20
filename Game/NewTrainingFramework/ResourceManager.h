#pragma once

#include "Model.h"
#include "Texture.h"
#include "Vertex.h"
#include "Shaders.h"

class ResourceManager
{
private:
	static ResourceManager* Instance;
	~ResourceManager();
public:
	void Init(const char* rmFile);
	static ResourceManager* GetInstance();
	static void CleanInstance();
	void* GetObjPart(MyEnum type, int ID);

	int numModels;
	Model* listModels;

	int numTextures;
	Texture* listTextures;

	int numSkyTextures;
	Texture* listSkyTextures;

	int numShaders;
	Shaders* listShaders;
};