#pragma once

#include "Object.h"
#include "Camera.h"
#include <stdarg.h>

extern int currentTick;

class SceneManager
{
private:
	static SceneManager* Instance;
	~SceneManager();
public:
	static void CleanInstance();
	int numObject, numBg;
	float sceneWidth, sceneHeight;
	Object* listObject;
	void Init(const char *smFile);
	void Draw(int binaryPos);
	static SceneManager* GetInstance();
};