#pragma once
#include<vector>
#include<string.h>
#include"SceneManager.h"
#include"NewTrainingFramework.h"
class StateMachine {
public:
	long  currentTime, lastTime;
	static StateMachine * Instance;
	static StateMachine * GetInstance();
	std::vector<Object*> textToDraw;
	StateMachine();
	void Init();
	void DeleteState();
	void Update(float deltaTime);
	void Render();
	~StateMachine();	
	enum GameState {
		GS_LOADING,
		GS_MAINMENU,
		GS_GAMEPLAY,
		GS_OPTIONMENU,
		GS_CREDIT
	};
	GameState currentState;
	void ChangState(GameState state);
};