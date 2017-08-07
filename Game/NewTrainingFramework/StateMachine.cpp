#pragma once
#include "stdafx.h"
#include"StateMachine.h"
using namespace std;
StateMachine* StateMachine::Instance = NULL;
StateMachine* StateMachine::GetInstance()
{
	if (!Instance)
	{
		Instance = new StateMachine();
	}
	return Instance;
}

StateMachine::StateMachine()
{
	currentState = GS_LOADING;
}

void StateMachine::Init()
{


	switch (currentState)
	{
	case StateMachine::GS_LOADING:
		LoadingInit();
		break;
	case StateMachine::GS_MAINMENU:
		MenuInit();
		break;
	case StateMachine::GS_GAMEPLAY:
		GamePlayInit();
		break;
	case StateMachine::GS_OPTIONMENU:
		break;
	case StateMachine::GS_CREDIT:
		break;
	default:
		break;
	}
}

void StateMachine::LoadingInit()
{
	currentTime = GetTickCount();
	lastTime = currentTime;
	SceneManager::GetInstance()->Init("../Resources/Resource_files/bear.txt");
	//textToDraw.push_back(&SceneManager::GetInstance()->listObject[0]);
}

void StateMachine::MenuInit()
{
	SceneManager::GetInstance()->Init("../Resources/Resource_files/level1.txt");
}

void StateMachine::GamePlayInit()
{
	SceneManager::GetInstance()->Init("../Resources/Resource_files/level1.txt");


}

void StateMachine::DeleteState()
{
	delete Instance;
	Instance = NULL;
}


void StateMachine::ChangState(GameState state)
{
	currentState = state;
	SceneManager::GetInstance()->CleanInstance();
	SceneManager::GetInstance()->CleanInstance();
	/*for (size_t i = 0; i < textToDraw.size(); i++)
	{
	textToDraw.pop_back();
	}
	textToDraw.clear();*/
	Init();
}



void StateMachine::Update(float deltaTime)
{

	switch (currentState)
	{
	case StateMachine::GS_LOADING:
		LoadingUpdate(deltaTime);
		break;
	case StateMachine::GS_MAINMENU:
		MenuUpdate(deltaTime);
		break;
	case StateMachine::GS_GAMEPLAY:
		GamePlayUpdate(deltaTime);
		currentTime = GetTickCount();
		break;
	case StateMachine::GS_OPTIONMENU:
		break;
	case StateMachine::GS_CREDIT:
		break;
	default:
		break;
	}

}
void StateMachine::LoadingUpdate(float deltaTime)
{
	static bool loaded = false;
	currentTime = GetTickCount();
	if (currentTime - lastTime >= 1000 && !loaded)
	{
		loaded = true;
		lastTime = currentTime;
		//textToDraw.pop_back();
		//textToDraw.push_back(&SceneManager::GetInstance()->listObject[1]);
	}
	else if (currentTime - lastTime >= 2000)
	{
		lastTime = currentTime;
		ChangState(GS_MAINMENU);
	}
}
void StateMachine::MenuUpdate(float deltaTime)
{

}
void StateMachine::GamePlayUpdate(float deltaTime)
{

}

void StateMachine::Render()
{
	SceneManager::GetInstance()->Draw(-1);
	if (currentState == GS_LOADING)
	{
		Vector4 color = Vector4(255, 0, 0, abs(100 - currentTick % 200) / 100.0);
		TextManager::GetInstance()->RenderString("Get READY to lose!", color, -280, -600, 0.7, 0.7);
	}
}
void StateMachine::OnMouseDown(float x, float y)
{
	/*switch (currentState)
	{
	case StateMachine::GS_LOADING:
	break;
	case StateMachine::GS_MAINMENU:
	break;
	case StateMachine::GS_GAMEPLAY:
	break;
	case StateMachine::GS_OPTIONMENU:
	break;
	case StateMachine::GS_CREDIT:
	break;
	default:
	break;
	}*/
	cout << x << " " << y;
}
StateMachine::~StateMachine()
{

}
