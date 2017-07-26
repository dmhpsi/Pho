// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "NewTrainingFramework.h"

Matrix globalVP;

int currentTick;

int Init(ESContext *esContext)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST); 
	ResourceManager* instance = ResourceManager::GetInstance();
	instance->Init("../Resources/Resource_files/rm.txt");
	char *test = "../Resources/Resource_files/level1.txt";
	//char *test2 = ResourceManager::GetInstance()->listScenes[0];
	SceneManager::GetInstance()->Init("../Resources/Resource_files/level1.txt");
	PlaySound(TEXT("../Resources/Sounds/YumewoKanaete.wav"), NULL, SND_ASYNC | SND_LOOP);
	return 0;
}

void Draw(ESContext *esContext)
{
	glEnable(GL_BLEND);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	globalVP = Camera::GetInstance()->ViewTheWorld();

	SceneManager::GetInstance()->Draw(-1);

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
	currentTick = GetTickCount();
}

void Update(ESContext *esContext, float deltaTime)
{
	if (deltaTime > 0)
	{
		Camera::GetInstance()->Update(deltaTime);
	}
}

void Key(ESContext *esContext, unsigned char key, bool bIsPressed)
{
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
	if (key == VK_UP)
	{
		Camera::GetInstance()->Act(MOVE_UP, bIsPressed);
	}
	else if (key == VK_DOWN)
	{
		Camera::GetInstance()->Act(MOVE_DOWN, bIsPressed);
	}
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
	else if (key == VK_F6)
	{
		PlaySound(NULL, NULL, SND_ASYNC | SND_LOOP);
	}
	else if (key == VK_F7)
	{
		PlaySound(TEXT("../Resources/Sounds/YumewoKanaete.wav"), NULL, SND_ASYNC | SND_LOOP);
	}
}

void CleanUp()
{
	ResourceManager::GetInstance()->CleanInstance();
	SceneManager::GetInstance()->CleanInstance();
	Camera::GetInstance()->CleanInstance();
}

