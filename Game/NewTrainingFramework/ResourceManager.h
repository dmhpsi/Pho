#pragma once

#include "Model.h"
#include "Texture.h"
#include "Vertex.h"
#include "Shaders.h"
#include <vector>
using namespace std;

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

	int numShaders;
	Shaders* listShaders;

	int numScenes;
	vector<const char *> listScenes;
};