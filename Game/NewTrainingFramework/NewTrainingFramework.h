#pragma once
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include "Texture.h"
#include <conio.h>
#include <stdlib.h>
#include "Model.h"
#include "Globals.h"
#include "Object.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "TextManager.h"
#include "Camera.h"
#include <Windows.h>
#include "Sound.h"
#include "Graphics.h"


int Init(ESContext *esContext);
void _Draw(ESContext *esContext);
void _Update(ESContext *esContext, float deltaTime);
void _Key(ESContext *esContext, unsigned char key, bool bIsPressed);
void CleanUp();
void _OnMouseUp(ESContext *esContext, float x, float y);
void _OnMouseDown(ESContext *esContext, float x, float y);
void _OnMouseMove(ESContext *esContext, float x, float y);

