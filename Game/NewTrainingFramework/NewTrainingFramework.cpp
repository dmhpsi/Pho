// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "NewTrainingFramework.h"

Matrix globalVP;
TextManager *tm;
int currentTick;
Shaders fontShader;

int Init(ESContext *esContext)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST); 

	// Create an instance of Resource and Scene to manage easily
	ResourceManager* instance = ResourceManager::GetInstance();
	instance->Init("../Resources/Resource_files/rm.txt");
	SceneManager::GetInstance()->Init("../Resources/Resource_files/bear.txt");

	// Create an instance of class TextManager to handle font
	tm = new TextManager();
	tm->Initialize();
	instance->listSounds[0].play();

	fontShader.Init("../Resources/Shaders/FontShaderVS.vs", "../Resources/Shaders/FontShaderFS.fs");
	return 0;
}

void Draw(ESContext *esContext)
{
	glEnable(GL_BLEND);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	globalVP = Camera::GetInstance()->ViewTheWorld();

	SceneManager::GetInstance()->Draw(-1);

	 //Draw text
	glUseProgram(fontShader.program);
	Vector4 color = Vector4(0, 0, 0, 1);
	tm->RenderString("H", color, 0, 0, 10, 10);

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
}

void CleanUp()
{
	ResourceManager::GetInstance()->CleanInstance();
	SceneManager::GetInstance()->CleanInstance();
	Camera::GetInstance()->CleanInstance();
	delete tm;
}

