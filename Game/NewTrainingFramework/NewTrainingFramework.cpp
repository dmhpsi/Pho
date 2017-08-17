// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "NewTrainingFramework.h"
#include "..\Game\PhysicManager.h"

Matrix globalVP, absoluteView;
int currentTick;
float globalVolume, globalFadeRatio;
bool isFading = false, isFaded = false;

int Init(ESContext *esContext)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glEnable(GL_DEPTH_TEST);
	globalFadeRatio = 0;

	// Create an instance of Resource Scene to manage easily
	ResourceManager* instance = ResourceManager::GetInstance();
	instance->Init("../Resources/Resource_files/rm.txt");
	//SceneManager::GetInstance()->Init("../Resources/Resource_files/splash.txt");

	globalVolume = 100;
//	instance->listMusics[0].Replay();

	esRegisterDrawFunc(esContext, _Draw);
	esRegisterUpdateFunc(esContext, _Update);
	esRegisterKeyFunc(esContext, _Key);
	esRegisterMouseDownFunc(esContext, _OnMouseDown);
	esRegisterMouseUpFunc(esContext, _OnMouseUp);
	esRegisterMouseMoveFunc(esContext, _OnMouseMove);
	return 0;
}

void _Draw(ESContext *esContext)
{
	glEnable(GL_BLEND);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	globalVP = Camera::GetInstance()->ViewTheWorld();
	absoluteView = Camera::GetInstance()->GetAbsoluteViewMatrix();

	//char *fileName = "THREE WOLVES";
	//SceneManager::GetInstance()->Draw(-1);
	//TextManager::GetInstance()->RenderString(fileName, color, -250, 400, 1.2, 1.2);

	Graphics::GetInstance()->Draw();

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);

	currentTick = GetTickCount();

	//if (false && isFaded)
	//{
	//	static int pos;
	//	SceneManager::GetInstance()->CleanInstance();
	//	SceneManager::GetInstance()->Init(ResourceManager::GetInstance()->listScenes[pos % ResourceManager::GetInstance()->numScenes]);
	//	SceneManager::GetInstance()->Fade(false, 1000);
	//	pos++;
	//}
}

void _Update(ESContext *esContext, float deltaTime)
{
	if (deltaTime > 0)
	{
		Camera::GetInstance()->Update(deltaTime);
	}
	Graphics::GetInstance()->Update(deltaTime);
	//eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void _Key(ESContext *esContext, unsigned char key, bool bIsPressed)
{
	//if (ResourceManager::GetInstance()->soundInstance.getStatus() == sf::Sound::Stopped)
	//if (key == 0x41)
	//{
	//	Camera::GetInstance()->Act(LOOK_LEFT, bIsPressed);
	//}
	//else if (key == 0x44)
	//{
	//	Camera::GetInstance()->Act(LOOK_RIGHT, bIsPressed);
	//}
	//else if (key == 0x57)
	//{
	//	Camera::GetInstance()->Act(LOOK_UP, bIsPressed);
	//}
	//else if (key == 0x53)
	//{
	//	Camera::GetInstance()->Act(LOOK_DOWN, bIsPressed);
	//}
	//else 
	//if (key == VK_UP)
	//{
	//	Camera::GetInstance()->Act(MOVE_UP, bIsPressed);
	//}
	//if (key == VK_DOWN)
	//{
	//	Camera::GetInstance()->Act(MOVE_DOWN, bIsPressed);
	//}
	//else
	//	if (bIsPressed)
	//		ResourceManager::GetInstance()->listSounds[0].Replay();
	//else if (key == VK_LEFT)
	//{
	//	Camera::GetInstance()->Act(MOVE_LEFT, bIsPressed);
	//}
	//else if (key == VK_RIGHT)
	//{
	//	Camera::GetInstance()->Act(MOVE_RIGHT, bIsPressed);
	//}
	//else if (key == VK_CONTROL)
	//{
	//	Camera::GetInstance()->Act(DUCKING, bIsPressed);
	//}
	//else if (key == VK_SPACE)
	//{
	//	Camera::GetInstance()->Act(JUMPING, bIsPressed);
	//}
	//else if (key == VK_SHIFT)
	//{
	//	Camera::GetInstance()->Act(RUSH, bIsPressed);
	//}
	//else if (key == VK_RETURN)
	//{
	//	Camera::GetInstance()->Act(FREE_MODE, !bIsPressed);
	//}
	//else if (key == VK_F5)
	//{
	//	Camera::GetInstance()->Act(RESET, bIsPressed);
	//}

	Graphics::GetInstance()->Key(key, bIsPressed);
}

void CleanUp()
{
	SceneManager::GetInstance()->CleanInstance();
	Camera::GetInstance()->CleanInstance();
	ResourceManager::GetInstance()->CleanInstance();
	TextManager::GetInstance()->CleanInstance();
}

void _OnMouseUp(ESContext * esContext, float x, float y)
{
	Graphics::GetInstance()->MouseUp(x, y);
}

void _OnMouseDown(ESContext * esContext, float x, float y)
{
	Graphics::GetInstance()->MouseDown(x, y);
}

void _OnMouseMove(ESContext * esContext, float x, float y)
{
	Graphics::GetInstance()->MouseMove(x, y);
}
