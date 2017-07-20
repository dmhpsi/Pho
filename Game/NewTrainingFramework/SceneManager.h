#pragma once

#include "Object.h"
#include <stdarg.h>

class SceneManager
{
private:
	static SceneManager* Instance;
	~SceneManager();
public:
	static void CleanInstance();
	int numObject;
	Object* listObject;
	void Init(const char *smFile);
	void Draw(int numObjects, ...);
	static SceneManager* GetInstance();
};