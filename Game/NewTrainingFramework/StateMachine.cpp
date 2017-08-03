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
	currentTime = GetTickCount();
	lastTime = currentTime;

	switch (currentState)
	{
	case StateMachine::GS_LOADING:
		SceneManager::GetInstance()->Init("../Resources/Resource_files/splash.txt");
	//	char *fileName = "hello";
		textToDraw.push_back(&SceneManager::GetInstance()->listObject[0]);
		break;
	case StateMachine::GS_MAINMENU:
		SceneManager::GetInstance()->Init("../Resources/Resource_files/bear.txt");

		break;
	case StateMachine::GS_GAMEPLAY:
		SceneManager::GetInstance()->Init("../Resources/Resource_files/");
		break;
		
	case StateMachine:: GS_OPTIONMENU:
		break;
	case StateMachine::GS_CREDIT:
		break;
	default:
		break;
	}
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
	for (size_t i = 0; i < textToDraw.size(); i++)
	{
		textToDraw.pop_back();
	}
	textToDraw.clear();
	Init();
}

void StateMachine::Update(float deltaTime)
{
	Graphics::GetInstance()->UpdateCallback(deltaTime);
	static bool loaded = false;
	switch (currentState)
	{
	case StateMachine::GS_LOADING:
		currentTime = GetTickCount();
		if (currentTime - lastTime >= 1000 && !loaded)
		{
			loaded = true;
			lastTime = currentTime;
			textToDraw.pop_back();
			textToDraw.push_back(&SceneManager::GetInstance()->listObject[1]);
		}
		else if (currentTime - lastTime >= 1000)
		{
			lastTime = currentTime;
			ChangState(GS_MAINMENU);
		}
		break;
	case StateMachine::GS_MAINMENU:
		break;
	case StateMachine::GS_GAMEPLAY:
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
void StateMachine::Render()
{
	SceneManager::GetInstance()->Draw(-1);
}

StateMachine::~StateMachine()
{

}
