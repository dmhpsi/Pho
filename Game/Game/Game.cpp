// Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PhysicManager.h"

#include "../NewTrainingFramework/NewTrainingFramework.h"
#include "Box2D/Box2D.h"
#include "../NewTrainingFramework/StateMachine.h"

bool isPlaying;

void Key(unsigned char key, bool isPressed)
{
	if (isPlaying)
	{
		if (isPressed)
			PhysicManager::GetInstance()->Keyboard(key);
	}
}
//void OnMouseUp(float x, float y)
//{
//	StateMachine::GetInstance()->OnMouseUp(x,y);
//}
void OnMouseDown(float x, float y)
{
	StateMachine::GetInstance()->OnMouseDown(x, y);
}
//void OnMouseMove(float x, float y)
//{
//	StateMachine::GetInstance()->OnMouseMove(x, y);
//}
void Update(float delta)
{
	if (isPlaying)
	{
		PhysicManager::GetInstance()->Update(delta);
	}
	if (delta > 50)
	{
		std::cout << "Some thing went wrong: deltatime " << delta << endl;
	}
	StateMachine::GetInstance()->Update(delta);
	if (StateMachine::GetInstance()->currentState == StateMachine::GS_MAINMENU)
	{
		if (!isPlaying)
		{
			PhysicManager::GetInstance()->Init();
		}
		isPlaying = true;
	}
}


void Draw()
{
	StateMachine::GetInstance()->Render();
	//SceneManager::GetInstance()->Draw(-1);
}

void GameInit()
{
	srand(time(0));
	Graphics::GetInstance()->RegisterKeyCallback(Key);
	Graphics::GetInstance()->RegisterDrawCallback(Draw);
	Graphics::GetInstance()->RegisterUpdateCallback(Update);
	Graphics::GetInstance()->RegisterDrawCallback(Draw);
	StateMachine::GetInstance()->Init();
	//	Graphics::GetInstance()->MouseDownCallback(FUNC_MOUSEDOWN,0.0f);
	isPlaying = false;
}

//PhysicManager::GetInstance()->Update(deltaTime);

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;

	esInitContext(&esContext);

	esCreateWindow(&esContext, "Pho", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	Init(&esContext);

	GameInit();

	esMainLoop(&esContext);

	//releasing OpenGL resources
	CleanUp();
	Graphics::GetInstance()->CleanInstance();
	PhysicManager::GetInstance()->CleanInstance();

	//identifying memory leaks	
	StateMachine::GetInstance()->DeleteState();
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}