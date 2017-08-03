// Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../NewTrainingFramework/NewTrainingFramework.h"
#include "Box2D/Box2D.h"
#include "PhysicsDemo.h"
#include "../NewTrainingFramework/StateMachine.h"

NewObj *list[12];

void Key(unsigned char key, bool isPressed)
{

}

void Update(float delta)
{
	for (int i = 0; i < 12; i++)
	{
		list[i]->Update(delta);
	}
}

void Draw()
{
	StateMachine::GetInstance()->Render();
	for (int i = 0; i < 12; i++)
	{
		list[i]->Draw();
	}
}

void GameInit()
{
	srand(time(0));
	Graphics::GetInstance()->RegisterKeyCallback(Key);
	Graphics::GetInstance()->RegisterDrawCallback(Draw);
	Graphics::GetInstance()->RegisterUpdateCallback(Update);
	Graphics::GetInstance()->RegisterDrawCallback(Draw);
	SceneManager* sm = SceneManager::GetInstance();
	sm->Init("../Resources/Resource_files/level1.txt");
	for (int i = 0; i < 12; i++)
	{
		list[i] = new NewObj(sm->listObject[i]);
		list[i]->speed = 1*(1 - 2 * (rand() % 2));
	}
	for (int i = 0; i < 6; i++)
	{
		list[i]->type = BG_OBJ;
		list[i]->SetFlip(false);

		list[i + 6]->type = MAN_OBJ;
		list[i + 6]->x = (16 - rand() % 32) * 4;
		if (list[i + 6]->speed > 0)
		{
			list[i + 6]->SetFlip(true);
		}
		else
		{
			list[i + 6]->SetFlip(false);
		}
	}
}


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

	//identifying memory leaks	
	StateMachine::GetInstance()->DeleteState();
	MemoryDump();
	printf("Press any key...\n");
	_getch();
	
	return 0;
}