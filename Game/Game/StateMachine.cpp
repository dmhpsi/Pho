#pragma once
#include "stdafx.h"
#include"StateMachine.h"

using namespace std;
extern bool waiting;

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
	glose = false;
	gwin = false;
	ingame = &ResourceManager::GetInstance()->listMusics[0];
	theme = &ResourceManager::GetInstance()->listMusics[2];
	lose = &ResourceManager::GetInstance()->listSounds[1];
	win = &ResourceManager::GetInstance()->listSounds[4];
	lose->Stop();
	theme->Stop();
	ingame->Stop();
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
	case StateMachine::GS_LEVELS:
		LevelsInit();
		break;
	case StateMachine::GS_GAMEPLAY:
		GamePlayInit();
		break;
	case StateMachine::GS_OPTIONMENU:
		OptionMenuInit();
		break;
	case StateMachine::GS_GAME_RETURN:
		GameReturn();
		break;
	case StateMachine::GS_CREDIT:
		break;
	default:
		break;
	}
}

void StateMachine::LoadingInit()
{
	lastTime = currentTick;
	SceneManager::GetInstance()->Init("../Resources/Resource_files/bear.txt");
	//textToDraw.push_back(&SceneManager::GetInstance()->listObject[0]);
}

void StateMachine::MenuInit()
{
	SceneManager::GetInstance()->Init("../Resources/Resource_files/GS_MAINMENU.txt");
	listButtons[B_CAMPAIGN].SetProperty(244, 520, 303, 80, B_CAMPAIGN);
	listButtons[B_ENDLESS].SetProperty(244, 685, 275, 80, B_ENDLESS);
}

void StateMachine::LevelsInit()
{
	SceneManager::GetInstance()->Init("../Resources/Resource_files/GS_LEVELS.txt");
	listButtons[B_BACK].SetProperty(244, 99, 488, 134, B_BACK);
	listButtons[B_LV1].SetProperty(244, 242, 488, 152, B_LV1);
	listButtons[B_LV2].SetProperty(244, 394, 488, 152, B_LV2);
	listButtons[B_LV3].SetProperty(244, 572, 488, 204, B_LV3);
	listButtons[B_LV4].SetProperty(244, 770, 488, 190, B_LV4);
}

void StateMachine::OptionMenuInit()
{
	//SceneManager::GetInstance()->Init("../Resources/Resource_files/GS_OPTIONMENU.txt");
	SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->winTextureId].SetVisible(true, 0);
	SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->homeButtonId].SetVisible(false, 0);
	SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->resumeButtonId].SetVisible(false, 0);
	SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->maskId].SetVisible(false, 0);
	listButtons[B_HOME].SetProperty(167, 432, 94, 92, B_HOME);
	listButtons[B_RESUME].SetProperty(319, 432, 94, 90, B_RESUME);
}

void StateMachine::GamePlayInit()
{
	wplayed = false;
	lplayed = false;
	theme->Stop();
	ingame->Replay();
	Camera::GetInstance()->SetHeight(0, 0);
	char f[50] = "../Resources/Resource_files/level1.txt";
	f[33] = PhysicManager::GetInstance()->m_ilevel + '0';
	printf(f);
	SceneManager::GetInstance()->Init(f); 
	PhysicManager::GetInstance()->Init("../Resources/Resource_files/physics.txt");
	printf("Level: %d\n", PhysicManager::GetInstance()->m_ilevel);
	// disable home button, resume button and win button
	SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->maskId].SetVisible(true, 0);
	SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->loseTextureId].SetVisible(true, 0);
	SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->winTextureId].SetVisible(true, 0);
	SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->homeButtonId].SetVisible(true, 0);
	listButtons[B_HOME].SetProperty(167, 432, 94, 92, B_VOID);
	SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->resumeButtonId].SetVisible(true, 0);
	listButtons[B_RESUME].SetProperty(319, 432, 94, 90, B_VOID);
	SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->nextButtonId].SetVisible(true, 0);
	listButtons[B_NEXT].SetProperty(319, 432, 94, 90, B_VOID);
	SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->replayButtonId].SetVisible(true, 0);
	listButtons[B_REPLAY].SetProperty(319, 432, 94, 90, B_VOID);
	listButtons[B_MENU_UI].SetProperty(453, 858, 85, 140, B_MENU_UI);
}

