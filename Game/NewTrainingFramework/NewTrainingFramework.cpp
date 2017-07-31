// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "NewTrainingFramework.h"

Matrix globalVP;
<<<<<<< HEAD
int currentTick;
float globalVolume;

int Init(ESContext *esContext)
{
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glEnable(GL_DEPTH_TEST); 

	// Create an instance of Resource Scene to manage easily
	ResourceManager* instance = ResourceManager::GetInstance();
	instance->Init("../Resources/Resource_files/rm.txt");
	SceneManager::GetInstance()->Init("../Resources/Resource_files/bear.txt");

	globalVolume = 100;
	instance->listMusics[0].Replay();
	return 0;
}

void Draw(ESContext *esContext)
=======

int currentTick;

int Init ( ESContext *esContext )
{
	glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );
	glEnable(GL_DEPTH_TEST); 
	ResourceManager* instance = ResourceManager::GetInstance();
	instance->Init("../Resources/Resource_files/rm.txt");
	SceneManager::GetInstance()->Init((char*)instance->GetResource(SCENE, 1));

	return 0;
}

void Draw ( ESContext *esContext )
>>>>>>> dmhpsi/huynx
{
	glEnable(GL_BLEND);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	globalVP = Camera::GetInstance()->ViewTheWorld();

	SceneManager::GetInstance()->Draw(-1);

<<<<<<< HEAD
	 //Draw text
	Vector4 color = Vector4(194, 24, 91);
	char *fileName = "THREE WOLVES";
	
	for (int i = 0; i < strlen(fileName); i++)
	{
		TextManager::GetInstance()->RenderString(fileName+i, Vector4(rand() % 256, rand() % 256, rand() % 256), -250 + 40*i, 400, 1.2, 1.2);
	}

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
	currentTick = GetTickCount();
}

void Update(ESContext *esContext, float deltaTime)
=======
	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
	currentTick = GetTickCount();
}

void Update ( ESContext *esContext, float deltaTime )
>>>>>>> dmhpsi/huynx
{
	if (deltaTime > 0)
	{
		Camera::GetInstance()->Update(deltaTime);
	}
}

<<<<<<< HEAD


void Key(ESContext *esContext, unsigned char key, bool bIsPressed)
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
=======
void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	if (key == 0x41)
	{
		Camera::GetInstance()->Act(LOOK_LEFT, bIsPressed);
	}
	else if (key == 0x44)
	{
		Camera::GetInstance()->Act(LOOK_RIGHT, bIsPressed);
	}
	else if (key == 0x57)
	{
		Camera::GetInstance()->Act(LOOK_UP, bIsPressed);
	}
	else if (key == 0x53)
	{
		Camera::GetInstance()->Act(LOOK_DOWN, bIsPressed);
	}
	else 
>>>>>>> dmhpsi/huynx
	if (key == VK_UP)
	{
		Camera::GetInstance()->Act(MOVE_UP, bIsPressed);
	}
	else if (key == VK_DOWN)
	{
		Camera::GetInstance()->Act(MOVE_DOWN, bIsPressed);
	}
<<<<<<< HEAD
	else
		if (bIsPressed)
			ResourceManager::GetInstance()->listSounds[0].Replay();
	//else if (key == VK_LEFT)
	//{
	//	Camera::GetInstance()->Act(MOVE_LEFT, bIsPressed);
	//}
	//else if (key == VK_RIGHT)
	//{
	//	Camera::GetInstance()->Act(MOVE_RIGHT, bIsPressed);
	//}
=======
	else if (key == VK_LEFT)
	{
		Camera::GetInstance()->Act(MOVE_LEFT, bIsPressed);
	}
	else if (key == VK_RIGHT)
	{
		Camera::GetInstance()->Act(MOVE_RIGHT, bIsPressed);
	}
>>>>>>> dmhpsi/huynx
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
<<<<<<< HEAD
	SceneManager::GetInstance()->CleanInstance();
	Camera::GetInstance()->CleanInstance();
	ResourceManager::GetInstance()->CleanInstance();
	TextManager::GetInstance()->CleanInstance();
}

void OnMouseUp(ESContext * esContext, float x, float y)
{
}

void OnMouseDown(ESContext * esContext, float x, float y)
{
}

void OnMouseMove(ESContext * esContext, float x, float y)
{
=======
	ResourceManager::GetInstance()->CleanInstance();
	SceneManager::GetInstance()->CleanInstance();
	Camera::GetInstance()->CleanInstance();
>>>>>>> dmhpsi/huynx
}

