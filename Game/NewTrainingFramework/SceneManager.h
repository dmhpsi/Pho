#pragma once

#include "Object.h"
#include "Camera.h"
#include <stdarg.h>


extern bool isFading, isFaded;
extern float globalFadeRatio;

class SceneManager
{
private:
	static SceneManager* Instance;
public:
	static void CleanInstance();
	int numObject, fadeStartTick, fadeMillis;
	float sceneWidth, sceneHeight;
	Object* listObject;
	void Init(const char *smFile);

	// Draw objects by the listed ID
	// PARAM:
	//      numDrawObjects: Number of objects to draw
	//      ...: List of objects' ID to draw
	// E.G. Draw(4, 4, 2, 3, 1);
	// *NOTE: The number of IDs must be equal to numDrawObjects
	void Draw(int numDrawObjects, ...);
	static SceneManager* GetInstance();

	// Set fade-translation effect of the scene
	// PARAM:
	//      isFadeIn: true to fade in, flase to fade out
	//      millis: Number of milliseconds the effecft happens
	void Fade(bool isFadeIn, int millis);
	~SceneManager();
};