void StateMachine::GameReturn()
{
	SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->homeButtonId].SetVisible(true, 0);
	listButtons[B_HOME].SetProperty(167, 432, 94, 92, B_VOID);
	SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->resumeButtonId].SetVisible(true, 0);
	listButtons[B_RESUME].SetProperty(319, 432, 94, 90, B_VOID);
	SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->maskId].SetVisible(true, 0);
}

void StateMachine::DeleteState()
{
	delete Instance;
	Instance = NULL;
}


void StateMachine::ChangeState(GameState state)
{
	if (state == GS_OPTIONMENU)
	{
		waiting = true;
		currentState = state;
		Init();
	}
	else if (state == GS_MAINMENU)
	{
		waiting = true;
		Camera::GetInstance()->SetHeight(0, 0);
		currentState = state;
		SceneManager::GetInstance()->CleanInstance();
		Init();
	}
	else if (state == GS_GAMEPLAY)
	{
		waiting = false;
		currentState = state; 
		SceneManager::GetInstance()->CleanInstance();
		Init();
	}
	else if (state == GS_GAME_RETURN)
	{
		waiting = false;
		currentState = state;
		Init();
	}
	else
	{
		currentState = state;
		SceneManager::GetInstance()->CleanInstance();
		Init();
	}
}

bool StateMachine::OnMouseDown(float x, float y)
{
	switch (currentState)
	{
	case StateMachine::GS_LOADING:
		break;
	case StateMachine::GS_MAINMENU:
		for (int i = 0; i < NUM_BUTTONS; i++)
		{
			if (listButtons[i].IsInside(x, y))
			{
				if (i == B_CAMPAIGN)
				{
					ChangeState(GS_LEVELS);
					return true;
				}
				if (i == B_ENDLESS)
				{
					PhysicManager::GetInstance()->CleanInstance();
					PhysicManager::GetInstance()->m_ilevel = 6;
					ChangeState(GS_GAMEPLAY);
					return true;
				}
			}
		}
		break;
	case StateMachine::GS_LEVELS:
		for (int i = 0; i < NUM_BUTTONS; i++)
		{
			if (listButtons[i].IsInside(x, y))
			{
				PhysicManager::GetInstance()->CleanInstance();
				if (i == B_BACK)
				{
					ChangeState(GS_MAINMENU);
					return true;
				}
				if (i == B_LV1)
				{
					PhysicManager::GetInstance()->m_ilevel = 1;
					ChangeState(GS_GAMEPLAY);
					return true;
				}
				if (i == B_LV2)
				{
					PhysicManager::GetInstance()->m_ilevel = 2;
					ChangeState(GS_GAMEPLAY);
					return true;
				}
				if (i == B_LV3)
				{
					PhysicManager::GetInstance()->m_ilevel = 4;
					ChangeState(GS_GAMEPLAY);
					return true;
				}
				if (i == B_LV4)
				{
					PhysicManager::GetInstance()->m_ilevel = 5;
					ChangeState(GS_GAMEPLAY);
					return true;
				}
			}
		}
	case StateMachine::GS_GAMEPLAY:
		for (int i = 0; i < NUM_BUTTONS; i++)
		{
			if (listButtons[i].IsInside(x, y))
			{
				if (i == B_MENU_UI)
				{
					ChangeState(GS_OPTIONMENU);
					return true;
				}
				if (i == B_HOME)
				{
					theme->Replay();
					ingame->Stop();
					ChangeState(GS_MAINMENU);
					return true;
				}
				if (i == B_REPLAY)
				{
					currentLevel = PhysicManager::GetInstance()->m_ilevel;
					PhysicManager::GetInstance()->CleanInstance();
					PhysicManager::GetInstance()->m_ilevel = currentLevel;
					ChangeState(GS_GAMEPLAY);
					return true;
				}
				if (i == B_NEXT)
				{
					currentLevel = PhysicManager::GetInstance()->m_ilevel;
					PhysicManager::GetInstance()->CleanInstance();
					switch (currentLevel)
					{
					case 1:
						PhysicManager::GetInstance()->m_ilevel = 2;
						break;
					case 2:
						PhysicManager::GetInstance()->m_ilevel = 4;
						break;
					case 4:
						PhysicManager::GetInstance()->m_ilevel = 5;
						break;
					case 5:
						PhysicManager::GetInstance()->m_ilevel = 6;
					}
					ChangeState(GS_GAMEPLAY);
					return true;
				}
			}
		}
		break;
	case StateMachine::GS_OPTIONMENU:
		for (int i = 0; i < NUM_BUTTONS; i++)
		{
			if (listButtons[i].IsInside(x, y))
			{
				if (i == B_HOME)
				{
					theme->Replay();
					ingame->Stop();
					ChangeState(GS_MAINMENU);
					return true;
				}
				if (i == B_RESUME)
				{
					ChangeState(GS_GAME_RETURN);
					return true;
				}
			}
		}
		break;
	case StateMachine::GS_GAME_RETURN:
		for (int i = 0; i < NUM_BUTTONS; i++)
		{
			if (listButtons[i].IsInside(x, y))
			{
				if (i == B_MENU_UI)
				{
					ChangeState(GS_OPTIONMENU);
					return true;
				}
				if (i == B_HOME)
				{
					theme->Replay();
					ingame->Stop();
					ChangeState(GS_MAINMENU);
					return true;
				}
				if (i == B_REPLAY)
				{
					currentLevel = PhysicManager::GetInstance()->m_ilevel;
					PhysicManager::GetInstance()->CleanInstance();
					PhysicManager::GetInstance()->m_ilevel = currentLevel;
					ChangeState(GS_GAMEPLAY);
					return true;
				}
			}
		}
	case StateMachine::GS_CREDIT:
		break;
	default:
		break;
	}
	return false;
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
		break;
	case StateMachine::GS_OPTIONMENU:
		break;
	case StateMachine::GS_CREDIT:
		break;
	default:
		break;
	}
	if (glose)
	{
		if (!lplayed)
		{
			lose->Replay();
			lplayed = true;
		}
		ingame->Stop();
		theme->Stop();
		glose = false;
	}
	if (gwin)
	{
		if (!wplayed)
		{
			win->Replay();
			wplayed = true;
		}
		ingame->Stop();
		theme->Stop();
		gwin = false;
	}
}

void StateMachine::LoadingUpdate(float deltaTime)
{
	static bool loaded = false;
	if (currentTick - lastTime >= 1000 && !loaded)
	{
		loaded = true;
		lastTime = currentTick;
		//textToDraw.pop_back();
		//textToDraw.push_back(&SceneManager::GetInstance()->listObject[1]);
	}
	else if (currentTick - lastTime >= 2000)
	{
		theme->Replay();
		lastTime = currentTick;
		ChangeState(GS_MAINMENU);
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
	if (currentState == StateMachine::GS_LOADING)
	{
		//Vector4 color = Vector4(255, 0, 0, abs(100 - currentTick % 200) / 100.0);
		//TextManager::GetInstance()->RenderString("Get READY to lose!", color, -280, -600, 0.7, 0.7);
	}
	else if (currentState == StateMachine::GS_GAMEPLAY || currentState == StateMachine::GS_OPTIONMENU || currentState == StateMachine::GS_GAME_RETURN)
	{
		TextManager::GetInstance()->RenderScore(PhysicManager::GetInstance()->currentFloor);
	}
}
StateMachine::~StateMachine()
{

}
